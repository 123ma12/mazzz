#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QGraphicsOpacityEffect>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());//设置固定大小
    QGraphicsOpacityEffect *tmd = new QGraphicsOpacityEffect;
    tmd->setOpacity(0.5);  //设置透明度
//    this->setWindowIcon(QIcon(":/picture/01_weather.png"));
    this->setWindowTitle("注册");

    ui->label_background->setGraphicsEffect(tmd);
    ui->label_background->lower();
//    QLabel *backgroundLabel = new QLabel(this);


    //判断当前项目是否已经包含数据库的默认链接，如果有就先得到该链接，没有则创建数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        //根据参数得到数据库的连接
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        //当前项目没有数据库的链接，就添加新的数据库链接
        //添加数据库
        db = QSqlDatabase::addDatabase("QSQLITE");
        //设置数据库的名称
        db.setDatabaseName("../user.db");
    }

    //打开数据库
    if(db.isOpen());
    else
    {
        if(!db.open())
            qDebug()<< "打开失败";
        else
        {
            //primary key autoincrement : 自动添加  primary key autoincrement
            QSqlQuery query("create table if not exists user(username text,password text);");
            if(query.exec());
            else
                //sql语句执行失败
                QMessageBox::warning(this,"错误","创建失败");
        }
    }
}

Login::~Login()
{
    delete ui;
    if(db.isOpen())
        db.close();
}

void Login::on_btn_1_clicked()
{
    emit mainShow();

    //判断注册的用户名是否已经存在
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :value");  //
    query.bindValue(":value", ui->le_1->text());
    if(!query.exec())
        qDebug()<< "查询失败";
    if(query.next())
    {
        QMessageBox::warning(this,"提示","该用户名已存在");
        return;
    }
    else
    {
        if(ui->le_2->text() != ui->le_3->text())
            QMessageBox::warning(this,"警告","请输入一致的密码!");
        else
        {
            QString sql = QString("insert into user values('%1','%2');")
                    .arg(ui->le_1->text())
                    .arg(ui->le_2->text());

            QSqlQuery query;
            if(!query.exec(sql))
                QMessageBox::warning(this,"失败","添加失败");
            QMessageBox::information(this,"注册","注册成功",QMessageBox::Ok);
            this->close();
        }
    }
}

void Login::on_btn_return_clicked()
{
    emit mainShow();
    this->close();
}
