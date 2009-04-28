#include <lua.h>
#include <lualib.h>
#include <stdio.h>

struct lua_State* L = NULL;

void report_lua_error(const char* file, int line, int status)
{
    if (status == 0)
        return;
    fprintf(stderr, "%s:%d %s\n", file, line, lua_tostring(L, -1));
    lua_pop(L, 1);
}

int foo(lua_State* L)
{
    lua_pushnumber(L, 2);
    return 1;
}

void prepare_table()
{
    lua_newtable(L); /* my empty environment aka {}              (sp += 1) */
    
    lua_newtable(L); // bar
    
    lua_newtable(L); // bar.__metatable
    lua_pushcfunction(L, foo);
    lua_setfield(L, -2, "__index");

    lua_setfield(L, -2, "bar");

    lua_setfenv(L, -2); /* on the stack should be a modified env (sp -= 1) */
}

int main(int ac, char* av[])
{
    if (ac != 2) {
        fprintf(stderr, "Usage: %s script.lua\n", av[0]);
        return 0;
    }
    L = luaL_newstate();
    luaL_openlibs(L);
    
    prepare_table();

    int s = luaL_loadfile(L, av[1]);
    report_lua_error(__FILE__, __LINE__, s);

    s = lua_pcall(L, 0, LUA_MULTRET, 0);
    report_lua_error(__FILE__, __LINE__, s);


    lua_close(L);
    return 0;
}

