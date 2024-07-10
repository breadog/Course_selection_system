#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>

namespace Ui {
class addstudent;
}

class addstudent : public QWidget
{
    Q_OBJECT

public:
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();

private slots:
    void on_comfirm_clicked();

    void on_execl_clicked();

private:
    Ui::addstudent *ui;
};

#endif // ADDSTUDENT_H
