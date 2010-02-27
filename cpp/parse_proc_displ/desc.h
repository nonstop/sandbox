#ifndef DESC_H
#define DESC_H

#include <string>

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


#endif /* DESC_H */

