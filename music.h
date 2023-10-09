#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class Music;
}

class Music : public QWidget
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = 0);
    ~Music();
signals:
    funShow();
private slots:
    void on_btn_prior_clicked();

    void on_btn_start_clicked();

    void on_btn_next_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_btn_find_clicked();

    void findMusic();

private:
    Ui::Music *ui;
    QSlider *slider;
    QMediaPlayer* player;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // MUSIC_H
