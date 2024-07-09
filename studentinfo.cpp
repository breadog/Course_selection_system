#include "studentinfo.h"
#include "ui_studentinfo.h"

StudentInfo::StudentInfo(const QString& username, int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentInfo)
{
    ui->setupUi(this);
    this->username = username;
    this->id = id;
    ui->name->setText(username);
    ui->name->setReadOnly(true);

    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM Student WHERE name = :username");
    query.bindValue(":username", username);
    query.exec();
    if (query.first()) {
        originalName = query.value("name").toString();
        originalGender = query.value("gender").toString();
        originalEthnicity = query.value("ethnicity").toString();
        originalClass= query.value("class").toString();
        originalMajor= query.value("major").toString();
        originalDepartment = query.value("department").toString();


        ui->name->setText(query.value("name").toString());
        ui->gender->setText(query.value("gender").toString());
        ui->ethnicity->setText(query.value("ethnicity").toString());
        ui->class_2->setText(query.value("class").toString());
        ui->department->setText(query.value("department").toString());
        ui->major->setText(query.value("major").toString());
    }

}

StudentInfo::~StudentInfo()
{
    delete ui;
}

void StudentInfo::on_save_clicked()
{
    QString name = ui->name->text().trimmed();
    QString gender = ui->gender->text().trimmed();
    QString ethnicity = ui->ethnicity->text().trimmed();
    QString class_2 = ui->class_2->text().trimmed();
    QString department = ui->department->text().trimmed();
    QString major = ui->major->text().trimmed();


    // 检查数据库连接是否仍然有效
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "错误", "数据库连接已断开！");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Student SET gender = :gender, ethnicity = :ethnicity, major = :major, department = :department, class = :class WHERE name = :name");
    updateQuery.bindValue(":gender", gender);
    updateQuery.bindValue(":ethnicity", ethnicity);
    updateQuery.bindValue(":major", major);
    updateQuery.bindValue(":department", department);
    updateQuery.bindValue(":class", class_2);
    updateQuery.bindValue(":name", name);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "错误", "更新用户信息" + updateQuery.lastError().text());
    } else {
        QMessageBox::information(this, "成功", "用户信息已成功更新！");
    }
}

void StudentInfo::on_cancel_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT name, gender, ethnicity, class, department, major FROM Student WHERE name = :username");
    query.bindValue(":username", username);
    query.exec();

    if (query.first()) {
        // 使用查询到的数据更新 UI
        ui->name->setText(query.value("name").toString());
        ui->gender->setText(query.value("gender").toString());
        ui->ethnicity->setText(query.value("ethnicity").toString());
        ui->class_2->setText(query.value("class").toString());
        ui->department->setText(query.value("department").toString());
        ui->major->setText(query.value("major").toString());
    } else {
        QMessageBox::warning(this, "警告", "无法找到学生信息。");
    }
}
