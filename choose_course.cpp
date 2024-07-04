#include "choose_course.h"
#include "ui_choose_course.h"

Choose_course::Choose_course(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Choose_course)
{
    ui->setupUi(this);


}

Choose_course::~Choose_course()
{
    delete ui;
}
