/********************************************************************************
** Form generated from reading UI file 'usermanageconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGECONFIG_H
#define UI_USERMANAGECONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usermanageconfig
{
public:
    QLabel *label_15;
    QLabel *updateStatusLabel;
    QLabel *brightnessLabel;
    QDateEdit *dateEdit;
    QLabel *label_10;
    QPushButton *clientRebootPushButton;
    QLineEdit *configFileDisplayLineEdit;
    QLabel *systimeAdjustLabel;
    QLabel *devConfigLabel;
    QPushButton *updateBeginPushButton;
    QComboBox *carriageSelectionComboBox;
    QLabel *label_9;
    QLineEdit *saturationLineEdit;
    QPushButton *timeAdjustPushButton;
    QLabel *label_18;
    QLabel *label_6;
    QLineEdit *brightnessLineEdit;
    QLineEdit *contrastLineEdit;
    QLabel *sysDataAdjustLabel;
    QLabel *label_14;
    QLabel *configFileSelectionLabel;
    QLabel *label_11;
    QComboBox *comboBox;
    QPushButton *configFilelookPushButton;
    QPushButton *configFileImportPushButton;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *carriageLabel;
    QLabel *contrastLabel;
    QLabel *saturationLabel;
    QPushButton *imageParamSetPushButton;
    QLabel *label_5;
    QPushButton *timeSetPushButton;
    QComboBox *cameraSelectionComboBox;
    QLabel *cameraLabel;
    QTimeEdit *timeEdit;
    QPushButton *clientRebootPushButton_2;

    void setupUi(QWidget *usermanageconfig)
    {
        if (usermanageconfig->objectName().isEmpty())
            usermanageconfig->setObjectName(QString::fromUtf8("usermanageconfig"));
        usermanageconfig->resize(944, 435);
        label_15 = new QLabel(usermanageconfig);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(670, 220, 101, 17));
        updateStatusLabel = new QLabel(usermanageconfig);
        updateStatusLabel->setObjectName(QString::fromUtf8("updateStatusLabel"));
        updateStatusLabel->setGeometry(QRect(620, 10, 71, 17));
        QFont font;
        font.setPointSize(12);
        updateStatusLabel->setFont(font);
        updateStatusLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        brightnessLabel = new QLabel(usermanageconfig);
        brightnessLabel->setObjectName(QString::fromUtf8("brightnessLabel"));
        brightnessLabel->setGeometry(QRect(500, 290, 51, 24));
        brightnessLabel->setFont(font);
        brightnessLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit = new QDateEdit(usermanageconfig);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(160, 60, 118, 26));
        dateEdit->setDateTime(QDateTime(QDate(2021, 8, 1), QTime(0, 0, 0)));
        dateEdit->setMaximumTime(QTime(23, 59, 59));
        label_10 = new QLabel(usermanageconfig);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 0, 441, 201));
        QFont font1;
        font1.setPointSize(10);
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8(" #label_10 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_10 * { \n"
"     background-color:; \n"
" }"));
        clientRebootPushButton = new QPushButton(usermanageconfig);
        clientRebootPushButton->setObjectName(QString::fromUtf8("clientRebootPushButton"));
        clientRebootPushButton->setGeometry(QRect(720, 160, 111, 27));
        clientRebootPushButton->setFont(font);
        clientRebootPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        configFileDisplayLineEdit = new QLineEdit(usermanageconfig);
        configFileDisplayLineEdit->setObjectName(QString::fromUtf8("configFileDisplayLineEdit"));
        configFileDisplayLineEdit->setGeometry(QRect(20, 320, 271, 27));
        configFileDisplayLineEdit->setFont(font);
        systimeAdjustLabel = new QLabel(usermanageconfig);
        systimeAdjustLabel->setObjectName(QString::fromUtf8("systimeAdjustLabel"));
        systimeAdjustLabel->setGeometry(QRect(330, 130, 91, 21));
        devConfigLabel = new QLabel(usermanageconfig);
        devConfigLabel->setObjectName(QString::fromUtf8("devConfigLabel"));
        devConfigLabel->setGeometry(QRect(40, 210, 431, 31));
        devConfigLabel->setFont(font);
        devConfigLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        updateBeginPushButton = new QPushButton(usermanageconfig);
        updateBeginPushButton->setObjectName(QString::fromUtf8("updateBeginPushButton"));
        updateBeginPushButton->setGeometry(QRect(600, 160, 101, 27));
        updateBeginPushButton->setFont(font);
        updateBeginPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        carriageSelectionComboBox = new QComboBox(usermanageconfig);
        carriageSelectionComboBox->addItem(QString());
        carriageSelectionComboBox->addItem(QString());
        carriageSelectionComboBox->setObjectName(QString::fromUtf8("carriageSelectionComboBox"));
        carriageSelectionComboBox->setEnabled(true);
        carriageSelectionComboBox->setGeometry(QRect(580, 250, 121, 24));
        carriageSelectionComboBox->setFont(font);
        carriageSelectionComboBox->setMinimumContentsLength(0);
        label_9 = new QLabel(usermanageconfig);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(210, 10, 67, 17));
        saturationLineEdit = new QLineEdit(usermanageconfig);
        saturationLineEdit->setObjectName(QString::fromUtf8("saturationLineEdit"));
        saturationLineEdit->setGeometry(QRect(710, 290, 81, 31));
        saturationLineEdit->setFont(font);
        timeAdjustPushButton = new QPushButton(usermanageconfig);
        timeAdjustPushButton->setObjectName(QString::fromUtf8("timeAdjustPushButton"));
        timeAdjustPushButton->setGeometry(QRect(190, 160, 81, 27));
        timeAdjustPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        label_18 = new QLabel(usermanageconfig);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(140, 250, 67, 17));
        label_18->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_6 = new QLabel(usermanageconfig);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(80, 60, 67, 17));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        brightnessLineEdit = new QLineEdit(usermanageconfig);
        brightnessLineEdit->setObjectName(QString::fromUtf8("brightnessLineEdit"));
        brightnessLineEdit->setGeometry(QRect(560, 290, 81, 31));
        brightnessLineEdit->setFont(font);
        contrastLineEdit = new QLineEdit(usermanageconfig);
        contrastLineEdit->setObjectName(QString::fromUtf8("contrastLineEdit"));
        contrastLineEdit->setGeometry(QRect(860, 290, 81, 31));
        contrastLineEdit->setFont(font);
        sysDataAdjustLabel = new QLabel(usermanageconfig);
        sysDataAdjustLabel->setObjectName(QString::fromUtf8("sysDataAdjustLabel"));
        sysDataAdjustLabel->setGeometry(QRect(160, 130, 161, 21));
        sysDataAdjustLabel->setFont(font1);
        sysDataAdjustLabel->setStyleSheet(QString::fromUtf8(""));
        label_14 = new QLabel(usermanageconfig);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(463, 0, 481, 201));
        label_14->setStyleSheet(QString::fromUtf8(" #label_14 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_14 * { \n"
"     background-color:; \n"
" }"));
        configFileSelectionLabel = new QLabel(usermanageconfig);
        configFileSelectionLabel->setObjectName(QString::fromUtf8("configFileSelectionLabel"));
        configFileSelectionLabel->setGeometry(QRect(20, 290, 101, 17));
        configFileSelectionLabel->setFont(font);
        configFileSelectionLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_11 = new QLabel(usermanageconfig);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 210, 471, 201));
        label_11->setStyleSheet(QString::fromUtf8(" #label_11 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_11 * { \n"
"     background-color:; \n"
" }"));
        comboBox = new QComboBox(usermanageconfig);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(230, 250, 86, 25));
        configFilelookPushButton = new QPushButton(usermanageconfig);
        configFilelookPushButton->setObjectName(QString::fromUtf8("configFilelookPushButton"));
        configFilelookPushButton->setGeometry(QRect(330, 320, 101, 27));
        configFilelookPushButton->setFont(font);
        configFilelookPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        configFileImportPushButton = new QPushButton(usermanageconfig);
        configFileImportPushButton->setObjectName(QString::fromUtf8("configFileImportPushButton"));
        configFileImportPushButton->setGeometry(QRect(90, 360, 81, 27));
        configFileImportPushButton->setFont(font);
        configFileImportPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        label_12 = new QLabel(usermanageconfig);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(80, 90, 67, 17));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_13 = new QLabel(usermanageconfig);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(490, 210, 455, 201));
        label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        carriageLabel = new QLabel(usermanageconfig);
        carriageLabel->setObjectName(QString::fromUtf8("carriageLabel"));
        carriageLabel->setGeometry(QRect(510, 254, 51, 17));
        carriageLabel->setFont(font);
        carriageLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        contrastLabel = new QLabel(usermanageconfig);
        contrastLabel->setObjectName(QString::fromUtf8("contrastLabel"));
        contrastLabel->setGeometry(QRect(800, 290, 52, 24));
        contrastLabel->setFont(font);
        contrastLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        saturationLabel = new QLabel(usermanageconfig);
        saturationLabel->setObjectName(QString::fromUtf8("saturationLabel"));
        saturationLabel->setGeometry(QRect(650, 290, 52, 24));
        saturationLabel->setFont(font);
        saturationLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        imageParamSetPushButton = new QPushButton(usermanageconfig);
        imageParamSetPushButton->setObjectName(QString::fromUtf8("imageParamSetPushButton"));
        imageParamSetPushButton->setGeometry(QRect(670, 370, 81, 27));
        imageParamSetPushButton->setFont(font);
        imageParamSetPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        label_5 = new QLabel(usermanageconfig);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 130, 67, 17));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        timeSetPushButton = new QPushButton(usermanageconfig);
        timeSetPushButton->setObjectName(QString::fromUtf8("timeSetPushButton"));
        timeSetPushButton->setGeometry(QRect(310, 80, 71, 31));
        timeSetPushButton->setFont(font);
        timeSetPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        cameraSelectionComboBox = new QComboBox(usermanageconfig);
        cameraSelectionComboBox->addItem(QString());
        cameraSelectionComboBox->addItem(QString());
        cameraSelectionComboBox->setObjectName(QString::fromUtf8("cameraSelectionComboBox"));
        cameraSelectionComboBox->setEnabled(true);
        cameraSelectionComboBox->setGeometry(QRect(800, 250, 121, 24));
        cameraSelectionComboBox->setFont(font);
        cameraLabel = new QLabel(usermanageconfig);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(736, 254, 61, 17));
        cameraLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        timeEdit = new QTimeEdit(usermanageconfig);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(160, 90, 118, 26));
        timeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(10, 3, 3)));
        clientRebootPushButton_2 = new QPushButton(usermanageconfig);
        clientRebootPushButton_2->setObjectName(QString::fromUtf8("clientRebootPushButton_2"));
        clientRebootPushButton_2->setGeometry(QRect(310, 360, 111, 27));
        clientRebootPushButton_2->setFont(font);
        clientRebootPushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        label_10->raise();
        systimeAdjustLabel->raise();
        label_9->raise();
        timeAdjustPushButton->raise();
        label_6->raise();
        label_14->raise();
        label_11->raise();
        configFilelookPushButton->raise();
        configFileImportPushButton->raise();
        label_12->raise();
        label_13->raise();
        carriageLabel->raise();
        contrastLabel->raise();
        saturationLabel->raise();
        imageParamSetPushButton->raise();
        label_5->raise();
        timeSetPushButton->raise();
        cameraSelectionComboBox->raise();
        cameraLabel->raise();
        timeEdit->raise();
        brightnessLabel->raise();
        brightnessLineEdit->raise();
        carriageSelectionComboBox->raise();
        clientRebootPushButton->raise();
        comboBox->raise();
        configFileDisplayLineEdit->raise();
        configFileSelectionLabel->raise();
        contrastLineEdit->raise();
        dateEdit->raise();
        devConfigLabel->raise();
        label_15->raise();
        label_18->raise();
        saturationLineEdit->raise();
        sysDataAdjustLabel->raise();
        updateBeginPushButton->raise();
        updateStatusLabel->raise();
        clientRebootPushButton_2->raise();

        retranslateUi(usermanageconfig);

        carriageSelectionComboBox->setCurrentIndex(0);
        cameraSelectionComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(usermanageconfig);
    } // setupUi

    void retranslateUi(QWidget *usermanageconfig)
    {
        usermanageconfig->setWindowTitle(QCoreApplication::translate("usermanageconfig", "Form", nullptr));
        label_15->setText(QCoreApplication::translate("usermanageconfig", "\345\233\276\345\275\242\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        updateStatusLabel->setText(QCoreApplication::translate("usermanageconfig", "\347\250\213\345\272\217\346\233\264\346\226\260", nullptr));
        brightnessLabel->setText(QCoreApplication::translate("usermanageconfig", "\344\272\256   \345\272\246:", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("usermanageconfig", "yyyy-MM-dd", nullptr));
        label_10->setText(QString());
        clientRebootPushButton->setText(QCoreApplication::translate("usermanageconfig", "\351\207\215\345\220\257", nullptr));
        systimeAdjustLabel->setText(QString());
        devConfigLabel->setText(QCoreApplication::translate("usermanageconfig", "                                         \350\256\276\345\244\207\351\205\215\347\275\256", nullptr));
        updateBeginPushButton->setText(QCoreApplication::translate("usermanageconfig", "\345\274\200\345\247\213\346\233\264\346\226\260", nullptr));
        carriageSelectionComboBox->setItemText(0, QCoreApplication::translate("usermanageconfig", "1\345\217\267\350\275\246\345\216\242", nullptr));
        carriageSelectionComboBox->setItemText(1, QCoreApplication::translate("usermanageconfig", "8\345\217\267\350\275\246\345\216\242", nullptr));

        label_9->setText(QCoreApplication::translate("usermanageconfig", "\346\211\213\345\212\250\346\240\241\346\227\266", nullptr));
        saturationLineEdit->setText(QCoreApplication::translate("usermanageconfig", "128", nullptr));
        timeAdjustPushButton->setText(QCoreApplication::translate("usermanageconfig", "\346\240\241  \346\227\266", nullptr));
        label_18->setText(QCoreApplication::translate("usermanageconfig", "\350\256\276\345\244\207\351\200\211\346\213\251:", nullptr));
        label_6->setText(QCoreApplication::translate("usermanageconfig", "\346\227\245\346\234\237", nullptr));
        brightnessLineEdit->setText(QCoreApplication::translate("usermanageconfig", "128", nullptr));
        contrastLineEdit->setText(QCoreApplication::translate("usermanageconfig", "128", nullptr));
        sysDataAdjustLabel->setText(QString());
        label_14->setText(QString());
        configFileSelectionLabel->setText(QCoreApplication::translate("usermanageconfig", "\351\200\211\346\213\251\351\205\215\347\275\256\346\226\207\344\273\266:", nullptr));
        label_11->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("usermanageconfig", "\347\273\210\347\253\257\350\275\257\344\273\266", nullptr));

        configFilelookPushButton->setText(QCoreApplication::translate("usermanageconfig", "\346\265\217\350\247\210", nullptr));
        configFileImportPushButton->setText(QCoreApplication::translate("usermanageconfig", "\345\257\274\345\205\245", nullptr));
        label_12->setText(QCoreApplication::translate("usermanageconfig", "\346\227\266\351\227\264", nullptr));
        label_13->setText(QString());
        carriageLabel->setText(QCoreApplication::translate("usermanageconfig", "\350\275\246\345\216\242\345\217\267:", nullptr));
        contrastLabel->setText(QCoreApplication::translate("usermanageconfig", "\345\257\271\346\257\224\345\272\246:", nullptr));
        saturationLabel->setText(QCoreApplication::translate("usermanageconfig", "\351\245\261\345\222\214\345\272\246:", nullptr));
        imageParamSetPushButton->setText(QCoreApplication::translate("usermanageconfig", "\350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        label_5->setText(QCoreApplication::translate("usermanageconfig", "\347\263\273\347\273\237\346\227\266\351\227\264", nullptr));
        timeSetPushButton->setText(QCoreApplication::translate("usermanageconfig", "\347\241\256\345\256\232", nullptr));
        cameraSelectionComboBox->setItemText(0, QCoreApplication::translate("usermanageconfig", "8\345\217\267\346\221\204\345\203\217\346\234\272", nullptr));
        cameraSelectionComboBox->setItemText(1, QCoreApplication::translate("usermanageconfig", "9\345\217\267\346\221\204\345\203\217\346\234\272", nullptr));

        cameraLabel->setText(QCoreApplication::translate("usermanageconfig", "   \346\221\204\345\203\217\346\234\272:", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("usermanageconfig", "hh:mm:ss", nullptr));
        clientRebootPushButton_2->setText(QCoreApplication::translate("usermanageconfig", "\351\207\215\345\220\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class usermanageconfig: public Ui_usermanageconfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGECONFIG_H
