#include "choose_course.h"
#include "ui_choose_course.h"

#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QStandardItemModel>

Choose_course::Choose_course(const QString& username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Choose_course)
{
    ui->setupUi(this);


    this->username = username;

    QStandardItemModel* course_model = new QStandardItemModel();

    ui->tableView->setModel(course_model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应


    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    // if (!db.open()) {
    //     QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
    //     return;
    // }
    QSqlQuery query;
    struct StudentCourseInfo {
        QString studentName;
        QString courseName;
        QString courseTime;
        QString coursePlace;
        QString courseTeacher;
    };
    QList<StudentCourseInfo> studentCourseList;
    query.exec("SELECT Student.studentname, Course.coursename, Course.coursetime, Course.courseplace, Course.courseteacher "
               "FROM Student "
               "JOIN Course ON Student.coursename = Course.coursename");


    while (query.next()) {
        StudentCourseInfo studentCourseInfo;
        studentCourseInfo.studentName = query.value(0).toString();
        studentCourseInfo.courseName = query.value(1).toString();
        studentCourseInfo.courseTime = query.value(2).toString();
        studentCourseInfo.coursePlace = query.value(3).toString();
        studentCourseInfo.courseTeacher = query.value(4).toString();

        // studentCourseList.append(studentCourseInfo);
        studentCourseList << studentCourseInfo;
        int row = 0; //行索引
        course_model->clear();
        for (const StudentCourseInfo& info : studentCourseList) {

            if(info.studentName == username)
            {

                QStringList table_h_headers;
                table_h_headers  << "课程名" << "任课教师" << "地点" << "上课时间"<< " ";//<< "课序号"<< dropcourse;

                course_model->setHorizontalHeaderLabels(table_h_headers);

                QStandardItem *itemName    = new QStandardItem(info.courseName);
                QStandardItem *itemTeacher = new QStandardItem(info.courseTeacher);
                QStandardItem *itemPlace   = new QStandardItem(info.coursePlace);
                QStandardItem *itemTime    = new QStandardItem(info.courseTime);


                course_model->setItem(row, 0, itemName);
                course_model->setItem(row, 1, itemTeacher);
                course_model->setItem(row, 2, itemPlace);
                course_model->setItem(row, 3, itemTime);

                QPushButton *choose_course = new QPushButton("选课");
                ui->tableView->setIndexWidget(course_model->index(course_model->rowCount()-1, 4),choose_course);


                ++row;
            }
        }
        db.close();
    }
}

Choose_course::~Choose_course()
{
    delete ui;
}
