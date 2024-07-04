#ifndef CHILDDIALOG2_H
#define CHILDDIALOG2_H

#include <QDialog>

namespace Ui {
class childDialog2;
}

class childDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit childDialog2(QWidget *parent = nullptr);
    ~childDialog2();
signals:
    void requestMainsig();
private:
    Ui::childDialog2 *ui;
public slots:
    void showMainsig();
};

#endif // CHILDDIALOG2_H
