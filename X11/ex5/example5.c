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
* SetWindowManagerHints - ��������� �������� ���������� �
* ��������� ��������� ��������� ����. 
*/

static void SetWindowManagerHints ( 
 Display *  display, /*��������� �� ��������� Display */
 char *   PClass, /*����� ��������� */
 char *   argv[],   /*��������� ��������� */
 int     argc,    /*����� ���������� */
 Window   window,    /*������������� ���� */
 int     x,     /*���������� ������ �������� */
 int     y,     /*���� ���� */
 int     win_wdt,
 int     win_hgt,  /*������ � ������ ���� */
 int     win_wdt_min,
 int     win_hgt_min, /*����������� ������ � ������ ���� */
 char *   ptrTitle,  /*��������� ���� */
 char *   ptrITitle,/*��������� ����������� ���� */
 Pixmap   pixmap /*������� ����������� */
)
{
 XSizeHints size_hints; /*������������ � �������� ����*/

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
*main - �������� ��������� ���������
*/

int main(int argc, char *argv[])
{
 Display *display;  /* ��������� �� ��������� Display */
 int screen_number;    /* ����� ������ */
 GC gc;
 XEvent report;
 Window window;
 int new_x, new_y,
     x = 0,
     y = 0;
 int button;
  
 /* ������������� ����� � �������� */
 if ( ( display = XOpenDisplay ( NULL ) ) == NULL ) {
  puts ("Can not connect to the X server!\n");
  exit ( 1 );
 }

 /* �������� ����� ��������� ������ */
 screen_number = DefaultScreen ( display );

 /* ������� ���� */
 window = XCreateSimpleWindow ( display,
     RootWindow ( display, screen_number ),
     X, Y, WIDTH, HEIGHT, BORDER_WIDTH,
     BlackPixel ( display, screen_number ),
     WhitePixel ( display, screen_number ) );

 /* ������ ������������ ��� ��������� ���� */
 SetWindowManagerHints ( display, PRG_CLASS, argv, argc,
   window, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
   HEIGHT_MIN, TITLE, ICON_TITLE, 0 );

 /* �������� �������, �������������� ���������� */
 XSelectInput ( display, window, ExposureMask | KeyPressMask | ButtonPressMask |
		 ButtonReleaseMask | PointerMotionMask | Button1MotionMask | Button2MotionMask );

 /* ���������� ���� */
 XMapWindow ( display, window );
 
 /* ���� ��������� � ��������� ������ */
 while ( 1 ) {
  XNextEvent ( display, &report );
  gc = XCreateGC ( display, window, 0 , NULL );
  
  switch ( report.type ) {
    case Expose :
     /* ������ �� ����������� */
     if ( report.xexpose.count != 0 )
      break;
    XDrawString( display, window, gc, 50, 50, "Push button to draw", strlen("Push button to draw") );  
    break;
     
    case ButtonPress:
	/* ��������� ���������� ������ ���� � ����� ���������� */
    /* ����� ��������� ������������� ����, � ������� ���� */
    /* ������ ������ ����                 */
     x = new_x;
     y = new_y;
     new_x = report.xbutton.x;
     new_y = report.xbutton.y;
     window = report.xbutton.window;
	 /* ���������, ����� �� ������ ���� ������, */
    switch( report.xbutton.button) {
        case Button1:
		/* ������ ����� ����� � ������� ���� */
	    XDrawLine( display, window, gc, x, y, new_x, new_y );
	    break;
        case Button3:
		/* ������� ����� */
	    XClearWindow( display, window );
	    XDrawString( display, window, gc, 50, 50, "Push button to draw or any key to exit",
	    strlen("Push button to draw or any key to exit") );  
	    break;
	default:
    	    break;
    }
    /*�� ��������� ��� ���������� ������*/
    case ButtonRelease:
    break;
    /*����� ��� ������� ����� �������*/
    case KeyPress :
     XCloseDisplay ( display );
     exit ( 0 );
  }
  
 XFreeGC ( display, gc );
 }
return 0;
}


