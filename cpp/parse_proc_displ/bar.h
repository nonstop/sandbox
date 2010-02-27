#ifndef BAR_H
#define BAR_H

#include <string>

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

int parse_bar(const std::string& str, Bar& bar);
int proc_bar(const Bar& bar, ResultBar& rf);
int display_bar(const ResultBar& rf, std::string& str);



#endif /* BAR_H */

