#include "music.h"
#include "ui_music.h"
#include <QUrl>
//#include <QMediaPlayList> //Qt版本不同，没有这个类



Music::Music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);
    this->setWindowTitle("音乐播放器");
    this->setWindowIcon(QIcon(":/picture/05_music.png"));

//    static int flag = 0;
//    QString filePath = "./ggbone.mp3";
    player = new QMediaPlayer;
    QUrl source = QUrl::fromLocalFile("./ggbone.mp3");
    player->setSource(source);
//    QMediaContent *content = new QMediaContent(QUrl::fromLocalFile("/path/to/your/file"));
//    player->setMediaObject(new QMediaService(this));
//    player->setMediaObject(content);
//    player->setMedia(QUrl::fromLocalFile("./ggbone.mp3"));


//    slider = new QSlider(this);
//    slider->setOrientation(Qt::Horizontal);
}

Music::~Music()
{
    delete ui;
}

void Music::on_btn_prior_clicked()
{

}
//int flag = 0;
void Music::on_btn_start_clicked()
{
    static int flag = 0;
    if(flag == 0)
    {
        ui->btn_start->setStyleSheet("QPushButton {"
                                     "  background-image: url(:/picture/09_stop.png);"
                                     "  background-repeat: no-repeat;"
                                     "  background-position: center;"
                                     "}");
        player->play();
        flag++;
    }
    else
    {
//        ui->btn_start->setStyleSheet(QPushButton{"background-image:url(:/picture/06_stop.png);"});
        ui->btn_start->setStyleSheet("QPushButton {"
                                 "  border-image: url(:/picture/06_start.png);"
                                 "}");
        flag = 0;
//        qDebug() << flag;
        player->pause();
    }
}
void Music::on_btn_next_clicked()
{

}

void Music::on_horizontalSlider_valueChanged(int value)
{

}
#if 1
void Music::on_btn_find_clicked()
{
    /*
     //创建网络请求对象
    QNetworkAccessManager manager;
    manager = new QNetworkAccessManager;

     //发送GET请求搜索音乐
    reply = new QNetworkReply;
    reply = manager->get(QNetworkRequest(QUrl("https://api.imjad.cn/cloudmusic/?type=search&search_type=1&s=hello")));

    //监听请求完成信号
    connect(reply,SIGNAL(finished()),this,SLOT(findMusic()));
    QString musicName = ui->lineEdit->text(); // 获取用户在LineEdit中输入的搜索关键词

    // 在这里使用搜索关键词进行网络搜索，并获取到搜索结果的URL
//    QString result = getSearchResultUrl(musicName); // 自行实现获取URL的函数或方法

    // 创建音乐播放器
//    QMediaPlayer* mediaPlayer = new QMediaPlayer(this);
//    player->setMedia(QUrl(result));

    // 开始播放音乐
//    player->play();
*/
}

void Music::findMusic()
{
    /*
    if (reply->error() == QNetworkReply::NoError)
    {
        // 读取返回的数据
        QByteArray data = reply->readAll();

        // 解析JSON数据
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject rootObj = doc.object();
        QJsonArray songsArray = rootObj.value("result").toObject().value("songs").toArray();

        // 播放第一首搜索结果
        if (!songsArray.isEmpty())
        {
            QString audioUrl = songsArray[0].toObject().value("audio").toString();
            QMediaPlayer player;
            player.setMedia(QUrl(audioUrl));
            player.play();
        }
    }
    // 删除网络请求对象和回复对象
    reply->deleteLater();
    manager->deleteLater();
*/
}
#endif
