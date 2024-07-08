#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QSettings>

#include "timetable.h"
namespace Ui {
class ChangePassword;
}

class ChangePassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = 0);
    ~ChangePassword();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //QString getCurrentUsernameFromDatabase();
    QString getUserPassword(QString &username);

    void on_pushButton_3_clicked();



private:
    Ui::ChangePassword *ui;
};

#endif // CHANGEPASSWORD_H
