
#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>



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

    QList<QStringList> data;
    QString acode;
    QString query_str;

private slots:
    void on_pushButtonGetWeather_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButton_clicked();

private:
    Ui::Weather* ui;
};


#endif // WEATHER_H
