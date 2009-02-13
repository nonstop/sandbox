#include <X11/Xlib.h>
#include <stdlib.h>
#include <math.h>

int main() {
 Display *display;	
 GC gc;
 Window window;
 XEvent report;
 XGCValues gcValues;
 XFontStruct *font_info;
   
 if ( ( display = XOpenDisplay( NULL ) ) == NULL ) {
  puts ("Can not connect to the X server!\n");
  exit(1);
 }
 
 window = XCreateSimpleWindow( display, DefaultRootWindow( display ),
 	0, 0, 300, 300, 0,
	BlackPixel( display,DefaultScreen( display ) ),
	WhitePixel( display, DefaultScreen( display )) );
 
 XSelectInput( display, window, ExposureMask | KeyPressMask );
 XMapWindow( display, window );
 if ( ( font_info = XLoadQueryFont( display,
    "*charter-medium-i-*-25-240-*" )) == NULL ) {
    exit(1);
 }
 gc = XCreateGC( display, window, 0, NULL );
 XSetForeground( display, gc, BlackPixel( display,DefaultScreen(display) ) );
 XSetFont( display, gc, font_info->fid );
 
 while(KeyPress) {
   XNextEvent( display, &report );
 
 if ( report.xexpose.count != 0 ) {
 exit(0); 
 }     
 
 XDrawString( display, window, gc, 100, 60, "Example!", 8 );
 XDrawRectangle( display, window, gc, 50, 100, 200, 150 );
 XDrawArc( display, window, gc, 75, 100, 150, 150, 0, 360*64 );
 XDrawLine( display, window, gc, 50, 30, 250, 30 );
 gcValues.line_width = 10;
 XChangeGC( display, gc, GCLineWidth, &gcValues );
 XDrawLine( display, window, gc, 50, 80, 250, 80 );
 XFreeGC( display, gc );
 XUnloadFont( display, font_info->fid );
 }
 
 XCloseDisplay(display);
 return 0;
}
 
