/********************************************************************************
** Form generated from reading UI file 'pvmsmonitorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVMSMONITORWIDGET_H
#define UI_PVMSMONITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pvmsMonitorWidget
{
public:
    QPushButton *presetNoPushButton_8;
    QPushButton *zoomOutPushButton;
    QPushButton *focusNearPushButton;
    QPushButton *startPollingPushButton;
    QLabel *label;
    QPushButton *cameraSwitchPushButton;
    QLabel *label_10;
    QPushButton *focusFarPushButton;
    QPushButton *presetNoPushButton_3;
    QPushButton *pausePollingPushButton;
    QPushButton *zoomInPushButton;
    QPushButton *presetNoPushButton_2;
    QPushButton *ptzRightPushButton;
    QLabel *label_2;
    QPushButton *ptzLeftPushButton;
    QPushButton *presetSetPushButton;
    QPushButton *presetNoPushButton_7;
    QPushButton *ptzDownPushButton;
    QPushButton *temporarySavePushButton;
    QPushButton *alarmPushButton;
    QPushButton *fillLightSwitchPushButton;
    QPushButton *presetNoPushButton_4;
    QPushButton *pollingNextOnePushButton;
    QPushButton *ptzUpPushButton;
    QPushButton *pollingLastOnePushButton;
    QLabel *label_3;
    QPushButton *presetNoPushButton_6;
    QPushButton *presetNoPushButton;
    QPushButton *presetNoPushButton_5;
    QPushButton *presetGetPushButton;
    QLabel *label_7;
    QPushButton *canselPushButton;
    QLabel *label_11;
    QLabel *mplayLabel;

    void setupUi(QWidget *pvmsMonitorWidget)
    {
        if (pvmsMonitorWidget->objectName().isEmpty())
            pvmsMonitorWidget->setObjectName(QString::fromUtf8("pvmsMonitorWidget"));
        pvmsMonitorWidget->resize(1024, 624);
        presetNoPushButton_8 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_8->setObjectName(QString::fromUtf8("presetNoPushButton_8"));
        presetNoPushButton_8->setGeometry(QRect(970, 360, 53, 32));
        QFont font;
        font.setPointSize(12);
        presetNoPushButton_8->setFont(font);
        presetNoPushButton_8->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/8.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_8->setCheckable(true);
        zoomOutPushButton = new QPushButton(pvmsMonitorWidget);
        zoomOutPushButton->setObjectName(QString::fromUtf8("zoomOutPushButton"));
        zoomOutPushButton->setGeometry(QRect(808, 160, 71, 32));
        zoomOutPushButton->setFont(font);
        zoomOutPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/plus.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        focusNearPushButton = new QPushButton(pvmsMonitorWidget);
        focusNearPushButton->setObjectName(QString::fromUtf8("focusNearPushButton"));
        focusNearPushButton->setGeometry(QRect(930, 210, 71, 32));
        focusNearPushButton->setFont(font);
        focusNearPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/near.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        startPollingPushButton = new QPushButton(pvmsMonitorWidget);
        startPollingPushButton->setObjectName(QString::fromUtf8("startPollingPushButton"));
        startPollingPushButton->setGeometry(QRect(915, 500, 30, 31));
        startPollingPushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/monres/start1.bmp);"));
        startPollingPushButton->setIconSize(QSize(30, 31));
        startPollingPushButton->setCheckable(true);
        startPollingPushButton->setChecked(false);
        startPollingPushButton->setFlat(true);
        label = new QLabel(pvmsMonitorWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(890, 170, 31, 17));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cameraSwitchPushButton = new QPushButton(pvmsMonitorWidget);
        cameraSwitchPushButton->setObjectName(QString::fromUtf8("cameraSwitchPushButton"));
        cameraSwitchPushButton->setGeometry(QRect(785, 460, 112, 32));
        cameraSwitchPushButton->setFont(font);
        cameraSwitchPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/cameraoff.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"\n"
""));
        cameraSwitchPushButton->setCheckable(true);
        label_10 = new QLabel(pvmsMonitorWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(890, 90, 31, 17));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        focusFarPushButton = new QPushButton(pvmsMonitorWidget);
        focusFarPushButton->setObjectName(QString::fromUtf8("focusFarPushButton"));
        focusFarPushButton->setGeometry(QRect(808, 210, 71, 32));
        focusFarPushButton->setFont(font);
        focusFarPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/fare.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        presetNoPushButton_3 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_3->setObjectName(QString::fromUtf8("presetNoPushButton_3"));
        presetNoPushButton_3->setGeometry(QRect(910, 300, 53, 32));
        presetNoPushButton_3->setFont(font);
        presetNoPushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/3.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_3->setCheckable(true);
        pausePollingPushButton = new QPushButton(pvmsMonitorWidget);
        pausePollingPushButton->setObjectName(QString::fromUtf8("pausePollingPushButton"));
        pausePollingPushButton->setGeometry(QRect(860, 500, 30, 31));
        pausePollingPushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/monres/pause.bmp);"));
        pausePollingPushButton->setIconSize(QSize(30, 31));
        pausePollingPushButton->setCheckable(true);
        pausePollingPushButton->setFlat(true);
        zoomInPushButton = new QPushButton(pvmsMonitorWidget);
        zoomInPushButton->setObjectName(QString::fromUtf8("zoomInPushButton"));
        zoomInPushButton->setGeometry(QRect(930, 160, 71, 32));
        zoomInPushButton->setFont(font);
        zoomInPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/substruct.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"\n"
""));
        presetNoPushButton_2 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_2->setObjectName(QString::fromUtf8("presetNoPushButton_2"));
        presetNoPushButton_2->setGeometry(QRect(850, 300, 53, 32));
        presetNoPushButton_2->setFont(font);
        presetNoPushButton_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{background-image: url(:/monres/2.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_2->setCheckable(true);
        ptzRightPushButton = new QPushButton(pvmsMonitorWidget);
        ptzRightPushButton->setObjectName(QString::fromUtf8("ptzRightPushButton"));
        ptzRightPushButton->setGeometry(QRect(950, 80, 71, 32));
        ptzRightPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/right.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        ptzRightPushButton->setIconSize(QSize(50, 50));
        label_2 = new QLabel(pvmsMonitorWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(890, 220, 31, 17));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        ptzLeftPushButton = new QPushButton(pvmsMonitorWidget);
        ptzLeftPushButton->setObjectName(QString::fromUtf8("ptzLeftPushButton"));
        ptzLeftPushButton->setGeometry(QRect(790, 80, 71, 32));
        ptzLeftPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/left.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        ptzLeftPushButton->setIconSize(QSize(50, 50));
        presetSetPushButton = new QPushButton(pvmsMonitorWidget);
        presetSetPushButton->setObjectName(QString::fromUtf8("presetSetPushButton"));
        presetSetPushButton->setGeometry(QRect(785, 420, 112, 32));
        presetSetPushButton->setFont(font);
        presetSetPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/setuse.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        presetSetPushButton->setCheckable(false);
        presetSetPushButton->setChecked(false);
        presetNoPushButton_7 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_7->setObjectName(QString::fromUtf8("presetNoPushButton_7"));
        presetNoPushButton_7->setGeometry(QRect(910, 360, 53, 32));
        presetNoPushButton_7->setFont(font);
        presetNoPushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/7.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_7->setCheckable(true);
        ptzDownPushButton = new QPushButton(pvmsMonitorWidget);
        ptzDownPushButton->setObjectName(QString::fromUtf8("ptzDownPushButton"));
        ptzDownPushButton->setGeometry(QRect(850, 120, 112, 32));
        ptzDownPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/down.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        ptzDownPushButton->setIconSize(QSize(50, 50));
        temporarySavePushButton = new QPushButton(pvmsMonitorWidget);
        temporarySavePushButton->setObjectName(QString::fromUtf8("temporarySavePushButton"));
        temporarySavePushButton->setGeometry(QRect(830, 540, 166, 32));
        temporarySavePushButton->setFont(font);
        temporarySavePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/savevedio.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        alarmPushButton = new QPushButton(pvmsMonitorWidget);
        alarmPushButton->setObjectName(QString::fromUtf8("alarmPushButton"));
        alarmPushButton->setGeometry(QRect(810, 580, 82, 36));
        alarmPushButton->setFont(font);
        alarmPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/alertoff.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        alarmPushButton->setCheckable(true);
        fillLightSwitchPushButton = new QPushButton(pvmsMonitorWidget);
        fillLightSwitchPushButton->setObjectName(QString::fromUtf8("fillLightSwitchPushButton"));
        fillLightSwitchPushButton->setGeometry(QRect(910, 460, 112, 32));
        fillLightSwitchPushButton->setFont(font);
        fillLightSwitchPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/ligtoff.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
""));
        fillLightSwitchPushButton->setCheckable(true);
        presetNoPushButton_4 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_4->setObjectName(QString::fromUtf8("presetNoPushButton_4"));
        presetNoPushButton_4->setGeometry(QRect(970, 300, 53, 32));
        presetNoPushButton_4->setFont(font);
        presetNoPushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/4.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_4->setCheckable(true);
        pollingNextOnePushButton = new QPushButton(pvmsMonitorWidget);
        pollingNextOnePushButton->setObjectName(QString::fromUtf8("pollingNextOnePushButton"));
        pollingNextOnePushButton->setGeometry(QRect(970, 500, 30, 31));
        pollingNextOnePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/monres/fast.bmp);}\n"
"QPushButton:pressed\n"
"{background-color: rgb(255, 255, 255);color: rgb(255, 255, 255);border-color: rgb(86, 164, 246);border-width: 6px;border-style: solid;}"));
        pollingNextOnePushButton->setIconSize(QSize(30, 31));
        pollingNextOnePushButton->setFlat(true);
        ptzUpPushButton = new QPushButton(pvmsMonitorWidget);
        ptzUpPushButton->setObjectName(QString::fromUtf8("ptzUpPushButton"));
        ptzUpPushButton->setGeometry(QRect(850, 40, 112, 32));
        ptzUpPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/up.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(192, 192, 192);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"\n"
"\n"
""));
        ptzUpPushButton->setIconSize(QSize(50, 50));
        ptzUpPushButton->setFlat(false);
        pollingLastOnePushButton = new QPushButton(pvmsMonitorWidget);
        pollingLastOnePushButton->setObjectName(QString::fromUtf8("pollingLastOnePushButton"));
        pollingLastOnePushButton->setGeometry(QRect(800, 500, 30, 31));
        pollingLastOnePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/monres/slow.bmp);}\n"
"QPushButton:pressed\n"
"{background-color: rgb(255, 255, 255);color: rgb(255, 255, 255);border-color: rgb(86, 164, 246);border-width: 6px;border-style: solid;}"));
        pollingLastOnePushButton->setIconSize(QSize(30, 31));
        pollingLastOnePushButton->setFlat(true);
        label_3 = new QLabel(pvmsMonitorWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(794, 0, 231, 40));
        QFont font1;
        font1.setPointSize(18);
        label_3->setFont(font1);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8(" #label_3 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_3 * { \n"
"     background-color:; \n"
" }"));
        label_3->setTextFormat(Qt::AutoText);
        presetNoPushButton_6 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_6->setObjectName(QString::fromUtf8("presetNoPushButton_6"));
        presetNoPushButton_6->setGeometry(QRect(850, 360, 53, 32));
        presetNoPushButton_6->setFont(font);
        presetNoPushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/6.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_6->setCheckable(true);
        presetNoPushButton = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton->setObjectName(QString::fromUtf8("presetNoPushButton"));
        presetNoPushButton->setGeometry(QRect(790, 300, 53, 32));
        presetNoPushButton->setFont(font);
        presetNoPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/11.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton->setCheckable(true);
        presetNoPushButton->setChecked(false);
        presetNoPushButton->setFlat(false);
        presetNoPushButton_5 = new QPushButton(pvmsMonitorWidget);
        presetNoPushButton_5->setObjectName(QString::fromUtf8("presetNoPushButton_5"));
        presetNoPushButton_5->setGeometry(QRect(790, 360, 53, 32));
        presetNoPushButton_5->setFont(font);
        presetNoPushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/5.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetNoPushButton_5->setCheckable(true);
        presetGetPushButton = new QPushButton(pvmsMonitorWidget);
        presetGetPushButton->setObjectName(QString::fromUtf8("presetGetPushButton"));
        presetGetPushButton->setGeometry(QRect(910, 420, 112, 32));
        presetGetPushButton->setFont(font);
        presetGetPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/res/usepreset.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(255, 255, 255);color: rgb(255, 255, 255);border-color: rgb(86, 164, 246);border-width: 6px;border-style: solid;}"));
        label_7 = new QLabel(pvmsMonitorWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(794, 250, 231, 40));
        label_7->setFont(font1);
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setStyleSheet(QString::fromUtf8(" #label_7 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_7 * { \n"
"     background-color:; \n"
" }"));
        label_7->setTextFormat(Qt::AutoText);
        canselPushButton = new QPushButton(pvmsMonitorWidget);
        canselPushButton->setObjectName(QString::fromUtf8("canselPushButton"));
        canselPushButton->setGeometry(QRect(930, 580, 82, 36));
        canselPushButton->setFont(font);
        canselPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/cancel.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        canselPushButton->setCheckable(true);
        label_11 = new QLabel(pvmsMonitorWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 0, 1024, 624));
        label_11->setToolTipDuration(0);
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        mplayLabel = new QLabel(pvmsMonitorWidget);
        mplayLabel->setObjectName(QString::fromUtf8("mplayLabel"));
        mplayLabel->setGeometry(QRect(0, 0, 784, 624));
        mplayLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        label_11->raise();
        label_2->raise();
        ptzDownPushButton->raise();
        ptzUpPushButton->raise();
        label_3->raise();
        presetGetPushButton->raise();
        label_7->raise();
        zoomOutPushButton->raise();
        zoomInPushButton->raise();
        label->raise();
        label_10->raise();
        ptzLeftPushButton->raise();
        ptzRightPushButton->raise();
        presetNoPushButton_2->raise();
        presetNoPushButton_3->raise();
        presetNoPushButton_7->raise();
        presetNoPushButton_6->raise();
        presetNoPushButton_5->raise();
        presetNoPushButton_8->raise();
        presetNoPushButton_4->raise();
        presetSetPushButton->raise();
        startPollingPushButton->raise();
        temporarySavePushButton->raise();
        fillLightSwitchPushButton->raise();
        cameraSwitchPushButton->raise();
        alarmPushButton->raise();
        pausePollingPushButton->raise();
        pollingLastOnePushButton->raise();
        pollingNextOnePushButton->raise();
        focusFarPushButton->raise();
        focusNearPushButton->raise();
        canselPushButton->raise();
        presetNoPushButton->raise();
        mplayLabel->raise();

        retranslateUi(pvmsMonitorWidget);

        QMetaObject::connectSlotsByName(pvmsMonitorWidget);
    } // setupUi

    void retranslateUi(QWidget *pvmsMonitorWidget)
    {
        pvmsMonitorWidget->setWindowTitle(QCoreApplication::translate("pvmsMonitorWidget", "Form", nullptr));
        presetNoPushButton_8->setText(QString());
        zoomOutPushButton->setText(QString());
        focusNearPushButton->setText(QString());
        startPollingPushButton->setText(QString());
        label->setText(QCoreApplication::translate("pvmsMonitorWidget", "\350\260\203\347\204\246", nullptr));
        cameraSwitchPushButton->setText(QString());
        label_10->setText(QCoreApplication::translate("pvmsMonitorWidget", "\346\226\271\345\220\221", nullptr));
        focusFarPushButton->setText(QString());
        presetNoPushButton_3->setText(QString());
        pausePollingPushButton->setText(QString());
        zoomInPushButton->setText(QString());
        presetNoPushButton_2->setText(QString());
        ptzRightPushButton->setText(QString());
        label_2->setText(QCoreApplication::translate("pvmsMonitorWidget", "\350\201\232\347\204\246", nullptr));
        ptzLeftPushButton->setText(QString());
        presetSetPushButton->setText(QString());
        presetNoPushButton_7->setText(QString());
        ptzDownPushButton->setText(QString());
        temporarySavePushButton->setText(QString());
        alarmPushButton->setText(QString());
        fillLightSwitchPushButton->setText(QString());
        presetNoPushButton_4->setText(QString());
        pollingNextOnePushButton->setText(QString());
        ptzUpPushButton->setText(QString());
        pollingLastOnePushButton->setText(QString());
        label_3->setText(QCoreApplication::translate("pvmsMonitorWidget", "  \344\272\221\345\217\260\346\216\247\345\210\266", nullptr));
        presetNoPushButton_6->setText(QString());
        presetNoPushButton->setText(QString());
        presetNoPushButton_5->setText(QString());
        presetGetPushButton->setText(QString());
        label_7->setText(QCoreApplication::translate("pvmsMonitorWidget", "  \351\242\204\347\275\256\347\202\271", nullptr));
        canselPushButton->setText(QString());
        label_11->setText(QString());
        mplayLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pvmsMonitorWidget: public Ui_pvmsMonitorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVMSMONITORWIDGET_H
