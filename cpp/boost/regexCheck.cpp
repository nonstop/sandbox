#include <iostream>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>

using std::cout;
using std::endl;


static void regexCheck(const std::string& pattern, const std::string& str)
{
    boost::smatch what;
    if (boost::regex_match(str, what, boost::regex(pattern))) {
        for (size_t i = 0; i < what.size(); ++i) {
            cout << i << "  " << what[i] << endl;
        }
    }
}


int main(int ac, char* av[])
{
    if (ac < 3) {
        cout << "usage: pattern str1 .. strN" << endl;
    }
    for (int i = 2; i < ac; ++i) {
        regexCheck(av[1], av[i]);
    }
    return 0;
}

