#ifndef T_MAINWINDOW_H
#define T_MAINWINDOW_H

#include <QMainWindow>

#include "changepassword.h"
#include "widget.h"
#include "teacherinfo.h"
#include "teacher.h"
#include "showallstudent.h"
#include "addstudent.h"

namespace Ui {
class T_MainWindow;
}

class T_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit T_MainWindow(const QString& username,int id,QWidget *parent = 0);
    ~T_MainWindow();

private slots:


    void on_personinfo_clicked();

    void on_teachinfo_clicked();

    void on_courseinfo_clicked();

    void on_passwordalter_clicked();

    void on_exit_clicked();

    void on_addstu_clicked();

private:
    Ui::T_MainWindow *ui;
    ChangePassword *changePassword;
    TeacherInfo *teacherInfo;
//    Teacher *teacher;
    Showallstudent * showAllStudent;
    addstudent *studentManagement;

    QString username;
    int id;
};

#endif // T_MAINWINDOW_H
