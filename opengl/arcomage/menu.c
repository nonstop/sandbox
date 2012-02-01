#include <GL/gl.h>

#include "FreeType.h"

typedef void (*MenuCallback) (void);
#define MIS_NONE 0x0
#define MIS_SELECTED 0x1
#define MIS_DISABLED 0x2

typedef struct MenuItem
{
    const char* label;
    int state;
    MenuCallback callback;
} MenuItem;

static MenuItem items[] = {
    {"New game", MIS_NONE | MIS_SELECTED},
    {"Resume", MIS_DISABLED},
    {"Scores", MIS_NONE},
    {"Quit", MIS_NONE}};

static const size_t itemsLen = sizeof(items)/sizeof(items[0]);

void menu_init()
{
    initFont("Test.ttf", 16);
}

void menu_draw()
{
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    size_t i = 0;
    for (; i < itemsLen; ++i) {
        printStr(items[i].label, 20, 300 - 20 * i);
    }
    glPopMatrix();
}
