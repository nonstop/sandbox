#include <stdio.h>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <boost/foreach.hpp>

const int SUCCESS = 0;
const int FAILURE = -1;
const int MY_REQUEST = -2;

std::string errText;
void setLastErrorText(const std::string& str) { errText = str; }
std::string getLastErrorText() { return errText; }


struct Bar
{
    int fld1;
    std::string fld2;
};
struct ResultBar
{
    int fld1;
    std::string fld2;
};

int parse_bar(const std::string& str, Bar& bar)
{
    if (str.substr(0, 4) != "BAR ")
        return FAILURE;
    char buff[100] = {};
    int ret = sscanf(str.c_str() + 4, "%d %s", &bar.fld1, buff);
    if (ret == 2) {
        bar.fld2 = buff;
        return SUCCESS;
    } else {
        setLastErrorText(std::string("invalid format: ") + str);
        return MY_REQUEST;
    }
}

int proc_bar(const Bar& bar, ResultBar& rf)
{
    rf.fld1 = bar.fld1 + 1000;
    rf.fld2 = bar.fld2;
    return SUCCESS;
}

int display_bar(const ResultBar& rf, std::string& str)
{
    std::stringstream s;
    s << "ResultBar: " << rf.fld1 << " [" << rf.fld2 << "]";
    str = s.str();
    return SUCCESS;
}

struct Foo
{
    int fld1;
    std::string fld2;
};
struct ResultFoo
{
    int fld1;
    std::string fld2;
};

int parse_foo(const std::string& str, Foo& foo)
{
    if (str.substr(0, 4) != "FOO ")
        return FAILURE;
    char buff[100] = {};
    int ret = sscanf(str.c_str() + 4, "%s %d", buff, &foo.fld1);
    if (ret == 2) {
        foo.fld2 = buff;
        return SUCCESS;
    } else {
        setLastErrorText(std::string("invalid format: ") + str);
        return MY_REQUEST;
    }
}

int proc_foo(const Foo& foo, ResultFoo& rf)
{
    rf.fld1 = foo.fld1 + 10000;
    rf.fld2 = foo.fld2;
    return SUCCESS;
}

int display_foo(const ResultFoo& rf, std::string& str)
{
    std::stringstream s;
    s << "ResultFoo: " << rf.fld1 << " [" << rf.fld2 << "]";
    str = s.str();
    return SUCCESS;
}

struct BaseDesc
{
    virtual ~BaseDesc() {}
    virtual int parse(const std::string& str) = 0;
    virtual int proc() = 0;
    virtual int disp(std::string& str) = 0;
};
template<typename ParseData, typename ProcData>
struct Desc
    : public BaseDesc
{
    typedef int (*ParseFunc_t) (const std::string&, ParseData&);
    typedef int (*ProcFunc_t) (const ParseData&, ProcData&);
    typedef int (*DispFunc_t) (const ProcData&, std::string&);
    ParseData parseData_;
    ProcData procData_;
    ParseFunc_t parseFunc_;
    ProcFunc_t procFunc_;
    DispFunc_t dispFunc_;
    Desc(ParseFunc_t paf, ProcFunc_t prf, DispFunc_t dif)
        : parseFunc_(paf), procFunc_(prf), dispFunc_(dif)
    {}
    virtual int parse(const std::string& str) { parseData_ = ParseData(); return parseFunc_(str, parseData_); }
    virtual int proc() { procData_ = ProcData(); return procFunc_(parseData_, procData_); }
    virtual int disp(std::string& str) { return dispFunc_(procData_, str); }
};
std::list<BaseDesc*> descs;
void initDescs()
{
    descs.push_back(new Desc<Foo, ResultFoo>(parse_foo, proc_foo, display_foo));
    descs.push_back(new Desc<Bar, ResultBar>(parse_bar, proc_bar, display_bar));
}

std::string textTermRequest(const std::string& str)
{
    initDescs();
    BOOST_FOREACH(BaseDesc* bd, descs) {
        int res = bd->parse(str);
        if (res == SUCCESS) {
            res = bd->proc();
            if (res == SUCCESS) {
                std::string answer;
                res = bd->disp(answer);
                if (res == SUCCESS) {
                    return answer;
                } else {
                    return getLastErrorText();
                }
            } else {
                return getLastErrorText();
            }
        } else {
            if (res == MY_REQUEST)
                return getLastErrorText();
        }
    }
    return "nothing appropriate";
}

int main(int ac, char* av[])
{
#define req(str) std::cout << str << ":\t" << textTermRequest(str) << std::endl;
    req("FOO 1 lala");
    req("FOO lala 1");
    req("BAR two lolo");
    req("BAR 2 lolo");
    req("LOL 1 lala");
    return 0;
}
