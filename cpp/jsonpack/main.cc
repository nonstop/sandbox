#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

#include <boost/optional.hpp>

#include "json_packer.h"
#include "json_pack_types.h"

#define TRACE(v) std::cout << __FILE__ << ":" << __LINE__ << " " << v << std::endl

struct Foo
{
    Foo(int v_)
        : f(v_)
    {}
    Foo(int v_, const std::vector<int>& ints_)
        : f(v_), ints(ints_)
    {}
    int f;
    std::vector<int> ints;

    bool operator==(const Foo& f_) const {
        return this->f == f_.f;
    }
    bool operator!=(const Foo& f_) const {
        return !operator==(f_);
    }
};
std::ostream& operator<<(std::ostream& os, const Foo& f)
{
    return os << "Foo:" << f.f;
}

struct Bar
{
    Bar(const Foo& f_, int b_, int b2_) : f(f_), b(b_), b2(b2_) {}
    Foo f;
    unsigned b;
    int b2;
};
std::ostream& operator<<(std::ostream& os, const Bar& b)
{
    return os << "Bar:" << b.f << " " << b.b << " " << b.b2;
}

#include "details.hpp"
namespace json_spirit {
/*
namespace details {

#define JSON_UNPACK_INT_OR_EXIT(Type, T, N) \
const boost::optional< T > MAKE_NAME(t, N)(json_spirit::details::unpackIntHelper< Type, T >(o, MAKE_NAME(f, N))); \
if (!MAKE_NAME(t, N)) { \
    TRACE(#T ": unpackInt failed "); \
    return boost::optional<Type>(); \
}

#define JSON_UNPACK_EXT_OR_EXIT(Type, T, N) \
const boost::optional< T > MAKE_NAME(t, N)(json_spirit::details::unpackExtHelper< Type, T >(o, MAKE_NAME(f, N))); \
if (!MAKE_NAME(t, N)) { \
    TRACE(#T ": unpackExt failed "); \
    return boost::optional<Type>(); \
}

template<int Int>
struct DefaultValue
{
    template<typename T> static boost::optional<T> value(const boost::optional<T>& def) { return def; }
};

template<>
struct DefaultValue<1>
{
    template<typename T> static boost::optional<T> value(const boost::optional<T>& def) {
        return def ? def : T();
    }
};

template<typename Type, typename T>
struct FieldDesc
{
    FieldDesc(const std::string& n,
            const boost::function<T (const Type&)>& getter_,
            const boost::optional<T>& def = boost::optional<T>()
            )
        : name(n),
        defaultVal(DefaultValue< Traits<T>::allowEmptyConstructor >::value(def)),
        get(getter_)
    {
    }
    std::string name;
    boost::optional<T> defaultVal;
    boost::function<T (const Type&)> get;
};

template<typename Type, typename T>
static boost::optional<T> unpackIntHelper(const mObject& o, const FieldDesc<Type, T>& fd)
{
    const mObject::const_iterator i(o.find(fd.name));
    if (i == o.end()) {
        TRACE(fd.name << " not found" << json_spirit::write(mValue(o)));
        return fd.defaultVal;
    }
    return Traits<T>::unpackInt(i->second);
}

template<typename Type, typename T>
static boost::optional<T> unpackExtHelper(const mObject& o, const FieldDesc<Type, T>& fd)
{
    const mObject::const_iterator i(o.find(fd.name));
    if (i == o.end()) {
        TRACE(fd.name << " not found" << json_spirit::write(mValue(o)));
        return fd.defaultVal;
    }
    return Traits<T>::unpackExt(i->second);
}

template<typename Type> struct Constructor0;
template<typename Type, typename T0> struct Constructor1;
template<typename Type, typename T0, typename T1> struct Constructor2;
template<typename Type, typename T0, typename T2, typename T3> struct Constructor3;
template<typename Type, typename T0, typename T2, typename T3, typename T4> struct Constructor4;

template<typename Type>
struct Constructor0
{
    template<typename T0> Constructor1<Type, T0> add_type(const std::string&, const boost::function<T0 (const Type&)>& get,
            const boost::optional<T0>& def = boost::optional<T0>());
     //we can be here only for empty structs
     //boost::optional<Type> construct(const mObject&) const;
};

template<typename Type, typename T0>
struct Constructor1
{
    FieldDesc<Type, T0> f0;
    Constructor1(const FieldDesc<Type, T0>& f0_) : f0(f0_) {}
    template<typename T1> Constructor2<Type, T0, T1> add_type(const std::string&, const boost::function<T1 (const Type&)>& get,
            const boost::optional<T1>& def = boost::optional<T1>());
    mValue packInt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
        return o;
    }
    boost::optional<Type> unpackInt(const mValue& v) const {
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
        return Type(*t0);
    }
    mValue packExt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
        return o;
    }
    boost::optional<Type> unpackExt(const mValue& v) const {
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
        return Type(*t0);
    }
};

template<typename Type, typename T0, typename T1>
struct Constructor2
{
    FieldDesc<Type, T0> f0;
    FieldDesc<Type, T1> f1;
    Constructor2(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_) : f0(f0_), f1(f1_) {}
    template<typename T2> Constructor3<Type, T0, T1, T2> add_type(const std::string&,
            const boost::function<T2 (const Type&)>& get, const boost::optional<T2>& def = boost::optional<T2>());
    mValue packInt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
        if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
        return o;
    }
    boost::optional<Type> unpackInt(const mValue& v) const {
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
        JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
        return Type(*t0, *t1);
    }
    mValue packExt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
        if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
        return o;
    }
    boost::optional<Type> unpackExt(const mValue& v) const {
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
        JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
        return Type(*t0, *t1);
    }
};

template<typename Type, typename T0, typename T1, typename T2>
struct Constructor3
{
    FieldDesc<Type, T0> f0;
    FieldDesc<Type, T1> f1;
    FieldDesc<Type, T2> f2;
    Constructor3(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_) : f0(f0_), f1(f1_), f2(f2_) {}
    template<typename T3> Constructor4<Type, T0, T1, T2, T3> add_type(const std::string&, const boost::function<T3 (const Type&)>& get, const boost::optional<T3>& def = boost::optional<T3>());
    mValue packInt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
        if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
        if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
        return o;
    }
    boost::optional<Type> unpackInt(const mValue& v) const {
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
        JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
        JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
        return Type(*t0, *t1, *t2);
    }
    mValue packExt(const Type& v) const {
        mObject o;
        if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
        if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
        if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
        return o;
    }
    boost::optional<Type> unpackExt(const mValue& v) const {
        TRACE("unpackExt " << json_spirit::write(v) << " type=" << v.type());
        JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
        const mObject& o(v.get_obj());
        TRACE("unpackExt " << json_spirit::write(mValue(o)));
        JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
        JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
        JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
        return Type(*t0, *t1, *t2);
    }
};

template<typename Type>template<typename T0>
Constructor1<Type, T0> Constructor0<Type>::add_type(const std::string& tag, const boost::function<T0 (const Type&)>& get, const boost::optional<T0>& def) {
    return Constructor1<Type, T0>(FieldDesc<Type, T0>(tag, get, def));
}

template<typename Type, typename T0>template<typename T1>
Constructor2<Type, T0, T1> Constructor1<Type, T0>::add_type(const std::string& tag, const boost::function<T1 (const Type&)>& get, const boost::optional<T1>& def) {
    return Constructor2<Type, T0, T1>(f0, FieldDesc<Type, T1>(tag, get, def));
}

template<typename Type, typename T0, typename T1>template<typename T2>
Constructor3<Type, T0, T1, T2> Constructor2<Type, T0, T1>::add_type(const std::string& tag, const boost::function<T2 (const Type&)>& get, const boost::optional<T2>& def) {
    return Constructor3<Type, T0, T1, T2>(f0, f1, FieldDesc<Type, T2>(tag, get, def));
}
} // details
*/
mValue Traits<unsigned>::packInt(const unsigned& i)
{
    return mValue(static_cast<int>(i));
}

boost::optional<unsigned> Traits<unsigned>::unpackInt(const mValue& v)
{
    JSON_ASSERT_TYPE(unsigned, v, json_spirit::int_type);
    return v.get_int();
}

mValue Traits<unsigned>::packExt(const unsigned& i)
{
    return mValue(boost::lexical_cast<std::string>(i));
}

boost::optional<unsigned> Traits<unsigned>::unpackExt(const mValue& v)
{
    JSON_ASSERT_TYPE(unsigned, v, json_spirit::str_type);
    return boost::lexical_cast<unsigned>(v.get_str());
}

template<typename T>
bool unpackInt__(T& t, const mValue& v)
{
    boost::optional<T> ot(Traits<T>::unpackInt(v));
    if (ot) {
        t = *ot;
    }
    return ot;
}

template<typename T>
bool unpackExt__(T& t, const mValue& v)
{
    boost::optional<T> ot(Traits<T>::unpackExt(v));
    if (ot) {
        t = *ot;
    }
    return ot;
}

template<typename Type>
struct FieldDesc
{
    std::string name;
    boost::function<mValue (const Type&)>  packInt;
    boost::function<bool (Type&, const mValue&)> unpackInt;
    boost::function<mValue (const Type&)>  packExt;
    boost::function<bool (Type&, const mValue&)> unpackExt;
};


template<typename Type>
struct DescHelper
{
    std::vector< FieldDesc<Type> > fields;

