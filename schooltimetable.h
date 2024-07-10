#ifndef SCHOOLTIMETABLE_H
#define SCHOOLTIMETABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class schooltimetable;
}

class schooltimetable : public QWidget
{
    Q_OBJECT

public:
    explicit schooltimetable(const QString& username, int id, QWidget *parent = 0);
    ~schooltimetable();

private slots:
    void on_refresh_clicked();

private:
    Ui::schooltimetable *ui;

    QString username; //传过来的用户名
    int id;
};

#endif // SCHOOLTIMETABLE_H
