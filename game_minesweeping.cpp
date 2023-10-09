#include "game_minesweeping.h"
#include "ui_game_minesweeping.h"
#include "array.h"
#include "dialog.h"

//定义全局变量
static int paint_flag = 0;
QPainter * paintmywindow;
Game_mineSweeping * app;
//初始化类,现在为初级
int ROW =9;
int COL =9;
int BOOMNUM = 10;
Array * mine = new Array(ROW,COL,BOOMNUM);
int click_x,click_y,end = 0,timeend=1;
int LENGTH=mine->getcol()*21;
int HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
static bool showimage = 1;

Game_mineSweeping::Game_mineSweeping(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_mineSweeping)
{
    app = this;
    ui->setupUi(this);
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
    runtime = new QTimer(this);

//    openAct = new QAction(QIcon(":/picture/1.png"),"打开文件",this);
    //设置菜单
    actionPrimary = new QAction("简单",this);
    actionMiddle = new QAction("一般",this);
    actionSenior = new QAction("困难",this);
    actionQuit = new QAction("退出",this);
    actionUser_defined = new QAction("自定义",this);
    actionHelp = new QAction("帮助",this);
    actionAbout = new QAction("关于",this);
    actionHow_to_play = new QAction("玩法",this);

    menuGame = menuBar()->addMenu("游戏");
    menuGame->addAction(actionPrimary);
    menuGame->addAction(actionMiddle);
    menuGame->addAction(actionSenior);
    menuGame->addAction(actionUser_defined);
    menuGame->addAction(actionQuit);

    menuAbout = menuBar()->addMenu("关于");
    menuAbout->addAction(actionHelp);
    menuAbout->addAction(actionHow_to_play);
    menuAbout->addAction(actionAbout);

    connect(actionPrimary,SIGNAL(triggered(bool)),this,SLOT(on_actionPrimary_triggered()));
    connect(actionMiddle,SIGNAL(triggered(bool)),this,SLOT(on_actionMiddle_triggered()));
    connect(actionSenior,SIGNAL(triggered(bool)),this,SLOT(on_actionSenior_triggered()));
    connect(actionQuit,SIGNAL(triggered(bool)),this,SLOT(on_actionQuit_triggered()));
    connect(actionUser_defined,SIGNAL(triggered(bool)),this,SLOT(on_actionUser_defined_triggered()));
    connect(actionHelp,SIGNAL(triggered(bool)),this,SLOT(on_actionHelp_triggered()));
    connect(actionHow_to_play,SIGNAL(triggered(bool)),this,SLOT(on_actionHow_to_play_triggered()));

    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

Game_mineSweeping::~Game_mineSweeping()
{
    delete ui;
}

//鼠标事件
void Game_mineSweeping::mousePressEvent(QMouseEvent *event)
{
   //用户鼠标点击，判断左右键，确定落点，修改块信息，确定是否结束
     click_x = event->x();
     click_y = event->y();
   //先判断是否点击了笑脸
     if(event->buttons()==(Qt::LeftButton)&&(click_x>(int)LENGTH*100/200-11)&&
             (click_x<(int)LENGTH*100/200+11 +EXPRESSION_LENGHT)&&(click_y>7+TTILE_BEGIN)&&
             (click_y<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    {
     qDebug()<<"点击了笑脸";
     restart(mine->getrow(),mine->getcol(),mine->getboomNum());
     paint_flag = 0;
     end = 0;
     timeend = 1;
     runtime->stop();
     update();
     return;
    }
    else if( click_y<TITILE_HEIGH ) return;

    if(end==1)
    return ;
   //确定落点
    click_x = click_x/BLOCK_LENGTH;
    click_y = (click_y-TITILE_HEIGH)/BLOCK_HEIGH;
    if(event->buttons()==(Qt::LeftButton))
     {
         if(timeend==1)
         {
             runtime->start(1000);
         }
         if(mine->p[click_y][click_x]==99)
         {
            //若点击了炸弹,瞬间爆炸，结束游戏
             paint_flag = 4;
             end = 1;
             timeend=1;
             runtime->stop();
             update();

         }
         else if((mine->p[click_y][click_x]<10))
         {
             //需要递归遍历，更改类中信息
             showblock(click_y,click_x);
             paint_flag = 2;
             if(end = iswin()==1)
             {
                 paint_flag = 5;
                 timeend=1;
                 runtime->stop();
             }
             update();
             if(end)
         {
             if(showimage)
              {
                  QMessageBox message(QMessageBox::NoIcon, "You win!", "You have gained the game's final victory!");
                  message.setIconPixmap(QPixmap(":/mine_sweeping/win.png"));
                  showimage = !showimage;
                  message.exec();
              }
             else
             {
                  QMessageBox message(QMessageBox::NoIcon, "you are win", " I will give you a red flower ");
                  message.setIconPixmap(QPixmap(":/mine_sweeping/good.png"));
                  showimage = !showimage;
                  message.exec();
             }

         }
         }
          else return;

     }
    else if(event->buttons()==(Qt::RightButton))
     {
         //如果点击了右键
         if((mine->p[click_y][click_x]<10)||(mine->p[click_y][click_x]==99))
         {
             mine->p[click_y][click_x] = mine->p[click_y][click_x] +50;
             mine->minusredFlagNum();
         }
         else if((mine->p[click_y][click_x]>=50&&mine->p[click_y][click_x]<60)||(mine->p[click_y][click_x]>110))
         {
             mine->p[click_y][click_x] = mine->p[click_y][click_x] -50;
             mine->addredFlagNum();
         }
         paint_flag = 3;
         if(end = iswin()==1)
         {
             paint_flag = 5;
             timeend=1;
             runtime->stop();
         }
         update();
         if(end)
         {
             if(showimage)
              {
                  QMessageBox message(QMessageBox::NoIcon, "you are win", "very good, I really very appreciate you ");
                  message.setIconPixmap(QPixmap(":/mine_sweeping/win.png"));
                  showimage = !showimage;
                  message.exec();
              }
             else
             {
                  QMessageBox message(QMessageBox::NoIcon, "you are win", " I will give you a red flower ");
                  message.setIconPixmap(QPixmap(":/mine_sweeping/good.png"));
                  showimage = !showimage;
                  message.exec();
             }
         }
    }
}
//绘图事件
void Game_mineSweeping::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     paintmywindow = &painter;
     //加载位图
     QPixmap mine_title(":/mine_sweeping/mine_title.bmp");
     QPixmap block_close(":/mine_sweeping/block_close.bmp");
     QPixmap block_open(":/mine_sweeping/block_open.bmp");
     QPixmap red_flag(":/mine_sweeping/redflag.bmp");
     QPixmap keil_boom(":/mine_sweeping/keilboom.bmp");
     QPixmap click_boom(":/mine_sweeping/clickboom.bmp");
     QPixmap boom(":/mine_sweeping/boom.bmp");
     QPixmap qq_smile(":/mine_sweeping/smile.bmp");
     QPixmap qq_lose(":/mine_sweeping/lose.bmp");
     QPixmap qq_pround(":/mine_sweeping/proud.bmp");
     QPixmap ele_0(":/mine_sweeping/ele0.bmp");
     QPixmap ele_1(":/mine_sweeping/ele1.bmp");
     QPixmap ele_2(":/mine_sweeping/ele2.bmp");
     QPixmap ele_3(":/mine_sweeping/ele3.bmp");
     QPixmap ele_4(":/mine_sweeping/ele4.bmp");
     QPixmap ele_5(":/mine_sweeping/ele5.bmp");
     QPixmap ele_6(":/mine_sweeping/ele6.bmp");
     QPixmap ele_7(":/mine_sweeping/ele7.bmp");
     QPixmap ele_8(":/mine_sweeping/ele8.bmp");
     QPixmap ele_9(":/mine_sweeping/ele9.bmp");
     QPixmap blk_1(":/mine_sweeping/blk1.bmp");
     QPixmap blk_2(":/mine_sweeping/blk2.bmp");
     QPixmap blk_3(":/mine_sweeping/blk3.bmp");
     QPixmap blk_4(":/mine_sweeping/blk4.bmp");
     QPixmap blk_5(":/mine_sweeping/blk5.bmp");
     QPixmap blk_6(":/mine_sweeping/blk6.bmp");
     QPixmap blk_7(":/mine_sweeping/blk7.bmp");
     QPixmap blk_8(":/mine_sweeping/blk8.bmp");


    //如果是第一次打开，则进行初始化
    if(paint_flag==0)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i = 0;i<mine->getcol()*BLOCK_LENGTH;i=i+BLOCK_LENGTH)
            for(int j =TITILE_HEIGH;j<TITILE_HEIGH+mine->getrow()*BLOCK_HEIGH;j=j+BLOCK_HEIGH)
              painter.drawPixmap(i,j,block_close,0,0,BLOCK_LENGTH,BLOCK_LENGTH);
    }
    //左键点到炸弹绘制
    else if (paint_flag == 4)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i = 0;i<mine->getrow();i++)
        {
            for(int j = 0;j<mine->getcol();j++ )
               {
                if((mine->p[i][j]<10))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if((mine->p[i][j]==99))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if (mine->p[i][j]>110)
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine->p[i][j]<60)&&(mine->p[i][j]>=50))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,keil_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((mine->p[i][j])>99&&(mine->p[i][j]<110))
                {
                   int blk_num = mine->p[i][j] - 100;
                   switch (blk_num)
                   {
                    case 0: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 1: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 2: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 3: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 4: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 5: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 6: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 7: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 8: painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                   }
                }
               }
            }
        //绘制点击的炸弹
        painter.drawPixmap(click_x*BLOCK_LENGTH,click_y*BLOCK_HEIGH+TITILE_HEIGH,click_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);

     }
    //左键点到空白绘制
    else if (paint_flag == 2 )
    {
       //绘制标题
       painttitle(paintmywindow);
       //绘制雷区
       paintboom(paintmywindow);
    }
    //右键点击绘制
    else if(paint_flag ==3)
    {

        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
    //游戏成功结束
    else if(paint_flag == 5)
    {
        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
}

//左键遍历递归
void showblock(int x,int y)
{
    for(int blockRow = x - 1; blockRow <=x + 1;blockRow++)
        for(int blockCol = y - 1;blockCol <=y + 1;blockCol++)
        {
            if(blockRow<0||blockCol<0||blockRow>=mine->getrow()||blockCol>=mine->getcol())
               continue;
            if(mine->p[blockRow][blockCol]<10)
            {
                mine->p[blockRow][blockCol] =  mine->p[blockRow][blockCol] + 100;
                if(mine->p[blockRow][blockCol]==100)
                showblock(blockRow,blockCol);
            }
        }
}
//判断是否结束游戏
int iswin()
{
    int cnt = 0;
    for(int row = 0; row <mine->getrow();row++)
        for(int col =0;col<mine->getcol();col++)
        {
            if((mine->p[row][col]>=100)&&(mine->p[row][col]<110))
                cnt++;
        }
    if(cnt>=((mine->getcol()*mine->getrow())-mine->getboomNum()))
        return 1;
    else
        return 0;
}
//重新开始游戏
void restart(int row,int col,int boolnum)
{
    mine = new Array (row,col,boolnum);
}
//绘制时间红旗数与标题
void painttitle(QPainter  * painter)
{
    //加载位图
    QPixmap mine_title(":/mine_sweeping/mine_title.bmp");
    QPixmap block_close(":/mine_sweeping/block_close.bmp");
    QPixmap block_open(":/mine_sweeping/block_open.bmp");
    QPixmap red_flag(":/mine_sweeping/redflag.bmp");
    QPixmap keil_boom(":/mine_sweeping/keilboom.bmp");
    QPixmap click_boom(":/mine_sweeping/clickboom.bmp");
    QPixmap boom(":/mine_sweeping/boom.bmp");
    QPixmap qq_smile(":/mine_sweeping/smile.bmp");
    QPixmap qq_lose(":/mine_sweeping/lose.bmp");
    QPixmap qq_pround(":/mine_sweeping/proud.bmp");
    QPixmap ele_0(":/mine_sweeping/ele0.bmp");
    QPixmap ele_1(":/mine_sweeping/ele1.bmp");
    QPixmap ele_2(":/mine_sweeping/ele2.bmp");
    QPixmap ele_3(":/mine_sweeping/ele3.bmp");
    QPixmap ele_4(":/mine_sweeping/ele4.bmp");
    QPixmap ele_5(":/mine_sweeping/ele5.bmp");
    QPixmap ele_6(":/mine_sweeping/ele6.bmp");
    QPixmap ele_7(":/mine_sweeping/ele7.bmp");
    QPixmap ele_8(":/mine_sweeping/ele8.bmp");
    QPixmap ele_9(":/mine_sweeping/ele9.bmp");
    QPixmap ele_10(":/mine_sweeping/ele10.bmp");
    QPixmap blk_1(":/mine_sweeping/blk1.bmp");
    QPixmap blk_2(":/mine_sweeping/blk2.bmp");
    QPixmap blk_3(":/mine_sweeping/blk3.bmp");
    QPixmap blk_4(":/mine_sweeping/blk4.bmp");
    QPixmap blk_5(":/mine_sweeping/blk5.bmp");
    QPixmap blk_6(":/mine_sweeping/blk6.bmp");
    QPixmap blk_7(":/mine_sweeping/blk7.bmp");
    QPixmap blk_8(":/mine_sweeping/blk8.bmp");
    //调整大小
    mine_title = mine_title.scaled(QSize(LENGTH,40));

    //显示标题部分
    painter->drawPixmap(0,TTILE_BEGIN,mine_title,0,0,1000,1000);
    if(paint_flag == 4)
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_lose,0,0,1000,1000);
    else if (paint_flag == 5)
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_pround,0,0,1000,1000);
    else
    painter->drawPixmap((int)LENGTH*100/200-11,7+TTILE_BEGIN,qq_smile,0,0,1000,1000);

    //显示红旗数量
    int redflagnum = mine->getredFlagNum();
    if(redflagnum<0)
    {
        redflagnum = -redflagnum;
        painter->drawPixmap((int)(LENGTH*40)/200-30,5+TTILE_BEGIN,ele_10,0,0,1000,1000);
    }
    else painter->drawPixmap((int)(LENGTH*40)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);
    switch(redflagnum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch (redflagnum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }

    //显示时间
    int timenum = mine->gettimeNum();
    switch  (timenum/100)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum/10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }
    switch  (timenum%10)
    {
    case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
    case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
    case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
    case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
    case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
    case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
    case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
    case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
    case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
    case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
    }

}
//绘制正常鼠标点击事件与结束的雷区
void paintboom(QPainter * painter)
{
    //加载位图
    QPixmap mine_title(":/mine_sweeping/mine_title.bmp");
    QPixmap block_close(":/mine_sweeping/block_close.bmp");
    QPixmap block_open(":/mine_sweeping/block_open.bmp");
    QPixmap red_flag(":/mine_sweeping/redflag.bmp");
    QPixmap keil_boom(":/mine_sweeping/keilboom.bmp");
    QPixmap click_boom(":/mine_sweeping/clickboom.bmp");
    QPixmap boom(":/mine_sweeping/boom.bmp");
    QPixmap qq_smile(":/mine_sweeping/smile.bmp");
    QPixmap qq_lose(":/mine_sweeping/lose.bmp");
    QPixmap qq_pround(":/mine_sweeping/proud.bmp");
    QPixmap ele_0(":/mine_sweeping/ele0.bmp");
    QPixmap ele_1(":/mine_sweeping/ele1.bmp");
    QPixmap ele_2(":/mine_sweeping/ele2.bmp");
    QPixmap ele_3(":/mine_sweeping/ele3.bmp");
    QPixmap ele_4(":/mine_sweeping/ele4.bmp");
    QPixmap ele_5(":/mine_sweeping/ele5.bmp");
    QPixmap ele_6(":/mine_sweeping/ele6.bmp");
    QPixmap ele_7(":/mine_sweeping/ele7.bmp");
    QPixmap ele_8(":/mine_sweeping/ele8.bmp");
    QPixmap ele_9(":/mine_sweeping/ele9.bmp");
    QPixmap blk_1(":/mine_sweeping/blk1.bmp");
    QPixmap blk_2(":/mine_sweeping/blk2.bmp");
    QPixmap blk_3(":/mine_sweeping/blk3.bmp");
    QPixmap blk_4(":/mine_sweeping/blk4.bmp");
    QPixmap blk_5(":/mine_sweeping/blk5.bmp");
    QPixmap blk_6(":/mine_sweeping/blk6.bmp");
    QPixmap blk_7(":/mine_sweeping/blk7.bmp");
    QPixmap blk_8(":/mine_sweeping/blk8.bmp");

    for(int i = 0;i<mine->getrow();i++)
    {
        for(int j = 0;j<mine->getcol();j++ )
           {

            if((mine->p[i][j]<10)||(mine->p[i][j]==99))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if (((mine->p[i][j]<60)&&(mine->p[i][j]>=50))||(mine->p[i][j]>120))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if ((mine->p[i][j]>99)&&(mine->p[i][j]<110))
            {
               int blk_num = mine->p[i][j] - 100;
               switch (blk_num)
               {
                case 0: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 1: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 2: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 3: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 4: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 5: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 6: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 7: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 8: painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
               }
            }
           }
     }
}
//计时器槽函数
void Game_mineSweeping::on_secondadd()
{
    mine->addtimeNum();
}

