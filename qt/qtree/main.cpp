
#include <QApplication>

#include "MainWindow.h"

int main(int ac, char* av[])
{
    QApplication app(ac, av);

    MainWindow *main  = new MainWindow;
    main->show();

    return app.exec();
}

