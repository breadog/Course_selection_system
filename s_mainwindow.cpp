#include "s_mainwindow.h"
#include "ui_s_mainwindow.h"

S_MainWindow::S_MainWindow(const QString& username,int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::S_MainWindow)
{
    ui->setupUi(this);
    this->username = username;
    this->id = id;

    studentInfo = new StudentInfo(username,id,this);
    chooseCourse = new Choose_course(username,this);
    sctable = new schooltimetable(username,id,this);
    changePassword = new ChangePassword(username,this);
    timetable = new Timetable(username,id,this);

    ui->stackedWidget->addWidget(studentInfo);
    ui->stackedWidget->addWidget(chooseCourse);
    ui->stackedWidget->addWidget(sctable);
    ui->stackedWidget->addWidget(changePassword);
    ui->stackedWidget->addWidget(timetable);

    connect(ui->studentInfo, &QToolButton::clicked, this, &S_MainWindow::on_studentInfo_clicked);
    connect(ui->chooseCourse, &QToolButton::clicked, this, &S_MainWindow::on_chooseCourse_clicked);
    connect(ui->myCourse, &QToolButton::clicked, this, &S_MainWindow::on_myCourse_clicked);
    connect(ui->changePassword, &QToolButton::clicked, this, &S_MainWindow::on_changePassword_clicked);
    connect(ui->courseChosen, &QToolButton::clicked, this, &S_MainWindow::on_courseChosen_clicked);


}

S_MainWindow::~S_MainWindow()
{
    delete ui;
}

void S_MainWindow::on_studentInfo_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(studentInfo);
}

void S_MainWindow::on_chooseCourse_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(chooseCourse);
}

void S_MainWindow::on_myCourse_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(sctable);
}

void S_MainWindow::on_changePassword_clicked()
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



void S_MainWindow::on_toolButton_5_clicked()
{
    Widget *w = new Widget;
    w->show();
    this->hide();
    return;
}


void S_MainWindow::on_courseChosen_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
    ui->stackedWidget->setCurrentWidget(timetable);
}
