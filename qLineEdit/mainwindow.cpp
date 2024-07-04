#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QRegExpValidator>     //使用正则表达式过滤的头文件
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置ip地址的输入规则
    ui->IPedit->setEchoMode(QLineEdit::Normal);     //设置输入方式为普通
    QString ip_mask = "000.000.000.000;_";      //表示输入掩码的规则
    ui->IPedit->setInputMask(ip_mask);      //设置ip_mask规则为IPedit的限制输入规则

    //设置mac地址
    //  ui->macedit->setEchoMode(QLineEdit::Normal);    //默认就是普通模式
    QString mac_mask = "HH:HH:HH:HH:HH:HH;_";
    //输入定义掩码来验证是否有效
    ui->macedit->setInputMask(mac_mask);

    //设置密码规则
    ui->pwdedit->setEchoMode(QLineEdit::Password);  //设置输入为密码形式，也就是隐藏

    //设置邮箱输入规则
    //QString email_mask = //错误，需要使用正则表达式过滤
    QRegExp regx("[a-zA-Z0-9-_]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+");
    //有效输入格式为regx，然后ui->emailedit是将要应用的输入框，共同构成这个验证器
    QValidator* validator = new QRegExpValidator(regx,ui->emailedit);
    //输入验证器对象验证是否有效
    ui->emailedit->setValidator(validator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

