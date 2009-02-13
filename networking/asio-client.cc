
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

enum { max_length = 1024 };
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket s(io_service);
        s.connect(*iterator);

        std::cout << "Enter message: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        size_t request_length = strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        size_t reply_length = boost::asio::read(s,
            boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}


