#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->Login, &QPushButton::clicked, this, &Widget::Login);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Login()
{

    QString username = ui->accountLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString role = ui->userTypeComboBox->currentText();


    if (username.isEmpty() && password.isEmpty()) {
        //**空处理**
        //Timetable *timetable = new Timetable(this);
        // table->show();
        // this->hide();

    }

    //连接数据库
    QString dbName = "database.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbPath);

    // QString dbName = "database.db";
    // // QString dbPath = QCoreApplication::applicationDirPath() + "./" + dbName;
    // QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    // database.setDatabaseName(dbName);

    //验证数据库是否打开
    if (!database.open()) {
        QMessageBox::critical(nullptr, "错误", "无法打开数据库: " + database.lastError().text());
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE name = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    //query.bindValue(":user_role", role);

    if(!query.exec())
    {
        QMessageBox::critical(nullptr, "错误", "查询执行失败: " + database.lastError().text());
        return;
    }
    if(query.next()) //用户存在
    {
        int id = query.value("id").toInt();
        Timetable *table = new Timetable(username, id);
//        Teacher *tea = new Teacher(username, id);
        T_MainWindow *tea = new T_MainWindow(username,id);
        QString userRole = query.value("user_role").toString();
        if(userRole == "学生")
        {
            table->show();
            this->hide();
        }  else if (userRole == "老师") // 老师登录
        {
            tea->show();
            this->hide();
        }
        else
        {
            QMessageBox::critical(nullptr, "错误", "无效的用户角色");
            return;
        }

    } else { //登录失败
        QMessageBox::critical(nullptr, "错误", "用户名或密码错误");
        return;
    }

    database.close();
}
