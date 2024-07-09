#include "studentinfo.h"
#include "ui_studentinfo.h"

StudentInfo::StudentInfo(const QString& username, int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentInfo)
{
    ui->setupUi(this);
}

StudentInfo::~StudentInfo()
{
    delete ui;
}
