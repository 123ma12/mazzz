#include "function.h"
#include "ui_function.h"
#include <QTimer>
#include <QDateTime>
#include <QGraphicsOpacityEffect>

Function::Function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Function)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/picture/20.png"));
    this->setWindowTitle("组件PLUS");
    this->setFixedSize(this->width(),this->height());//设置固定大小
    QGraphicsOpacityEffect *tmd = new QGraphicsOpacityEffect;
    tmd->setOpacity(0.5);  //设置透明度
    ui->label->setGraphicsEffect(tmd);
    ui->label->lower();
//    ui->label_2->lower();

    timer = new QTimer;
    timer->setInterval(1000); // 设置更新时间间隔，这里设置为1000毫秒，即1秒
    timer->start();

    connect(timer,SIGNAL(timeout()),this,SLOT(showData()));
}

Function::~Function()
{
    delete ui;
}

void Function::showData()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_time->setText("    " + currentDateTimeString);
}

void Function::on_btn_weather_clicked()
{
    weather = new Weather;
    connect(weather,SIGNAL(funShow()),this,SLOT(funShow()));
    weather->show();
//    this->close();
}

void Function::on_btn_data_clicked()
{
    mydata = new Mydata;
    connect(mydata,SIGNAL(funShow()),this,SLOT(funShow()));
    mydata->show();
//    this->close();
}

void Function::on_btn_game_clicked()
{
    game = new Game;
    connect(game,SIGNAL(funShow()),this,SLOT(funShow()));
    game->show();
//    this->close();
}

void Function::on_btn_music_clicked()
{
    music = new Music;
    connect(music,SIGNAL(funShow()),this,SLOT(funShow()));
    music->show();
//    this->close();
}

void Function::funShow()
{
    this->show();
}
