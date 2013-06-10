namespace json_spirit {
namespace details {
#define JSON_UNPACK_INT_OR_EXIT(Type, T, N) const boost::optional< T > MAKE_NAME(t, N)(json_spirit::details::unpackIntHelper< Type, T >(o, MAKE_NAME(f, N))); if (!MAKE_NAME(t, N)) {     TRACE(#T ": unpackInt failed ");     return boost::optional<Type>(); }

#define JSON_UNPACK_EXT_OR_EXIT(Type, T, N) const boost::optional< T > MAKE_NAME(t, N)(json_spirit::details::unpackExtHelper< Type, T >(o, MAKE_NAME(f, N))); if (!MAKE_NAME(t, N)) {     TRACE(#T ": unpackExt failed ");     return boost::optional<Type>(); }

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
template<typename Type, typename T0, typename T1, typename T2> struct Constructor3;
template<typename Type, typename T0, typename T1, typename T2, typename T3> struct Constructor4;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4> struct Constructor5;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5> struct Constructor6;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct Constructor7;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct Constructor8;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct Constructor9;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct Constructor10;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct Constructor11;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11> struct Constructor12;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12> struct Constructor13;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13> struct Constructor14;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14> struct Constructor15;
template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15> struct Constructor16;



template<typename Type> struct Constructor0
{
  Constructor0()  {}
    template<typename T0> Constructor1<Type, T0>
    add_type(const std::string&, const boost::function<T0 (const Type&)>& get, const boost::optional<T0>& def = boost::optional<T0>());
};

template<typename Type, typename T0> struct Constructor1
{
  FieldDesc<Type, T0> f0;
  Constructor1(const FieldDesc<Type, T0>& f0_) : f0(f0_) {}
    template<typename T1> Constructor2<Type, T0, T1>
    add_type(const std::string&, const boost::function<T1 (const Type&)>& get, const boost::optional<T1>& def = boost::optional<T1>());
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

template<typename Type, typename T0, typename T1> struct Constructor2
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1;
  Constructor2(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_) : f0(f0_), f1(f1_) {}
    template<typename T2> Constructor3<Type, T0, T1, T2>
    add_type(const std::string&, const boost::function<T2 (const Type&)>& get, const boost::optional<T2>& def = boost::optional<T2>());
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

template<typename Type, typename T0, typename T1, typename T2> struct Constructor3
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2;
  Constructor3(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_) : f0(f0_), f1(f1_), f2(f2_) {}
    template<typename T3> Constructor4<Type, T0, T1, T2, T3>
    add_type(const std::string&, const boost::function<T3 (const Type&)>& get, const boost::optional<T3>& def = boost::optional<T3>());
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
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    return Type(*t0, *t1, *t2);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3> struct Constructor4
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3;
  Constructor4(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_) {}
    template<typename T4> Constructor5<Type, T0, T1, T2, T3, T4>
    add_type(const std::string&, const boost::function<T4 (const Type&)>& get, const boost::optional<T4>& def = boost::optional<T4>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    return Type(*t0, *t1, *t2, *t3);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    return Type(*t0, *t1, *t2, *t3);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4> struct Constructor5
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4;
  Constructor5(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_) {}
    template<typename T5> Constructor6<Type, T0, T1, T2, T3, T4, T5>
    add_type(const std::string&, const boost::function<T5 (const Type&)>& get, const boost::optional<T5>& def = boost::optional<T5>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    return Type(*t0, *t1, *t2, *t3, *t4);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    return Type(*t0, *t1, *t2, *t3, *t4);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5> struct Constructor6
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5;
  Constructor6(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_) {}
    template<typename T6> Constructor7<Type, T0, T1, T2, T3, T4, T5, T6>
    add_type(const std::string&, const boost::function<T6 (const Type&)>& get, const boost::optional<T6>& def = boost::optional<T6>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct Constructor7
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6;
  Constructor7(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_) {}
    template<typename T7> Constructor8<Type, T0, T1, T2, T3, T4, T5, T6, T7>
    add_type(const std::string&, const boost::function<T7 (const Type&)>& get, const boost::optional<T7>& def = boost::optional<T7>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct Constructor8
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7;
  Constructor8(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_) {}
    template<typename T8> Constructor9<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8>
    add_type(const std::string&, const boost::function<T8 (const Type&)>& get, const boost::optional<T8>& def = boost::optional<T8>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct Constructor9
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8;
  Constructor9(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_) {}
    template<typename T9> Constructor10<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
    add_type(const std::string&, const boost::function<T9 (const Type&)>& get, const boost::optional<T9>& def = boost::optional<T9>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct Constructor10
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9;
  Constructor10(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_) {}
    template<typename T10> Constructor11<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
    add_type(const std::string&, const boost::function<T10 (const Type&)>& get, const boost::optional<T10>& def = boost::optional<T10>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct Constructor11
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9; FieldDesc<Type, T10> f10;
  Constructor11(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_, const FieldDesc<Type, T10>& f10_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_), f10(f10_) {}
    template<typename T11> Constructor12<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>
    add_type(const std::string&, const boost::function<T11 (const Type&)>& get, const boost::optional<T11>& def = boost::optional<T11>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packInt(f10.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_INT_OR_EXIT(Type, T10, 10)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packExt(f10.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_EXT_OR_EXIT(Type, T10, 10)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11> struct Constructor12
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9; FieldDesc<Type, T10> f10; FieldDesc<Type, T11> f11;
  Constructor12(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_, const FieldDesc<Type, T10>& f10_, const FieldDesc<Type, T11>& f11_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_), f10(f10_), f11(f11_) {}
    template<typename T12> Constructor13<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>
    add_type(const std::string&, const boost::function<T12 (const Type&)>& get, const boost::optional<T12>& def = boost::optional<T12>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packInt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packInt(f11.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_INT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_INT_OR_EXIT(Type, T11, 11)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packExt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packExt(f11.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_EXT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_EXT_OR_EXIT(Type, T11, 11)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12> struct Constructor13
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9; FieldDesc<Type, T10> f10; FieldDesc<Type, T11> f11; FieldDesc<Type, T12> f12;
  Constructor13(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_, const FieldDesc<Type, T10>& f10_, const FieldDesc<Type, T11>& f11_, const FieldDesc<Type, T12>& f12_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_), f10(f10_), f11(f11_), f12(f12_) {}
    template<typename T13> Constructor14<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>
    add_type(const std::string&, const boost::function<T13 (const Type&)>& get, const boost::optional<T13>& def = boost::optional<T13>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packInt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packInt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packInt(f12.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_INT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_INT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_INT_OR_EXIT(Type, T12, 12)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packExt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packExt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packExt(f12.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_EXT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_EXT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_EXT_OR_EXIT(Type, T12, 12)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13> struct Constructor14
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9; FieldDesc<Type, T10> f10; FieldDesc<Type, T11> f11; FieldDesc<Type, T12> f12; FieldDesc<Type, T13> f13;
  Constructor14(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_, const FieldDesc<Type, T10>& f10_, const FieldDesc<Type, T11>& f11_, const FieldDesc<Type, T12>& f12_, const FieldDesc<Type, T13>& f13_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_), f10(f10_), f11(f11_), f12(f12_), f13(f13_) {}
    template<typename T14> Constructor15<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>
    add_type(const std::string&, const boost::function<T14 (const Type&)>& get, const boost::optional<T14>& def = boost::optional<T14>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packInt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packInt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packInt(f12.get(v)); }
    if (!f13.defaultVal || *f13.defaultVal != f13.get(v)) { o[f13.name] = Traits< T13 >::packInt(f13.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_INT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_INT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_INT_OR_EXIT(Type, T12, 12)
    JSON_UNPACK_INT_OR_EXIT(Type, T13, 13)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packExt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packExt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packExt(f12.get(v)); }
    if (!f13.defaultVal || *f13.defaultVal != f13.get(v)) { o[f13.name] = Traits< T13 >::packExt(f13.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_EXT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_EXT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_EXT_OR_EXIT(Type, T12, 12)
    JSON_UNPACK_EXT_OR_EXIT(Type, T13, 13)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13);  
  }
};

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14> struct Constructor15
{
  FieldDesc<Type, T0> f0; FieldDesc<Type, T1> f1; FieldDesc<Type, T2> f2; FieldDesc<Type, T3> f3; FieldDesc<Type, T4> f4; FieldDesc<Type, T5> f5; FieldDesc<Type, T6> f6; FieldDesc<Type, T7> f7; FieldDesc<Type, T8> f8; FieldDesc<Type, T9> f9; FieldDesc<Type, T10> f10; FieldDesc<Type, T11> f11; FieldDesc<Type, T12> f12; FieldDesc<Type, T13> f13; FieldDesc<Type, T14> f14;
  Constructor15(const FieldDesc<Type, T0>& f0_, const FieldDesc<Type, T1>& f1_, const FieldDesc<Type, T2>& f2_, const FieldDesc<Type, T3>& f3_, const FieldDesc<Type, T4>& f4_, const FieldDesc<Type, T5>& f5_, const FieldDesc<Type, T6>& f6_, const FieldDesc<Type, T7>& f7_, const FieldDesc<Type, T8>& f8_, const FieldDesc<Type, T9>& f9_, const FieldDesc<Type, T10>& f10_, const FieldDesc<Type, T11>& f11_, const FieldDesc<Type, T12>& f12_, const FieldDesc<Type, T13>& f13_, const FieldDesc<Type, T14>& f14_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), f4(f4_), f5(f5_), f6(f6_), f7(f7_), f8(f8_), f9(f9_), f10(f10_), f11(f11_), f12(f12_), f13(f13_), f14(f14_) {}
    template<typename T15> Constructor16<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>
    add_type(const std::string&, const boost::function<T15 (const Type&)>& get, const boost::optional<T15>& def = boost::optional<T15>());
  mValue packInt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packInt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packInt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packInt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packInt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packInt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packInt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packInt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packInt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packInt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packInt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packInt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packInt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packInt(f12.get(v)); }
    if (!f13.defaultVal || *f13.defaultVal != f13.get(v)) { o[f13.name] = Traits< T13 >::packInt(f13.get(v)); }
    if (!f14.defaultVal || *f14.defaultVal != f14.get(v)) { o[f14.name] = Traits< T14 >::packInt(f14.get(v)); }
    return o;
  }
  boost::optional<Type> unpackInt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_INT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_INT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_INT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_INT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_INT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_INT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_INT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_INT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_INT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_INT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_INT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_INT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_INT_OR_EXIT(Type, T12, 12)
    JSON_UNPACK_INT_OR_EXIT(Type, T13, 13)
    JSON_UNPACK_INT_OR_EXIT(Type, T14, 14)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13, *t14);  
  }
  mValue packExt(const Type& v) const {
    mObject o;
    if (!f0.defaultVal || *f0.defaultVal != f0.get(v)) { o[f0.name] = Traits< T0 >::packExt(f0.get(v)); }
    if (!f1.defaultVal || *f1.defaultVal != f1.get(v)) { o[f1.name] = Traits< T1 >::packExt(f1.get(v)); }
    if (!f2.defaultVal || *f2.defaultVal != f2.get(v)) { o[f2.name] = Traits< T2 >::packExt(f2.get(v)); }
    if (!f3.defaultVal || *f3.defaultVal != f3.get(v)) { o[f3.name] = Traits< T3 >::packExt(f3.get(v)); }
    if (!f4.defaultVal || *f4.defaultVal != f4.get(v)) { o[f4.name] = Traits< T4 >::packExt(f4.get(v)); }
    if (!f5.defaultVal || *f5.defaultVal != f5.get(v)) { o[f5.name] = Traits< T5 >::packExt(f5.get(v)); }
    if (!f6.defaultVal || *f6.defaultVal != f6.get(v)) { o[f6.name] = Traits< T6 >::packExt(f6.get(v)); }
    if (!f7.defaultVal || *f7.defaultVal != f7.get(v)) { o[f7.name] = Traits< T7 >::packExt(f7.get(v)); }
    if (!f8.defaultVal || *f8.defaultVal != f8.get(v)) { o[f8.name] = Traits< T8 >::packExt(f8.get(v)); }
    if (!f9.defaultVal || *f9.defaultVal != f9.get(v)) { o[f9.name] = Traits< T9 >::packExt(f9.get(v)); }
    if (!f10.defaultVal || *f10.defaultVal != f10.get(v)) { o[f10.name] = Traits< T10 >::packExt(f10.get(v)); }
    if (!f11.defaultVal || *f11.defaultVal != f11.get(v)) { o[f11.name] = Traits< T11 >::packExt(f11.get(v)); }
    if (!f12.defaultVal || *f12.defaultVal != f12.get(v)) { o[f12.name] = Traits< T12 >::packExt(f12.get(v)); }
    if (!f13.defaultVal || *f13.defaultVal != f13.get(v)) { o[f13.name] = Traits< T13 >::packExt(f13.get(v)); }
    if (!f14.defaultVal || *f14.defaultVal != f14.get(v)) { o[f14.name] = Traits< T14 >::packExt(f14.get(v)); }
    return o;
  }
  boost::optional<Type> unpackExt(const mValue& v) const {
    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);
    const mObject& o(v.get_obj());
    JSON_UNPACK_EXT_OR_EXIT(Type, T0, 0)
    JSON_UNPACK_EXT_OR_EXIT(Type, T1, 1)
    JSON_UNPACK_EXT_OR_EXIT(Type, T2, 2)
    JSON_UNPACK_EXT_OR_EXIT(Type, T3, 3)
    JSON_UNPACK_EXT_OR_EXIT(Type, T4, 4)
    JSON_UNPACK_EXT_OR_EXIT(Type, T5, 5)
    JSON_UNPACK_EXT_OR_EXIT(Type, T6, 6)
    JSON_UNPACK_EXT_OR_EXIT(Type, T7, 7)
    JSON_UNPACK_EXT_OR_EXIT(Type, T8, 8)
    JSON_UNPACK_EXT_OR_EXIT(Type, T9, 9)
    JSON_UNPACK_EXT_OR_EXIT(Type, T10, 10)
    JSON_UNPACK_EXT_OR_EXIT(Type, T11, 11)
    JSON_UNPACK_EXT_OR_EXIT(Type, T12, 12)
    JSON_UNPACK_EXT_OR_EXIT(Type, T13, 13)
    JSON_UNPACK_EXT_OR_EXIT(Type, T14, 14)
    return Type(*t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13, *t14);  
  }
};



template<typename Type>template<typename T0>
Constructor1<Type, T0>
  Constructor0<Type>::add_type(const std::string& tag, const boost::function<T0 (const Type&)>& get, const boost::optional<T0>& def) {
  return Constructor1<Type, T0>(FieldDesc<Type, T0>(tag, get, def));
}

template<typename Type, typename T0>template<typename T1>
Constructor2<Type, T0, T1>
  Constructor1<Type, T0>::add_type(const std::string& tag, const boost::function<T1 (const Type&)>& get, const boost::optional<T1>& def) {
  return Constructor2<Type, T0, T1>(f0, FieldDesc<Type, T1>(tag, get, def));
}

template<typename Type, typename T0, typename T1>template<typename T2>
Constructor3<Type, T0, T1, T2>
  Constructor2<Type, T0, T1>::add_type(const std::string& tag, const boost::function<T2 (const Type&)>& get, const boost::optional<T2>& def) {
  return Constructor3<Type, T0, T1, T2>(f0, f1, FieldDesc<Type, T2>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2>template<typename T3>
Constructor4<Type, T0, T1, T2, T3>
  Constructor3<Type, T0, T1, T2>::add_type(const std::string& tag, const boost::function<T3 (const Type&)>& get, const boost::optional<T3>& def) {
  return Constructor4<Type, T0, T1, T2, T3>(f0, f1, f2, FieldDesc<Type, T3>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3>template<typename T4>
Constructor5<Type, T0, T1, T2, T3, T4>
  Constructor4<Type, T0, T1, T2, T3>::add_type(const std::string& tag, const boost::function<T4 (const Type&)>& get, const boost::optional<T4>& def) {
  return Constructor5<Type, T0, T1, T2, T3, T4>(f0, f1, f2, f3, FieldDesc<Type, T4>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4>template<typename T5>
Constructor6<Type, T0, T1, T2, T3, T4, T5>
  Constructor5<Type, T0, T1, T2, T3, T4>::add_type(const std::string& tag, const boost::function<T5 (const Type&)>& get, const boost::optional<T5>& def) {
  return Constructor6<Type, T0, T1, T2, T3, T4, T5>(f0, f1, f2, f3, f4, FieldDesc<Type, T5>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>template<typename T6>
Constructor7<Type, T0, T1, T2, T3, T4, T5, T6>
  Constructor6<Type, T0, T1, T2, T3, T4, T5>::add_type(const std::string& tag, const boost::function<T6 (const Type&)>& get, const boost::optional<T6>& def) {
  return Constructor7<Type, T0, T1, T2, T3, T4, T5, T6>(f0, f1, f2, f3, f4, f5, FieldDesc<Type, T6>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>template<typename T7>
Constructor8<Type, T0, T1, T2, T3, T4, T5, T6, T7>
  Constructor7<Type, T0, T1, T2, T3, T4, T5, T6>::add_type(const std::string& tag, const boost::function<T7 (const Type&)>& get, const boost::optional<T7>& def) {
  return Constructor8<Type, T0, T1, T2, T3, T4, T5, T6, T7>(f0, f1, f2, f3, f4, f5, f6, FieldDesc<Type, T7>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>template<typename T8>
Constructor9<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8>
  Constructor8<Type, T0, T1, T2, T3, T4, T5, T6, T7>::add_type(const std::string& tag, const boost::function<T8 (const Type&)>& get, const boost::optional<T8>& def) {
  return Constructor9<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8>(f0, f1, f2, f3, f4, f5, f6, f7, FieldDesc<Type, T8>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>template<typename T9>
Constructor10<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
  Constructor9<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8>::add_type(const std::string& tag, const boost::function<T9 (const Type&)>& get, const boost::optional<T9>& def) {
  return Constructor10<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>(f0, f1, f2, f3, f4, f5, f6, f7, f8, FieldDesc<Type, T9>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>template<typename T10>
Constructor11<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
  Constructor10<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::add_type(const std::string& tag, const boost::function<T10 (const Type&)>& get, const boost::optional<T10>& def) {
  return Constructor11<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, FieldDesc<Type, T10>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>template<typename T11>
Constructor12<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>
  Constructor11<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::add_type(const std::string& tag, const boost::function<T11 (const Type&)>& get, const boost::optional<T11>& def) {
  return Constructor12<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, FieldDesc<Type, T11>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>template<typename T12>
Constructor13<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>
  Constructor12<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::add_type(const std::string& tag, const boost::function<T12 (const Type&)>& get, const boost::optional<T12>& def) {
  return Constructor13<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, FieldDesc<Type, T12>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>template<typename T13>
Constructor14<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>
  Constructor13<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::add_type(const std::string& tag, const boost::function<T13 (const Type&)>& get, const boost::optional<T13>& def) {
  return Constructor14<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, FieldDesc<Type, T13>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>template<typename T14>
Constructor15<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>
  Constructor14<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::add_type(const std::string& tag, const boost::function<T14 (const Type&)>& get, const boost::optional<T14>& def) {
  return Constructor15<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, FieldDesc<Type, T14>(tag, get, def));
}

template<typename Type, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>template<typename T15>
Constructor16<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>
  Constructor15<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::add_type(const std::string& tag, const boost::function<T15 (const Type&)>& get, const boost::optional<T15>& def) {
  return Constructor16<Type, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, FieldDesc<Type, T15>(tag, get, def));
}
} // details
} // json_spirit
#undef JSON_UNPACK_OPTIONAL
