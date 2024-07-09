#include "teacher.h"
#include "ui_teacher.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QSqlError>
#include <QDebug>
#include <QPushButton>
//#include <QtXlsx/xlsxdocument.h>

Teacher::Teacher(const QString& username, int id, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Teacher)
{
    ui->setupUi(this);

    this->id = id;
    this->username=username;

    QStandardItemModel* model_teacher = new QStandardItemModel();
    ui->tableView->setModel(model_teacher);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }

    // 声明一个结构体用于存储学生选课信息
    struct StudentCourseInfo {
        QString studentName;
        QString courseName;
        QString courseTeacher;
        QString coursePlace;
        QString courseTime;
        int courseScore;
    };

    // 创建一个 QList 存储学生选课信息
    QList<StudentCourseInfo> studentCourseList;

    QSqlQuery query;
    //
    query.prepare("SELECT User.name, Course.name, Course.teacher, Course.place, Course.time, SC.score "
                  "FROM SC "
                  "JOIN User ON User.id = SC.student_id "
                  "JOIN Course ON SC.course_id = Course.id "
                  "WHERE teacher = :username;");
    query.bindValue(":username",username);
    query.exec();
    while (query.next()) {
        StudentCourseInfo studentCourseInfo;
        studentCourseInfo.studentName    = query.value(0).toString();
        studentCourseInfo.courseName     = query.value(1).toString();
        studentCourseInfo.courseTeacher  = query.value(2).toString();
        studentCourseInfo.coursePlace    = query.value(3).toString();
        studentCourseInfo.courseTime     = query.value(4).toString();
        studentCourseInfo.courseScore    = query.value(5).toInt();
        studentCourseList << studentCourseInfo;
    }
        int row = 0;
        //model_teacher->clear();

        QStringList table_h_headers;
        table_h_headers  << "学生姓名" << "课程名" << "任课教师" << "地点"<< "上课时间" << "成绩" <<" ";

        model_teacher->setHorizontalHeaderLabels(table_h_headers);

        for (const StudentCourseInfo& info : studentCourseList) {

            // qDebug() << "学生姓名：" << info.studentName;
            // qDebug() << "课程名："   << info.courseName;
            // qDebug() << "任课教师：" << info.courseTeacher;
            // qDebug() << "地点："    << info.coursePlace;
            // qDebug() << "上课时间：" << info.courseTime;
            // qDebug() << "------------------------";

            QStandardItem *itemStudent = new QStandardItem(info.studentName);
            QStandardItem *itemName    = new QStandardItem(info.courseName);
            QStandardItem *itemTeacher = new QStandardItem(info.courseTeacher);
            QStandardItem *itemPlace   = new QStandardItem(info.coursePlace);
            QStandardItem *itemTime    = new QStandardItem(info.courseTime);
            QStandardItem *itemScore = new QStandardItem(QString::number(info.courseScore));
            qDebug() << "itemScore:"<<itemScore;

            model_teacher->setItem(row, 0, itemStudent);
            model_teacher->setItem(row, 1, itemName);
            model_teacher->setItem(row, 2, itemTeacher);
            model_teacher->setItem(row, 3, itemPlace);
            model_teacher->setItem(row, 4, itemTime);
            model_teacher->setItem(row, 5, itemScore);

            QPushButton *give_score = new QPushButton("录入成绩");
            ui->tableView->setIndexWidget(model_teacher->index(model_teacher->rowCount()-1, 6),give_score);
            connect(give_score, &QPushButton::clicked, this, &Teacher::Give_score);

            ++row;
        }

    db.close();
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::Give_score()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    qDebug()<<"selectedRows:"<<selectedRows;
    if (!selectedRows.isEmpty()) {
        // 获取选中行的数据
        int row = selectedRows.first().row();
        QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->tableView->model());

        // 获取前两列的数据
        QString studentName = model->data(model->index(row, 0)).toString();  // 学生姓名
        QString courseName = model->data(model->index(row, 1)).toString();   // 课程名
        qDebug() << "studentName:" << studentName;
        qDebug() << "courseName:" << courseName;

        QString dbName = "database.db";
        QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        }
        QSqlQuery query;
        query.prepare("SELECT student_id, course_id FROM SC "
                      "INNER JOIN User ON SC.student_id = User.id "
                      "INNER JOIN Course ON SC.course_id = Course.id "
                      "WHERE User.name = :studentName AND Course.name = :courseName");
        query.bindValue(":studentName", studentName);
        query.bindValue(":courseName", courseName);

        if (query.exec() && query.next()) {
            int studentId = query.value(0).toInt();    // 学生ID
            int courseId = query.value(1).toInt();     // 课程ID
            qDebug() << "studentId:" << studentId;
            qDebug() << "courseId:" << courseId;

            // 创建 enter_scores 对象并传递数据
            enter_scores *score = new enter_scores(studentId, courseId, id);
            score->show();
        } else {
            QMessageBox::information(this, "提示", "未找到匹配的学生和课程");
        }
        db.close();
    }
    else {
        QMessageBox::information(this, "提示", "请选择一行记录");
    }

}

void Teacher::on_refresh_clicked()
{
    Teacher *tea = new Teacher(username, id);
    this->hide();
    tea->show();
}




