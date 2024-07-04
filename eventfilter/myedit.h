#ifndef MYEDIT_H
#define MYEDIT_H
#include <QLineEdit>
#include <QWidget>
#include <QKeyEvent>
class MyEdit:public QLineEdit
{
    Q_OBJECT
public:
    explicit MyEdit(QWidget *parent = nullptr);      //只允许显式调用

protected:
   void keyPressEvent(QKeyEvent *);     //按键事件
   bool event(QEvent * event);      //所有的事件处理器，重写他是不推荐的写法，推荐filter

signals:
    public slots:
};

#endif // MYEDIT_H
