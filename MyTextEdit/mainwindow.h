#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); 

    ~MainWindow();
public slots:
    void show_text_frame();
    void showTextBlock();
    void setTextFont(bool checked);

    void insertTable();
    void insertList();
    void insertImage();

    void textFind();
    void findNext();
private:
    Ui::MainWindow *ui;

    QDialog* findDialog;
    QLineEdit* lineEdit;
};
#endif // MAINWINDOW_H
