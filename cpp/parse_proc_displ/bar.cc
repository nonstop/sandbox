#include <stdio.h>
#include <sstream>
#include "bar.h"
#include "err.h"

int parse_bar(const std::string& str, Bar& bar)
{
    if (str.substr(0, 4) != "BAR ")
        return SKIP;
    char buff[100] = {};
    int ret = sscanf(str.c_str() + 4, "%d %s", &bar.fld1, buff);
    if (ret == 2) {
        bar.fld2 = buff;
        return SUCCESS;
    } else {
        setLastErrorText(std::string("invalid format: ") + str);
        return FAILURE;
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

