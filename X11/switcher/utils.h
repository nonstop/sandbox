#ifndef UTILS_H_
#define UTILS_H_

#include <X11/Xlib.h>

void SetWindowManagerHints(
    char * PClass, Window window, int x, int y, int win_wdt, int win_hgt, int win_wdt_min, int win_hgt_min,
    char * ptrTitle, char * ptrITitle, Pixmap pixmap);
Display *getDisplay();
int getScreenNumber();
void draw_icon(Window& wnd, GC& gc);


#endif /* UTILS_H_ */

