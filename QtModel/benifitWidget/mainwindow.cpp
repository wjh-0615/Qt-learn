#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置一个listWidget，widget是一个集成view和model
    auto listWidget = new QListWidget(this);
    QListWidgetItem * listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("listItem");

    QPixmap pixmap(50,50);
    pixmap.fill(Qt::blue);
    listWidgetItem->setIcon(pixmap);    //设置icon
    listWidgetItem->setToolTip("this is list item");

    listWidget->insertItem(0,listWidgetItem);   //在对应行插入item

    QListWidgetItem * listWidgetItem2 = new QListWidgetItem;
    listWidgetItem2->setText("listItem2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    listWidgetItem2->setData(Qt::DecorationRole,QIcon(pixmap2));
    listWidgetItem2->setToolTip("this is list item2");
    listWidget->insertItem(1,listWidgetItem2);

    listWidget->sortItems(Qt::DescendingOrder);     //对item进行排序并按照降序
    //展示listwidget
    listWidget->show();
    this->setCentralWidget(listWidget);

    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);       //设置list为单选模式

    listWidget->setDragEnabled(true);       //启用拖动

    listWidget->viewport()->setAcceptDrops(true);   //设置接受拖放

    listWidget->setDropIndicatorShown(true);        //设置显示将要放置的位置

    listWidget->setDragDropMode(QAbstractItemView::InternalMove);   //设置拖放模式为移动项目，如果不设置，则为复制项目




    //---------------------------------------//
    //设置_treeWidget
    _treeWidget = new QTreeWidget();

    _treeWidget->setColumnCount(2);     //设置列数
    QStringList headers;
    headers << "name" << "year";        //设置树头
    _treeWidget->setHeaderLabels(headers);

    //添加项目

    //父节点是_treeWidget
    QTreeWidgetItem * grade1 = new QTreeWidgetItem(_treeWidget);
    grade1->setText(0,"Grade1");
    //父节点是grade1
    QTreeWidgetItem * student = new QTreeWidgetItem(grade1);
    student->setText(0,"Tom");
    student->setText(1,"1996");

    //父节点是grade1, 在student之后
    QTreeWidgetItem * student2 = new QTreeWidgetItem(grade1, student);
    student2->setText(0,"Zack");
    student2->setText(1,"1988");

    //父节点是_treeWidget, 在grade1之后
    QTreeWidgetItem * grade2 = new QTreeWidgetItem(_treeWidget,grade1);
    grade2->setText(0,"Grade2");

    QTreeWidgetItem * student3 = new QTreeWidgetItem(grade1, student2);
    student3->setText(0,"Will");
    student3->setText(1,"1989");

    //删除student3
    auto *parent_student3 = student3->parent();             //先获取其父节点

    auto index_student3 = parent_student3->indexOfChild(student3);  //IndexofChild是返回孩子节点在父节点下的索引

    delete parent_student3->takeChild(index_student3);          //根据index删除父节点下的student3

    //删除grade2
    auto * parent_grade2 = grade2->parent();

    assert(parent_grade2 == nullptr);       //grade2为顶层节点，所以其父节点必为null

    auto index_grade2 = _treeWidget->indexOfTopLevelItem(grade2);   //对于顶层节点，通过treewidget获取grade2的index，输入item返回他的顶层索引

    delete _treeWidget->takeTopLevelItem(index_grade2);

    _treeWidget->show();



    //创建表格指定行号和列号
   _tableWidget =  new QTableWidget(3,2);
    //创建表格项目，将其插入到表格中
    QTableWidgetItem * tableWidgetItem = new QTableWidgetItem("qt");
    _tableWidget->setItem(1,1,tableWidgetItem);

    //创建表头
    QTableWidgetItem * headerV = new QTableWidgetItem("first");
    _tableWidget->setVerticalHeaderItem(0, headerV);
    QTableWidgetItem * headerH = new QTableWidgetItem("ID");
    _tableWidget->setHorizontalHeaderItem(0, headerH);
    _tableWidget->show();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow Destruction";
    delete ui;
    delete  _treeWidget;
    delete  _tableWidget;
}

