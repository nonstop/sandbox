#!/usr/bin/python

import sys

print """namespace json_spirit {
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

"""

def templateStr(n):
    s = "template<typename Type"
    for i in range(0, n):
        s += ", typename T" + str(i)
    s += ">"
    return s

def typesStr(n):
    s = "Type"
    for i in range(0, n):
        s += ", T" + str(i)
    return s

def varsStr(n):
    s = ""
    for i in range(0, n):
        s += ", *t" + str(i)
    if len(s) == 0:
        return s
    return s[2:]

def fieldsStr(n):
    s = ""
    for i in range(0, n):
        s += ", f" + str(i)
    if len(s) == 0:
        return s
    return s[2:]

def structName(n):
    return "Constructor" + str(n)

class Constructor(object):
    def __init__(self, n):
        self.n = n
        self.name = structName(n)
    def forwardDecl(self):
        return templateStr(self.n) + " struct " + self.name + ";"
    def packStr(self, mode):
        s = "\n  mValue pack" + mode + "(const Type& v) const {"
        s += "\n    mObject o;"
        for i in range(0, self.n):
            s += "\n    if (!f{0}.defaultVal || *f{0}.defaultVal != f{0}.get(v)) { o[f{0}.name] = Traits< T{0} >::pack{1}(f{0}.get(v)); }"\
                    .replace("{0}", str(i)).replace("{1}", mode)
        s += "\n    return o;\n  }"
        return s
    def unpackStr(self, mode):
        s = "\n  boost::optional<Type> unpack" + mode + "(const mValue& v) const {"
        s += "\n    JSON_ASSERT_TYPE(Type, v, json_spirit::obj_type);"
        s += "\n    const mObject& o(v.get_obj());"
        for i in range(0, self.n):
            s += "\n    JSON_UNPACK_{1}_OR_EXIT(Type, T{0}, {0})".format(i, mode.upper())
        s += "\n    return Type(" + varsStr(self.n) + ");  \n  }"
        return s
    def structDecl(self):
        s = templateStr(self.n) + " struct " + self.name + "\n{"
        if self.n > 0:
            s += "\n "
        for i in range(0, self.n):
            s += " FieldDesc<Type, T{0}> f{0};".format(i)
        s += "\n  " + self.name + "("
        for i in range(0, self.n):
            s += "const FieldDesc<Type, T{0}>& f{0}_, ".format(i)
        if (self.n > 0):
            s = s[:-2]
        s += ") "
        if self.n > 0:
            s += ': '
        for i in range(0, self.n):
            s += "f{0}(f{0}_), ".format(i)
        if self.n > 0:
            s = s[:-2]
        s += " {}"
        s += "\n    template<typename {0}> {1}<{2}>\n    add_type(const std::string&, const boost::function<{0} (const Type&)>& get, const boost::optional<{0}>& def = boost::optional<{0}>());"\
                .format("T" + str(self.n), structName(self.n + 1), typesStr(self.n + 1))
        if self.n > 0:
            s += self.packStr("Int")
            s += self.unpackStr("Int")
            s += self.packStr("Ext")
            s += self.unpackStr("Ext")
        
        s += "\n};"
        return s
    def add_type(self):
        s = templateStr(self.n) + "template<typename T{0}>".format(str(self.n))
        s += "\n" + structName(self.n + 1) + "<" + typesStr(self.n + 1) + ">"
        s += "\n  " + structName(self.n) + "<" + typesStr(self.n) + ">"
        s += "::add_type(const std::string& tag, const boost::function<T{0} (const Type&)>& get, const boost::optional<T{0}>& def) {"\
                .replace("{0}", str(self.n))
        fields = fieldsStr(self.n)
        if self.n > 0:
            fields += ", "
        s += "\n  return {0}<{1}>(-fields-FieldDesc<Type, T{2}>(tag, get, def));"\
                .format(structName(self.n + 1), typesStr(self.n + 1), self.n)\
                .replace("-fields-", fields)
        s += "\n}"
        return s

n = 10
if len(sys.argv) == 2:
    n = int(sys.argv[1]) + 1

l = []
for i in range(0, n + 1):
    l.append(Constructor(i))

for c in l:
    print c.forwardDecl()

l = l[:-1]
print "\n"
for c in l:
    print '\n' + c.structDecl()

print "\n"
for c in l:
    print '\n' + c.add_type()


print """} // details
} // json_spirit
#undef JSON_UNPACK_OPTIONAL"""
