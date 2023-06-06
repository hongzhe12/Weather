
#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Weather;
}
QT_END_NAMESPACE

class Weather : public QMainWindow

{
    Q_OBJECT

public:
    Weather(QWidget* parent = nullptr);
    ~Weather();

    QSqlDatabase database;
    QList<QStringList> data;
    QString adcode = "420300";
    QString query_str;
    // 执行查询
    QSqlQuery query;
    QList<QStringList> fetchDataFromField(const QString& tableName, const QString& fieldName); // 查询某个字段下的所有数据
    QString queryAdcodeByChineseName(const QString& chineseName); // 按中文名查询


private slots:
    void on_pushButtonGetWeather_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButton_clicked();

private:
    Ui::Weather* ui;
};


#endif // WEATHER_H
