#ifndef SCWINDOW_H
#define SCWINDOW_H

#include <QMainWindow>

class QPushButton;
class QAction;
class SCWindow
    : public QMainWindow
{
    Q_OBJECT
public:
    SCWindow();
    virtual ~SCWindow();
private slots:
    void click();
private:
    QPushButton* m_btn;

    QAction *m_act1, *m_act2;
};

#endif /* SCWINDOW_H */

