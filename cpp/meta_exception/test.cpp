#include <string>
#include <stdio.h>

#include "meta_exception.h"
#include "callstack.h"

#define NICKNAME "nonstop"

void test_func(int par1, const std::string& par2)
{
    F_STACK;
    VAR_STACK(par1);
    VAR_STACK(par2);
    
    for (int i=0; i<5; ++i)
    {
        VAR_STACK(i);
    }
}

int main(int ac, char *av[])
{
    try
    {
        throw MetaException("exception text");
    }
    catch (const MetaException &e)
    {
        fprintf(stderr, "meta: %s\n", e.meta());
        fprintf(stderr, "text: %s\n", e.what());
    }

    try
    {
#define __LINE__ 999999
        throw MetaException(__FILE__, __LINE__, "NICKNAME", "nice line");
    }
    catch (const MetaException &e)
    {
        fprintf(stderr, "meta: %s\n", e.meta());
        fprintf(stderr, "text: %s\n", e.what());
    }
    
    try
    {
#define __LINE__ 9999999
        throw MetaException(__FILE__, __LINE__, "NICKNAME", "mad line number");
    }
    catch (const MetaException &e)
    {
        fprintf(stderr, "meta: %s\n", e.meta());
        fprintf(stderr, "text: %s\n", e.what());
    }
    
    test_func(10, "ten");
    Callstack::instance()->dump(stderr);
    return 0;
}

