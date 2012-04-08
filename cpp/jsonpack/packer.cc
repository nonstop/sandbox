#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>

#include "packer.h"
#include "json_spirit.h"

// TODO: look at another JSON libraries
// yajl, jsoncpp, json-c may be smth else

namespace {
typedef json_spirit::mObject Object;
typedef json_spirit::mArray Array;
typedef json_spirit::mValue Value;
typedef json_spirit::Pair Pair;

static Object createObject(const Flight& f)
{
    Object o;
    o["airline"] = boost::lexical_cast<std::string>(f.airline);
    o["number"] = boost::lexical_cast<std::string>(f.number);
    if (f.suffix) {
        o["suffix"] = boost::lexical_cast<std::string>(f.suffix);
    }
    return o;
}
static Object createObject(const Period& p)
{
    Object o;
    o["d1"] = boost::gregorian::to_iso_string(p.start);
    o["d2"] = boost::gregorian::to_iso_string(p.end);
    return o;
}

static Object createObject(const ScdPeriod& p)
{
    Object o;
    o["prd"] = createObject(p.period);
    o["sclord"] = p.subclOrder.order;
    o["tts"] = boost::lexical_cast<std::string>(p.tts);
    return o;
}
} // namespace

std::string JsonPacker::packSchedule(const Schedule& scd)
{
    Object o;
    o["flt"] = createObject(scd.flight);
    Array pa;
    for (size_t i = 0; i < scd.scdPeriods.size(); ++i) {
        pa.push_back(createObject(scd.scdPeriods[i]));
    }
    o["periods"] = pa;
    return json_spirit::write_string(Value(o), json_spirit::pretty_print);
}

boost::optional<Schedule> JsonPacker::unpackSchedule(const std::string&)
{
    return boost::optional<Schedule>();
}
