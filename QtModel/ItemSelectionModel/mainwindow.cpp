#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel * model = new QStandardItemModel(7,4,this);
    for(int row=0; row < 7; row++){
        for(int column = 0; column < 4; column++){
            QStandardItem * item = new QStandardItem(QString("%1").arg(row*4+column));
            model->setItem(row, column, item);
        }
    }
    _table_view = new QTableView;
    _table_view->setModel(model);
    setCentralWidget(_table_view);
    this->resize(800,800);

    //获取视图的项目选择模型
    QItemSelectionModel * selection_model =  _table_view->selectionModel();
   //定义左上角和右下角的索引
    QModelIndex topLeft;
    QModelIndex bottomRight;
    //根据上面两个索引选择项目
    topLeft = model->index(1,1,QModelIndex());  //第1行1列,选择的item的索引，因为是根节点，就直接使用这个
    bottomRight = model->index(5,2,QModelIndex());  //第5行2列

    //设置选择区域
    QItemSelection selection(topLeft, bottomRight);
    //将选择的区域设置给选择模型, 枚举设置已选中的部分为选中状态
    selection_model->select(selection, QItemSelectionModel::Select);

    ui->mainToolBar->addAction(tr("当前项目"), this, &MainWindow::getCurrentItemData);
    ui->mainToolBar->addAction(tr("切换选择"), this, &MainWindow::toggleSelection);

    //选择模型的选中的条目更改后触发updateSelection函数
    connect(selection_model, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateSelection);

    //选择模型改变后，当前项目也会改变，触发changeCurrent函数
    connect(selection_model, &QItemSelectionModel::currentChanged, this, &MainWindow::changeCurrent);

    //设置view2，共用一个模型，实现效果同步
    QTableView * tableView2;
    tableView2 = new QTableView();
    tableView2->setWindowTitle("tableView2");
    tableView2->resize(400,300);
    tableView2->setModel(model);
    tableView2->setSelectionModel(selection_model);
    tableView2->show();
}

void MainWindow::getCurrentItemData(){      //获取当前模型选中的数据

   auto currentData = _table_view->selectionModel()->currentIndex().data().toString();      //根据当前模型的当前索引获取数据并转化为字符串
   qDebug() <<tr("当前项目的内容") << currentData;
}

void MainWindow::toggleSelection(){
    //找到根节点下第0行0列的item的索引
    QModelIndex topLeft = _table_view->model()->index(0,0,QModelIndex());

    auto max_row = _table_view->model()->rowCount(QModelIndex());           //获取根节点下最大的行号

    auto max_column = _table_view->model()->columnCount(QModelIndex());     //获取根节点下最大的列号
    //根据列号和行号获取最右下角的item的索引
    QModelIndex bottomRight = _table_view->model()->index(max_row-1, max_column-1, QModelIndex());
    //设置选择区域
    QItemSelection curSelection(topLeft, bottomRight);
    _table_view->selectionModel()->select(curSelection, QItemSelectionModel::Toggle);   //这里选择的模式是切换，没选中的就全被选中
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateSelection(const QItemSelection& selected, const QItemSelection& deselected){
    QModelIndex index;
    QModelIndexList list = selected.indexes();

    //为选中的条目设置显示选中的行列号
    for(int i =0; i < list.size(); i++){
        QString text = QString("(%1, %2)").arg(list[i].row()).arg(list[i].column());
        _table_view->model()->setData(list[i], text);
    }

    list = deselected.indexes();        //上一次被选中，这次未被选中的索引列表

    foreach(index, list){       //遍历每个未被选中的索引
        _table_view->model()->setData(index,"");
    }
}

void MainWindow::changeCurrent(const QModelIndex& current, const QModelIndex& previous){

    //当选中发生改变的时候，就会触发此函数，然后输出上一次索引的位置和这次的
    qDebug() << tr("move(%1, %2) to (%3, %4)").arg(previous.row())
              .arg(previous.column()).arg(current.row()).arg(current.column());

}

