#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTextCursor>
#include <QAction>
#include <QToolBar>
#include <QDebug>
#include <QTextBlockFormat>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextDocument *doc= ui->textEdit->document();   //获取控件中的文档对象

    //修改文本框样式
    QTextFrame* root_frame = doc->rootFrame();  //获取根框架

    QTextFrameFormat format;    //创建一个框架
    format.setBorderBrush(Qt::blue);
    format.setBorder(3);    //边界
    root_frame->setFrameFormat(format);     //应用到根框架上


    //设置一个新的框架，用来修改光标处文本的样式
    QTextFrameFormat  frameFormat;
    frameFormat.setBackground(Qt::lightGray);   //文本背景
    frameFormat.setMargin(10);  //外边距
    frameFormat.setPadding(5);  //内边距
    frameFormat.setBorder(2);   //边框
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dashed);   //边框样式，断点

    //设置光标并在光标处插入框架
    QTextCursor cursor = ui->textEdit->textCursor();    //获取文本光标
    cursor.insertFrame(frameFormat);        //在光标处插入样式
    ui->textEdit->insertPlainText("inner text!\n");     //插入文本在框架中
    ui->textEdit->insertPlainText("Hello inner Text!\n");

    //设置往工具栏添加部件，使得根框架文本全部显示
    QAction* action_frame = new QAction("Frame",this);  //设置动作
    ui->toolBar->addAction(action_frame);               //往工具栏加入动作
    connect(action_frame,&QAction::triggered,this,&MainWindow::show_text_frame);

    //因为上一个会出现框架里面的文本无法进入的问题：
    QAction* action_text = new QAction("文本块",this);
    ui->toolBar->addAction(action_text);
    connect(action_text,&QAction::triggered,this,&MainWindow::showTextBlock);


    //直接设置文本块的样式，需要添加菜单，设置文本块的字体样式
    QAction* action_font = new QAction(tr("字体"), this);
    action_font->setCheckable(true);        //允许被选中

    connect(action_font, &QAction::toggled, this, &MainWindow::setTextFont);
    ui->toolBar->addAction(action_font);

    //插入表格列表图片
    QAction* action_textTable = new QAction(tr("表格"), this);
    ui->toolBar->addAction(action_textTable);
    connect(action_textTable, &QAction::triggered,this, &MainWindow::insertTable);

    QAction* action_textList = new QAction(tr("列表"), this);
    ui->toolBar->addAction(action_textList);
    connect(action_textList, &QAction::triggered,this, &MainWindow::insertList);

    QAction* action_textImage = new QAction(tr("图片"), this);
    ui->toolBar->addAction(action_textImage);
    connect(action_textImage, &QAction::triggered,this, &MainWindow::insertImage);


    //实现查找功能
    QAction* action_textFind = new QAction(tr("查找"), this);
    ui->toolBar->addAction(action_textFind);
    connect(action_textFind, &QAction::triggered, this, &MainWindow::textFind);


    findDialog = new QDialog(this);     //创建一个界面
    lineEdit = new QLineEdit(findDialog);       //把这个界面作为父类创建行编辑器
    QPushButton * btn = new QPushButton(findDialog);    //同时创建一个pushbtn
    btn->setText(tr("查找下一个"));

    connect(btn, &QPushButton::clicked, this, &MainWindow::findNext);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    findDialog->setLayout(layout);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_text_frame()
{
    auto* doc = ui->textEdit->document();
    auto* rootFrame = doc->rootFrame();  //获取根框架

    for(auto iter = rootFrame->begin(); iter != rootFrame->end(); iter++){

        auto cur_frame = iter.currentFrame();       //返回文本块外面的框架
        auto cur_block = iter.currentBlock();       //返回文本块

        if(cur_frame){
            qDebug() << "cur node is frame " ;
            //因为有一些文本写在框架里面，因此可以使用递归的方法将框架里面的文本获取 show_text_frame()

        } else if(cur_block.isValid()){ //文本块是否有效
            qDebug() << "cur node is text block ,text is " << cur_block.text();
        }

    }
}
//展示文本块内容
void MainWindow::showTextBlock()
{
    QTextDocument* document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();  //初始化文本块

    for(int i = 0; i < document->blockCount(); i++){
        qDebug() << tr("文本块%1, 文本块首行行号%2, 长度%3, 内容:%4").arg(i).arg(block.firstLineNumber())
                    .arg(block.length()).arg(block.text());

        block = block.next();
    }
}

//设置光标处插入字体样式
void MainWindow::setTextFont(bool checked)
{
    if(checked){
        QTextCursor cursor = ui->textEdit->textCursor();    //获取光标
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);  //文本块样式居中
        cursor.insertBlock(blockFormat);    //插入文本块样式

        QTextCharFormat charFormat;         //字符样式
        charFormat.setBackground(Qt::lightGray);    //背景颜色
        charFormat.setForeground(Qt::blue);            //字体颜色

        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));    //字体样式插入，加粗，true是斜体
        charFormat.setFontUnderline(true);          //有下划线
        cursor.setCharFormat(charFormat);           //将字体样式应用于光标处
        cursor.insertText(tr("插入字体"));          //同时插入文本
    }else{
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignLeft);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
//        charFormat.setBackground(Qt::white);
//        charFormat.setForeground(Qt::black);
//        charFormat.setFont(QFont(tr("微软雅黑"),12,QFont::Normal, false));
//        charFormat.setFontUnderline(false);
        cursor.setCharFormat(charFormat);
        cursor.insertText(tr("微软雅黑字体"));
    }
}


void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    //设置表格样式
    QTextTableFormat format;
    format.setCellSpacing(2);
    format.setCellPadding(10);
    cursor.insertTable(2,2,format);
}

void MainWindow::insertList(){
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage(){
    QTextImageFormat format;
    format.setName(":/img/head.jpg");   //设置图片样式的名称，即路径
    ui->textEdit->textCursor().insertImage(format);
    //ui->textEdit->textCursor是获取光标处,然后insertImage
}

void MainWindow::textFind(){
    findDialog->show();
}

void MainWindow::findNext(){
    QString string = lineEdit->text();

    bool isFind = ui->textEdit->find(string, QTextDocument::FindBackward);  //在textEdit上查找文本，向后查找(也就是向上查找)
    if(isFind){
        qDebug() << tr("行号:%1 列号:%2").arg(ui->textEdit->textCursor().blockNumber())
                    .arg(ui->textEdit->textCursor().columnNumber());
    }
}
