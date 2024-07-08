#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>

namespace Ui {
class Teacher;
}

class Teacher : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher(const QString& username, int id, QWidget *parent = nullptr);
    ~Teacher();

private:
    Ui::Teacher *ui;

    QString username; //传过来的用户名
    int id;
};

#endif // TEACHER_H
