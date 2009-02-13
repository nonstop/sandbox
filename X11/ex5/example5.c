#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#define X 0
#define Y 0
#define WIDTH 300
#define HEIGHT 300
#define WIDTH_MIN 100
#define HEIGHT_MIN 100
#define BORDER_WIDTH 5
#define TITLE "Draw line!"
#define ICON_TITLE "Draw line!"
#define PRG_CLASS "Draw line!"

/*
* SetWindowManagerHints - процедура передает информацию о
* свойствах программы менеджеру окон. 
*/

static void SetWindowManagerHints ( 
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

 if ( !XStringListToTextProperty (&ptrTitle, 1, &windowname ) ||
    !XStringListToTextProperty (&ptrITitle, 1, &iconname ) ) {
  puts ( "No memory!\n");
  exit ( 1 );
}

size_hints.flags = PPosition | PSize | PMinSize;
size_hints.min_width = win_wdt_min;
size_hints.min_height = win_hgt_min;
wm_hints.flags = StateHint | IconPixmapHint |
         InputHint;
wm_hints.initial_state = NormalState;
wm_hints.input = True;
wm_hints.icon_pixmap= pixmap;

class_hint.res_name = argv[0];
class_hint.res_class = PClass;

XSetWMProperties ( display, window, &windowname,
  &iconname, argv, argc, &size_hints, &wm_hints,
  &class_hint );
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
 int new_x, new_y,
     x = 0,
     y = 0;
 int button;
  
 /* Устанавливаем связь с сервером */
 if ( ( display = XOpenDisplay ( NULL ) ) == NULL ) {
  puts ("Can not connect to the X server!\n");
  exit ( 1 );
 }

 /* Получаем номер основного экрана */
 screen_number = DefaultScreen ( display );

 /* Создаем окно */
 window = XCreateSimpleWindow ( display,
     RootWindow ( display, screen_number ),
     X, Y, WIDTH, HEIGHT, BORDER_WIDTH,
     BlackPixel ( display, screen_number ),
     WhitePixel ( display, screen_number ) );

 /* Задаем рекомендации для менеджера окон */
 SetWindowManagerHints ( display, PRG_CLASS, argv, argc,
   window, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
   HEIGHT_MIN, TITLE, ICON_TITLE, 0 );

 /* Выбираем события, обрабатываемые программой */
 XSelectInput ( display, window, ExposureMask | KeyPressMask | ButtonPressMask |
		 ButtonReleaseMask | PointerMotionMask | Button1MotionMask | Button2MotionMask );

 /* Показываем окно */
 XMapWindow ( display, window );
 
 /* Цикл получения и обработки ошибок */
 while ( 1 ) {
  XNextEvent ( display, &report );
  gc = XCreateGC ( display, window, 0 , NULL );
  
  switch ( report.type ) {
    case Expose :
     /* Запрос на перерисовку */
     if ( report.xexpose.count != 0 )
      break;
    XDrawString( display, window, gc, 50, 50, "Push button to draw", strlen("Push button to draw") );  
    break;
     
    case ButtonPress:
	/* сохраняем координаты кнопки мыши в целых переменных */
    /* также сохраняем идентификатор окна, в котором была */
    /* нажата кнопка мыши                 */
     x = new_x;
     y = new_y;
     new_x = report.xbutton.x;
     new_y = report.xbutton.y;
     window = report.xbutton.window;
	 /* проверяем, какая из кнопок была нажата, */
    switch( report.xbutton.button) {
        case Button1:
		/* рисуем новую линию к позиции мыши */
	    XDrawLine( display, window, gc, x, y, new_x, new_y );
	    break;
        case Button3:
		/* очищаем экран */
	    XClearWindow( display, window );
	    XDrawString( display, window, gc, 50, 50, "Push button to draw or any key to exit",
	    strlen("Push button to draw or any key to exit") );  
	    break;
	default:
    	    break;
    }
    /*Не забывайте про отпускание кнопки*/
    case ButtonRelease:
    break;
    /*Выход при нажатии любой клавиши*/
    case KeyPress :
     XCloseDisplay ( display );
     exit ( 0 );
  }
  
 XFreeGC ( display, gc );
 }
return 0;
}


