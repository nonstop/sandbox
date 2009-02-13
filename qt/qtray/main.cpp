#include <QApplication>

#include "TrayTest.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TrayTest main;
    main.show();
//    main.hide();

    return app.exec();
}
