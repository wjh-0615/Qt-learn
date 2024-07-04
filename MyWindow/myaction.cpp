#include "myaction.h"
#include <QSplitter>
#include <QLabel>
MyAction::MyAction(QObject * parent):QWidgetAction(parent)
{
    //这个action要实现一个行编辑器和一个标签的东西
    lineEdit = new QLineEdit;
    // 将行编辑器的按下回车键信号和发送文本槽关联
    connect(lineEdit, &QLineEdit::returnPressed, this, &MyAction::sentText);

}

QWidget *MyAction::createWidget(QWidget *parent)
{
    if(!(parent->inherits("QMenu"))&& !(parent->inherits("QToolBar"))){ //如果不是菜单栏或者工具栏，就返回
       return 0;
    }
    QSplitter * spliter = new QSplitter(parent);    //设置容器部件
    QLabel * label = new QLabel;
    label->setText(tr("插入文本:"));
    spliter->addWidget(label);
    spliter->addWidget(lineEdit);
    return spliter;
}

void MyAction::sentText()
{
    emit getText(lineEdit->text());
    lineEdit->clear();
}
