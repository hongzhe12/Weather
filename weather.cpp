#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

#include "weather.h"
#include "ui_weather.h"
#include "helper.h"

Weather::Weather(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    // 读取文件
    data = readCSV("citys.csv");
    query_str = ui->comboBox->currentText();
    acode = queryCSV(data, query_str);

    qDebug() <<  query_str << acode;


    // 将数据写入ComboBox组件
    bool skipHeader = true;
    for(const QStringList& list : data)
    {
        if(skipHeader)
        {
            skipHeader = false;
            continue;
        }
        ui->comboBox->addItem(list[0]);
    }
}

Weather::~Weather()
{
    delete ui;
}



struct WeatherInfo
{
    QString province;
    QString city;
    QString adcode;
    QString weather;
    QString temperature;
    QString winddirection;
    QString windpower;
    QString humidity;
    QString reporttime;
    double temperature_float;
    double humidity_float;
};

WeatherInfo parseWeatherInfo(const QJsonObject& jsonObject)
{
    WeatherInfo weatherInfo;

    weatherInfo.province = jsonObject["province"].toString();
    weatherInfo.city = jsonObject["city"].toString();
    weatherInfo.adcode = jsonObject["adcode"].toString();
    weatherInfo.weather = jsonObject["weather"].toString();
    weatherInfo.temperature = jsonObject["temperature"].toString();
    weatherInfo.winddirection = jsonObject["winddirection"].toString();
    weatherInfo.windpower = jsonObject["windpower"].toString();
    weatherInfo.humidity = jsonObject["humidity"].toString();
    weatherInfo.reporttime = jsonObject["reporttime"].toString();
    weatherInfo.temperature_float = jsonObject["temperature_float"].toDouble();
    weatherInfo.humidity_float = jsonObject["humidity_float"].toDouble();

    return weatherInfo;
}

WeatherInfo getWeather(QString apiKey, QString acode)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QNetworkReply* reply;
    QEventLoop loop;

    // 构造 API 请求 URL

    QString apiUrl = QString("https://restapi.amap.com/v3/weather/weatherInfo?city=%2&key=%1").arg(apiKey).arg(acode);

    request.setUrl(QUrl(apiUrl));
    reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject.contains("lives"))
        {
            QJsonArray livesArray = jsonObject["lives"].toArray();
            if(!livesArray.isEmpty())
            {
                QJsonObject weatherObject = livesArray.at(0).toObject();
                WeatherInfo weatherInfo = parseWeatherInfo(weatherObject);
                reply->deleteLater();
                return weatherInfo;
            }
        }
    }

    qDebug() << "Error: Failed to parse weather data";
    reply->deleteLater();
    return WeatherInfo();
}


QString concatenateWeatherInfo(const WeatherInfo& weatherInfo)
{
    QString result;
    result += "省份: " + weatherInfo.province + "\n";
    result += "城市: " + weatherInfo.city + "\n";
    result += "天气: " + weatherInfo.weather + "\n";
    result += "温度: " + weatherInfo.temperature + "\n";
    result += "风向: " + weatherInfo.winddirection + "\n";
    result += "风力: " + weatherInfo.windpower + "\n";
    result += "湿度: " + weatherInfo.humidity + "\n";
    result += "报告时间: " + weatherInfo.reporttime + "\n";

    return result;
}

void Weather::on_pushButtonGetWeather_clicked()
{
    // 查询当前选择城市的acode
    query_str = ui->comboBox->currentText();
    acode = queryCSV(data, query_str);

    QString apiKey = "364c1605664267a5433d9d3ad7c7e8f3"; // 替换为您的天气 API 密钥
    WeatherInfo weatherInfo = getWeather(apiKey, acode);
    QString weatherString = concatenateWeatherInfo(weatherInfo);
    qDebug() << weatherString;
    ui->textBrowser->setPlainText(weatherString);
}


void Weather::on_pushButtonClear_clicked()
{
    ui->textBrowser->clear();
}


void Weather::on_pushButton_clicked()
{
    // 查询当前选择城市的acode
    QString search_str = ui->lineEdit->text();
    ui->comboBox->setCurrentText(search_str);
}

