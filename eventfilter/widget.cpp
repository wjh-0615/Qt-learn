#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTextEdit>
#include <QSpinBox>
#include <QWheelEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    line_edit_ = new MyEdit(this);
    line_edit_->move(100,100);
    //然后调用自己的事件过滤器
    line_edit_->installEventFilter(this);   //安装父节点上的事件过滤器，也就是写的那个
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent * event){      //重写按键点击事件
    qDebug()<<"Widget key press event" << endl;
}

//验证;如果滚轮事件那里是false，然后这里重写widget的滚轮，抛给上层后就会打印像上面的东西

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == line_edit_){       //如果对象是自己实现的edit
        if(event->type() == QEvent::KeyPress){      //同时事件类型是按键事件，type取到事件类型
            qDebug() << "widget eventfilter catch line_edit" << endl;       //

            return false;       //line_edit的按键事件并不停滞，依旧交给同层的按键，然后触发同层的ignore，然后交给上层，触发keyPressEvent
        }           //这里是因为同层有个ignore，因此不需要在这个类的后面加上return false就能返回上层
    }

    if(watched == ui->textEdit){
        if(event->type()==QEvent::Wheel){       //如果这是一个滚轮事件
            QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);     //将Qevent类型强制转化，这样就可以调用QWheel相关的函数

            if(wheelEvent->delta() > 0){
                //向近滚动
                qDebug()<<"catch wheel event delta > 0"<<endl;
                ui->textEdit->zoomIn();    //把他缩小
            }else{
                qDebug()<<"catch wheel event delta < 0"<<endl;
                ui->textEdit->zoomOut();    //把他放大
            }
            return true;    //textEdit的滚轮就此停滞，不交给同层其他的滚轮事件处理了
            //return false;
        }
        return false;       //让text的其他事件可以去上层处理，但上层没有重写这个东西，因此不会触发widget上的qdebug
    }

    if(watched == ui->spinBox){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);

            if(keyevent->key()==Qt::Key_Space){
                ui->spinBox->setValue(0);

                return true;
            }
            return false;       //如果是其他按键，继续交给同层的其他按键对应方法处理
        }
        return false;       //这个对象的其他东西会返回到上层，因此上层的按键重写就会触发
    }

    return QWidget::eventFilter(watched, event);
}
