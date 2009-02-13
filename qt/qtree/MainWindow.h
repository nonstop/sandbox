#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class QTreeWidget;

class MainWindow
    : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

private:
    QTreeWidget *tree;

    void initTree();
};

#endif /* PIMWINDOW_H_ */
