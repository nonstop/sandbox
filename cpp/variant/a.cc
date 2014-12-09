#include "variant.h"

#include <cassert>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

typedef Variant<std::string, int> StrIntVar;

void check_good_get()
{
    StrIntVar v1(std::string("lol")), v2(10);
    assert(v1.get<std::string>() == "lol");
    assert(v2.get<int>() == 10);
}

void check_bad_get()
{
    try {
        StrIntVar v(123);
        v.get<std::string>();
    } catch (const std::logic_error& e) {
        cout << "throw: " << e.what() << endl;
        return;
    }
    assert("bad get must throw");
}

struct Foo
{
    ~Foo() {
        cout << "Foo::~Foo" << endl;
    }
};

void check_user_type()
{
    Variant<std::string, Foo> v{Foo()}, v2(std::string("lolka"));
}

void check_copy()
{
    StrIntVar v1(std::string("lolka")), v2(10);
    StrIntVar v3(v1);
    assert(v1.get<std::string>() == v3.get<std::string>());
    v3 = v2;
    assert(v3.get<int>() == v2.get<int>());
    assert(v3 == v2);
}

int main(int ac, char* av[])
{
    check_good_get();
    check_bad_get();
    check_user_type();
    check_copy();
    return 0;
}
