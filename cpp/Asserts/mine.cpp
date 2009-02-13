#include <iostream>
#include <string>

using namespace std;

#define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
#define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
#define SMART_ASSERT_OP(x, next) \
    SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next
#define SMART_ASSERT( expr) \
    if ( (expr) ) ; \
    else make_assert( #expr).print_context( __FILE__, __LINE__).SMART_ASSERT_A 


class Assert
{
public:
    Assert& SMART_ASSERT_A;
    Assert& SMART_ASSERT_B;

    Assert& print_current_val(const string &val, const string &name)
    {
        cout << "       Value for " << name << " : [" << val << "]" << endl;
    }
    Assert& print_context(const char *fl, int ln)
    {
        cout << fl << ":" << ln << endl;
    }
private:
};

Assert &make_assert(const string &str)
{
    cout << "Assert (" << str << ") at ";
    return *(new Assert());
}

int main(int ac, char *av[])
{
    cout << "start" << endl;
 
    string s1 = "Wake up, Neo";
    string s2 = "It's time to reload.";
    SMART_ASSERT(s1.empty() && s2.empty())(s1)(s2);

    string s3 = "Wake up, Neo";
    string s4 = "";
    SMART_ASSERT(s3.empty() && s4.empty())(s3)(s4);

    string s5 = "";
    string s6 = "";
    SMART_ASSERT(s5.empty() && s6.empty())(s5)(s6);

    cout << "finish" << endl;
    return 0;
}


