#include <string.h>
#include <lualib.h>
#include <lauxlib.h>

#include "utils.h"
#include "giel.h"
#include "basic_unit.h"
#include "giel_lua.h"

static struct lua_State* L = NULL;
static char* name = NULL;
static char* units = NULL;

static void report_lua_error(const char* file, int line, int status)
{
    if (status == 0)
        return;
    TRACE(" %s:%d %s", file, line, lua_tostring(L, -1));
    lua_pop(L, 1);
}

static int giel_lua_setForm(lua_State* ls)
{
    if (lua_isnil(ls, 1) || !lua_isstring(ls, 1)) {
        TRACE("invalid name");
        return 0;
    } else if (lua_isnil(ls, 2) || !lua_isstring(ls, 2)) {
        TRACE("invalid unitstring");
        return 0;
    }
    name =  strdup(lua_tostring(ls, 1));
    units = strdup(lua_tostring(ls, 2));
    return 0;
}

static void appendUnits(Globals* globals, const char* units)
{
    int idx = 0;
    BasicUnit* currentUnit = NULL;
    while (*units) {
        if (!globals->head) {
            globals->head = calloc(1, sizeof(BasicUnit));
            globals->currentUnit = globals->head;
            globals->currentUnit->isCurrent = 1;
            currentUnit = globals->currentUnit;
        } else {
            appendBasicUnits(currentUnit, 1);
            currentUnit = currentUnit->next;
        }
        switch (*units) {
        case '-':
            break;
        case '\\':
            basic_unit_turn_left(currentUnit);
            break;
        case '/':
            basic_unit_turn_right(currentUnit);
            break;
        case '|':
            basic_unit_turn_right(currentUnit);
            basic_unit_turn_right(currentUnit);
            break;
        }
        ++idx;
        ++units;
    }
}

void initSceneFromFile(Globals* globals, const char* file)
{
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "setForm", giel_lua_setForm);

    TRACE("load file %s", file);
    int s = luaL_loadfile(L, file);
    report_lua_error(__FILE__, __LINE__, s);

    s = lua_pcall(L, 0, LUA_MULTRET, 0);
    report_lua_error(__FILE__, __LINE__, s);

    lua_close(L);
    TRACE("name=[%s] units=[%s]", name, units);
    appendUnits(globals, units);
    free(name);
    free(units);
    BasicUnit* c = globals->head;
    while (c) {
        TRACE("%p odd=%d rot=%d", c, c->isOdd, c->rot);
        c = c->next;
    }
    return;
}
