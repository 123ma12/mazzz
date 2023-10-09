#ifndef GAME_MINESWEEPING_H
#define GAME_MINESWEEPING_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QMenu>          //菜单头文件
#include <QMenuBar>       //菜单栏头文件
#include <QToolBar>       //工具栏头文件
#include <QAction>        //菜单项的头文件
#include <QStatusBar>     //状态栏头文件
#include <array.h>
#include <QTimer>
#include <QMessageBox>
#include <qmessagebox.h>
#include <dialog.h>

//定义常量
#define BLOCK_LENGTH 21
#define BLOCK_HEIGH 21
#define ELENUM_LENGHT 20
#define EXPRESSION_LENGHT 24
#define EXPRESSION_HEIGH 24
#define TTILE_BEGIN 23
#define TITILE_HEIGH  (TTILE_BEGIN+40)
#define PRIMARY_LENGTH  189
#define MIDDLE_LENGTH   336
#define TOP_LENGTH      630

namespace Ui {
class Game_mineSweeping;
}

class Game_mineSweeping : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_mineSweeping(QWidget *parent = 0);
    ~Game_mineSweeping();

private:
    Ui::Game_mineSweeping *ui;
    QTimer * runtime;
    Dialog * useDefineWindows;
    QAction *actionPrimary,*actionMiddle,*actionSenior,*actionUser_defined,*actionQuit,*actionHelp,
            *actionAbout,*actionHow_to_play;
    QMenu *menuGame,*menuAbout;

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    lastShow();
private slots:
    void on_secondadd();
    //void lastShow();

    void on_actionPrimary_triggered();
    void on_actionMiddle_triggered();
    void on_actionSenior_triggered();
    void on_actionQuit_triggered();
    void on_actionUser_defined_triggered();
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();
    void on_actionHow_to_play_triggered();
};

void showblock(int x,int y);
int iswin();
void restart(int row,int col,int boolnum);
void painttitle(QPainter  * painter);
void paintboom(QPainter * painter);

#endif // GAME_MINESWEEPING_H
