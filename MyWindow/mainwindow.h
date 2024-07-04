#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void init_status_bar();
    ~MainWindow();

private slots:
    void on_actionshowdock_D_triggered();

    void on_actionN_triggered();
    void on_action_open_triggered();
public slots:
    void slot_set_text(const QString &string);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
