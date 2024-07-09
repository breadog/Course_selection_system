#include "t_mainwindow.h"
#include "ui_t_mainwindow.h"

T_MainWindow::T_MainWindow(const QString& username,int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::T_MainWindow)
{
    ui->setupUi(this);
    this->username = username;
    this->id = id;

    teacherInfo = new TeacherInfo(username,id,this);
    changePassword = new ChangePassword(username,this);
//    teacher = new Teacher(username,id,this);

    ui->stackedWidget->addWidget(teacherInfo);
//    ui->stackedWidget->addWidget(teacher);
    ui->stackedWidget->addWidget(changePassword);

    connect(ui->toolButton, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_clicked);
//    connect(ui->toolButton_2, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_2_clicked);
    connect(ui->toolButton_5, &QToolButton::clicked, this, &T_MainWindow::on_toolButton_5_clicked);

}

T_MainWindow::~T_MainWindow()
{
    delete ui;
}

void T_MainWindow::on_toolButton_clicked()
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

void T_MainWindow::on_toolButton_2_clicked()
{
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;  // Use a relative path

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
        return;
    }
//    ui->stackedWidget->setCurrentWidget(teacher);
}

void T_MainWindow::on_toolButton_3_clicked()
{

}

void T_MainWindow::on_toolButton_4_clicked()
{

}

void T_MainWindow::on_toolButton_5_clicked()
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

void T_MainWindow::on_toolButton_6_clicked()
{
    Widget *w = new Widget;
    w->show();
    this->hide();
    return;
}
