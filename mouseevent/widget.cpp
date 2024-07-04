#include "widget.h"
#include "ui_widget.h"
#include <QCursor>
#include <QPixmap>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QWheelEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建光标对象
    QCursor cursor;
    //修改鼠标形状
    cursor.setShape(Qt::OpenHandCursor);
    //设置鼠标
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //如果是鼠标左键按下
    if(event->button() == Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);      //设置鼠标样式
        QApplication::setOverrideCursor(cursor);    //使用现有鼠标样式覆盖原有

        offset = event->globalPos() - pos();        //鼠标全局位置1-窗口左上角的位置

    }else if(event->button() == Qt::RightButton){
        //QCursor cursor(QPixmap("://../../../head.png"));    //使用图片加载鼠标样式
        QCursor cursor(Qt::SizeAllCursor);
        QApplication::setOverrideCursor(cursor);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //释放事件,重设鼠标样式
    QApplication::restoreOverrideCursor();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << "event button is " << event->button() << endl;
        qDebug() << "window state is " << windowState() << endl;

        //如果窗口不是全屏状态，就将窗口全屏
        if(windowState() != Qt::WindowFullScreen){
            setWindowState(Qt::WindowFullScreen);
        }else{
            setWindowState(Qt::WindowNoState);
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //移动过程中判断鼠标是左键点击并且移动，那么要用buttons，返回的是鼠标状态的集合
    if(event->buttons() & Qt::LeftButton){
        //获取窗口应当移动到的位置
        QPoint windowpos = event->globalPos() - offset;     //鼠标的全局位置2-偏移量=移动后的相较于之前偏移量的偏移量
        this->move(windowpos);
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    qDebug() << "catch wheel event " << endl;
    //鼠标滚动远离使用者放大textedit
    if(event->delta() > 0){
        qDebug() << "catch wheel event delta > 0" << endl;
        ui->textEdit->zoomIn();
    }else {
        qDebug() << "catch wheel event delta < 0" << endl;
        ui->textEdit->zoomOut();
    }
}
