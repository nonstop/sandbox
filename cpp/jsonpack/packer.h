#ifndef TEST_PACKER_H
#define TEST_PACKER_H

#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

struct Flight
{
    int airline;
    int number;
    int suffix;
    
    Flight(int a, int n, int s)
        : airline(a), number(n), suffix(s)
    {}
};

struct Period
{
    boost::gregorian::date start, end;
    Period(const boost::gregorian::date& s, const boost::gregorian::date& e)
        : start(s), end(e)
    {}
};

struct SubclOrder
{
    std::string order;
    
    SubclOrder(const std::string& o)
        : order(o)
    {}
};

struct ScdPeriod
{
    int tts;
    Period period;
//    Route route;
    SubclOrder subclOrder;

    ScdPeriod(int tts_, const Period& p, const SubclOrder& so)
        : tts(tts_), period(p), subclOrder(so)
    {}
};
typedef std::vector<ScdPeriod> ScdPeriods;

struct Schedule
{
    Flight flight;
    ScdPeriods scdPeriods;

    Schedule(const Flight& f, const ScdPeriods& p)
        : flight(f), scdPeriods(p)
    {}
};

class JsonPacker
{
public:
    static std::string packSchedule(const Schedule&);
    static boost::optional<Schedule> unpackSchedule(const std::string&);
};

#endif /* TEST_PACKER_H */

