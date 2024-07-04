#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    //创建splitter，可以拖动分隔条调整子控件大小
    QSplitter* splitter = new QSplitter;


    //先文件系统模型
    QFileSystemModel * model = new QFileSystemModel;
    //这个模型同时需要一个路径作为模型的根路径
    model->setRootPath(QDir::currentPath());        //设置当前目录为文件系统模型的根目录，定义了模型可以显示的最大范围

    //显示1
    QTreeView * tree = new QTreeView(splitter);
    tree->setModel(model);
    //显示模型的哪一级目录？根据当前目录取到model的index，并且把索引设置到tree的根索引上
    tree->setRootIndex(model->index(QDir::currentPath()));      //定义了视图实际显示的起点


    //显示2
    QListView * list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->resize(1000,800);
    splitter->show();

    return a.exec();
}
