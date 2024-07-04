#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QTextCodec>
#include <QTextStream>
//我们想要做到主窗口接收拖拽事件，然后在textedit中显示出文件内容
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);       //允许主窗口接收放下事件
    ui->textEdit->setAcceptDrops(false);    //textEdit禁用拖动的放下事件

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //拖动操作中，数据在mimeData中，hasUrls检查是否存在url列表，也即是否存在数据
    if(event->mimeData()->hasUrls()){
        //主窗口接收动作
        event->acceptProposedAction();  //这个方法是通知该拖动操作在目标区域(主窗口)是有效的，且该区域接收
    }
    else{
        //忽略动作
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData * mimeData = event->mimeData();
    //如果存在文件
    if(mimeData->hasUrls()){
        //获取文件数据url列表
        QList<QUrl> urlList = mimeData->urls();
        //将第一个匹配为本地文件路径
        QString filename = urlList[0].toLocalFile();

        if(!filename.isEmpty()){
            QTextCodec *codec=QTextCodec::codecForName("UTF-8");    //返回指针,指针用于指向，处理UTF-8的字节
            QTextCodec::setCodecForLocale(codec);
            //创建file对象并将文件路径传给他
            QFile file(filename);       //创建QFile对象并关联此文件
            //打开文件失败
            if(!file.open(QIODevice::ReadOnly)){
                return;
            }

            //打开成功
            QTextStream in(&file);    //将file对象传入数据流这个类
            //qDebug()<< "in readall is " << in.readAll() << endl;

            //从数据流类中读取里面的内容并将其写入textEdit中
            ui->textEdit->setText(in.readAll());
        }

    }else{
        event->ignore();
    }

}

