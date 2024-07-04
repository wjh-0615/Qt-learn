#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QWizard>  //向导管理器
#include <QLabel>   //页中加入新的类似标签
#include <QVBoxLayout>  //引入布局管理器
#include <QButtonGroup>     //引入按钮组
#include <QRadioButton>     //引入单选按钮
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//颜色对话框
void MainWindow::on_colorbtn_clicked()
{
    QColorDialog colordlg(Qt::blue,this);    //通过QColor来创建颜色dialog
    colordlg.setOption(QColorDialog::ShowAlphaChannel);
    colordlg.exec();
    QColor color = colordlg.currentColor();
    qDebug() << "color is " << color;

}

//文件对话框
void MainWindow::on_textbtn_clicked()
{
    //文本对话框需要初始化一个默认路径，因为它本质上就是打开一个文件
    QString path = QDir::currentPath();     //返回当前文件所在路径

    QString title = tr("文件对话框");    //设置打开路径界面的标题
    QString filter = tr("文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)");     //过滤器
    //这里执行的是打开文件对话框并获取文件名的操作，同时这是一个阻塞方法
    QString aFileName=QFileDialog::getOpenFileName(this,title,path,filter);

    // 检查用户是否选择了一个文件
//        if (!aFileName.isEmpty()) {
//            QMessageBox::information(this, "Selected File", aFileName);
//        } else {
//            QMessageBox::information(this, "No File Selected", "You did not select any file.");
//        }
    qDebug() << aFileName << endl;
}

//条目对话框
void MainWindow::on_pushButton_clicked()
{
    QStringList items;
    bool ok=false;
    items<<tr("条目1")<<tr("条目2");
    //把items传入，0表示停在第一个,true表示可以编辑，返回ok
    auto itemData = QInputDialog::getItem(this,tr("条目对话框"),tr("输入或选择"),items,0,true,&ok);
    if(ok){
        qDebug()<< "item is" << itemData << endl;
    }
}


//提示对话框，使用QMessageBox
void MainWindow::on_pushButton_2_clicked()
{

    //各个对话框类型都有自己的具体函数实现

    auto ret = QMessageBox::question(this,tr("提问对话框"),tr("你是单身吗"),QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){
        qDebug() << "ret is " << ret << endl;
    }else{
        return;
    }

    auto ret2 = QMessageBox::information(this,tr("通知对话框"),tr("你好单身狗"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok){
        qDebug() << "ret2 is " << ret2 << endl;
    }else{
        return;
    }

    //警告对话框
    auto ret3 = QMessageBox::warning(this,tr("警告对话框"),tr("你最好找个地方发泄一下"),QMessageBox::Ok);
    if(ret3 == QMessageBox::Ok){
        qDebug() << "ret3 is " << ret3 << endl;
    }else{
        return;
    }


    auto ret4 = QMessageBox::critical(this,tr("关键提示对话框"), tr("我梦寐以求是真爱和自由"),QMessageBox::Ok);
    if(ret4 == QMessageBox::Ok){
        qDebug() << "ret4 is " << ret4 << endl;
    }
}

//进度对话框
void MainWindow::on_pushButton_3_clicked()
{

    //设置创建一个进度对话框,具体对象功能搜索
    _progressdialog = new QProgressDialog(tr("正在复制"),tr("取消复制"),0,5000,this);
    //设置对话框标题
    _progressdialog->setWindowTitle(tr("复制对话框"));
    //设置对话框模态显示
    _progressdialog->setWindowModality(Qt::ApplicationModal);

    //设置计时器用于演示对话框进度
    _timer = new QTimer(this);

    //连接计时器信号和对话框演示,信号是一个超时信号
    connect(_timer,&QTimer::timeout,this,&MainWindow::on_updateProgressDialog);
    //还要设置取消复制的信号导致进度对话框取消
    connect(_progressdialog,&QProgressDialog::canceled,this,&MainWindow::on_cancelProgressDialog);

    _timer->start(2);
}

//实现超时后更新的槽函数
void MainWindow::on_updateProgressDialog()
{
    _count++;
    if(_count>5000){
        _timer->stop();
        delete _timer;
        _timer = nullptr;
        delete _progressdialog;
        _progressdialog = nullptr;
        _count=0;
        return;
    }
    _progressdialog->setValue(_count);
}

//取消槽函数
void MainWindow::on_cancelProgressDialog()
{
    _timer->stop();
    delete  _timer;
    _timer = nullptr;
    delete _progressdialog;
    _progressdialog = nullptr;
    _count = 0;
    return;
}

//向导对话框
void MainWindow::on_pushButton_4_clicked()
{
    auto* wizard = new QWizard(this);
    wizard->setWindowTitle(tr("五常游戏副本"));

    //做向导页的页面1
    auto* page1 = new QWizardPage();
    page1->setTitle(tr("副本指引"));

    //为了布局完美，引入布局管理器，用于垂直排列窗口
    QVBoxLayout *layout = new QVBoxLayout();

    //创建标签并添加到布局
    auto* label1=new QLabel();
    label1->setText(tr("五常副本难度极大，请谨慎选择！"));
    layout->addWidget(label1);

    //设置页面的布局
    page1->setLayout(layout);

    //把页面添加到向导页中
    wizard->addPage(page1);

    //做页面2
    auto* page2 = new QWizardPage();
    page2->setTitle(tr("请选择你要挑战的五常副本"));

    //因为要选择，所以在页面2引入一个按钮组
    auto* group = new QButtonGroup(page2);
    auto* btn1= new QRadioButton(tr("怒海狂涛"));
    auto* btn2= new QRadioButton(tr("凛冬将至"));
    auto* btn3= new QRadioButton(tr("雾都孤儿"));
    auto* btn4= new QRadioButton(tr("铁塔尚在"));
    auto* btn5= new QRadioButton(tr("长城守望"));

    //将各个按钮加入
    group->addButton(btn1);
    group->addButton(btn2);
    group->addButton(btn3);
    group->addButton(btn4);
    group->addButton(btn5);

    //设置垂直布局
    auto* layout2 = new QVBoxLayout();
    //或者使用循环加入
    //for(int i = 0; i < group->buttons().size(); i++){
            //layout2->addWidget(group->buttons()[i]);
        //}

    layout2->addWidget(btn1);
    layout2->addWidget(btn2);
    layout2->addWidget(btn3);
    layout2->addWidget(btn4);
    layout2->addWidget(btn5);

    page2->setLayout(layout2);

    //把页面加入向导页
    wizard->addPage(page2);
    //页面3
    QWizardPage* page3 = new QWizardPage();
    page3->setTitle(tr("副本生成"));
    auto* label3 = new QLabel();
    label3->setText(tr("祝您挑战副本顺利"));

    auto* layout3 = new QVBoxLayout();
    layout3->addWidget(label3);
    page3->setLayout(layout3);
    wizard->addPage(page3);

    wizard->show();
    wizard->exec();
}

//文本输入对话框
void MainWindow::on_pushButton_5_clicked()
{
    bool ok = false;
    auto text = QInputDialog::getText(this, tr("文字输入对话框"), tr("请输入用户的姓名"), QLineEdit::Normal, tr("admin"), &ok);
    if(ok){
        qDebug() << text << endl;
    }
}

//整型输入对话框
void MainWindow::on_pushButton_6_clicked()
{
    bool ok = false;
    //标题，输入数字，开始数字200，最小数字-200，最大数字400，每次10
    auto intdata = QInputDialog::getInt(this,tr("数字输入对话框"),tr("请输入数字"),200,-200,400,10,&ok);
    if(ok){
        qDebug() << intdata << endl;
    }
}
