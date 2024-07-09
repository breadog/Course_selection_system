#include "enter_scores.h"
#include "ui_enter_scores.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

enter_scores::enter_scores(int studentId, int courseId, int id, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::enter_scores)
{
    ui->setupUi(this);

    this->studentId = studentId;
    this->courseId = courseId;
    this->id = id;
    qDebug() << "studentId:" << studentId;
    qDebug() << "courseId:" << courseId;
    qDebug() << "id:" << id;

}

enter_scores::~enter_scores()
{
    delete ui;
}

void enter_scores::on_comfirm_clicked()
{
    QString scoreText = ui->input->text();
    int score = scoreText.toInt();
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.prepare("UPDATE SC SET score = :score "
                  "WHERE student_id = :studentId AND course_id = :courseId ");//AND id = :id
    query.bindValue(":studentId", studentId);     // 学生ID
    //query.bindValue(":id", id);                   // 插入记录的ID
    query.bindValue(":courseId", courseId);       // 课程ID
    query.bindValue(":score", score);             // 分数

    if (query.exec()) {
        // 成功插入记录
        QMessageBox::information(this, "成功", "成绩录入成功");
    } else {
        // 插入失败，处理错误
        qDebug() << "插入失败：" << query.lastError().text();
    }
}


void enter_scores::on_cancel_clicked()
{
    this->hide();
}

