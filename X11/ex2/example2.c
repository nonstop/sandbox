#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define X 0
#define Y 0
#define WIDTH 250
#define HEIGHT 200
#define WIDTH_MIN 150
#define HEIGHT_MIN 100
#define BORDER_WIDTH 5
#define TITLE "Press button!"
#define ICON_TITLE "Press button!"
#define PRG_CLASS "Press button!"

/*
* SetWindowManagerHints - процедура передает информацию о
* свойствах программы менеджеру окон.
*/

static void SetWindowManagerHints(
    Display *  display, /*Указатель на структуру Display */
    char *   PClass, /*Класс программы */
    char *   argv[],   /*Аргументы программы */
    int     argc,    /*Число аргументов */
    Window   window,    /*Идентификатор окна */
    int     x,     /*Координаты левого верхнего */
    int     y,     /*угла окна */
    int     win_wdt,
    int     win_hgt,  /*Ширина и высота окна */
    int     win_wdt_min,
    int     win_hgt_min, /*Минимальные ширина и высота окна */
    char *   ptrTitle,  /*Заголовок окна */
    char *   ptrITitle,/*Заголовок пиктограммы окна */
    Pixmap   pixmap /*Рисунок пиктограммы */
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
    wm_hints.flags = StateHint | IconPixmapHint |
                     InputHint;
    wm_hints.initial_state = NormalState;
    wm_hints.input = True;
    wm_hints.icon_pixmap = pixmap;

    class_hint.res_name = argv[0];
    class_hint.res_class = PClass;

    XSetWMProperties(display, window, &windowname,
                     &iconname, argv, argc, &size_hints, &wm_hints,
                     &class_hint);
}

/*
*main - основная процедура программы
*/

int main(int argc, char *argv[])
{
    Display *display;  /* Указатель на структуру Display */
    int screen_number;    /* Номер экрана */
    GC gc;
    XEvent report;
    Window window;

    /* Устанавливаем связь с сервером */
    if ((display = XOpenDisplay(NULL)) == NULL)
    {
        puts("Can not connect to the X server!\n");
        exit(1);
    }

    /* Получаем номер основного экрана */
    screen_number = DefaultScreen(display);

    /* Создаем окно */
    window = XCreateSimpleWindow(display,
                                 RootWindow(display, screen_number),
                                 X, Y, WIDTH, HEIGHT, BORDER_WIDTH,
                                 BlackPixel(display, screen_number),
                                 WhitePixel(display, screen_number));

    /* Задаем рекомендации для менеджера окон */
    SetWindowManagerHints(display, PRG_CLASS, argv, argc,
                          window, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
                          HEIGHT_MIN, TITLE, ICON_TITLE, 0);

    /* Выбираем события, обрабатываемые программой */
    XSelectInput(display, window, ExposureMask | ButtonPressMask
                 | ButtonReleaseMask | KeyPressMask);

    /* Показываем окно */
    XMapWindow(display, window);

    /* Цикл получения и обработки ошибок */
    while (1)
    {
        XNextEvent(display, &report);
        gc = XCreateGC(display, window, 0 , NULL);
        XSetForeground(display, gc, BlackPixel(display, 0));

        switch (report.type)
        {
        case Expose :
            /* Запрос на перерисовку */
            if (report.xexpose.count != 0)
                break;

            XDrawString(display, window, gc, 25, 50, "Press button or any key to exit!",
                        strlen("Press button or any key to exit!"));
            break;

        case ButtonPress :
            XClearWindow(display, window);
            XSetWindowBackground(display, window, rand());
            XDrawString(display, window, gc, 50, 50, "Press!", strlen("Press!"));
            break;

        case ButtonRelease :
            XClearWindow(display, window);
            XSetWindowBackground(display, window, rand());
            XDrawString(display, window, gc, 50, 50, "Release!", strlen("Release!"));
            break;

        case KeyPress :
            XCloseDisplay(display);
            exit(0);
        }
        XFreeGC(display, gc);
    }
    return 0;
}
