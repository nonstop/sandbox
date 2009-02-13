#include <time.h>

#include <iostream>
#include <string>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;


string getDateTimeStr()
{
    boost::date_time::time_facet<ptime, char>* output_facet = new boost::date_time::time_facet<ptime, char>();
    stringstream ss;
    ptime t(second_clock::local_time());

    ss.imbue(locale(locale::classic(), output_facet));
    output_facet->format("%y%m%d_%H_%M_%S");
    ss << t;
    return ss.str();
}

int main(int ac, char * av)
{
    cout << "ctime is: " << time(0) << endl;
    cout << "boost::date_time is: " << getDateTimeStr() << endl;
    return 0;
}

