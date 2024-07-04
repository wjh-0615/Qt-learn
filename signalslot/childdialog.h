#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>

namespace Ui {
class ChildDialog;
}

class ChildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChildDialog(QWidget *parent = nullptr);
    ~ChildDialog();
signals:
    void requestMainsig();

private:
    Ui::ChildDialog *ui;
    QWidget* _parent;
public slots:
    void showMainWin();
    void sigshowChild();
};

#endif // CHILDDIALOG_H
