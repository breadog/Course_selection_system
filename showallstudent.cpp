#include "showallstudent.h"
#include "ui_showallstudent.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QSqlError>

Showallstudent::Showallstudent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Showallstudent)
{
    ui->setupUi(this);

    QStandardItemModel* model_allstu = new QStandardItemModel();

    ui->tableView->setModel(model_allstu);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应

    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    QSqlQuery query;

    struct StudentCourseInfo {
        QString courseId;
        QString studentName;
        QString courseName;
        QString courseTime;
        QString coursePlace;
        QString courseTeacher;
        int courseScore;
    };
    QList<StudentCourseInfo> studentCourseList;

    query.exec("SELECT User.name AS studentName, Course.name AS courseName, Course.teacher, Course.place, Course.time, SC.score "
               "FROM SC "
               "JOIN User ON User.id = SC.student_id "
               "JOIN Course ON SC.course_id = Course.id;");

    while (query.next()) {
        StudentCourseInfo studentCourseInfo;

        studentCourseInfo.studentName = query.value(0).toString();
        studentCourseInfo.courseName = query.value(1).toString();
        studentCourseInfo.courseTeacher = query.value(2).toString();
        studentCourseInfo.coursePlace = query.value(3).toString();
        studentCourseInfo.courseTime = query.value(4).toString();
        studentCourseInfo.courseScore = query.value(5).toInt();

        studentCourseList << studentCourseInfo;

        int row = 0; //行索引
        model_allstu->clear();
        for (const StudentCourseInfo& info : studentCourseList) {

            QStringList table_h_headers;
            table_h_headers  << "学生姓名" << "课程名" << "任课教师" << "地点" << "上课时间"<< "成绩";

            model_allstu->setHorizontalHeaderLabels(table_h_headers);

            QStandardItem *itemStu     = new QStandardItem(info.studentName);
            QStandardItem *itemName    = new QStandardItem(info.courseName);
            QStandardItem *itemTeacher = new QStandardItem(info.courseTeacher);
            QStandardItem *itemPlace   = new QStandardItem(info.coursePlace);
            QStandardItem *itemTime    = new QStandardItem(info.courseTime);
            //QStandardItem *itemId      = new QStandardItem(info.courseId);
            QStandardItem *itemScore   = new QStandardItem(QString::number(info.courseScore));

            model_allstu->setItem(row, 0, itemStu);
            model_allstu->setItem(row, 1, itemName);
            model_allstu->setItem(row, 2, itemTeacher);
            model_allstu->setItem(row, 3, itemPlace);
            model_allstu->setItem(row, 4, itemTime);
            model_allstu->setItem(row, 5, itemScore);

            row++;
        }

    }
    db.close();
}
Showallstudent::~Showallstudent()
{
    delete ui;
}
