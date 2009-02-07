#include <iostream>
#include <list>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>


using std::cout;
using std::endl;

void func1()
{
    cout << __FUNCTION__ << endl;
}

void func2(int a)
{
    cout << __FUNCTION__ << " a=" << a << endl;
}

void func3(int a, const char* b)
{
    cout << __FUNCTION__ << " a=" << a << " b=" << b << endl;
}

int main(int argc, char *argv[ ])
{
    typedef boost::function<void()> func_type;
    typedef std::list<func_type> func_list;
    
    func_list fl;

    fl.push_back(func_type(func1));
    fl.push_back(boost::bind(func2, 3));
    fl.push_back(boost::bind(func3, 2, "Hello!"));

    BOOST_FOREACH(func_type it, fl) {
        it();
    }

    return 0;
}

