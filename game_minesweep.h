#ifndef GAME_MINESWEEP_H
#define GAME_MINESWEEP_H

#include <QMainWindow>

namespace Ui {
class Game_mineSweep;
}

class Game_mineSweep : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_mineSweep(QWidget *parent = 0);
    ~Game_mineSweep();

private:
    Ui::Game_mineSweep *ui;
};

#endif // GAME_MINESWEEP_H
