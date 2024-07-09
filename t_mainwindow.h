#ifndef T_MAINWINDOW_H
#define T_MAINWINDOW_H

#include <QMainWindow>

#include "widget.h"
#include "changepassword.h"
// #include "coursemanagement.h"
// #include "userinfo.h"
// #include "studentmanagement.h"
#include "teacher.h"

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

    void on_toolButton_6_triggered(QAction *arg1);

private:
    Ui::T_MainWindow *ui;

    Teacher *teacherCourse;
    UserInfo *userInfo;
    // StudentManagement *studentManagement;
    // CourseManagement *courseManagement;
    ChangePassword *changePassword;

    QString username;

    int id;
};


#endif // T_MAINWINDOW_H
