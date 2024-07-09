#ifndef S_MAINWINDOW_H
#define S_MAINWINDOW_H

#include <QMainWindow>

#include "widget.h"
#include "changepassword.h"
#include "choose_course.h"
#include "schooltimetable.h"
#include "studentinfo.h"
#include "timetable.h"

namespace Ui {
class S_MainWindow;
}

class S_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit S_MainWindow(const QString& username,int id,QWidget *parent = 0);
    ~S_MainWindow();

private slots:
    void on_studentInfo_clicked();

    void on_chooseCourse_clicked();

    void on_myCourse_clicked();

    void on_changePassword_clicked();


    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();

    void on_courseChosen_clicked();

private:
    Ui::S_MainWindow *ui;

    ChangePassword *changePassword;
    Choose_course * chooseCourse;
    schooltimetable *sctable;
    StudentInfo *studentInfo;
    Timetable *timetable;

    QString  username;
    int id;
};

#endif // S_MAINWINDOW_H
