#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <iostream>

using namespace std;

struct thread_alarm
{
    thread_alarm(int secs) : m_secs(secs) { }
    void operator()()
    {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += m_secs;

        boost::thread::sleep(xt);

        std::cout << "alarm sounded..." << std::endl;
    }

    int m_secs;
};

int main(int argc, char* argv[])
{
    int secs = 5;
    std::cout << "setting alarm for 5 seconds..." << std::endl;
    thread_alarm alarm(secs);
    boost::thread thrd(alarm);
    for (int i=0; i<20; i++)
        cout << i << endl;
    thrd.join();
}

