#include <list>
#include <iostream>


#include "LocalLua.h"

#define TRACE(x) cout << __FILE__ << ":" << __LINE__ << " " << x << endl




using namespace std;

namespace
{
typedef list<string> VarNames;
LocalLua ll;


void readConfigs(const string& configFile, const VarNames& vns)
{
    TRACE(__FUNCTION__);
    ll.process(configFile);
    for (VarNames::const_iterator it = vns.begin(); it != vns.end(); ++it)
        ll.readVar(*it);
}

void printConfigs(const VarNames& vns)
{
    TRACE(__FUNCTION__);
    for (VarNames::const_iterator it = vns.begin(); it != vns.end(); ++it)
        TRACE(ll.getVar(*it));
}

}

int main(int ac, char* av[])
{
    if (ac < 2)
    {
        cout << "Usage: " << av[0] << " config.lua" << endl;
        return 1;
    }
    
    VarNames names;
    names.push_back("var1");
    names.push_back("var2");
    names.push_back("VAR2");
    readConfigs(av[1], names);

    printConfigs(names);

    return 0;
}

