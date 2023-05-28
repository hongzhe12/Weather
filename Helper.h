#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QtCore/QDebug>

#ifndef HELPER_H
#define HELPER_H




class Helper
{
public:
    Helper();
};



// CSV读取函数
static QList<QStringList> readCSV(const QString& filePath)
{
    QList<QStringList> data; // 用于存储CSV数据

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件:" << filePath;
        return data;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        data.append(fields);
    }

    file.close();
    return data;
}


// CSV查询函数
QString queryCSV(const QList<QStringList>& data, const QString& name)
{
    for(const QStringList& row : data)
    {
        // 在这里根据您的查询条件对row进行判断，例如：
        if(row[0] == name)
        {
            return row[1];
        }
    }
    return QString(); // 返回空字符串表示未找到满足条件的结果
}



#endif // HELPER_H
