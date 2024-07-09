#ifndef T_MAINWINDOW_H
#define T_MAINWINDOW_H

#include <QMainWindow>

#include "changepassword.h"
#include "widget.h"
#include "teacherinfo.h"
#include "teacher.h"
#include "showallstudent.h"
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
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

private:
    Ui::T_MainWindow *ui;
    ChangePassword *changePassword;
    TeacherInfo *teacherInfo;
//    Teacher *teacher;
    QString username;
    int id;
};

#endif // T_MAINWINDOW_H
