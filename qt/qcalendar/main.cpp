#include <QApplication>

#include "Calendar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Calendar main;
    main.show();
//    main.hide();

    return app.exec();
}
