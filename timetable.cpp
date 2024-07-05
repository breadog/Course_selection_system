#include "timetable.h"
#include "ui_timetable.h"

#include <QMessageBox>
#include <QVector>

Timetable::Timetable(const QString& username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timetable)
{
    ui->setupUi(this);
    this->username = username;
    qDebug() << username;

    ui->usernameLine->setText(username);

    QStandardItemModel* course_model = new QStandardItemModel();

    ui->tableView->setModel(course_model);
    QStringList table_h_headers;
    table_h_headers << "星期一" << "星期二" << "星期三" << "星期四"<< "星期五"<< "星期六"<< "星期日";

    course_model->setHorizontalHeaderLabels(table_h_headers);

    QStringList table_v_headers;
    table_v_headers << "08:25-10:00" << "10:25-12:00" << "14:30-16:05" << "16:30-18:00";

    course_model->setVerticalHeaderLabels(table_v_headers);

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
    query.prepare("SELECT coursename FROM Student");

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
    qDebug() << coursenameArray;
    qDebug() << coursetimeArray;
    qDebug() << courseteacherArray;
    qDebug() << courseplaceArray;
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
