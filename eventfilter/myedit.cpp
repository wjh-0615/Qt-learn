#include "myedit.h"
#include <QDebug>

MyEdit::MyEdit(QWidget *parent):QLineEdit(parent)
{

}

void MyEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"MyEdit key press event";

    QLineEdit::keyPressEvent(event);    //新构建的edit缺失了原本的功能，因此要在调用基类的keypress

    event->ignore();    //告诉系统，此事件没有被处理，因此继续传递给类似于父组件；否则会被拦截

}

bool MyEdit::event(QEvent *pevent)      //重写所有的事件处理器，优先处理的
{
    if(pevent->type() == QEvent::KeyPress){     //如果是按键事件，保证只重写原本的按键事件
        qDebug() << tr("my edit event") << endl;

        //return true;   //就会在这里停滞，父节点就不会触发
        //return false;     //依旧是在这里处理了按键事件，因此上面的keyPress就不会触发；但是会返回至父节点
    }

    return  QLineEdit::event(pevent);       //不是就调用原本的事件处理器，然后会把所有的子类事件都会触发，包括重写的
}
