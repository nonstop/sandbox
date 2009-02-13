#include <QtGui>
#include "SCWindow.h"

SCWindow::SCWindow()
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    
    m_btn = new QPushButton("Push me");
    mainLayout->addWidget(m_btn, 1);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Qt shortcuts"));
    setMinimumSize(160, 160);

    connect(m_btn, SIGNAL(clicked(bool)), this, SLOT(click()));

    m_act1 = new QAction(this);
    m_act1->setShortcut(QKeySequence("Ctrl+1"));
    connect(m_act1, SIGNAL(triggered()), this, SLOT(click()));
    
    m_act2 = new QAction(this);
    m_act2->setShortcut(QKeySequence("Ctrl+2"));
    connect(m_act2, SIGNAL(triggered()), this, SLOT(click()));

    centralWidget->addAction(m_act1);
    centralWidget->addAction(m_act2);
}

SCWindow::~SCWindow()
{
}

void SCWindow::click()
{
    QMessageBox::information(this, "Hi", "click", QMessageBox::Ok);
}

int main(int ac, char *av[])
{
    QApplication app(ac, av);

    SCWindow main;
    main.show();
    
    return app.exec();
}

