#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QWidget>

namespace Ui {
class StudentInfo;
}

class StudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfo(const QString& username, int id, QWidget *parent = nullptr);
    ~StudentInfo();

private:
    Ui::StudentInfo *ui;

    QString username;
    int id;

};

#endif // STUDENTINFO_H
