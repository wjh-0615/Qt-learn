#include "login.h"
#include "ui_login.h"
#include <register.h>
using namespace std;
Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::initSignals()   //让登录类有注册类
{
    _register = make_shared<Register>();    //相当于login有了register，初始化了一个注册类
    //让登录类和注册类有了关联
    _register->set_login(shared_from_this());   //返回login的一个智能指针，和之前引用login的共享一个
    //和set_login成员函数关联，然后register中也就有了_login，share_from_this相当于填入login类
}


void Login::on_pushButton_clicked()
{
    this->close();
    _register->show();
}
