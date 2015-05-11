#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>
#include <openssl/ssl.h>
#include <vector>
#include <memory>
#include <functional>
 
static std::string serverKeyFile = "./privkey.pem";
static std::string serverCertificate = "./cert.pem";
static int serverPort = 8082;
static std::vector<std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::\
        tcp::socket>>> connList;
static boost::array<char, 100> _data;
static void
handleAccept(boost::asio::io_service &,
        boost::asio::ssl::context &,
        boost::asio::ip::tcp::acceptor &,
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::\
        socket>>,
        const boost::system::error_code &
        );
 
static void
readComplete(boost::asio::io_service &io,
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::\
        socket>> conn,
        const boost::system::error_code &ec,
        size_t bytesRecvd
        )
{
    if(!ec && bytesRecvd)
    {
        std::cerr<<"\ndata from client:"<<_data.data();
        //send back hello client
        char mesg[] = "hello client";
        conn->write_some(boost::asio::buffer(mesg, sizeof(mesg)));
        conn->async_read_some(boost::asio::buffer(_data, 100),
                boost::bind(&readComplete,
                    boost::ref(io),
                    conn,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                    ));
    }else
        std::cerr<<"\nreadComplete() failed with error:"<<ec.message();
    return;
}
 
static void
handleHandshake(boost::asio::io_service &io,
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::\
        socket>> conn,
        const boost::system::error_code &ec
        )
{
    if(!ec)
    {
        std::cerr<<"\nOpenssl handshake with client succeeded.";
        conn->async_read_some(boost::asio::buffer(_data, 100),
                boost::bind(&readComplete,
                    boost::ref(io),
                    conn,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                    ));
    }else
        std::cerr<<"\nhandleHandshake() failed with error:"<<ec.message();
    return;
 
}
 
static void
startAccept(boost::asio::io_service &io,
        boost::asio::ssl::context &ctx,
        boost::asio::ip::tcp::acceptor &acceptor_
        )
{
    auto newConn = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::\
                   tcp::socket>> (io, ctx);
    connList.push_back(newConn);
    acceptor_.async_accept(newConn->lowest_layer(),
            boost::bind(&handleAccept,
                boost::ref(io),
                boost::ref(ctx),
                boost::ref(acceptor_),
                newConn,
                boost::asio::placeholders::error));
    return;
}
 
static void
handleAccept(boost::asio::io_service &io,
        boost::asio::ssl::context &ctx,
        boost::asio::ip::tcp::acceptor &acceptor_,
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::\
        socket>> conn,
        const boost::system::error_code &ec
    )
{
    if(!ec){
        conn->async_handshake(boost::asio::ssl::stream_base::server,
                boost::bind(&handleHandshake,
                    boost::ref(io),
                    conn,
                    boost::asio::placeholders::error));
        startAccept(io, ctx, acceptor_);
    }
    return;
}
 
 
int
main (int ac, char **av, char **env)
{
    try
    {
        boost::asio::io_service io;
        boost::asio::ip::tcp::acceptor acceptor_(io, \
                boost::asio::ip::tcp::endpoint(\
                    boost::asio::ip::tcp::v4(), \
                    serverPort));
        boost::asio::ssl::context ctx(io, boost::asio::ssl::context::\
                tlsv12_server);
        ctx.set_options(boost::asio::ssl::context::default_workarounds \
                | boost::asio::ssl::context::no_sslv2 \
                | boost::asio::ssl::context::no_sslv3);
        ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
        ctx.use_certificate_chain_file(serverCertificate);
        ctx.use_private_key_file(serverKeyFile,\
                boost::asio::ssl::context_base::file_format::pem);
        startAccept(io, ctx, acceptor_);
        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr<<"main() exited with exception:"<<e.what();
        return 1;
    }
    return 0;
}

