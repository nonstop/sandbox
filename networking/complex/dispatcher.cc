#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Dispatcher
{
public:
    Dispatcher(boost::asio::io_service& io_service, short clientPort, short handlersPort)
        : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), clientPort)) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&Dispatcher::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd) {
        if (!error && bytes_recvd > 0) {
            cnt_ += bytes_recvd;
            memset(reply_, 0, sizeof(reply_));
            strcpy(reply_, "Reply on: ");
            strncat(reply_, data_, 10);
            socket_.async_send_to(
                    boost::asio::buffer(reply_, strlen(reply_)), sender_endpoint_,
                    boost::bind(&Dispatcher::handle_send_to, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        } else {
            std::cerr << "error: " << error << " bytes_recvd: " << bytes_recvd << std::endl;
            socket_.async_receive_from(
                    boost::asio::buffer(data_, max_length), sender_endpoint_,
                    boost::bind(&Dispatcher::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }
    }
    void handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&Dispatcher::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }
private:
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 65000 };
    char data_[max_length];
    char reply_[max_length];
    int cnt_;
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 3) {
            std::cerr << "Usage: displatcher clientPort handlersPort\n";
            return 1;
        }
        const short clientPort = atoi(argv[1]);
        const short handlersPort = atoi(argv[2]);
        if (!clientPort || handlersPort) {
            std::cerr << "Bad args: clientPort=" << argv[1]
                << " handlersPort=" << argv[2] << std::endl;
            return 1;
        }
        boost::asio::io_service io_service;

        Dispatcher s(io_service, clientPort, handlersPort);

        io_service.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}


