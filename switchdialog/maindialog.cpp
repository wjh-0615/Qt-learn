#include "maindialog.h"
#include "ui_maindialog.h"
#include "childdialog.h"
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}


void MainDialog::on_pushButton_clicked()
{
    //需要实现功能是点击按钮，如果是acccpet，就关闭主界面，打开子界面；反之关闭
    //因此都会关闭主界面，先关闭
    close();    //也可以是this->hide();
    ChildDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        //其中dialog.exec()是一种阻塞机制，已经打开子界面，并等待用户操作
        this->show();
    }else{
        return;
    }
}
