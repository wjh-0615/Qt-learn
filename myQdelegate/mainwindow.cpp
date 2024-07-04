#include "mainwindow.h"
#include "ui_mainwindow.h"
# include <QStandardItemModel>  //添加标准模型
#include <QTableView>
# include"spinboxdelegate.h"    //引入我们自己设置的代理
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建一个模型，模型负责管理和存储数据
    auto* model = new QStandardItemModel(7,4,this);     //这个就是创建一个7行4列的标准模型，并且显示窗口为，也就是父窗口是mainwindow
    //对模型进行填数
    for(int row=0;row<7;row++){
        for(int col=0;col<4;col++){
            QStandardItem * item=new QStandardItem(QString("%1").arg(row*4+col));
            //其中Qstring 为占字符，.arg是将占位符%替换为arg里面的数字，item是一个单元格
            model->setItem(row,col,item);
        }
    }
    //创建TableView并且将模型加载，这些是视图，用来展示数据
    QTableView* _table_view = new QTableView(this);
    _table_view->setModel(model);
    //在窗口的中央部件中显示
    setCentralWidget(_table_view);
    this->resize(600,600);

//-----------------------------------//
//-----------------------------------//
    //创建第二个独立的模型
    auto* model2 = new QStandardItemModel(7,4,this);     //这个就是创建一个7行4列的标准模型，并且显示窗口为，也就是父窗口是mainwindow
    //对模型进行填数
    for(int row=0; row<7; row++){
        for(int col=0; col<4; col++){
            QStandardItem * item = new QStandardItem(QString("%1").arg(row*4+col));
            //其中Qstring 为占字符，.arg是将占位符%替换为arg里面的数字
            model2->setItem(row, col, item);
        }
    }

    //创建TableView并且将模型加载
    _table_view2 = new QTableView();    //设置为mainwindow成员
    _table_view2->setModel(model2);
    //_table_view2->setModel(true);     //和Dialog是不同的

    //这里就是与第一个方法不同，通过自己设置的代理spinbox进行对_table的数修改

    auto* delegate = new SpinBoxDelegate(this);

    //设置代理，委托delegate负责编辑和绘制数据
    _table_view2->setItemDelegate(delegate);    //将自定义的委托 delegate 设置为 _table_view2 的项委托
    _table_view2->show();
    _table_view2->resize(800,800);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _table_view2;
}

