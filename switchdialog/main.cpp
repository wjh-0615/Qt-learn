#include "maindialog.h"

#include <QApplication>
#include "childdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    ChildDialog dialog;
    //当点击childdialog的btn时，调用槽函数，退出是reject，返回到exec上是reject，因此直接子界面退出；
    //相反，进入主界面是accpet，因此显示w，也就是主界面
    if(dialog.exec()==QDialog::Accepted){
        w.show();
        return a.exec();
    }else{
        return 0;
    }

}
