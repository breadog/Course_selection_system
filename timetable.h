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

namespace Ui {
class Timetable;
}

class Timetable : public QWidget
{
    Q_OBJECT

public:
    explicit Timetable(const QString& username, QWidget *parent = nullptr);
    ~Timetable();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Timetable *ui;

    QString username; //传过来的用户名
};

#endif // TIMETABLE_H
