#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myhighlighter.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto my_highlighter = new MyHighlighter(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

