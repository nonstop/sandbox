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

static void trace_stack(lua_State* ls)
{
    const int stackSz = lua_gettop(ls);
    int i = 1;
    for (; i<=stackSz; ++i) {
        TRACE("stack[%d]=[%s]", i, lua_typename(ls, lua_type(ls, i)));
    }
}

static int print_table__(lua_State* ls, const int tableIndex)
{
    if (!lua_istable(ls, tableIndex)) {
        TRACE("not a table");
        return 0;
    }
    TRACE("printing table... tableIndex=%d top=%d", tableIndex, lua_gettop(ls));

    lua_pushnil(ls);
    trace_stack(ls);
    while (lua_next(ls, tableIndex) != 0) {
        /*TRACE("[%s]-[%s]",*/
                /*lua_typename(ls, lua_type(ls, -2)),*/
                /*lua_typename(ls, lua_type(ls, -1)));*/
        const char* name = "";
        if (lua_isstring(ls, tableIndex +1) && !lua_isnumber(ls, tableIndex + 1)) {
            name = lua_tostring(ls, tableIndex + 1);
        }
        if (lua_isnumber(ls, tableIndex + 2)) {
            TRACE("[%s]=[%d]", name, lua_tonumber(ls, tableIndex + 2));
        } else if (lua_isstring(ls, tableIndex + 2)) {
            TRACE("[%s]=[%s]", name, lua_tostring(ls, tableIndex + 2));
        } else if (lua_istable(ls, tableIndex + 2)) {
            TRACE("[%s]=[table]", name);
            print_table__(ls, tableIndex + 2);
        }
        lua_pop(ls, 1);
    }
    return 0;
}


static int print_table(lua_State* ls)
{
    return print_table__(ls, 1);
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

    lua_register(L, "printTable", print_table);
    int s = luaL_loadfile(L, av[1]);
    report_lua_error(__FILE__, __LINE__, s);

    s = lua_pcall(L, 0, LUA_MULTRET, 0);
    report_lua_error(__FILE__, __LINE__, s);


    lua_close(L);
    return 0;
}

