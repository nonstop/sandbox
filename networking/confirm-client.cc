#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/regex.hpp>

using boost::asio::ip::tcp;

#define TRACE std::cout << __FILE__ << ":" << __LINE__ << std::endl

class client
{
public:
    client(boost::asio::io_service & io_service, const std::string & host, const std::string & port)
        : socket_(io_service), resolver_(io_service)
    {
        TRACE;
        std::ostream request_stream(&request_);
        request_stream << "ReQuEsT";

        tcp::resolver::query query(tcp::v4(), host, port);
        resolver_.async_resolve(query, boost::bind(&client::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator));
    }
private:
    tcp::socket socket_;
    tcp::resolver resolver_;
    boost::asio::streambuf answer;
    boost::asio::streambuf request_;
    std::size_t bytes_transferred;

    void handle_resolve(const boost::asio::error& err, tcp::resolver::iterator endpoint_iterator)
    {
        TRACE;
        if (!err)
        {
          // Attempt a connection to the first endpoint in the list. Each endpoint
          // will be tried until we successfully establish a connection.
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint, boost::bind(&client::handle_connect, this,
                boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
        {
          std::cout << "Error: " << err << "\n";
        }
    }

    void handle_connect(const boost::asio::error& err,
          tcp::resolver::iterator endpoint_iterator)
    {
        TRACE;
        if (!err)
        {
        TRACE;
            // The connection was successful. Send the request.
//            boost::asio::async_read(socket_, answer, boost::bind(&client::handle_after_read, this, boost::asio::placeholders::error));
            boost::asio::async_write(socket_, request_, boost::bind(&client::handle_read_request, this, boost::asio::placeholders::error));
        }
        else if (endpoint_iterator != tcp::resolver::iterator())
        {
        TRACE;
            // The connection failed. Try the next endpoint in the list.
            socket_.close();
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
        }
        else
            std::cout << "Error: " << err << "\n";
    }
    void handle_read_request(const boost::asio::error& err)
    {
        TRACE;
        if (!err)
        {
            TRACE;
            boost::asio::async_read(socket_, answer, 
                boost::bind(&client::condition, this, boost::asio::placeholders::error),
                boost::bind(&client::handle_after_read, this, boost::asio::placeholders::error));
        }
        else
            std::cout << "Error: " << err << "\n";
    }
    bool condition(const boost::asio::error& err)
    {
        TRACE;
        std::cout << bytes_transferred << std::endl;
        std::cout << answer.size() << std::endl;
        return answer.size() == 8;
    }
    void handle_after_read(const boost::asio::error& err)
    {
        TRACE;
        std::cout << answer.size() << std::endl;
    }
};


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cout << "Usage: confirm_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    client c(io_service, argv[1], argv[2]);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
  }

  return 0;
}

