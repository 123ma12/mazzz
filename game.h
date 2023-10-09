#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <game_minesweeping.h>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
signals:
    funShow();
private slots:
    void on_btn_game1_clicked();

    void on_btn_game2_clicked();

    void thisShow();  //显示当前界面

private:
    Ui::Game *ui;
    Game_mineSweeping *mineSweeping;
};

#endif // GAME_H
