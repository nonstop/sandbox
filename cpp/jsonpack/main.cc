#include <iostream>
#include <boost/date_time/gregorian/gregorian_types.hpp>

#include "packer.h"

Schedule createTestSchedule()
{
    const boost::gregorian::date today(boost::gregorian::day_clock::local_day());
    const Flight f(119, 100, 0);
    ScdPeriod p(23, Period(today, today + boost::gregorian::days(3)), SubclOrder("F CDJ YKLMN"));
    ScdPeriods periods;
    periods.push_back(p);
    p.tts = 79;
    p.period.start += boost::gregorian::days(4);
    p.period.end += boost::gregorian::days(14);
    p.subclOrder = SubclOrder("CJ YNM");
    periods.push_back(p);
    Schedule scd(f, periods);
    return scd;
}

int main()
{
    std::cout << JsonPacker::packSchedule(createTestSchedule()) << std::endl;
    return 0;
}
