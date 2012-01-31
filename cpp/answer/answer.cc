#include <iostream>
#include <string>
#include <list>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

enum Language {English, Russian};

static std::string getMsgByNum(int msg)
{
    static const std::string messages[] = {
        "OK", "OK WITH %s %s VALUES", "FAIL", "FAIL WITH %s %s %s VALUES"
    };
    return messages[msg];
}

template<typename T>
static std::string makeBindString(const std::string& type, const T& val)
{
    return "{{" + type + ":" + boost::lexical_cast<std::string>(val) + "}}";
}

template<typename T>
std::string bindType(const T& t);

class Answer
{
public:
    Answer()
        : error_(0), msg_(0)
    {}
    Answer(int error, int msg)
        : error_(0), msg_(msg)
    {}
    Answer(int error)
        : error_(error), msg_(error)
    {}
    ~Answer() {}
    operator bool() const {
        return error_ == 0;
    }
    template<typename T>
    Answer& bind(const T& t) {
        bindings_.push_back(bindType(t));
        return *this;
    }
    int msg() const {
        return msg_;
    }
    std::string prepare() const {
        boost::format msgFmt(getMsgByNum(msg_));
        BOOST_FOREACH(const std::string& str, bindings_) {
            msgFmt % str;
        }
        return msgFmt.str();
    }
private:
    int error_, msg_;
    std::list<std::string> bindings_;
};
#define ANSWER_BIND_SIMPLE_TYPE(Type, value) template<> std::string bindType<Type>(const Type& t) { \
    return makeBindString(#Type, t.value); \
}
struct Type1 {
    int val;
};
ANSWER_BIND_SIMPLE_TYPE(Type1, val);

struct Type2 {
    bool fld;
};
ANSWER_BIND_SIMPLE_TYPE(Type2, fld);

class ComplexType3 {
public:
    ComplexType3(const std::string& val) : val_(val) {}
    const std::string& value() const { return val_; }
private:
    std::string val_;
};

template<> std::string bindType<ComplexType3>(const ComplexType3& t)
{
    return makeBindString("CoTy3", t.value());
}

static Answer goodFunc()
{
    return Answer();
}

static Answer goodFuncWithBindings()
{
    Type1 t1;
    t1.val = 2;
    Type2 t2;
    t2.fld = true;
    return Answer(0, 1).bind(t1).bind(t2);
}

static Answer badFunc()
{
    return Answer(2);
}

static Answer badFuncWithBindings()
{
    Type1 t1;
    t1.val = 1;
    Type2 t2;
    t2.fld = false;
    ComplexType3 t3("lolka");
    return Answer(3).bind(t1).bind(t2).bind(t3);
}

static std::string typeToStr(const std::string& name, const std::string& value, Language lang)
{
    if (name == "CoTy3") {
        return "???";
    }
    return (lang == English ? "[Eng " : "[Rus ") + name + "=" + value + "]";
}

static std::string displayAnswer(const Answer& answer, Language lang)
{
    const boost::regex bindingPattern("\\{\\{([a-zA-Z0-9]+):([a-zA-Z0-9]+)\\}\\}");
    std::string str(answer.prepare());
    std::string::const_iterator start = str.begin(), end = str.end();
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    std::string msg;
    while (regex_search(start, end, what, bindingPattern, flags)) {
        msg += std::string(start, what[0].first);
        // update search position:
        start = what[0].second;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
        msg += typeToStr(what[1], what[2], lang);
    }
    msg += std::string(start, end);
    return msg;
}

int main()
{
#define displayFunc(func) { \
    Answer answer = func(); \
    std::cout << "message: [" << getMsgByNum(answer.msg()) << "]" << std::endl; \
    std::cout << "prepared: [" << answer.prepare() << "]" << std::endl; \
    std::cout << "display " #func << " Eng: " << displayAnswer(answer, English) << std::endl; \
    std::cout << "display " #func << " Rus: " << displayAnswer(answer, Russian) << "\n" << std::endl; \
}
    displayFunc(goodFunc);
    displayFunc(badFunc);
    displayFunc(goodFuncWithBindings);
    displayFunc(badFuncWithBindings);
    return 0;
}
