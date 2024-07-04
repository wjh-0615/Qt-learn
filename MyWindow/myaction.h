#ifndef MYACTION_H
#define MYACTION_H

//首先自己定义动作类，需要继承自带的动作类
#include <QWidgetAction>
#include <QLineEdit>
#include <QObject>
class MyAction:public QWidgetAction
{
    Q_OBJECT
public:
    MyAction(QObject * parent = nullptr);

protected:
    //往菜单或工具栏中加入action就会调用这个函数，因此我们定义自己的动作就需要重写此函数
    virtual QWidget *createWidget(QWidget *parent);

signals:
    void getText(const QString& string);   //发送获取文本的信号

private:
    QLineEdit* lineEdit;

private slots:
    void sentText();
};

#endif // MYACTION_H
