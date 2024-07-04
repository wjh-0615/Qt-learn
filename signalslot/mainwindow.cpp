#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childdialog.h"
#include "childdialog2.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _child_dialog = new ChildDialog(this);
    _child_dialog2 = new childDialog2(this);
    connect(ui->showChildwin1,&QPushButton::clicked,this,&MainWindow::showChildDialog);     //进入子界面
    connect(_child_dialog,&ChildDialog::requestMainsig,this,&MainWindow::sigshowMain);

    //将2的界面的传输数据放到这里来处理
    connect(ui->showChildwin2,&QPushButton::clicked,this,&MainWindow::showChildDialog2);     //进入子界面
    connect(_child_dialog2,&childDialog2::requestMainsig,this,&MainWindow::sigshowMain2);
    //个人理解：在2.cpp将信号从按钮传到界面2上，之后在这里的第二句通过信号传到主界面，然后执行main中的显示main

}

MainWindow::~MainWindow()
{
    delete ui;
    if(_child_dialog){
            delete  _child_dialog;
            _child_dialog = nullptr;
        }
}

//void MainWindow::onButtonClicked()
//{
//    emit requestChildsig();         //发送信号
//}
void MainWindow::showChildDialog() {
    _child_dialog->show();
    this->hide();
}
void MainWindow::sigshowMain()
{
    this->show();
    _child_dialog->hide();
}

//第二个子界面
void MainWindow::showChildDialog2() {
    _child_dialog2->show();
    this->hide();
}
void MainWindow::sigshowMain2()
{
    this->show();
    _child_dialog2->hide();
}

