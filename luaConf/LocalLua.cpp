#include <iostream>
#include <map>
#include <lua.hpp>

#include "LocalLua.h"

#define TRACE(x) cout << __FILE__ << ":" << __LINE__ << " " << x << endl

using namespace std;

namespace
{
lua_State* ls = NULL;
typedef map<string, string> VarValues;
VarValues varValues;
}

LocalLua::LocalLua()
{
    TRACE(__FUNCTION__);
    ls = lua_open();
    luaL_openlibs(ls);
}

LocalLua::~LocalLua()
{
    TRACE(__FUNCTION__);
    lua_close(ls);
}

void LocalLua::process(const string& configFile)
{
    TRACE(configFile);
    luaL_dofile(ls, configFile.c_str());
}

void LocalLua::readVar(const std::string& name)
{
    lua_getglobal(ls, "getVar");
    lua_pushstring(ls, name.c_str());
    lua_call(ls, 1, 1);
    const char* res = lua_tostring(ls, -1);
    if (res)
        varValues[name] = res;
}

const string& LocalLua::getVar(const string& name, const string& defaultValue) const
{
    VarValues::const_iterator it = varValues.find(name);
    if (it != varValues.end())
        return it->second;
    return defaultValue;
}

