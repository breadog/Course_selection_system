#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QMainWindow>
#include "timetable.h"


namespace Ui {
class ChangePassword;
}

class ChangePassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangePassword(const QString& username,QWidget *parent = nullptr);
    ~ChangePassword();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    QString getUserPassword(QString &username);

private:
    Ui::ChangePassword *ui;

    QString username;
};

#endif // CHANGEPASSWORD_H
