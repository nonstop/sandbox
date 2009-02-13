#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <X11/Xlib.h>
#include <string>

class MainWindow
{
public:
    MainWindow(Window parent, const std::string & title, int width, int height);
    virtual ~MainWindow();

    void show();
private:
    int m_width;
    int m_height;
    int m_widthMin;
    int m_heightMin;
    int m_borderWidth;
    std::string m_title;
    std::string m_iconTitle;
    std::string m_prgClass;
    Display *m_display;
    Window m_wnd;
};


/*
 * #define WIDTH 200
#define HEIGHT 200
#define WIDTH_MIN 50
#define HEIGHT_MIN 50
#define BORDER_WIDTH 5
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"

 * */
#endif /* MAINWINDOW_H_ */

