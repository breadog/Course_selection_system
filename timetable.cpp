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
    QStringList table_h_headers;
    table_h_headers  << "课程名" << "任课教师" << "地点" << "上课时间" ;//<< "课序号"<< dropcourse;

    course_model->setHorizontalHeaderLabels(table_h_headers);

    /*QStringList table_v_headers;
    table_v_headers << "08:25-10:00" << "10:25-12:00" << "14:30-16:05" << "16:30-18:00";

    course_model->setVerticalHeaderLabels(table_v_headers);*/

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

    // query.prepare("SELECT courseteacher FROM Course");
    // QVector<QString> courseteacherArray;
    // if (query.exec())
    // {
    //     while (query.next())
    //     {
    //         QString courseteacher = query.value(0).toString();
    //         courseteacherArray.append(courseteacher);
    //     }
    // }

    query.prepare("SELECT courseteacher FROM Course");
    QVector<QString> courseteacherArray;
    if (query.exec())
    {
        while (query.next())
        {
            QString courseteacher = query.value(0).toString();
            courseteacherArray.append(courseteacher);
            // QStandardItem *item = new QStandardItem(courseteacher);
            // course_model->setItem(0, 2, item);
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

    QMap<QString, QString> studentCourseMap;

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

    //qDebug() << "studentCourseMap[1]:" << studentCourseMap[1];
        // if(studentName == username && courseName)
        // {

        // }
    }

    qDebug() << coursenameArray;
    qDebug() << coursetimeArray;
    qDebug() << courseteacherArray;
    qDebug() << courseplaceArray;

    //插入课程表
    // QTableWidgetItem *item0 = new QTableWidgetItem(coursenameArray.at(0));
    // QTableWidgetItem *item1 = new QTableWidgetItem();
    // QTableWidgetItem *item2 = new QTableWidgetItem();
    QStandardItem *item = new QStandardItem(coursenameArray.at(0));


    course_model->setItem(0, 2, item);
    // course_model->setItem(0, 0, item0);
    // course_model->setItem(0, 1, item1);
    // course_model->setItem(0, 2, item2);
    // course_model->setItem(0, 3, item3);


}

Timetable::~Timetable()
{
    delete ui;
}

void Timetable::on_pushButton_clicked()
{
    Widget *w = new Widget;
    w->show();
    this->hide();
    return;
}

