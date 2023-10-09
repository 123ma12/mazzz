#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <data.h>
#include <QNetworkAccessManager>
#include<QNetworkReply>
#include<QMap>

namespace Ui {
class Weather;
}

class Weather : public QWidget
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = 0);
    ~Weather();
    void getWeatherInfo_BycityName(QString location);//发送请求信息
    void paseJson(QByteArray &arr);//解析json
    QNetworkAccessManager *manager;
    QMap<int,day>dayList;
    QString location;
signals:
    funShow();
private slots:
    void on_btn_findCity_clicked();
    void onReplied(QNetworkReply *reply);//接收信息

private:
    Ui::Weather *ui;
};

#endif // WEATHER_H
