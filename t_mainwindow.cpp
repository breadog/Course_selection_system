#include "t_mainwindow.h"
#include "ui_t_mainwindow.h"

// #include <

T_MainWindow::T_MainWindow(const QString& username,int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::T_MainWindow)
{
    ui->setupUi(this);
    this->username = username;
    this->id = id;

    teacherInfo = new TeacherInfo(username,id,this);
    changePassword = new ChangePassword(username,this);
    showAllStudent = new Showallstudent(this);
    studentManagement = new addstudent(this);
//    teacher = new Teacher(username,id,this);

    ui->stackedWidget->addWidget(teacherInfo);
//    ui->stackedWidget->addWidget(teacher);
    ui->stackedWidget->addWidget(changePassword);
    ui->stackedWidget->addWidget(showAllStudent);
    ui->stackedWidget->addWidget(studentManagement);

    //connect(ui->personinfo, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_clicked);
//    connect(ui->toolButton_2, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_2_clicked);
    // connect(ui->toolButton_5, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_5_clicked);

}

T_MainWindow::~T_MainWindow()
{
    delete ui;
}

void T_MainWindow::on_personinfo_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(teacherInfo);
}




void T_MainWindow::on_teachinfo_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    Teacher *tea = new Teacher(username, id);
    tea->show();
}


void T_MainWindow::on_courseinfo_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(showAllStudent);

}


void T_MainWindow::on_passwordalter_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(changePassword);
}


void T_MainWindow::on_exit_clicked()
{
    Widget *w = new Widget;
    w->show();
    this->hide();
    return;
}


void T_MainWindow::on_addstu_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(studentManagement);
}

