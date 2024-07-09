#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "choose_course.h"
#include "changepassword.h"
#include "schooltimetable.h"

namespace Ui {
class Timetable;
}

class Timetable : public QWidget
{
    Q_OBJECT

public:
    explicit Timetable(const QString& username, int id, QWidget *parent = nullptr);
    ~Timetable();

private slots:

    void Drop_a_course();

    void on_ChooseCourse_clicked();

    void on_backtomain_clicked();

    void on_refresh_clicked();

    void on_alterpassword_clicked();

    void on_mycourse_clicked();

private:
    Ui::Timetable *ui;

    QString username; //传过来的用户名
    int id;
};

#endif // TIMETABLE_H
