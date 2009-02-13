
#include <QtGui>

#include "TrayTest.h"

TrayTest::TrayTest()
{
    QLabel *l = new QLabel("");
    setCentralWidget(l);
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        fprintf(stderr, "can't tray :(\n");
        return;
    }
    if (!QSystemTrayIcon::supportsMessages())
    {
        fprintf(stderr, "messages not supported :(\n");
        return;
    }
    m_menu = new QMenu("");
    m_menu->addAction("close");

    m_ti = new QSystemTrayIcon(QIcon("relax.png"), this);
    m_ti->setContextMenu(m_menu);

    connect(m_ti, SIGNAL(messageClicked()), this, SLOT(onMsgClick()));
    connect(m_ti, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), 
            this, SLOT(onTrayAcivate(QSystemTrayIcon::ActivationReason)));
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(onClose(QAction*)));

    m_ti->show();
}

void TrayTest::onTrayAcivate(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick:
        isVisible() ? hide() : show();
        break;
    default:
        break;
    }
}

void TrayTest::onClose(QAction *)
{
    close();
}

void TrayTest::onMsgClick()
{
    show();
}

void TrayTest::closeEvent(QCloseEvent *event)
{
    if (isVisible())
    {
        fprintf(stderr, "hiding\n");
        m_ti->showMessage("title", "tray message");
    }
    else
    {
        delete m_ti;
        fprintf(stderr, "closing\n");
    }
    event->accept();
}

