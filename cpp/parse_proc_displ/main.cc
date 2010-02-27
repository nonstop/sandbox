#include <iostream>
#include <list>
#include <string>
#include <boost/foreach.hpp>

#include "foo.h"
#include "bar.h"
#include "desc.h"
#include "err.h"

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
            if (res != SKIP)
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
