#include "weather.h"
#include "ui_weather.h"
#include<QDebug>
#include<QMessageBox>
#include<QIcon>
#include<data.h>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonValue>
#include<QJsonParseError>
#include<QPixmap>
#include <QRandomGenerator>
#include<QDate>
#include<QTime>
#include<QDateTime>

Weather::Weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/picture/01_weather.png"));
    this->setWindowTitle("天气");
    this->setFixedSize(this->width(),this->height());//设置固定大小
//    ui->label_weatherShow->setPixmap(QPixmap(":/weather/4.png"));
//    ui->label_weatherShow->setScaledContents(true);
    ui->label_background->lower();
    //创建http 网络访问管理对象
    this->manager = new QNetworkAccessManager(this);
    //关联槽函数
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReplied(QNetworkReply*)));
    //发送http请求
    location ="成都";
    getWeatherInfo_BycityName(location);

}

Weather::~Weather()
{
    delete ui;
}

void Weather::on_btn_findCity_clicked()
{
    this->location = ui->lineEdit_city->text();
    getWeatherInfo_BycityName(location);
}

void Weather::getWeatherInfo_BycityName(QString location)
{
    //连接心知天气API，可以免费使用14天，得加钱，剩余天数：12
   QString path = QString("https://api.seniverse.com/v3/weather/now.json?key=ShYu-1HDTE1FCw4zD&location=%1&language=zh-Hans&unit=c").arg(location);
   QUrl url(path);
//    QUrl url("https://api.seniverse.com/v3/weather/now.json?key=Sp-40492mSnCffMnn&location=beijing&language=zh-Hans&unit=c");
   this->manager->get(QNetworkRequest(url));
}

void Weather::paseJson(QByteArray &arr)
{
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(arr,&err);  //获取API 返回的JSON数据
    if(err.error!=QJsonParseError::NoError)
    {
        return;
    }
    else
    {
//        QJsonObject rootObj=doc.object();
//        QJsonArray resArr=rootObj.value("results").toArray();
//        QJsonObject obj=resArr[0].toObject();
//        QJsonArray dailyARR=obj.value("daily").toArray();

//        for(int i=0;i<dailyARR.size();i++)
//        {
//            day myday;
//            QJsonObject dayObj=dailyARR[i].toObject();
//            dayList.insert(i,myday);
//        }

//        day today = dayList.value(1);
//        QString weatherText = "天气：" + today.text;
//        int temperatureText = today.tempture;
//        QString temp = QString::number(temperatureText);
//        ui->label_tianqi->setText(weatherText);
//        ui->label_wendu->setText("温度：" + temp);
        QJsonObject jsonObject = doc.object();
        QJsonArray resultsArray = jsonObject["results"].toArray();
        QJsonObject firstResult = resultsArray.at(0).toObject();

        //提取数据信息

        QString cityName = firstResult["location"].toObject()["name"].toString();
        QString weatherText = firstResult["now"].toObject()["text"].toString();
        QString temperature = firstResult["now"].toObject()["temperature"].toString();
        QString humidity = firstResult["now"].toObject()["humidity"].toString();
        QString where    = firstResult["location"].toObject()["path"].toString();

        QString displayText = "城市：" + cityName + "\n"
                              "天气：" + weatherText + "\n"
                              "温度：" + temperature + " °C\n"
                              "湿度：" + humidity + "%";


         // 将 displayText 设置到对应的标签上，例如：
//        ui->label_city->setText(cityName);
//        ui->label_weather->setText(weatherText);
//        ui->label_temperature->setText(temperature + " °C");
//            ui->label_humidity->setText(humidity + "%");
        ui->label_where->setText("           " + where);
        ui->label_tianqi->setText("          " + weatherText);
//        ui->label_weatherShow->setText(displayText + "°C");
        ui->label_wendu->setText("          " + temperature + "°C");
        ui->label_shidu->setText("          " + humidity + "%");
        qDebug()<<firstResult["now"].toObject()["code"].toString().toInt();
        //根据firstResult["now"].toObject()["code"]的值显示不同的天气图标
        switch (firstResult["now"].toObject()["code"].toString().toInt())
        {
        case 0:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/0.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 1:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/1.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 2:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/2.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 3:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/3.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 4:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/4.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 5:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/5.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 6:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/6.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 7:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/7.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 8:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/8.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 9:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/9.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 10:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/10.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 11:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/11.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 12:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/12.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 13:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/13.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 14:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/14.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 15:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/15.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 16:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/16.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 17:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/17.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 18:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/18.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 19:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/19.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 20:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/20.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 21:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/21.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 22:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/22.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 23:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/23.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 24:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/24.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 25:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/25.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 26:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/26.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 27:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/27.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 28:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/28.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 29:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/29.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 30:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/31.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 31:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/31.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 32:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/32.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 33:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/33.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 34:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/34.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 35:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/35.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 36:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/36.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 37:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/37.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 38:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/38.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        case 99:
            ui->label_weatherShow->setPixmap(QPixmap(":/weather/99.png"));
            ui->label_weatherShow->setScaledContents(true);
            break;
        default:
            break;
        }
    }
}

void Weather::onReplied(QNetworkReply *reply)
{
   qDebug()<<"send Request success!";
   int statusCode=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
   //打印状态码 200 成功  失败 404
   qDebug()<<"operation:"<<reply->operation();
   qDebug()<<"status Code:"<<statusCode;
   qDebug()<<"Url:"<<reply->url();
   qDebug()<<"Header:"<<reply->rawHeaderList();

   if(statusCode!=200||reply->error()!=QNetworkReply::NoError)
   {
       QMessageBox::warning(this,"Reply","Fail to Request weather");
   }
   else
   {
       QByteArray arr=reply->readAll();
       qDebug()<<arr.data();//json

       //解析json
       paseJson(arr);
       //ui->label_weatherShow->setText(location);
   }
   reply->deleteLater();//释放资源
}
