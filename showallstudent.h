#ifndef SHOWALLSTUDENT_H
#define SHOWALLSTUDENT_H

#include <QWidget>

namespace Ui {
class Showallstudent;
}

class Showallstudent : public QWidget
{
    Q_OBJECT

public:
    explicit Showallstudent(QWidget *parent = nullptr);
    ~Showallstudent();

private:
    Ui::Showallstudent *ui;
};

#endif // SHOWALLSTUDENT_H
