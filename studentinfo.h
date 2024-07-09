#ifndef STUDENTINFO_H
#define STUDENTINFO_H

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
class StudentInfo;
}

class StudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfo(const QString& username, int id, QWidget *parent = nullptr);
    ~StudentInfo();

private slots:
    void on_save_clicked();

    void on_cancel_clicked();

private:
    Ui::StudentInfo *ui;

    QString originalName;
    QString originalGender;
    QString originalEthnicity;
    QString originalMajor;
    QString originalDepartment;
    QString originalClass;

    QString username;
    int id;

};

#endif // STUDENTINFO_H
