
#include <X11/Xutil.h>
#include "X11/xpm.h"
#include "icon.xpm"
#include <stdexcept>

#include "utils.h"
#include "common.h"

Display *getDisplay()
{
    static Display *display = NULL;

    if (!display)
        display = XOpenDisplay(NULL);

    if (!display)
        throw std::logic_error("can't open display");
    return display;
}

int getScreenNumber()
{
    return DefaultScreen(getDisplay);
}

void SetWindowManagerHints(
    char * PClass,   /*Класс программы */
    Window window,      /*Идентификатор окна */
    int x,        /*Координаты левого верхнего */
    int y,        /*угла окна */
    int win_wdt,   /*Ширина  окна */
    int win_hgt,     /*Высота окна */
    int win_wdt_min,   /*Минимальная ширина окна */
    int win_hgt_min,   /*Минимальная высота окна */
    char * ptrTitle,    /*Заголовок окна */
    char * ptrITitle, /*Заголовок пиктограммы окна */
    Pixmap pixmap  /*Рисунок пиктограммы */
)
{
    XSizeHints size_hints; /*Рекомендации о размерах окна*/

    XWMHints wm_hints;
    XClassHint class_hint;
    XTextProperty windowname, iconname;

    if (!XStringListToTextProperty(&ptrTitle, 1, &windowname) ||
            !XStringListToTextProperty(&ptrITitle, 1, &iconname))
    {
        puts("No memory!\n");
        exit(1);
    }

    size_hints.flags = PPosition | PSize | PMinSize;
    size_hints.min_width = win_wdt_min;
    size_hints.min_height = win_hgt_min;
    wm_hints.flags = StateHint | IconPixmapHint | InputHint;
    wm_hints.initial_state = NormalState;
    wm_hints.input = True;
    wm_hints.icon_pixmap = pixmap;
    class_hint.res_name = "";
    class_hint.res_class = PClass;

    XSetWMProperties(getDisplay(), window, &windowname,
                     &iconname, NULL, 0, &size_hints, &wm_hints,
                     &class_hint);
}

#define ICONWIDTH 25
#define ICONHEIGHT 25

void draw_icon(Window& wnd, GC& gc)
{
    Pixmap generic_mask, generic_icon;
    XpmCreatePixmapFromData(getDisplay(), wnd, icon_xpm, &generic_icon, &generic_mask, NULL);

    XSetClipMask(getDisplay(), gc, generic_mask);
    XSetClipOrigin(getDisplay(), gc, 50, 50);
    XCopyArea(getDisplay(), generic_icon, wnd, gc, 0, 0, ICONWIDTH, ICONHEIGHT, 50, 50);
    XSetClipMask(getDisplay(), gc, None);
}

