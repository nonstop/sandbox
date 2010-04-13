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

class Foo
{
public:
    void func(const char* data) {
        cout << "Foo::func [" << data << "]" << endl;
    }
    //void func() {
        //cout << "Foo::func" << endl;
    //}
};

int main(int argc, char *argv[ ])
{
    //typedef boost::function<void()> func_type;
    typedef boost::function<void (const char* data)> func_type;
    typedef std::list<func_type> func_list;
    
    func_list fl;

    //fl.push_back(func_type(func1));
    //fl.push_back(boost::bind(func2, 3));
    //fl.push_back(boost::bind(func3, 2, "Hello!"));
    Foo foo;
    fl.push_back(boost::bind(&Foo::func, &foo, _1));

    BOOST_FOREACH(func_type it, fl) {
        it("123");
        //it();
    }

    return 0;
}

