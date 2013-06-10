#include "json_pack_types.h"

static JsonLogger* activeLogger = 0;

static void registerLogger(JsonLogger* logger)
{
    activeLogger = logger;
}

static void unregisterLogger()
{
    activeLogger = 0;
}

JsonLogger::JsonLogger()
{
    registerLogger(this);
}

JsonLogger::~JsonLogger()
{
    unregisterLogger();
}

const std::string& JsonLogger::msg() const
{
    return msg_;
}

void writeJsonLog(const std::string& str)
{
    if (activeLogger) {
        if (activeLogger->msg_.empty()) {
            activeLogger->msg_ = str;
        } else {
            activeLogger->msg_ = str + "-" + activeLogger->msg_;
        }
    }
}
namespace json_spirit
{

mValue Traits<int>::packInt(const int& i)
{
    return mValue(i);
}

boost::optional<int> Traits<int>::unpackInt(const mValue& v)
{
    JSON_ASSERT_TYPE(int, v, json_spirit::int_type);
    return v.get_int();
}

mValue Traits<int>::packExt(const int& i)
{
    return mValue(i);
}

boost::optional<int> Traits<int>::unpackExt(const mValue& v)
{
    JSON_ASSERT_TYPE(int, v, json_spirit::int_type);
    return v.get_int();
}

} // json_spirit

