#ifndef TRAYTEST_H
#define TRAYTEST_H

#include <QMainWindow>
#include <QSystemTrayIcon>

class QCloseEvent;
class QMenu;
class QAction;

class TrayTest
    : public QMainWindow
{
Q_OBJECT
public:
    TrayTest();
    virtual ~TrayTest()
    {}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void onMsgClick();
    void onClose(QAction*);
    void onTrayAcivate(QSystemTrayIcon::ActivationReason);
private:
    QSystemTrayIcon *m_ti;
    QMenu *m_menu;
};


#endif /* TRAYTEST_H */

