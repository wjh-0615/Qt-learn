#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ChildDialog;
class childDialog2;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void requestChildsig();
private:
    Ui::MainWindow *ui;
    ChildDialog* _child_dialog;
    childDialog2* _child_dialog2;

public slots:
    void showChildDialog();
    void sigshowMain();

    void showChildDialog2();
    void sigshowMain2();
    //void onButtonClicked();
};
#endif // MAINWINDOW_H
