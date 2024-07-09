#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>

#include "enter_scores.h"
#include "widget.h"
#include "showallstudent.h"
namespace Ui {
class Teacher;
}

class Teacher : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher(const QString& username, int id, QWidget *parent = nullptr);
    ~Teacher();

private slots:
    void Give_score();


    void on_backtomain_clicked();

    void on_refresh_clicked();

    void on_showallstu_clicked();

    void on_addstu_clicked();

private:
    Ui::Teacher *ui;

    QString username; //传过来的用户名
    int id;

};

#endif // TEACHER_H
