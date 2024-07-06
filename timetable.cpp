#include "timetable.h"
#include "ui_timetable.h"
#include "widget.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QVector>

Timetable::Timetable(const QString& username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timetable)
{
    ui->setupUi(this);

    this->username = username;
    ui->usernameLine->setText(username);

    // QPushButton *dropcourse = new QPushButton(this);

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
    query.prepare("SELECT coursename FROM Course");

    QVector<QString> coursenameArray;
    if (query.exec())
    {
        while (query.next())
        {
            QString coursename = query.value(0).toString();
            coursenameArray.append(coursename);

        }
    }

    query.prepare("SELECT coursetime FROM Course");
    QVector<QString> coursetimeArray;
    if (query.exec())
    {
        while (query.next())
        {
            QString coursetime = query.value(0).toString();
            coursetimeArray.append(coursetime);
        }
    }

    query.prepare("SELECT courseteacher FROM Course");
    QVector<QString> courseteacherArray;
    if (query.exec())
    {
        while (query.next())
        {
            QString courseteacher = query.value(0).toString();
            courseteacherArray.append(courseteacher);

        }
    }
    query.prepare("SELECT courseplace FROM Course");
    QVector<QString> courseplaceArray;
    if (query.exec())
    {
        while (query.next())
        {
            QString courseplace = query.value(0).toString();
            courseplaceArray.append(courseplace);

        }
    }

    QMultiMap<QString, QString> studentCourseMap;

    query.prepare("SELECT studentname, coursename FROM Student");
    if (query.exec())
    {
        while (query.next())
        {
            QString studentName = query.value(0).toString();
            QString courseName = query.value(1).toString();

            studentCourseMap.insert(studentName, courseName);
            qDebug() << studentCourseMap;
        }
    }
    QMap<QString, QString>::const_iterator it;
    for (it = studentCourseMap.constBegin(); it != studentCourseMap.constEnd(); ++it)
    {
        QString studentName = it.key();       // 提取学生姓名（键）
        QString courseName = it.value();      // 提取课程名（值）

        // 在这里可以使用学生姓名和课程名进行后续操作
        // ...

        qDebug() << "Student: " << studentName << ", Course: " << courseName;

    }

    qDebug() << coursenameArray;
    qDebug() << coursetimeArray;
    qDebug() << courseteacherArray;
    qDebug() << courseplaceArray;

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
            qDebug() << "info.studentName: "   << info.studentName;
            qDebug() << "info.courseName: "    << info.courseName;
            qDebug() << "info.courseTime: "    << info.courseTime;
            qDebug() << "info.coursePlace: "   << info.coursePlace;
            qDebug() << "info.courseTeacher: " << info.courseTeacher;
            qDebug() << "-------------------------";


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

                QPushButton *drop_course = new QPushButton("退课");
                ui->tableView->setIndexWidget(course_model->index(course_model->rowCount()-1, 4),drop_course);
                connect(drop_course, &QPushButton::clicked, this, &Timetable::Drop_a_course);

                ++row;
            }
        }
        db.close();
    }

}

Timetable::~Timetable()
{
    delete ui;
}

void Timetable::Drop_a_course()
{
    // 获取点击的按钮所在的行
    QPushButton* dropButton = qobject_cast<QPushButton*>(sender());  // 获取发送信号的按钮
    QModelIndex buttonIndex = ui->tableView->indexAt(dropButton->pos());  // 获取按钮的索引
    int row = buttonIndex.row();  // 获取按钮所在的行
    // 获取要退课的课程信息
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->tableView->model());
    QString courseName = model->index(row, 0).data().toString();  // 获取课程名
    qDebug()<<"Drop courseName:" << courseName;
    // QString courseTeacher = model->index(row, 1).data().toString();  // 获取任课教师
    // QString coursePlace = model->index(row, 2).data().toString();  // 获取地点
    // QString courseTime = model->index(row, 3).data().toString();  // 获取上课时间

    // 弹出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退课确认", "确定要退选该课程吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 在数据库中删除课程记录
        QSqlQuery query;
        query.prepare("DELETE FROM Student WHERE studentname = :studentName "
                      "AND coursename = :courseName");
        query.bindValue(":studentName", username);
        query.bindValue(":courseName", courseName);
        if (query.exec()) {
            // 成功删除记录
            QMessageBox::information(this, "退课成功", "成功退选该课程！");
            model->removeRow(row);  // 从表格中移除对应的行
        } else {
            // 删除记录失败
            QMessageBox::critical(this, "退课失败", "无法退选该课程，请稍后重试！");
        }
    }

}

void Timetable::on_ChooseCourse_clicked()
{
    Choose_course *choose = new Choose_course(username);
    choose->show();
}


void Timetable::on_backtomain_clicked()
{
    Widget *w = new Widget;
    w->show();
    this->hide();
    return;
}

