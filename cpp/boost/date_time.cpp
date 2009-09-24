#include <time.h>

#include <iostream>
#include <string>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;


string getDateTimeStr(const char* format)
{
    boost::date_time::time_facet<ptime, char>* output_facet = new boost::date_time::time_facet<ptime, char>();
    stringstream ss;
    ptime t(microsec_clock::local_time());

    ss.imbue(locale(locale::classic(), output_facet));
    output_facet->format(format);
    ss << t;
    return ss.str();
}

int main(int ac, char * av[])
{
    cout << "ctime is: " << time(0) << endl;
    const char* format = (ac > 1 ? av[1] : "%y%m%d_%H_%M_%S%.2F");
    cout << "format=[" << format << "] boost::date_time is: " << getDateTimeStr(format) << endl;
    return 0;
}

