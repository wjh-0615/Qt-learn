#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Register;
class Login : public QDialog,public std::enable_shared_from_this<Login>     //允许其他智能指针共享Login
        //不然可能出现两个引用login，导致两个都释放的时候内存重复释放崩溃
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void initSignals();     //初始化信号和槽的函数

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    std::shared_ptr<Register> _register;
};
#endif // LOGIN_H
