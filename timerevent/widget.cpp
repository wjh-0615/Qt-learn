#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QPalette>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //这是第一种定时器设计方法
//    id1 = startTimer(1000);     //启动定时器功能
//    id2 = startTimer(1500);
//    id3 = startTimer(2000);

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_lcd);   //定时器会发出timeout信号
    timer->start(1000);     //类似于1s发出一个timeout信号
}

Widget::~Widget()
{
    delete ui;
}


//定时器事件回调函数
void Widget::timerEvent(QTimerEvent* event){

    //判断触发的timer是哪一个
    if(event->timerId() == id1){
        qDebug() << "id1 timer triggerd" << endl;
    }

    if(event->timerId() == id2){
        qDebug() << "id2 timer triggerd" << endl;
    }

    if(event->timerId() == id3){
        qDebug() << "id3 timer triggerd" << endl;
    }
}

void Widget::slot_update_lcd(){

      QTime time = QTime::currentTime();        //获取当前时间

      QString text = time.toString("hh:mm:ss");     //将time换成字符串显示h,min,s

      if(time.second()%2 == 0){   //获取当前秒数%2，中间的:变为空格，也就是实现:每秒闪烁的功能
        text[5] = ' ';
      }
      //设置lcd的样式
      QPalette palette = ui->lcdNumber->palette();
      ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
      palette.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
      ui->lcdNumber->setPalette(palette);

      ui->lcdNumber->setDigitCount(text.length());      //把lcd的显示数字长度设置为字符串长度从而达到时分秒都显示

      //把时间的文本打印上lcd中
      ui->lcdNumber->display(text);
}
