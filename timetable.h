#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>

namespace Ui {
class Timetable;
}

class Timetable : public QWidget
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = nullptr);
    ~Timetable();

private:
    Ui::Timetable *ui;
};

#endif // TIMETABLE_H
