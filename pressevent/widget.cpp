#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);       //设置控件焦点状态，从而控件接收键盘焦点
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //判断是ctrl+M
    if(event->modifiers() == Qt::ControlModifier){  //判断是不是按下control键,而且这些修饰键必须使用modifiers
        if(event->key() == Qt::Key_M  && windowState() != Qt::WindowFullScreen){    //判断有没有按下M且是不是全屏
            setWindowState(Qt::WindowFullScreen);
            return;
        }
        return;
    }

    //如果按下的是ESC且是全屏
    if(event->key() == Qt::Key_Escape && windowState() == Qt::WindowFullScreen){
        setWindowState(Qt::WindowNoState);
        return;
    }


    bool b_upflag= false;
    bool b_downflag = false;
    bool b_leftflag = false;
    bool b_rightflag = false;

    //然后实现按下左键往左走之类的
    if(event->key()==Qt::Key_Up){
        if(event->isAutoRepeat()){      //如果一直重复按着不放
            auto curpos = ui->pushButton->pos();        //获取pushBtn的位置
            curpos.setY(curpos.y()-5);      //向上走5

            ui->pushButton->move(curpos);
            return;

        }else{      //如果不是重复按下
            b_upflag = true;
        }
    }

    if(event->key() == Qt::Key_Left){
           if(event->isAutoRepeat()){
               auto curpos = ui->pushButton->pos();
               curpos.setX(curpos.x()-5);
               ui->pushButton->move(curpos);
               return;
           }else{
               b_leftflag = true;
           }
       }

    if(event->key() == Qt::Key_Down){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setY(curpos.y()+5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_downflag = true;
        }
    }

    if(event->key() == Qt::Key_Right){
        if(event->isAutoRepeat()){
            auto curpos = ui->pushButton->pos();
            curpos.setX(curpos.x()+5);
            ui->pushButton->move(curpos);
            return;
        }else{
            b_rightflag = true;
        }
    }

    auto curpos = ui->pushButton->pos();
    if(b_upflag){
        curpos.setY(curpos.y()-5);
    }

    if(b_downflag){
        curpos.setY(curpos.y()+5);
    }

    if(b_leftflag){
        curpos.setX(curpos.x()-5);
    }

    if(b_rightflag){
        curpos.setX(curpos.x()+5);
    }

     ui->pushButton->move(curpos);



}

void Widget::keyReleaseEvent(QKeyEvent *event)
{

}

