#include "game_minesweep.h"
#include "ui_game_minesweep.h"

Game_mineSweep::Game_mineSweep(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_mineSweep)
{
    ui->setupUi(this);
}

Game_mineSweep::~Game_mineSweep()
{
    delete ui;
}
