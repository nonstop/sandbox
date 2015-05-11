#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
 
static std::string serverCertificateFile = "./cert.pem";
static std::string serverUrl = "localhost";
static int serverPort = 8082;
static boost::array<char, 100> _data;
 
static void
readComplete(boost::asio::io_service &io,
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,
        const boost::system::error_code &ec,
        size_t bytesRecvd
        )
{
    if(!ec && bytesRecvd)
    {  
        std::cerr<<"\ndata from server:"<<_data.data();
        socket->async_read_some(boost::asio::buffer(_data, 100),
                boost::bind(&readComplete,
                    boost::ref(io),
                    socket,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                    ));
    }else
        std::cerr<<"\nreadComplete() failed with error:"<<ec.message();
    return;
}
 
 
static void
connectToCloud( \
        boost::asio::io_service &io, \
        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket,\
        boost::asio::ip::tcp::resolver &resolver
        )
{
    std::cerr<<"\nConnecting to cloud...";
    auto endpoint_iterator = resolver.resolve({serverUrl, \
            std::to_string(serverPort)});
    boost::asio::async_connect(socket->lowest_layer(), endpoint_iterator, \
            [&](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator){
            if(!ec){
            //perform handshake before xmitting any kind of data on socket.
            std::cerr<<"\nPerforming SSL handshake with cloud.";
            socket->lowest_layer().set_option(boost::asio::ip::tcp::\
                no_delay(true));
            socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::\
                socket>::client);
            std::cerr<<"\nHandshake succeeded. Connected to cloud.";
            char mesg[] = "hello server";
            socket->write_some(boost::asio::buffer(mesg, sizeof(mesg)));
            socket->async_read_some(boost::asio::buffer(_data, 100),
                                   boost::bind(&readComplete,
                                   boost::ref(io),
                                   socket,
                                   boost::asio::placeholders::error,
                                   boost::asio::placeholders::bytes_transferred));
            }
            else{
            std::cerr<<"Unable to connect to server"<<ec.message();
            return;
            }
            });
    return;
}
 
int
main (int ac, char **av, char **env)
{
    try
    {
        boost::asio::io_service io;
        boost::asio::ssl::context ctx(io,
                boost::asio::ssl::context::tlsv12_client);
        ctx.set_options(boost::asio::ssl::context::no_sslv2 \
                | boost::asio::ssl::context::no_sslv3 \
                | boost::asio::ssl::context::default_workarounds);
        ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
        ctx.load_verify_file(serverCertificateFile);
        auto socket = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(io, ctx);
        boost::asio::ip::tcp::resolver resolver(io);
        connectToCloud(io, socket, resolver);
        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr<<"main() exited with exception:"<<e.what();
        return 1;
    }
    return 0;
}

