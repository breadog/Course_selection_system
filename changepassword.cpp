#include "changepassword.h"
#include "ui_changepassword.h"

ChangePassword::ChangePassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);



    QString dbName = "database.db";
 //    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }





}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void ChangePassword::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text().trimmed();
    QString oldPassword = ui->lineEdit_2->text().trimmed();
    QString newPassword = ui->lineEdit_3->text().trimmed();
    QString confirmNewPassword = ui->lineEdit_4->text().trimmed();


    // 验证输入


    if (oldPassword.isEmpty()) {
           QMessageBox::warning(this, "警告", "旧密码不能为空！");
           return;
       }
    if (newPassword.isEmpty() || confirmNewPassword.isEmpty()) {
        QMessageBox::warning(this, "警告", "新密码和确认新密码不能为空！");
        return;
    }
    if (newPassword != confirmNewPassword) {
        QMessageBox::warning(this, "警告", "新密码和确认新密码不匹配！");
        return;
       }

    // 从数据库获取明文密码
    QString storedPassword = getUserPassword(username);
    if (storedPassword.isEmpty()) {
        QMessageBox::warning(this, "警告", "找不到该用户或密码为空！");
        return;
    }

    // 验证旧密码
    if (storedPassword != oldPassword) {
        QMessageBox::warning(this, "警告", "旧密码不正确！");
        return;
    }

    // 旧密码验证通过，现在更新新密码（注意：这里我们仍然直接存储明文密码，不推荐）
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE User SET password = :new_password WHERE username = :username");
    updateQuery.bindValue(":new_password", newPassword);
    updateQuery.bindValue(":username", username);
    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "错误", "更新密码失败：" + updateQuery.lastError().text());
    } else {
        QMessageBox::information(this, "成功", "密码已成功更新！");
    }


}

QString ChangePassword::getUserPassword(QString &username) {
    QString password;
    QSqlQuery query;
    query.prepare("SELECT password FROM User WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec()) {
        if (query.next()) {
            password = query.value(0).toString();
        }
    }
    return password;
}



void ChangePassword::on_pushButton_3_clicked()
{
    // QString username = ui->lineEdit->text().trimmed();
    // Timetable *t = new Timetable(username, id);
    // t->show();
}
