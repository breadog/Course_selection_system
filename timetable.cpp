#include "timetable.h"
#include "ui_timetable.h"

Timetable::Timetable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timetable)
{
    ui->setupUi(this);


    QStandardItemModel* course_model = new QStandardItemModel();

    ui->tableView->setModel(course_model);
    QStringList table_h_headers;
    table_h_headers << "星期一" << "星期二" << "星期三" << "星期四"<< "星期五"<< "星期六"<< "星期日";

    course_model->setHorizontalHeaderLabels(table_h_headers);

    QStringList table_v_headers;
    table_v_headers << "08:25 10:00" << "10:25 12:00" << "14:30 16:05" << "16:30 18:00";

    course_model->setVerticalHeaderLabels(table_v_headers);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应

    // QTableWidgetItem *item0 = new QTableWidgetItem();
    // QTableWidgetItem *item1 = new QTableWidgetItem();
    // QTableWidgetItem *item2 = new QTableWidgetItem();

    // course_model->setItem(0, 0, item0);
    // course_model->setItem(0, 1, item1);
    // course_model->setItem(0, 2, item2);
    // course_model->setItem(0, 3, item3);


}

Timetable::~Timetable()
{
    delete ui;
}
