#ifndef SERVERLIB_JSON_PACKER_H
#define SERVERLIB_JSON_PACKER_H

#include <string>
#include <vector>
#include <set>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/optional.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "json_spirit.h"

#define MAKE_NAME(n1, n2) n1##n2
#define MAKE_NAME_BY_LINE(n1, n2) MAKE_NAME(n1, n2)

void writeJsonLog(const std::string& str);

namespace json_spirit
{

template<typename T> struct Traits;
template<typename T> struct Describer;

#define JSON_ASSERT_TYPE(Type, val, json_type) { \
if (val.type() != json_type) { \
    writeJsonLog(#Type ": invalid type " + boost::lexical_cast<std::string>(val.type()) + " expected " + boost::lexical_cast<std::string>(json_type) + "("#json_type")" ); \
    return boost::optional<Type>(); \
} \
}

template<typename T> struct Traits< std::vector<T> >;

template<typename T>
struct Traits
{
    enum { allowEmptyConstructor = 0 };
    static mValue packInt(const T& v) {
        return Describer<T>::packInt(v);
    }
    static boost::optional<T> unpackInt(const mValue& v) {
        return Describer<T>::unpackInt(v);
    }
    static mValue packExt(const T& v) {
        return Describer<T>::packExt(v);
    }
    static boost::optional<T> unpackExt(const mValue& v) {
        return Describer<T>::unpackExt(v);
    }
};

template<typename T>
struct Traits< std::vector<T> >
{
    enum { allowEmptyConstructor = 1 };
    static mValue packInt(const std::vector<T>& v) {
        mArray arr;
        for (size_t i = 0; i < v.size(); ++i) {
            arr.push_back(Traits<T>::packInt(v[i]));
        }
        return arr;
    }
    static boost::optional< std::vector<T> > unpackInt(const mValue& v) {
        JSON_ASSERT_TYPE(std::vector<T>, v, json_spirit::array_type);
        const mArray& arr(v.get_array());
        std::vector<T> ts;
        for (size_t i = 0; i < arr.size(); ++i) {
            boost::optional<T> t(Traits<T>::unpackInt(arr[i]));
            if (!t) {
                //writeJsonLog(HelpCpp::string_cast(i));
                return boost::optional< std::vector<T> >();
            }
            ts.push_back(*t);
        }
        return ts;
    }
    static mValue packExt(const std::vector<T>& v) {
        mArray arr;
        for (size_t i = 0; i < v.size(); ++i) {
            arr.push_back(Traits<T>::packExt(v[i]));
        }
        return arr;
    }
    static boost::optional< std::vector<T> > unpackExt(const mValue& v) {
        const mArray& arr(v.get_array());
        std::vector<T> ts;
        for (size_t i = 0; i < arr.size(); ++i) {
            boost::optional<T> t(Traits<T>::unpackExt(arr[i]));
            if (!t) {
                //writeJsonLog(HelpCpp::string_cast(i));
                return boost::optional< std::vector<T> >();
            }
            ts.push_back(*t);
        }
        return ts;
    }
};

} // json_spirit

#define JSON_PACK_UNPACK_DECL(Type) template<> struct Traits< Type > {\
enum { allowEmptyConstructor = 0 }; \
static mValue packInt(const Type&); \
static mValue packExt(const Type&); \
static boost::optional< Type > unpackInt(const mValue&); \
static boost::optional< Type > unpackExt(const mValue&); \
}

#define JSON_DESC_TYPE_DECL(Type) \
template<> struct Describer< Type > \
{ \
    static mValue packInt(const Type&); \
    static boost::optional< Type > unpackInt(const mValue& v); \
    static mValue packExt(const Type&); \
    static boost::optional< Type > unpackExt(const mValue& v); \
};

//#define JSON_BEGIN_DESC_TYPE(Type) namespace MAKE_NAME(ns_, Type) { \
    //typedef Type this_type; \
    //static const auto MAKE_NAME(describer_, Type) = json_spirit::details::Constructor0< Type >()

//#define DESC_TYPE_FIELD(tag, fld) \
    //.add_type<decltype(this_type::fld)>(tag, boost::mem_fn(&this_type::fld))
//#define DESC_TYPE_FIELD2(tag, fld, def) \
    //.add_type<decltype(this_type::fld)>(tag, boost::mem_fn(&this_type::fld), def)

//#define JSON_END_DESC_TYPE(Type) ; } \
//mValue Describer< Type >::packInt(const Type& v) { \
    //return MAKE_NAME(ns_, Type)::MAKE_NAME(describer_, Type).packInt(v); \
//} \
//boost::optional< Type > Describer< Type >::unpackInt(const mValue& v) { \
    //return MAKE_NAME(ns_, Type)::MAKE_NAME(describer_, Type).unpackInt(v); \
//} \
//mValue Describer< Type >::packExt(const Type& v) { \
    //return MAKE_NAME(ns_, Type)::MAKE_NAME(describer_, Type).packExt(v); \
//} \
//boost::optional< Type > Describer< Type >::unpackExt(const mValue& v) { \
    //return MAKE_NAME(ns_, Type)::MAKE_NAME(describer_, Type).unpackExt(v); \
//}


class JsonLogger
{
public:
    JsonLogger();
    ~JsonLogger();
    const std::string& msg() const;
private:
    friend void writeJsonLog(const std::string& str);
private:
    std::string msg_;
};

#endif /* SERVERLIB_JSON_PACKER_H */

