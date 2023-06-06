/********************************************************************************
** Form generated from reading UI file 'weather.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHER_H
#define UI_WEATHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Weather
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButtonGetWeather;
    QPushButton *pushButtonClear;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Weather)
    {
        if (Weather->objectName().isEmpty())
            Weather->setObjectName(QString::fromUtf8("Weather"));
        Weather->resize(407, 810);
        centralwidget = new QWidget(Weather);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 110, 351, 591));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(16);
        textBrowser->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 60, 211, 31));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(270, 60, 111, 31));
        QFont font2;
        font2.setPointSize(12);
        comboBox->setFont(font2);
        pushButtonGetWeather = new QPushButton(centralwidget);
        pushButtonGetWeather->setObjectName(QString::fromUtf8("pushButtonGetWeather"));
        pushButtonGetWeather->setGeometry(QRect(30, 720, 100, 31));
        pushButtonGetWeather->setFont(font2);
        pushButtonClear = new QPushButton(centralwidget);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));
        pushButtonClear->setGeometry(QRect(269, 720, 100, 31));
        pushButtonClear->setFont(font2);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 20, 111, 31));
        pushButton->setFont(font2);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 20, 211, 31));
        Weather->setCentralWidget(centralwidget);
        label->raise();
        comboBox->raise();
        pushButtonGetWeather->raise();
        pushButtonClear->raise();
        textBrowser->raise();
        pushButton->raise();
        lineEdit->raise();
        menubar = new QMenuBar(Weather);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 407, 17));
        Weather->setMenuBar(menubar);
        statusbar = new QStatusBar(Weather);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Weather->setStatusBar(statusbar);

        retranslateUi(Weather);

        QMetaObject::connectSlotsByName(Weather);
    } // setupUi

    void retranslateUi(QMainWindow *Weather)
    {
        Weather->setWindowTitle(QCoreApplication::translate("Weather", "\351\230\277\347\213\270\345\244\251\346\260\224(v1.0)", nullptr));
        label->setText(QCoreApplication::translate("Weather", "\351\200\211\346\213\251\345\237\216\345\270\202", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Weather", "\345\215\201\345\240\260\345\270\202", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Weather", "\346\255\246\346\261\211\345\270\202", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Weather", "\345\275\223\351\230\263\345\270\202", nullptr));

        pushButtonGetWeather->setText(QCoreApplication::translate("Weather", "\350\216\267\345\217\226\345\244\251\346\260\224", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("Weather", "\346\270\205\347\251\272", nullptr));
        pushButton->setText(QCoreApplication::translate("Weather", "\346\220\234\347\264\242", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("Weather", "\345\234\250\350\277\231\351\207\214\350\276\223\345\205\245\345\237\216\345\270\202\345\220\215\347\247\260\344\276\213\345\246\202:\345\215\201\345\240\260\345\270\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Weather: public Ui_Weather {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHER_H
