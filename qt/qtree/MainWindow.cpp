#include <QtGui>
#include "MainWindow.h"

MainWindow::MainWindow()
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    tree = new QTreeWidget;
    tree->setAcceptDrops(true);
    tree->setDragEnabled(true);
    tree->setDragDropMode(QAbstractItemView::InternalMove);

    mainLayout->addWidget(tree);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("QTree");
    setMinimumSize(160, 160);
    resize(650, 400);

    initTree();
}

MainWindow::~MainWindow()
{}

void MainWindow::initTree()
{
    QTreeWidgetItem *tmp = new QTreeWidgetItem(QStringList("item 1"));
    tmp->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
    tree->addTopLevelItem(tmp);
    tree->addTopLevelItem(new QTreeWidgetItem(QStringList("item 2")));
    tree->addTopLevelItem(new QTreeWidgetItem(QStringList("item 3")));
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList("item 4"));
    tree->addTopLevelItem(item);
    tmp = new QTreeWidgetItem(QStringList("item 5"));
    tmp->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
    item->addChild(tmp);
    item->addChild(new QTreeWidgetItem(QStringList("item 6")));
    item->addChild(new QTreeWidgetItem(QStringList("item 7")));
}

