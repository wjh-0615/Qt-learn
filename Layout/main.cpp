#include "login.h"
#include "register.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //将login转化为智能指针     Login w;
    std::shared_ptr<Login> w = make_shared<Login>();
    w->initSignals();

    w->show();
//    Register r;
//    r.show();
    return a.exec();
}
