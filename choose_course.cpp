#include "choose_course.h"
#include "ui_choose_course.h"

#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QSqlError>
#include <QDebug>

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

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    QSqlQuery query;


    struct StudentCourseInfo {
        QString studentName;
        QString courseName;
        QString courseTime;
        QString coursePlace;
        QString courseTeacher;
    };

    QList<StudentCourseInfo> studentCourseList;
    query.prepare("SELECT DISTINCT c.coursename, c.coursetime, c.time, c.courseteacher, c.courseplace "
                  "FROM Course c "
                  "LEFT JOIN Student s ON c.coursename = s.coursename "
                  "WHERE s.studentname IS NULL OR s.studentname != :username");
    query.bindValue(":username", username);
    query.exec();
    //course_model->setColumnCount(4); // 设置模型的列数为4


    while (query.next()) {
        StudentCourseInfo studentCourseInfo;
        // studentCourseInfo.studentName = query.value(0).toString();
        // studentCourseInfo.courseName = query.value(1).toString();
        // studentCourseInfo.courseTime = query.value(2).toString();
        // studentCourseInfo.coursePlace = query.value(3).toString();
        // studentCourseInfo.courseTeacher = query.value(4).toString();

        studentCourseInfo.courseName = query.value(0).toString();
        studentCourseInfo.courseTime = query.value(1).toString();
        //studentCourseInfo. = query.value(2).toString();
        studentCourseInfo.courseTeacher = query.value(3).toString();
        studentCourseInfo.coursePlace = query.value(4).toString();

        studentCourseList << studentCourseInfo;


        int row = 0; //行索引
        course_model->clear();

        for (const StudentCourseInfo& info : studentCourseList) {


            QStringList table_h_headers;
            table_h_headers  << "课程名" << "任课教师" << "地点" << "上课时间"<< " ";
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
            connect(choose_course, &QPushButton::clicked, this, &Choose_course::Choose_a_course);

            ++row;

        }

    }
    db.close();
}

Choose_course::~Choose_course()
{
    delete ui;
}

void Choose_course::Choose_a_course()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    // 获取点击的按钮所在的行
    QPushButton* dropButton = qobject_cast<QPushButton*>(sender());  // 获取发送信号的按钮
    QModelIndex buttonIndex = ui->tableView->indexAt(dropButton->pos());  // 获取按钮的索引
    int row = buttonIndex.row();  // 获取按钮所在的行
    // 获取要退课的课程信息
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->tableView->model());
    QString courseName = model->index(row, 0).data().toString();  // 获取课程名

    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "选课确认", "确定要选该课程吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    QSqlQuery query;
    query.exec("SELECT MAX(studentid) FROM Student");

    int maxStudentID = 0;  // 初始化为0，以防表中没有数据
    if (query.next()) {
        maxStudentID = query.value(0).toInt();
            // 获取最大的studentid
    }

    if (reply == QMessageBox::Yes) {
            // 在数据库中删除课程记录
        query.prepare("INSERT INTO Student (studentid, studentname, coursename) VALUES (:id, :studentname, :coursename)");
        query.bindValue(":id", maxStudentID + 1);
        query.bindValue(":studentname", username);
        query.bindValue(":coursename", courseName);
        if (query.exec()) {
            // 成功选择记录
            QMessageBox::information(this, "选课成功", "成功选择该课程！");
              // 从表格中移除对应的行
        } else {
            // 删除记录失败
            QMessageBox::critical(this, "选课失败", "无法选择该课程，请稍后重试！");
        }

    }
    db.close();

}
