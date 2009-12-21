#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#define TRACE(x) std::cerr << __FILE__ << ":" << __LINE__ << " " x << std::endl;

const size_t BUF_SZ = 10000;

using boost::asio::ip::udp;

class udp_server
{
public:
    udp_server(boost::asio::io_service& io_service, int port)
        : socket_(io_service, udp::endpoint(udp::v4(), port)) {
        start_receive();
    }
private:
    void start_receive() {
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&udp_server::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }
    void handle_receive(const boost::system::error_code& error,
            std::size_t /*bytes_transferred*/)
    {
        if (!error || error == boost::asio::error::message_size) {
            TRACE((const char*)(&recv_buffer_[0]));

            boost::shared_ptr<std::string> message(new std::string("answer"));

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                    boost::bind(&udp_server::handle_send, this, message,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/)
    {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, BUF_SZ> recv_buffer_;
};

int main()
{
    try
    {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


