#ifndef CHOOSE_COURSE_H
#define CHOOSE_COURSE_H

#include <QWidget>

namespace Ui {
class Choose_course;
}

class Choose_course : public QWidget
{
    Q_OBJECT

public:
    explicit Choose_course(QWidget *parent = nullptr);
    ~Choose_course();

private:
    Ui::Choose_course *ui;
};

#endif // CHOOSE_COURSE_H
