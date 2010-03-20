#include <lua.h>
#include <lualib.h>
#include <stdio.h>

struct lua_State* L = NULL;

#define TRACE(format, ...) \
         fprintf(stderr, "%s:%d %s " format "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)

static void report_lua_error(const char* file, int line, int status)
{
    if (status == 0)
        return;
    TRACE(" %s:%d %s", file, line, lua_tostring(L, -1));
    lua_pop(L, 1);
}

static int foo__index(lua_State* L)
{
    size_t len;
    const char *buf = luaL_checklstring(L, 2, &len);
    TRACE("args=%s len=%d", buf, len);

    TRACE("argc=%d ", lua_gettop(L));
    TRACE("argv[1]=%s argv[2]=%s", lua_tostring(L, 1), lua_tostring(L, 2));
    lua_pushnumber(L, 2);
    return 1;
}

static int foo__newindex(lua_State* L)
{
    size_t len;
    const char *buf = luaL_checklstring(L, 2, &len);
    TRACE("args=%s len=%d", buf, len);

    TRACE("argc=%d ", lua_gettop(L));
    TRACE("argv[1]=%s argv[2]=%s", lua_tostring(L, 1), lua_tostring(L, 2));
    lua_pushnumber(L, 2);
    return 1;
}

static void prepare_table()
{
    lua_newtable(L);
    luaL_newmetatable(L, "bar_meta");
    lua_pushcfunction(L, foo__index);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, foo__newindex);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);
    lua_setfield(L, LUA_GLOBALSINDEX, "bar"); // table bar
}

int main(int ac, char* av[])
{
    if (ac != 2) {
        TRACE("Usage: %s script.lua\n", av[0]);
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

