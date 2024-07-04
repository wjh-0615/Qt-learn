#include "childdialog.h"
#include "ui_childdialog.h"

ChildDialog::ChildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChildDialog)
{
    ui->setupUi(this);
    connect(ui->showMainWin,&QPushButton::clicked,this,&ChildDialog::sigshowChild);
    //connect(_parent,&ChildDialog::sigshowChild,this,&ChildDialog::showMainWin);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::showMainWin()
{
    this->hide();
    _parent->show();
}

void ChildDialog::sigshowChild()
{
    emit requestMainsig();  //发送请求主界面的信号
}
