#include "addstudent.h"
#include "ui_addstudent.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtXlsx>
#include <QFileDialog>
#include <QDebug>
addstudent::addstudent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addstudent)
{
    ui->setupUi(this);


}

addstudent::~addstudent()
{
    delete ui;
}

void addstudent::on_comfirm_clicked()
{

    int     stuid         = ui->id->text().toInt();
    QString stuname       = ui->name->text();
    QString stugender     = ui->gender->text();
    QString studepartment = ui->department->text();
    QString stuclass      = ui->class_2->text();
    QString stumajor      = ui->major->text();
    QString stueth        = ui->ethnicit->text();

    //连接数据库
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbPath);

    //验证数据库是否打开
    if (!database.open()) {
        QMessageBox::critical(nullptr, "错误", "无法打开数据库: " + database.lastError().text());
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Student(student_id,name,gender,department,class,major,ethnicity) "
                  "VALUES (:student_id,:name,:gender,:department,:class,:major,:ethnicity); " );

    query.bindValue(":student_id", stuid);
    query.bindValue(":name", stuname);
    query.bindValue(":gender", stugender);
    query.bindValue(":department", studepartment);
    query.bindValue(":class", stuclass);
    query.bindValue(":major", stumajor);
    query.bindValue(":ethnicity", stueth);


    //成功提醒

    if (query.exec()) {
        QMessageBox::information(nullptr, "成功", "学生信息插入成功！");
    } else {
        QMessageBox::critical(nullptr, "错误", "插入失败: " + query.lastError().text());
    }

    // 关闭数据库连接
    database.close();
}


void addstudent::on_execl_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择Excel文件"), "", tr("Excel文件 (*.xlsx)"));

    QXlsx::Document xlsx(filePath);
    QXlsx::Workbook *workBook = xlsx.workbook();
    QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

    if (workSheet) {  // 检查工作表是否加载成功
        ulong xlsxrows = workSheet->dimension().rowCount();  // 读取文件行数
        //ulong xlsxcloums = workSheet->dimension().columnCount();  // 读取文件列数

        QSqlQuery query;

        for (ulong row = 2; row <= xlsxrows; row++) {
            QString id = workSheet->read(row, 1).toString();
            QString name = workSheet->read(row, 2).toString();
            QString gender = workSheet->read(row, 3).toString();
            QString department = workSheet->read(row, 4).toString();
            QString className = workSheet->read(row, 5).toString();
            QString major = workSheet->read(row, 6).toString();
            QString ethnicity = workSheet->read(row, 7).toString();

            qDebug() << "ID:" << id;
            qDebug() << "姓名:" << name;
            qDebug() << "性别:" << gender;
            qDebug() << "院系:" << department;
            qDebug() << "班别:" << className;
            qDebug() << "专业:" << major;
            qDebug() << "民族:" << ethnicity;


            query.prepare("INSERT INTO Student (student_id, name, gender, department, class, major, ethnicity) "
                          "VALUES (:id, :name, :gender, :department, :className, :major, :ethnicity);" );
            query.bindValue(":id", id);
            query.bindValue(":name", name);
            query.bindValue(":gender", gender);
            query.bindValue(":department", department);
            query.bindValue(":className", className);
            query.bindValue(":major", major);
            query.bindValue(":ethnicity", ethnicity);

            if (!query.exec()) {
                qDebug() << "插入失败：" << query.lastError().text();
                QMessageBox::critical(this, tr("插入失败"), tr("数据插入失败：") + query.lastError().text());
            } else {
                QMessageBox::information(this, tr("插入成功"), tr("数据插入成功"));
            }
        }
    } else {
        qDebug() << "Excel 文件加载失败";
        QMessageBox::critical(this, tr("加载失败"), tr("Excel 文件加载失败"));
    }

}

