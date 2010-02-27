#include <stdio.h>
#include <sstream>
#include "foo.h"
#include "err.h"

int parse_foo(const std::string& str, Foo& foo)
{
    if (str.substr(0, 4) != "FOO ")
        return SKIP;
    char buff[100] = {};
    int ret = sscanf(str.c_str() + 4, "%s %d", buff, &foo.fld1);
    if (ret == 2) {
        foo.fld2 = buff;
        return SUCCESS;
    } else {
        setLastErrorText(std::string("invalid format: ") + str);
        return FAILURE;
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


