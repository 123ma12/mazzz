#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include <QMessageBox>
#include <game.h>
#include <music.h>
#include <weather.h>
#include <mydata.h>

namespace Ui {
class Function;
}

class Function : public QWidget
{
    Q_OBJECT

public:
    explicit Function(QWidget *parent = 0);
    ~Function();

//signals:
//    mainShow();
private slots:

    void on_btn_weather_clicked();

    void on_btn_data_clicked();

    void on_btn_game_clicked();

    void on_btn_music_clicked();

    void showData();

    void funShow();

private:
    Ui::Function *ui;
    QTimer *timer;
    Game *game;
    Mydata *mydata;
    Music *music;
    Weather *weather;
};

#endif // FUNCTION_H
