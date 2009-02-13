#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


Window create_simple_window(Display* display, int width, int height, int x, int y)
{
    int scr_number = DefaultScreen(display);
    int win_border_width = 2;
    Window window;

    window = XCreateSimpleWindow(display, RootWindow(display, scr_number),
                                 x, y, width, height, win_border_width,
                                 BlackPixel(display, scr_number),
                                 WhitePixel(display, scr_number));

    XMapWindow(display, window);
    XFlush(display);

    return window;
}


int main(int argc, char* argv[])
{
    Display* display; /* указатель на структуру дисплея Х */
    int scr_number; /* количество экранов для размещения окон */
    Window window; /* дескриптор создаваемого окна */
    unsigned int display_width,
    display_height; /* высота и ширина Х дисплея */
    unsigned int window_width,
    window_height; /* высота и ширина нового окна */
    char *display_name = getenv("DISPLAY"); /* имя Х дисплея */

    /* устанавливаем соединение с Х сервером */
    display = XOpenDisplay(display_name);
    if (display == NULL)
    {
        fprintf(stderr, "%s: не могу соединиться с Х сервером '%s'\n",
                argv[0], display_name);
        exit(1);
    }

    /* получаем геометрию экрана по умолчанию для нашего дисплея */
    scr_number = DefaultScreen(display);
    display_width = DisplayWidth(display, scr_number);
    display_height = DisplayHeight(display, scr_number);

    /* создаем новое окно */
    window_width = (display_width / 6);
    window_height = (display_height / 6);
    /* печать в стандартный вывод */
    printf("ширина окна - '%d'; высота - '%d'\n", window_width, window_height);

    /* создаем простое окно как прямой потомок корневого окна экрана,  */
    /* используя черный и белый цвета в качестве основного и фонового, и*/
    /* размещая новое окно в верхнем левом углу по заданным координатам */
    window = create_simple_window(display, window_width, window_height, 0, 0);

    XFlush(display);

    /* отдохнем после трудов праведных */
    sleep(3);

    /* пример изменения размеров окна */
    {
        int i;

        /* в цикле уменьшаем окно */
        for (i = 0; i < 40; i++)
        {
            window_width -= 3;
            window_height -= 3;
            XResizeWindow(display, window, window_width, window_height);
            XFlush(display);
            usleep(20000);
        }

        /* в цикле увеличиваем окно */
        for (i = 0; i < 40; i++)
        {
            window_width += 3;
            window_height += 3;
            XResizeWindow(display, window, window_width, window_height);
            XFlush(display);
            usleep(20000);
        }
    }

    sleep(1);

    /* пример перемещения окна */
    {
        int i;
        XWindowAttributes window_attr;
        int x, y;
        int scr_x, scr_y;
        Window child_window;
        /* переменная для хранения дескриптора родительского окна */
        Window parent_window;

        /* вначале получаем текущие атрибуты окна */
        XGetWindowAttributes(display, window, &window_attr);

        x = window_attr.x;
        y = window_attr.y;

        /* затем находим окно родителя */
        {
            /* эта переменная будет хранить дескриптор корневого окна */
            /* экрана, на котором отображено наше окно */
            Window root_window;
            /* эта переменная будет хранить массив дескрипторов */
            /* дочерних окон нашего окна, */
            Window* child_win;
            /* а эта - их количество */
            unsigned int num_child_win;

            /* выполним запрос необходимых значений */
            XQueryTree(display, window,
                       &root_window,
                       &parent_window,
                       &child_win, &num_child_win);

            /* мы должны освободить список дочерних дескрипторов, */
            /* так как он был динамически выделен XQueryTree()  */
            XFree(child_win);
        }

        /* Транслируем локальные координаты в экранные, используя  */
        /* корневое окно как окно, относительно которого выполняется */
        /* трансляция. Это работает потому, что корневое окно всегда */
        /*занимает весь экран, и его левый верхний угол совпадает  */
        /* с левым верхним углом экрана               */
        XTranslateCoordinates(display,
                              parent_window, window_attr.root,
                              x, y,
                              &scr_x, &scr_y,
                              &child_window);

        /* перемещаем окно влево */
        for (i = 0; i < 40; i++)
        {
            scr_x -= 3;
            XMoveWindow(display, window, scr_x, scr_y);
            XFlush(display);
            usleep(10000);
        }

        /* перемещаем окно вправо */
        for (i = 0; i < 40; i++)
        {
            scr_x += 3;
            XMoveWindow(display, window, scr_x, scr_y);
            XFlush(display);
            usleep(10000);
        }
    }

    sleep(1);

    /* пример сворачивания и восстановления окна */
    {
        /* сворачиваем окно */
        XIconifyWindow(display, window, DefaultScreen(display));
        XFlush(display);
        sleep(2);
        /* восстанавливаем окно */
        XMapWindow(display, window);
        XFlush(display);
        sleep(2);
    }

    XFlush(display);

    /* короткая передышка */
    sleep(2);

    /* закрываем соединение с Х сервером */
    XCloseDisplay(display);
    return 0;
}