void Game_mineSweeping::on_actionPrimary_triggered()
{
    end =0;
    timeend =1;
    mine = new Array(9,9,10);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void Game_mineSweeping::on_actionMiddle_triggered()
{
    end =0;
    timeend =1;
    mine = new Array(16,16,40);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void Game_mineSweeping::on_actionSenior_triggered()
{
    end =0;
    timeend =1;
    mine = new Array(16,30,99);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void Game_mineSweeping::on_actionQuit_triggered()
{
//    QApplication::quit();
    emit lastShow();
    this->close();
}

void Game_mineSweeping::on_actionUser_defined_triggered()
{
    useDefineWindows = new Dialog(this);
    useDefineWindows->show();

}
void createinterface()
{
    end =0;
    timeend =1;
    mine = new Array(ROW,COL,BOOMNUM);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    app->setMinimumSize(LENGTH,HEIGHT);
    app->setMaximumSize(LENGTH,HEIGHT);
}

void Game_mineSweeping::on_actionHelp_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "errow", "自己想");
    message.setIconPixmap(QPixmap(":/mine_sweeping/unknow.png"));
    message.exec();
}

void Game_mineSweeping::on_actionAbout_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "rule","");
    message.setIconPixmap(QPixmap(":/mine_sweeping/rule.jpg"));
    message.exec();
}

void Game_mineSweeping::on_actionHow_to_play_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "Example", "");
    message.setIconPixmap(QPixmap(":/mine_sweeping/example.png"));
    message.exec();
}
