#include "mainwindow.h"
#include <QApplication>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPixmap>
#include <QTreeView>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    //创建标准itemmodel
    QStandardItemModel model;

    //获取模型根项，根项不可见
    QStandardItem * parentItem = model.invisibleRootItem();

    //创建文本显示，图标，和工具显示
    QStandardItem * item0 = new QStandardItem();
    item0->setText("item0");

    //设置一个pixmap0作为图标
    QPixmap pixmap0(50,50);
    pixmap0.fill(Qt::red);
    item0->setIcon(pixmap0);

    item0->setToolTip("indexA");    //做一个显示提示，当鼠标放在上面的时候

    parentItem->appendRow(item0);   //往父节点加入当前项
    //将新的项设置为父节点项
    parentItem = item0;

    QStandardItem * item1 = new QStandardItem();
    item1->setText("item1");
    QPixmap pixmap1(50,50);
    pixmap1.fill(Qt::blue);
    item1->setIcon(pixmap1);
    item1->setToolTip("indexB");
    parentItem->appendRow(item1);

    //这里使用第二种方法进行设置，通过setdata和设置editRole的方法

    QStandardItem * item2 = new QStandardItem();
    item2->setData("item2",Qt::EditRole);
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    item2->setData(QIcon(pixmap2), Qt::DecorationRole);     //设置角色是装饰角色
    item2->setData("indexC",Qt::ToolTipRole);
    parentItem->appendRow(item2);

    //取出根节点第0行0列的item的模型索引
    QModelIndex indexA = model.index(0,0, QModelIndex());   //QModelIndex表示根节点的Index
    qDebug() << "model indexA row count is " << model.rowCount(indexA);     //看看indexA下面的行数

    //获取indexA节点下0行0列
    QModelIndex indexB = model.index(0,0,indexA);
    qDebug() << "indexB text is " << model.data(indexB,Qt::EditRole).toString();
    qDebug() << "indexB icon is " << model.data(indexB,Qt::DecorationRole);
    qDebug() << "indexB tool tip  is " << model.data(indexB,Qt::ToolTipRole).toString();
    //qDebug() << "indexB text is " << model.data(indexB,Qt::DisplayRole).toString();



    QTreeView view;
    view.setModel(&model);
    view.show();
    return a.exec();
}
