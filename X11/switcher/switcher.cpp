
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <X11/Xlocale.h>

#include <stdexcept>
#include <vector>

//#include "MainWindow.h"
#include "common.h"
#include "utils.h"

using namespace std;


Window root_wnd;


#define X 0
#define Y 0
#define WIDTH 200
#define HEIGHT 200
#define WIDTH_MIN 50
#define HEIGHT_MIN 50
#define BORDER_WIDTH 5
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"


char *atom_names[] = {
                         "_WIN_WORKSPACE",
                         "_NET_CLIENT_LIST",
                         "_NET_NUMBER_OF_DESKTOPS"
                     };

#define ATOM_COUNT (sizeof (atom_names) / sizeof (atom_names[0]))

Atom atoms[ATOM_COUNT];

#define atom__WIN_WORKSPACE atoms[0]
#define atom__NET_CLIENT_LIST atoms[1]
#define atom__NET_NUMBER_OF_DESKTOPS atoms[2]


class WindowInfo
{
public:
    WindowInfo(Window wnd, const std::string& name)
        : m_wnd(wnd), m_name(name)
    {}
    Window window() const
    {   return m_wnd;   }
    const string& name() const
    {   return m_name;  }
private:
    Window m_wnd;
    string m_name;
    Pixmap m_pixmap;
};
typedef vector<WindowInfo> WindowInfos;
typedef WindowInfos::iterator WindowInfosIter;
WindowInfos g_windows;

void *get_prop_data(Window win, Atom prop, Atom type, int *items)
{
    Atom type_ret;
    int format_ret;
    unsigned long items_ret;
    unsigned long after_ret;
    unsigned char *prop_data;

    prop_data = 0;

    XGetWindowProperty(getDisplay(), win, prop, 0, 0x7fffffff, False,
                       type, &type_ret, &format_ret, &items_ret,
                       &after_ret, &prop_data);
    if (items)
        *items = items_ret;

    return prop_data;
}

int find_desktop(Window win)
{
    int desk = 0;
    unsigned long *data;

    data = (unsigned long*)get_prop_data(win, atom__WIN_WORKSPACE, XA_CARDINAL, 0);
    if (data)
    {
        desk = *data;
        XFree(data);
    }
    return desk;
}

void get_windows_info()
{
    int num = 0;

    Window *win = (Window*)get_prop_data(root_wnd, atom__NET_CLIENT_LIST, XA_WINDOW, &num);
    int desk = find_desktop(root_wnd);
    TRACE1(desk);
    for (int i = 0; i < num; i++)
    {
        Window wnd = win[i];
        string name;
//        if (desk != find_desktop(wnd))
//            continue;
        XTextProperty tp;
        if (!XGetWMName(getDisplay(), wnd, &tp))
        {
            name = " (has no name)";
            printf(" (has no name)");
        }
        else if (tp.nitems > 0)
        {
            int count = 0, i, ret;
            char **list = NULL;
            ret = XmbTextPropertyToTextList(getDisplay(), &tp, &list, &count);
            if ((ret == Success || ret > 0) && list != NULL)
            {
                for (i = 0; i < count; i++)
                {
                    printf("%s\n", list[i]);
                    name += list[i];
                }                
                XFreeStringList(list);
            }
            else
            {
                printf("%s\n", tp.value);
                name = (char*)tp.value;
            }
        }
        g_windows.push_back(WindowInfo(wnd, name));
        TRACE1(i);
        TRACE1(name);
        TRACE1(find_desktop(wnd));
        /*        else
                {
                    char *name = (char*)get_prop_data(wnd, XA_WM_NAME, XA_STRING, 0, dd);
                    TRACE1(strlen(name));
                    fprintf(stderr, "Window: %s, %i\n", name, (int)wnd);
                }*/
    }

}


/*
* SetWindowManagerHints - функция, которая передает информацию о
* свойствах программы менеджеру окон.
*/


/* main - основная функция программы */

void Display_Window_Id(Display *getDisplay(), Window window, Bool newline_wanted)
{
    char *win_name;
    if (!XFetchName(getDisplay(), window, &win_name))
    { /* Get window name if any */
        printf(" (NO NAME)");
    }
    else if (win_name)
    {
        printf("\n%s:%i\n", __FILE__, __LINE__);
        printf(" \"%s\"", win_name);
        XFree(win_name);
    }
    else
        printf(" (has no name)");
}


Window createSwitcherWindow()
{
    int ScreenNumber;    /* Номер экрана */
    Window window;

    /* Получаем номер основного экрана */
    ScreenNumber = DefaultScreen(getDisplay());
    root_wnd = RootWindow(getDisplay(), ScreenNumber);
    /* Создаем окно */
    window = XCreateSimpleWindow(getDisplay(),
                                 root_wnd,
                                 X, Y, WIDTH, HEIGHT, BORDER_WIDTH,
                                 BlackPixel(getDisplay(), ScreenNumber),
                                 WhitePixel(getDisplay(), ScreenNumber));
    XInternAtoms(getDisplay(), atom_names, ATOM_COUNT, False, atoms);

    SetWindowManagerHints(PRG_CLASS, window, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
                          HEIGHT_MIN, TITLE, ICON_TITLE, 0);

    XSelectInput(getDisplay(), window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonReleaseMask | ButtonPressMask);

    return window;
}

int main(int argc, char *argv[])
{
    {
        char *lc;
        lc = setlocale(LC_ALL, "");
        if (!lc)
            fprintf(stderr, "can not set locale properly\n");
    }
    XEvent report;
    Window window = createSwitcherWindow();

    XMapWindow(getDisplay(), window);
    
    /* Создадим цикл получения и обработки ошибок */
    get_windows_info();

    for (WindowInfosIter it = g_windows.begin(); it != g_windows.end(); it++)
    {
        TRACE1("********");
        TRACE1(it->window());
        TRACE1(it->name());
    }
    while (1)
    {
        XNextEvent(getDisplay(), &report);
        GC gc = XCreateGC(getDisplay(), window, 0 , NULL);
        XSetForeground(getDisplay(), gc, BlackPixel(getDisplay(), 0));

        switch (report.type)
        {
        case Expose :
            /* Запрос на перерисовку */
            if (report.xexpose.count != 0)
                break;
            XDrawString(getDisplay(), window, gc, 20, 50,
                        "First example", strlen("First example"));
            XFlush(getDisplay());
            break;
        case ButtonRelease:
        {
            XClearWindow(getDisplay(), window);
            XSetWindowBackground(getDisplay(), window, rand());
            XDrawString(getDisplay(), window, gc, 50, 50, "Release!", strlen("Release!"));
            draw_icon(window, gc);
            break;
        }
        case ButtonPress:
        {
            XClearWindow(getDisplay(), window);
            XSetWindowBackground(getDisplay(), window, rand());
            XDrawString(getDisplay(), window, gc, 50, 50, "Press!", strlen("Press!"));
            break;
        }
        case KeyRelease :
            TRACE1(report.xkey.keycode);
            TRACE1(report.xkey.state);
            if ((report.xkey.keycode != 24)
                    || (report.xkey.state != 8))
                break;
            // Выход нажатием клавиши Alt-q клавиатуры
            XCloseDisplay(getDisplay());
            return 0;
        }
        XFreeGC(getDisplay(), gc);
    }
    return 0;
}
