#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class server
{
public:
    server(boost::asio::io_service& io_service, short port)
        : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), port)),
        timer_(io_service), cnt_(0) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&server::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&server::handle_timer, this, boost::asio::placeholders::error));
    }

    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {
        if (!error && bytes_recvd > 0) {
            cnt_ += bytes_recvd;
            memset(reply_, 0, sizeof(reply_));
            strcpy(reply_, "Reply on: ");
            strncat(reply_, data_, 10);
            socket_.async_send_to(
                    boost::asio::buffer(reply_, strlen(reply_)), sender_endpoint_,
                    boost::bind(&server::handle_send_to, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        } else {
            std::cerr << "error: " << error << " bytes_recvd: " << bytes_recvd << std::endl;
            socket_.async_receive_from(
                    boost::asio::buffer(data_, max_length), sender_endpoint_,
                    boost::bind(&server::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }
    }
    void handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&server::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }
    void handle_timer(const boost::system::error_code& error) {
        std::cerr << "received: " << cnt_ << " bytes" << std::endl;
        cnt_ = 0;
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&server::handle_timer, this, boost::asio::placeholders::error));
    }
private:
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    boost::asio::deadline_timer timer_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 65535 - 1 };
    char data_[max_length];
    char reply_[max_length];
    int cnt_;
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_udp_echo_server <port>\n";
            return 1;
        }
        boost::asio::io_service io_service;

        using namespace std; // For atoi.
        server s(io_service, atoi(argv[1]));

        io_service.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

