
#include <QtGui>

#include "Calendar.h"

Calendar::Calendar()
{
    QCalendarWidget* cw = new QCalendarWidget;
    cw->setFirstDayOfWeek(Qt::Monday);
    setCentralWidget(cw);
}

Calendar::~Calendar()
{}

