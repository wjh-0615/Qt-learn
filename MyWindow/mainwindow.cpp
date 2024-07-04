#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextEdit>
#include <QMdiSubWindow>
#include "myaction.h"
#include <QToolButton>     //这个是工具栏的具体
#include <QToolBar>     //这个就是工具栏
#include <QSpinBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //在menubar上添加一个menu
    QMenu* editMenu = ui->menubar->addMenu(tr("编辑(&E)"));
    editMenu->addSeparator();   //添加分隔符
    QAction * action_Open = editMenu->addAction(QIcon(":/img/head.png"), tr("打开文件(&O)"));   //设置menu的动作
    action_Open->setShortcut(QKeySequence("Ctrl+O"));   //设置这个动作的快捷键
    //连接动作和界面，执行槽函数
    connect(action_Open,&QAction::triggered, this, &MainWindow::on_action_open_triggered);

    //为菜单栏添加动作组，这是一个组，因此只能一个
    QActionGroup * group = new QActionGroup(this);
    QAction* action_L = group->addAction(tr("左对齐(&L)"));
    action_L->setCheckable(true);   //可选中的状态
    QAction* action_R = group->addAction(tr("右对齐(&L)"));
    action_R->setCheckable(true);
    QAction* action_C = group->addAction(tr("居中(&L)"));
    action_C->setCheckable(true);

    editMenu->addSeparator();       //加上分隔符
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);

    //使用自己定义的动作类
    MyAction * action = new MyAction(this);
    editMenu->addAction(action);
    connect(action, &MyAction::getText, this, &MainWindow::slot_set_text);
    //接收到信号的时候，这个信号所携带的信息，也会被槽函数接收

    //设置工具栏按钮
    QToolButton* toolBtn = new QToolButton(this);
    toolBtn->setText(tr("颜色"));

    QMenu* colorMenu = new QMenu(this);     //颜色按钮的目录

    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));         //加入动作

    toolBtn->setMenu(colorMenu);            //往按钮上加入颜色目录
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);    //设置按钮打开方式
    ui->toolBar->addWidget(toolBtn);        //往工具栏上添加按钮

   QSpinBox* spinbox = new QSpinBox(this);
   ui->toolBar->addSeparator();
   ui->toolBar->addWidget(spinbox);

   //设置状态栏的东西
   init_status_bar();

}

void MainWindow::init_status_bar()  //通过函数来将状态栏初始化
{
    //显示临时消息
    ui->statusbar->showMessage(tr("欢迎使用多文档编辑器"),2000);  //这里是直接显示消息，代表显示2S

    //显示永久状态栏，创建标签
    QLabel* permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);     //这是标签的样式
    permanent->setText("llfc.club");
    ui->statusbar->addPermanentWidget(permanent);   //这是一种永久显示标签的添加方式
    //ui->statusbar->addWidget(permanent);  //这种会被临时消息覆盖导致不显示
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionshowdock_D_triggered()
{
    ui->dockWidget_2->show();
}

void MainWindow::on_actionN_triggered()
{
    qDebug() << "新建文件..." << endl;
    QTextEdit * textEdit = new QTextEdit(this);
    auto childWindow = ui->mdiArea->addSubWindow(textEdit);
    childWindow->setWindowTitle(tr("文本编辑子窗口"));
    childWindow->show();
}

void MainWindow::on_action_open_triggered()
{
    qDebug() << "打开文件..." << endl;
}

void MainWindow::slot_set_text(const QString &string)
{
    ui->textEdit->setText(string);  //这里设置槽函数是把接收到的文本显示在textEdit上
}


