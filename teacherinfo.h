#ifndef TEACHERINFO_H
#define TEACHERINFO_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>

namespace Ui {
class TeacherInfo;
}

class TeacherInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherInfo(const QString& username, int id, QWidget *parent = nullptr);
    ~TeacherInfo();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::TeacherInfo *ui;

    QString originalName;
    QString originalGender;
    QString originalEthnicity;
    QString originalTitle;
    QString originalDepartment;
    QString originalEmail;

    QString username;
    int id;
};

#endif // TEACHERINFO_H