    char buf_[sizeof(Type)];


    template<typename T> DescHelper<Type>& addField(const boost::function<const T& (const Type&)>& get1) {
        FieldDesc<Type> fd;
        fd.packInt = boost::bind(&Traits<T>::packInt, boost::bind(get1, _1));
        fd.packExt = boost::bind(&Traits<T>::packExt, boost::bind(get1, _1));
        fd.unpackInt = boost::bind(&unpackInt__<T>, reinterpret_cast<Foo*>(buf_)->f, _2);
        fd.unpackExt = boost::bind(&unpackExt__<T>, reinterpret_cast<Foo*>(buf_)->ints, _2);
        fields.push_back(fd);
        return *this;
    }

};

DescHelper<Foo> helper_foo = DescHelper<Foo>()
    .addField(boost::function<const int& (const Foo&)>(boost::mem_fn(&Foo::f)))
    .addField(boost::function<const std::vector<int>& (const Foo&)>(boost::mem_fn(&Foo::ints)))
    ;

JSON_DESC_TYPE_DECL(Foo);

mValue Describer<Foo>::packInt(const Foo& foo)
{
    mObject obj;
    for(const FieldDesc<Foo>& fd : helper_foo.fields) {
        obj[fd.name] = fd.packInt(foo);
    }
    return obj;
} 

boost::optional<Foo> Describer<Foo>::unpackInt(const mValue&)
{
    return boost::optional<Foo>();
}

mValue Describer<Foo>::packExt(const Foo& foo)
{
    return mValue();
}

boost::optional<Foo> Describer<Foo>::unpackExt(const mValue&)
{
    return boost::optional<Foo>();
}

//JSON_DESC_TYPE_DECL(Foo)
//JSON_BEGIN_DESC_TYPE(Foo)
    //DESC_TYPE_FIELD("f", f)
    //DESC_TYPE_FIELD("ints", ints)
//JSON_END_DESC_TYPE(Foo)

JSON_DESC_TYPE_DECL(Bar)
//JSON_BEGIN_DESC_TYPE(Bar)
    //DESC_TYPE_FIELD("f", f)
    //DESC_TYPE_FIELD("b", b)
    //DESC_TYPE_FIELD2("b2", b2, 43)
//JSON_END_DESC_TYPE(Bar)

mValue Describer<Bar>::packInt(const Bar& foo)
{
    return mValue();
}

boost::optional<Bar> Describer<Bar>::unpackInt(const mValue&)
{
    return boost::optional<Bar>();
}

mValue Describer<Bar>::packExt(const Bar& foo)
{
    return mValue();
}

boost::optional<Bar> Describer<Bar>::unpackExt(const mValue&)
{
    return boost::optional<Bar>();
}

} // json_spirit

int main()
{
    json_spirit::mValue v;
    if (!json_spirit::read("{\"f\":{\"f\":100},\"b\":200}", v)) {
        TRACE("read JSON failed");
    }
    boost::optional<Bar> ob = json_spirit::Traits<Bar>::unpackInt(v);
    if (!ob) {
        TRACE("unpackInt Bar failed");
        return 1;
    }
    TRACE("unpacked:  " << *ob);
    std::string s = json_spirit::write(json_spirit::Traits<Bar>::packInt(*ob));
    TRACE("packed:    " << s);
    ob->b2 = 42;
    s = json_spirit::write(json_spirit::Traits<Bar>::packInt(*ob));
    TRACE("packed:    " << s);
    s = json_spirit::write(json_spirit::Traits<Bar>::packExt(*ob));
    TRACE("packedExt: " << s);
    TRACE("         s=" << s);
    if (!json_spirit::read(s, v)) {
        TRACE("read failed: " << s);
        return 1;
    }
    boost::optional<Bar> ob2 = json_spirit::Traits<Bar>::unpackExt(v);
    if (!ob2) {
        return 1;
    }
    TRACE("unpacked:  " << *ob2);
    return 0;
}
