#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QObject>
#include "myedit.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //让widget也可以按键事件实现
    void keyPressEvent(QKeyEvent *);

    bool eventFilter(QObject* watched, QEvent* event);       //事件过滤器，优先级最最高,如果对象是要重写的，就去重写

private:
    Ui::Widget *ui;
    MyEdit* line_edit_;
};
#endif // WIDGET_H
