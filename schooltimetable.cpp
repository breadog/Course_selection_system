#include "schooltimetable.h"
#include "ui_schooltimetable.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QVector>
#include <QList>

QList<int> convertStringToIntList(const QString& input, const QString& delimiter) {
    // 将输入字符串根据指定的符号分割成QStringList
    QStringList stringList = input.split(delimiter, QString::SkipEmptyParts);
    QList<int> intList;

    // 将QStringList转换为QList<int>
    for (const QString& str : stringList) {
        bool ok;
        int num = str.toInt(&ok);
        if (ok) {
            intList.append(num);
        } else {
            qDebug() << "Conversion failed for" << str;
        }
    }

    return intList;
}

schooltimetable::schooltimetable(const QString& username, int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schooltimetable)
{
    ui->setupUi(this);
    this->username=username;
    this->id=id;

    // 绑定table
    QStandardItemModel* course_model = new QStandardItemModel();
    QTableWidget *tableWidget= ui->tableWidget;
    tableWidget->setColumnCount(7);
    QStringList headers;
    headers << "周一" << "周二" << "周三" << "周四" << "周五" << "周六" << "周日";
    tableWidget->setHorizontalHeaderLabels(headers);
    // 设置列宽自动调整
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 设置行数
    tableWidget->setRowCount(8);

    // 设置行高自动调整
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        tableWidget->setRowHeight(row, tableWidget->height() / tableWidget->rowCount());
    }

    // 当表格大小改变时重新调整行高
    connect(tableWidget->verticalHeader(), &QHeaderView::sectionResized, [tableWidget]() {
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            tableWidget->setRowHeight(row, tableWidget->height() / tableWidget->rowCount());
        }
    });
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //加载数据
    struct Course{
        QString name;
        QString teacher;
        QString place;
        QList<int> time;
        QList<int> date;
        QList<int> week;

    };

    // 连接数据库
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }

    QVector<Course> cList;
    QSqlQuery query;
    //显示学生已选课程
    query.prepare("SELECT Course.name, Course.teacher , Course.place, Course.time, Course.date, Course.week "
               "FROM SC "
               "INNER JOIN Course ON SC.course_id = Course.id "
               "WHERE SC.student_id = :userId");
    query.bindValue(":userId", id);
    query.exec();

    while(query.next()){
        Course course;
        course.name = query.value(0).toString();
        course.teacher = query.value(1).toString();
        course.place = query.value(2).toString();
        course.time = convertStringToIntList(query.value(3).toString(),",");
        course.date = convertStringToIntList(query.value(4).toString(),",");
        course.week = convertStringToIntList(query.value(5).toString(),"-");
        cList.append(course);
    }



    // 将课程数据映射到表格中
    for (const Course& course : cList) {
        QString courseInfo = course.name + "\n" + course.teacher + "\n" + course.place;
        for (int time : course.time) {
            for (int date : course.date) {
                int row = time - 1; // time 1-8对应row 0-7
                int col = date - 1; // date 1-7对应col 0-6
                QTableWidgetItem *item = new QTableWidgetItem(courseInfo);
                tableWidget->setItem(row, col, item);
            }
        }
    }

}

schooltimetable::~schooltimetable()
{
    delete ui;
}

void schooltimetable::on_refresh_clicked()
{

    //加载数据
    struct Course{
        QString name;
        QString teacher;
        QString place;
        QList<int> time;
        QList<int> date;
        QList<int> week;

    };

    // 连接数据库
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }

    // 清除表格现有数据
    ui->tableWidget->clearContents();

    // 重新加载数据
    QVector<Course> cList;
    QSqlQuery query;
    query.prepare("SELECT Course.name, Course.teacher, Course.place, Course.time, Course.date, Course.week "
                  "FROM SC "
                  "INNER JOIN Course ON SC.course_id = Course.id "
                  "WHERE SC.student_id = :userId");
    query.bindValue(":userId", id);
    if (!query.exec()) {
        QMessageBox::critical(nullptr, "错误", "数据库查询失败：" + query.lastError().text());
        return;
    }

    while(query.next()) {
        Course course;
        course.name = query.value(0).toString();
        course.teacher = query.value(1).toString();
        course.place = query.value(2).toString();
        course.time = convertStringToIntList(query.value(3).toString(), ",");
        course.date = convertStringToIntList(query.value(4).toString(), ",");
        course.week = convertStringToIntList(query.value(5).toString(), "-");
        cList.append(course);
    }

    // 将课程数据映射到表格中
    for (const Course& course : cList) {
        QString courseInfo = course.name + "\n" + course.teacher + "\n" + course.place;
        for (int time : course.time) {
            for (int date : course.date) {
                int row = time - 1; // time 1-8对应row 0-7
                int col = date - 1; // date 1-7对应col 0-6
                QTableWidgetItem *item = new QTableWidgetItem(courseInfo);
                ui->tableWidget->setItem(row, col, item);
            }
        }
    }


}
