#include "teacherinfo.h"
#include "ui_teacherinfo.h"

TeacherInfo::TeacherInfo(const QString& username, int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherInfo)
{
    ui->setupUi(this);
    this->username = username;
    ui->name_3->setText(username);
    ui->name_3->setReadOnly(true);
    this->id = id;

    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM Teacher WHERE name = :username");
    query.bindValue(":username", username);
    query.exec();
    if (query.first()) {
        originalName = query.value("name").toString();
        originalGender = query.value("gender").toString();
        originalEthnicity = query.value("ethnicity").toString();
        originalTitle = query.value("title").toString();
        originalDepartment = query.value("department").toString();
        originalEmail = query.value("email").toString();


        ui->name_3->setText(query.value("name").toString());
        ui->gender_3->setText(query.value("gender").toString());
        ui->ethnicity_3->setText(query.value("ethnicity").toString());
        ui->title_3->setText(query.value("title").toString());
        ui->department_3->setText(query.value("department").toString());
        ui->email_3->setText(query.value("email").toString());
//        QString avatarUrl = query.value("avatar_path").toString();
    }
}



TeacherInfo::~TeacherInfo()
{
    delete ui;
}


void TeacherInfo::on_toolButton_clicked()
{
    QString name = ui->name_3->text().trimmed();
    QString gender = ui->gender_3->text().trimmed();
    QString ethnicity = ui->ethnicity_3->text().trimmed();
    QString title = ui->title_3->text().trimmed();
    QString department = ui->department_3->text().trimmed();
    QString email = ui->email_3->text().trimmed();


    // 检查数据库连接是否仍然有效
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "错误", "数据库连接已断开！");
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Teacher SET gender = :gender, ethnicity = :ethnicity, title = :title, department = :department, email = :email WHERE name = :name");
    updateQuery.bindValue(":gender", gender);
    updateQuery.bindValue(":ethnicity", ethnicity);
    updateQuery.bindValue(":title", title);
    updateQuery.bindValue(":department", department);
    updateQuery.bindValue(":email", email);
    updateQuery.bindValue(":name", name);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "错误", "更新用户信息" + updateQuery.lastError().text());
    } else {
        QMessageBox::information(this, "成功", "用户信息已成功更新！");
    }
}

void TeacherInfo::on_toolButton_2_clicked() {
    // 重置控件到原始值
    ui->name_3->setText(originalName);
    ui->gender_3->setText(originalGender);
    ui->ethnicity_3->setText(originalEthnicity);
    ui->title_3->setText(originalTitle);
    ui->department_3->setText(originalDepartment);
    ui->email_3->setText(originalEmail);
    // 如果有头像显示，也需要重置头像
}

