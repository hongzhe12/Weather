#include "weather.h"
#include "ui_weather.h"



Weather::Weather(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    // 创建数据库连接
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("my.db");

    // 查询数据库
    data = fetchDataFromField("citys","中文名");

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
    // 关闭数据库连接
    database.close();
    delete ui;
}


// 查询某个字段的所有数据，返回QList<QStringList>
QList<QStringList> Weather::fetchDataFromField(const QString& tableName, const QString& fieldName)
{
    QList<QStringList> result;

    // 打开数据库
    if (!database.open()) {
        qDebug() << "无法打开数据库";
        return result;
    }

    // 执行查询
    QSqlQuery query;
    query.exec(QString("SELECT %1 FROM %2").arg(fieldName, tableName));

    // 遍历结果集
    while (query.next()) {
        QStringList row;
        QVariant value = query.value(0);
        row.append(value.toString());
        result.append(row);
    }
    return result;
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

// 获取天气按钮
void Weather::on_pushButtonGetWeather_clicked()
{
    // 查询当前选择城市的acode
    query_str = ui->comboBox->currentText();
    adcode = queryAdcodeByChineseName(query_str);

    qDebug() << "获取天气按钮" << query_str << adcode;

    QString apiKey = "364c1605664267a5433d9d3ad7c7e8f3"; // 替换为您的天气 API 密钥
    WeatherInfo weatherInfo = getWeather(apiKey, adcode);
    QString weatherString = concatenateWeatherInfo(weatherInfo);
    qDebug() << weatherString;
    ui->textBrowser->setPlainText(weatherString);
}


void Weather::on_pushButtonClear_clicked()
{
    ui->textBrowser->clear();
}


// 搜索按钮
void Weather::on_pushButton_clicked()
{
    // 查询当前选择城市的acode
    query_str = ui->lineEdit->text();
    QString last = adcode;  // 上次的adcode
    adcode = queryAdcodeByChineseName(query_str);
    qDebug() << adcode;
    if(QString::compare(adcode,last) == 0)
    {
        QMessageBox::information(this,
        tr("提示"),
        tr("城市未查找到！"),
        QMessageBox::Ok | QMessageBox::Ok);

    }
    ui->comboBox->setCurrentText(query_str);
}


// 数据库查询函数
QString Weather::queryAdcodeByChineseName(const QString& chineseName)
{
    QSqlQuery query;
    query.prepare(QString("SELECT adcode FROM %1 WHERE 中文名 = :chineseName").arg("citys"));
    query.bindValue(":chineseName", chineseName);

    if (!query.exec()) {
        qDebug() << "查询失败";
        return "";
    }

    // 获取查询结果
    if (query.next()) {
        QVariant value = query.value(0);
        adcode = value.toString();
    }
    return adcode;
}

