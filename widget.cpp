#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QGraphicsOpacityEffect>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());//设置固定大小

    QGraphicsOpacityEffect *tmd = new QGraphicsOpacityEffect;
    tmd->setOpacity(0.5);  //设置透明度

    ui->label->setGraphicsEffect(tmd);
    ui->label->lower();

    this->setWindowIcon(QIcon(":/picture/20.png"));
    this->setWindowTitle("组件PLUS");

    myfun = new Function;

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    //添加数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库的名称
    db.setDatabaseName("../user.db");
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

Widget::~Widget()
{
    delete ui;
    if(db.isOpen())
        db.close();
}

void Widget::on_btn_login_clicked()
{
    //查询数据库中有无行编辑框中的信息
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :value");  //
    query.bindValue(":value", ui->lineEdit_username->text());
    if(!query.exec())
        qDebug()<< "查询失败";
//        QMessageBox::warning(this,"登录","用户名或密码错误！");
    if(query.next())
    {
//        int record_count = query.value(0).toInt();
//        if (record_count == 0)
//        {
//           QMessageBox::warning(this,"登录","用户名或密码错误！");
//        }
        QSqlQuery query1;
        query1.prepare("SELECT username,password FROM user WHERE username = :value");  //
        query1.bindValue(":value", ui->lineEdit_username->text());
        if(!query1.exec())
            qDebug() << "查询失败";
//            QMessageBox::warning(this,"登录","用户名或密码错误！");
//        else
//        {
//            if(query1.value(0) != ui->lineEdit_username->text())
//            {
//                QMessageBox::warning(this,"登录","用户名或密码错误！");
//            }
//        }
        if(query1.next())
        {
//            QVariant value1 = query1.value(0);
            if(query1.value(1) == ui->lineEdit_password->text())
            {
                QMessageBox::information(this,"登录","登录成功",QMessageBox::Ok);  //对话框
                //跳转到功能界面
//                myfun = new function;
                myfun->show();
                this->close();
            }
//            else if(query1.value()
            else
                QMessageBox::warning(this,"登录","用户名或密码错误！");
        }
        else
            QMessageBox::warning(this,"登录","用户名或密码错误！");
    }
    else
        QMessageBox::warning(this,"登录","用户名或密码错误！");
//    QMessageBox::information(this,"登录","登录成功",QMessageBox::Ok);  //对话框
}

void Widget::on_btn_enroll_clicked()
{
    mylogin = new Login;
    connect(mylogin,SIGNAL(mainShow()),this,SLOT(mainShow()));
    mylogin->show();
    this->close();
}

void Widget::mainShow()
{
    this->show();
}
