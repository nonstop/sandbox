#ifndef FOO_H
#define FOO_H

#include <string>

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

int parse_foo(const std::string& str, Foo& foo);
int proc_foo(const Foo& foo, ResultFoo& rf);
int display_foo(const ResultFoo& rf, std::string& str);

#endif /* FOO_H */

