#include "childdialog2.h"
#include "ui_childdialog2.h"

childDialog2::childDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::childDialog2)
{
    ui->setupUi(this);
    connect(ui->showMainWin1,&QPushButton::clicked,this,&childDialog2::showMainsig);    //通过信号将请求进入主界面信号发送
    //点击请求主界面的按钮后，执行槽函数是传输请求函数
}

childDialog2::~childDialog2()
{
    delete ui;
}

void childDialog2::showMainsig()
{
    emit requestMainsig();
}
