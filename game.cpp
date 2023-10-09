#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->label_background->lower();
    this->setFixedSize(this->width(),this->height());//设置固定大小
    this->setWindowIcon(QIcon(":/picture/04_game.png"));
    this->setWindowTitle("游戏");

    mineSweeping = new Game_mineSweeping;
    connect(mineSweeping,SIGNAL(lastShow()),this,SLOT(thisShow()));
}

Game::~Game()
{
    emit funShow();
    delete ui;
}

void Game::on_btn_game1_clicked()
{
//    mineSweeping = new Game_mineSweeping;
    mineSweeping->show();
    this->close();
}

void Game::on_btn_game2_clicked()
{

}

void Game::thisShow()
{
    this->show();
}
