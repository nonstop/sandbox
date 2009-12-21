#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using std::cout;
using std::endl;

static const size_t max_buff_sz = 1024;
static size_t buff_sz = 0;
static char buff[ max_buff_sz ];

static boost::asio::io_service ios;
static boost::asio::posix::stream_descriptor sd(ios);

static void handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        cout << "handler got error: " << error << endl;
        return;
    }
    cout << "size: " << bytes_transferred << " buffer: " << buff;
    sd.async_read_some(boost::asio::buffer(buff, max_buff_sz),
            boost::bind(&handler, boost::asio::placeholders::error, buff_sz));
    memset(buff, 0, sizeof(buff));
}

int main(int av, char* ac[])
{
    sd.assign(0);
    sd.async_read_some(boost::asio::buffer(buff, max_buff_sz),
            boost::bind(&handler, boost::asio::placeholders::error, buff_sz));

    ios.run();
    return 0;
}
