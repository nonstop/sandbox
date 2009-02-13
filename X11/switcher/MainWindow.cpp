
#include <X11/Xutil.h>

#include "MainWindow.h"
#include "common.h"
#include "utils.h"

using namespace std;

/*
 * #define WIDTH 200
#define HEIGHT 200
#define WIDTH_MIN 50
#define HEIGHT_MIN 50
#define BORDER_WIDTH 5
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"
    Display *m_display;
    int m_width;
    int m_height;
    int m_widthMin;
    int m_heightMin;
    int m_borderWidth;
    std::string m_title;
    std::string m_iconTitle;
    std::string m_prgClass;
*/

static void SetWindowManagerHints(
    Display * display,   /*Указатель на структуру Display */
    const char * PClass,   /*Класс программы */
    const char * argv[],     /*Аргументы программы */
    int argc,       /*Число аргументов */
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
    class_hint.res_name = argv[0];
    class_hint.res_class = PClass;

    XSetWMProperties(getDisplay(), window, &windowname,
                     &iconname, argv, argc, &size_hints, &wm_hints,
                     &class_hint);
}

MainWindow::MainWindow(Window parent, const std::string & title, int width, int height)
    : m_width(width), m_height(height), m_title(title)
{
    m_wnd = XCreateSimpleWindow(getDisplay(),
                                 parent,
                                 0/*X*/, 0/*Y*/, m_width, m_height, m_borderWidth,
                                 BlackPixel(getDisplay(), getScreenNumber()),
                                 WhitePixel(getDisplay(), getScreenNumber()));
    TRACE;

    /* Задаем рекомендации для менеджера окон */
    SetWindowManagerHints(/*getDisplay(), */m_prgClass.c_str(), NULL/*argv*/, 0/*argc*/,
                          m_wnd, 0/*X*/, 0/*Y*/, m_width, m_height, m_widthMin, m_heightMin, m_title.c_str(), m_iconTitle.c_str(), 0);

    /* Выбираем события,  которые будет обрабатывать программа */
    XSelectInput(getDisplay(), m_wnd, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonReleaseMask | ButtonPressMask);
}

MainWindow::~MainWindow()
{
}


void MainWindow::show()
{
    XMapWindow(getDisplay(), m_wnd);
}

