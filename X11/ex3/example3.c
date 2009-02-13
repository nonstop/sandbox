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
    Display* display; /* ��������� �� ��������� ������� � */
    int scr_number; /* ���������� ������� ��� ���������� ���� */
    Window window; /* ���������� ������������ ���� */
    unsigned int display_width,
    display_height; /* ������ � ������ � ������� */
    unsigned int window_width,
    window_height; /* ������ � ������ ������ ���� */
    char *display_name = getenv("DISPLAY"); /* ��� � ������� */

    /* ������������� ���������� � � �������� */
    display = XOpenDisplay(display_name);
    if (display == NULL)
    {
        fprintf(stderr, "%s: �� ���� ����������� � � �������� '%s'\n",
                argv[0], display_name);
        exit(1);
    }

    /* �������� ��������� ������ �� ��������� ��� ������ ������� */
    scr_number = DefaultScreen(display);
    display_width = DisplayWidth(display, scr_number);
    display_height = DisplayHeight(display, scr_number);

    /* ������� ����� ���� */
    window_width = (display_width / 6);
    window_height = (display_height / 6);
    /* ������ � ����������� ����� */
    printf("������ ���� - '%d'; ������ - '%d'\n", window_width, window_height);

    /* ������� ������� ���� ��� ������ ������� ��������� ���� ������,  */
    /* ��������� ������ � ����� ����� � �������� ��������� � ��������, �*/
    /* �������� ����� ���� � ������� ����� ���� �� �������� ����������� */
    window = create_simple_window(display, window_width, window_height, 0, 0);

    XFlush(display);

    /* �������� ����� ������ ��������� */
    sleep(3);

    /* ������ ��������� �������� ���� */
    {
        int i;

        /* � ����� ��������� ���� */
        for (i = 0; i < 40; i++)
        {
            window_width -= 3;
            window_height -= 3;
            XResizeWindow(display, window, window_width, window_height);
            XFlush(display);
            usleep(20000);
        }

        /* � ����� ����������� ���� */
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

    /* ������ ����������� ���� */
    {
        int i;
        XWindowAttributes window_attr;
        int x, y;
        int scr_x, scr_y;
        Window child_window;
        /* ���������� ��� �������� ����������� ������������� ���� */
        Window parent_window;

        /* ������� �������� ������� �������� ���� */
        XGetWindowAttributes(display, window, &window_attr);

        x = window_attr.x;
        y = window_attr.y;

        /* ����� ������� ���� �������� */
        {
            /* ��� ���������� ����� ������� ���������� ��������� ���� */
            /* ������, �� ������� ���������� ���� ���� */
            Window root_window;
            /* ��� ���������� ����� ������� ������ ������������ */
            /* �������� ���� ������ ����, */
            Window* child_win;
            /* � ��� - �� ���������� */
            unsigned int num_child_win;

            /* �������� ������ ����������� �������� */
            XQueryTree(display, window,
                       &root_window,
                       &parent_window,
                       &child_win, &num_child_win);

            /* �� ������ ���������� ������ �������� ������������, */
            /* ��� ��� �� ��� ����������� ������� XQueryTree()  */
            XFree(child_win);
        }

        /* ����������� ��������� ���������� � ��������, ���������  */
        /* �������� ���� ��� ����, ������������ �������� ����������� */
        /* ����������. ��� �������� ������, ��� �������� ���� ������ */
        /*�������� ���� �����, � ��� ����� ������� ���� ���������  */
        /* � ����� ������� ����� ������               */
        XTranslateCoordinates(display,
                              parent_window, window_attr.root,
                              x, y,
                              &scr_x, &scr_y,
                              &child_window);

        /* ���������� ���� ����� */
        for (i = 0; i < 40; i++)
        {
            scr_x -= 3;
            XMoveWindow(display, window, scr_x, scr_y);
            XFlush(display);
            usleep(10000);
        }

        /* ���������� ���� ������ */
        for (i = 0; i < 40; i++)
        {
            scr_x += 3;
            XMoveWindow(display, window, scr_x, scr_y);
            XFlush(display);
            usleep(10000);
        }
    }

    sleep(1);

    /* ������ ������������ � �������������� ���� */
    {
        /* ����������� ���� */
        XIconifyWindow(display, window, DefaultScreen(display));
        XFlush(display);
        sleep(2);
        /* ��������������� ���� */
        XMapWindow(display, window);
        XFlush(display);
        sleep(2);
    }

    XFlush(display);

    /* �������� ��������� */
    sleep(2);

    /* ��������� ���������� � � �������� */
    XCloseDisplay(display);
    return 0;
}

