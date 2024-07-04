#include "register.h"
#include "ui_register.h"
#include "login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    //设置最大最小界面固定界面
    this->setMaximumSize(QSize(300,350));
    this->setMinimumSize(QSize(300,350));

    auto vbox_layout = new QVBoxLayout();   //设置垂直布局
    //设置spacer并加入垂直布局
    auto verticalSpacer1 = new QSpacerItem(40,20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    vbox_layout->addItem(verticalSpacer1);


    QSpacerItem *name_item1 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Minimum); //设置最左边的水平spacer
    //设置邮箱标签和edit并加入水平布局
    QLabel * name_label = new QLabel();
    name_label->setText("邮箱:");
    QLineEdit * name_edit = new QLineEdit();    //填写邮箱editor

    //创建水平布局并将水平弹簧和邮箱的标签的editor加入
    auto name_layout = new QHBoxLayout();
    name_layout->addItem(name_item1);
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_edit);

    QSpacerItem *name_item2 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Minimum); //设置最右边的水平spacer
    //在最右边加入水平弹簧
    name_layout->addItem(name_item2);

    vbox_layout->addLayout(name_layout);        //然后将整个邮箱的水平布局加入到大的垂直布局中


    //
    //这里开始是密码
    //设置密码水平布局
    auto pwd_layout = new QHBoxLayout();
    QLabel * pwd_label = new QLabel();
    pwd_label->setText("密码:");
    QLineEdit * pwd_edit = new QLineEdit();
    //垂直布局的弹簧并加入
    auto verticalSpacer2 = new QSpacerItem(40,20, QSizePolicy::Maximum, QSizePolicy::Maximum);
    vbox_layout->addItem(verticalSpacer2);


    QSpacerItem *pwd_item2 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *pwd_item1 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    pwd_layout->addItem(pwd_item1);     //最左边的弹簧加入
    pwd_layout->addWidget(pwd_label);
    pwd_layout->addWidget(pwd_edit);
    pwd_layout->addItem(pwd_item2);     //最右边的弹簧加入
    vbox_layout->addLayout(pwd_layout);     //将密码的水平布局加入大的垂直布局

    auto verticalSpacer3 = new QSpacerItem(40,30, QSizePolicy::Fixed, QSizePolicy::Maximum);
    vbox_layout->addItem(verticalSpacer3);      //弹簧3并加入垂直布局

    //加入水平布局并将左右两边弹簧加入
    QSpacerItem* reg_btn_item1 = new QSpacerItem(150,20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    auto* _reg_btn = new QPushButton();
    _reg_btn->setText("注册");
    auto regbtn_layout = new QHBoxLayout();
    regbtn_layout->addItem(reg_btn_item1);
    regbtn_layout->addWidget(_reg_btn,5);
    QSpacerItem* reg_btn_item2 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    regbtn_layout->addItem(reg_btn_item2);
    vbox_layout->addLayout(regbtn_layout);

    auto verticalSpacer4 = new QSpacerItem(40,20, QSizePolicy::Fixed, QSizePolicy::Expanding);
    vbox_layout->addItem(verticalSpacer4);
    this->setLayout(vbox_layout);

    connect(_reg_btn,&QPushButton::clicked,this,&Register::slot_register);

}

Register::~Register()
{
    delete ui;
}

void Register::set_login(const weak_ptr<Login> &login)
{
    _login = login;     //赋值
}

void Register::slot_register()
{
    this->close();

    auto shared_login = _login.lock();  //因为_login为弱指针，因此无法直接show出来
    shared_login->show();
}
