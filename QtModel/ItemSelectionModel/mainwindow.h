#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableView* _table_view;

public slots:
    void getCurrentItemData();
    void toggleSelection();
    void updateSelection(const QItemSelection& selected, const QItemSelection& deselected);
    void changeCurrent(const QModelIndex& current, const QModelIndex& previous);
};
#endif // MAINWINDOW_H
