#ifndef REGISTER_H
#define REGISTER_H
#include <memory>
#include <QDialog>
using namespace std;
class Login;    //因为注册完后要回到登录，因此设置login类，方便使用
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void set_login(const weak_ptr<Login>& login);  //加载了login
public slots:
    void slot_register();

private:
    Ui::Register *ui;
    std::weak_ptr<Login> _login;    //这里设置弱引用，防止两个都来回析构，陷入死锁
};

#endif // REGISTER_H
