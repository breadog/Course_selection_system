#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

#include "timetable.h"
#include "teacher.h"
#include "t_mainwindow.h"
#include "s_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void Login();
private:
    Ui::Widget *ui;

    // Timetable *table;
};
#endif // WIDGET_H
