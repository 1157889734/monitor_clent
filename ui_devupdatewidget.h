/********************************************************************************
** Form generated from reading UI file 'devupdatewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVUPDATEWIDGET_H
#define UI_DEVUPDATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_devUpdateWidget
{
public:
    QPushButton *permissonManagePushButton;
    QLabel *presetReturnTimeSetLabel;
    QLineEdit *pollingTimeSetLineEdit;
    QPushButton *trainTypeSetPushButton;
    QRadioButton *pollingTimeSetRadioButton_3;
    QLabel *label_2;
    QRadioButton *pollingTimeSetRadioButton;
    QRadioButton *presetReturnTimeSetRadioButton_2;
    QRadioButton *pollingTimeSetRadioButton_4;
    QRadioButton *presetReturnTimeSetRadioButton_3;
    QLabel *pollingTimeSetLabel;
    QRadioButton *presetReturnTimeSetRadioButton;
    QRadioButton *presetReturnTimeSetRadioButton_4;
    QLabel *label_7;
    QRadioButton *pollingTimeSetRadioButton_2;
    QLabel *label;
    QComboBox *trainTypeSetComboBox;
    QLineEdit *presetReturnTimeSetLineEdit;
    QPushButton *alarmPushButton;
    QLabel *label_4;
    QPushButton *canselPushButton;
    QWidget *deviceManagewidget;
    QLineEdit *configFileDisplayLineEdit;
    QLineEdit *brightnessLineEdit;
    QLabel *carriageLabel;
    QPushButton *configFilelookPushButton;
    QComboBox *carriageSelectionComboBox;
    QComboBox *cameraSelectionComboBox;
    QLineEdit *contrastLineEdit;
    QLabel *label_9;
    QPushButton *timeAdjustPushButton;
    QLabel *label_15;
    QComboBox *comboBox;
    QLineEdit *saturationLineEdit;
    QPushButton *imageParamSetPushButton;
    QLabel *saturationLabel;
    QLabel *brightnessLabel;
    QPushButton *clientRebootPushButton;
    QLabel *configFileSelectionLabel;
    QLabel *cameraLabel;
    QLabel *contrastLabel;
    QPushButton *configFileImportPushButton;
    QLabel *devConfigLabel;
    QLabel *updateStatusLabel;
    QLabel *label_18;
    QPushButton *updateBeginPushButton;
    QPushButton *downLoadLogPushButton;
    QTextEdit *updateStatueTextEdit;
    QLineEdit *configFileDisplayLineEdit_2;
    QLabel *label_19;
    QPushButton *configFilelookPushButton_2;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QLabel *sysTimeAdjustLabel;
    QRadioButton *setManalTimeRadioButton;
    QRadioButton *setSysTimeRadioButton;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QLineEdit *timeSetLineEdit;
    QPushButton *timeSetPushButton_2;
    QLabel *label_6;
    QComboBox *PISSetcomboBox;
    QLabel *label_10;
    QPushButton *PISSetPushButton;

    void setupUi(QWidget *devUpdateWidget)
    {
        if (devUpdateWidget->objectName().isEmpty())
            devUpdateWidget->setObjectName(QString::fromUtf8("devUpdateWidget"));
        devUpdateWidget->resize(1024, 630);
        devUpdateWidget->setMinimumSize(QSize(20, 20));
        devUpdateWidget->setFocusPolicy(Qt::StrongFocus);
        devUpdateWidget->setStyleSheet(QString::fromUtf8(""));
        permissonManagePushButton = new QPushButton(devUpdateWidget);
        permissonManagePushButton->setObjectName(QString::fromUtf8("permissonManagePushButton"));
        permissonManagePushButton->setGeometry(QRect(430, 560, 100, 50));
        QFont font;
        font.setPointSize(12);
        permissonManagePushButton->setFont(font);
        permissonManagePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/monres/user.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        presetReturnTimeSetLabel = new QLabel(devUpdateWidget);
        presetReturnTimeSetLabel->setObjectName(QString::fromUtf8("presetReturnTimeSetLabel"));
        presetReturnTimeSetLabel->setGeometry(QRect(50, 80, 211, 21));
        presetReturnTimeSetLabel->setFont(font);
        presetReturnTimeSetLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        pollingTimeSetLineEdit = new QLineEdit(devUpdateWidget);
        pollingTimeSetLineEdit->setObjectName(QString::fromUtf8("pollingTimeSetLineEdit"));
        pollingTimeSetLineEdit->setGeometry(QRect(780, 10, 151, 31));
        pollingTimeSetLineEdit->setFont(font);
        pollingTimeSetLineEdit->setReadOnly(false);
        trainTypeSetPushButton = new QPushButton(devUpdateWidget);
        trainTypeSetPushButton->setObjectName(QString::fromUtf8("trainTypeSetPushButton"));
        trainTypeSetPushButton->setGeometry(QRect(340, 45, 112, 32));
        trainTypeSetPushButton->setFont(font);
        trainTypeSetPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/sure.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        pollingTimeSetRadioButton_3 = new QRadioButton(devUpdateWidget);
        pollingTimeSetRadioButton_3->setObjectName(QString::fromUtf8("pollingTimeSetRadioButton_3"));
        pollingTimeSetRadioButton_3->setGeometry(QRect(440, 13, 61, 22));
        pollingTimeSetRadioButton_3->setFont(font);
        pollingTimeSetRadioButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pollingTimeSetRadioButton_3->setIconSize(QSize(20, 20));
        pollingTimeSetRadioButton_3->setChecked(false);
        label_2 = new QLabel(devUpdateWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 8, 221, 31));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(" #label_2 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_2 * { \n"
"     background-color:; \n"
" }"));
        pollingTimeSetRadioButton = new QRadioButton(devUpdateWidget);
        pollingTimeSetRadioButton->setObjectName(QString::fromUtf8("pollingTimeSetRadioButton"));
        pollingTimeSetRadioButton->setGeometry(QRect(270, 13, 61, 22));
        pollingTimeSetRadioButton->setFont(font);
        pollingTimeSetRadioButton->setAutoFillBackground(false);
        pollingTimeSetRadioButton->setStyleSheet(QString::fromUtf8(""));
        pollingTimeSetRadioButton->setIconSize(QSize(20, 20));
        presetReturnTimeSetRadioButton_2 = new QRadioButton(devUpdateWidget);
        presetReturnTimeSetRadioButton_2->setObjectName(QString::fromUtf8("presetReturnTimeSetRadioButton_2"));
        presetReturnTimeSetRadioButton_2->setGeometry(QRect(350, 80, 81, 22));
        presetReturnTimeSetRadioButton_2->setFont(font);
        presetReturnTimeSetRadioButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        presetReturnTimeSetRadioButton_2->setIconSize(QSize(20, 20));
        pollingTimeSetRadioButton_4 = new QRadioButton(devUpdateWidget);
        pollingTimeSetRadioButton_4->setObjectName(QString::fromUtf8("pollingTimeSetRadioButton_4"));
        pollingTimeSetRadioButton_4->setGeometry(QRect(700, 13, 81, 22));
        pollingTimeSetRadioButton_4->setFont(font);
        pollingTimeSetRadioButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pollingTimeSetRadioButton_4->setChecked(false);
        presetReturnTimeSetRadioButton_3 = new QRadioButton(devUpdateWidget);
        presetReturnTimeSetRadioButton_3->setObjectName(QString::fromUtf8("presetReturnTimeSetRadioButton_3"));
        presetReturnTimeSetRadioButton_3->setGeometry(QRect(440, 80, 81, 22));
        presetReturnTimeSetRadioButton_3->setFont(font);
        presetReturnTimeSetRadioButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        presetReturnTimeSetRadioButton_3->setIconSize(QSize(20, 20));
        presetReturnTimeSetRadioButton_3->setChecked(false);
        pollingTimeSetLabel = new QLabel(devUpdateWidget);
        pollingTimeSetLabel->setObjectName(QString::fromUtf8("pollingTimeSetLabel"));
        pollingTimeSetLabel->setGeometry(QRect(50, 10, 211, 21));
        pollingTimeSetLabel->setFont(font);
        pollingTimeSetLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        presetReturnTimeSetRadioButton = new QRadioButton(devUpdateWidget);
        presetReturnTimeSetRadioButton->setObjectName(QString::fromUtf8("presetReturnTimeSetRadioButton"));
        presetReturnTimeSetRadioButton->setGeometry(QRect(270, 80, 71, 22));
        presetReturnTimeSetRadioButton->setFont(font);
        presetReturnTimeSetRadioButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        presetReturnTimeSetRadioButton->setIconSize(QSize(20, 20));
        presetReturnTimeSetRadioButton_4 = new QRadioButton(devUpdateWidget);
        presetReturnTimeSetRadioButton_4->setObjectName(QString::fromUtf8("presetReturnTimeSetRadioButton_4"));
        presetReturnTimeSetRadioButton_4->setGeometry(QRect(700, 80, 81, 22));
        presetReturnTimeSetRadioButton_4->setFont(font);
        presetReturnTimeSetRadioButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_7 = new QLabel(devUpdateWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(940, 85, 31, 17));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pollingTimeSetRadioButton_2 = new QRadioButton(devUpdateWidget);
        pollingTimeSetRadioButton_2->setObjectName(QString::fromUtf8("pollingTimeSetRadioButton_2"));
        pollingTimeSetRadioButton_2->setGeometry(QRect(350, 13, 61, 22));
        pollingTimeSetRadioButton_2->setFont(font);
        pollingTimeSetRadioButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pollingTimeSetRadioButton_2->setIconSize(QSize(20, 20));
        label = new QLabel(devUpdateWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 91, 31));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(" #label { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label * { \n"
"     background-color:; \n"
" }"));
        trainTypeSetComboBox = new QComboBox(devUpdateWidget);
        trainTypeSetComboBox->setObjectName(QString::fromUtf8("trainTypeSetComboBox"));
        trainTypeSetComboBox->setGeometry(QRect(130, 45, 161, 27));
        trainTypeSetComboBox->setFont(font);
        presetReturnTimeSetLineEdit = new QLineEdit(devUpdateWidget);
        presetReturnTimeSetLineEdit->setObjectName(QString::fromUtf8("presetReturnTimeSetLineEdit"));
        presetReturnTimeSetLineEdit->setGeometry(QRect(780, 80, 151, 31));
        presetReturnTimeSetLineEdit->setFont(font);
        presetReturnTimeSetLineEdit->setReadOnly(false);
        alarmPushButton = new QPushButton(devUpdateWidget);
        alarmPushButton->setObjectName(QString::fromUtf8("alarmPushButton"));
        alarmPushButton->setGeometry(QRect(590, 570, 82, 36));
        alarmPushButton->setFont(font);
        alarmPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/alertoff.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
""));
        alarmPushButton->setCheckable(true);
        label_4 = new QLabel(devUpdateWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(940, 13, 31, 17));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        canselPushButton = new QPushButton(devUpdateWidget);
        canselPushButton->setObjectName(QString::fromUtf8("canselPushButton"));
        canselPushButton->setGeometry(QRect(760, 570, 82, 36));
        canselPushButton->setFont(font);
        canselPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/cancel.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        canselPushButton->setCheckable(true);
        deviceManagewidget = new QWidget(devUpdateWidget);
        deviceManagewidget->setObjectName(QString::fromUtf8("deviceManagewidget"));
        deviceManagewidget->setGeometry(QRect(20, 115, 981, 430));
        deviceManagewidget->setFocusPolicy(Qt::StrongFocus);
        configFileDisplayLineEdit = new QLineEdit(deviceManagewidget);
        configFileDisplayLineEdit->setObjectName(QString::fromUtf8("configFileDisplayLineEdit"));
        configFileDisplayLineEdit->setGeometry(QRect(5, 330, 121, 27));
        configFileDisplayLineEdit->setFont(font);
        brightnessLineEdit = new QLineEdit(deviceManagewidget);
        brightnessLineEdit->setObjectName(QString::fromUtf8("brightnessLineEdit"));
        brightnessLineEdit->setGeometry(QRect(570, 315, 90, 30));
        brightnessLineEdit->setFont(font);
        carriageLabel = new QLabel(deviceManagewidget);
        carriageLabel->setObjectName(QString::fromUtf8("carriageLabel"));
        carriageLabel->setGeometry(QRect(520, 272, 51, 24));
        carriageLabel->setFont(font);
        carriageLabel->setStyleSheet(QString::fromUtf8(""));
        configFilelookPushButton = new QPushButton(deviceManagewidget);
        configFilelookPushButton->setObjectName(QString::fromUtf8("configFilelookPushButton"));
        configFilelookPushButton->setGeometry(QRect(130, 330, 112, 32));
        configFilelookPushButton->setFont(font);
        configFilelookPushButton->setFocusPolicy(Qt::ClickFocus);
        configFilelookPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/browse.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        carriageSelectionComboBox = new QComboBox(deviceManagewidget);
        carriageSelectionComboBox->setObjectName(QString::fromUtf8("carriageSelectionComboBox"));
        carriageSelectionComboBox->setEnabled(true);
        carriageSelectionComboBox->setGeometry(QRect(580, 270, 121, 24));
        carriageSelectionComboBox->setFont(font);
        carriageSelectionComboBox->setMinimumContentsLength(0);
        cameraSelectionComboBox = new QComboBox(deviceManagewidget);
        cameraSelectionComboBox->setObjectName(QString::fromUtf8("cameraSelectionComboBox"));
        cameraSelectionComboBox->setEnabled(true);
        cameraSelectionComboBox->setGeometry(QRect(810, 270, 121, 24));
        cameraSelectionComboBox->setFont(font);
        contrastLineEdit = new QLineEdit(deviceManagewidget);
        contrastLineEdit->setObjectName(QString::fromUtf8("contrastLineEdit"));
        contrastLineEdit->setGeometry(QRect(880, 315, 90, 30));
        contrastLineEdit->setFont(font);
        label_9 = new QLabel(deviceManagewidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(200, 5, 67, 21));
        label_9->setFont(font);
        timeAdjustPushButton = new QPushButton(deviceManagewidget);
        timeAdjustPushButton->setObjectName(QString::fromUtf8("timeAdjustPushButton"));
        timeAdjustPushButton->setGeometry(QRect(170, 170, 137, 39));
        timeAdjustPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/timing.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_15 = new QLabel(deviceManagewidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(680, 240, 101, 21));
        label_15->setFont(font);
        comboBox = new QComboBox(deviceManagewidget);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(220, 270, 101, 25));
        comboBox->setFont(font);
        saturationLineEdit = new QLineEdit(deviceManagewidget);
        saturationLineEdit->setObjectName(QString::fromUtf8("saturationLineEdit"));
        saturationLineEdit->setGeometry(QRect(725, 315, 90, 30));
        saturationLineEdit->setFont(font);
        imageParamSetPushButton = new QPushButton(deviceManagewidget);
        imageParamSetPushButton->setObjectName(QString::fromUtf8("imageParamSetPushButton"));
        imageParamSetPushButton->setGeometry(QRect(700, 360, 161, 43));
        imageParamSetPushButton->setFont(font);
        imageParamSetPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/settingconfig.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        saturationLabel = new QLabel(deviceManagewidget);
        saturationLabel->setObjectName(QString::fromUtf8("saturationLabel"));
        saturationLabel->setGeometry(QRect(665, 315, 52, 24));
        saturationLabel->setFont(font);
        saturationLabel->setStyleSheet(QString::fromUtf8(""));
        brightnessLabel = new QLabel(deviceManagewidget);
        brightnessLabel->setObjectName(QString::fromUtf8("brightnessLabel"));
        brightnessLabel->setGeometry(QRect(515, 315, 51, 24));
        brightnessLabel->setFont(font);
        brightnessLabel->setStyleSheet(QString::fromUtf8(""));
        clientRebootPushButton = new QPushButton(deviceManagewidget);
        clientRebootPushButton->setObjectName(QString::fromUtf8("clientRebootPushButton"));
        clientRebootPushButton->setGeometry(QRect(810, 170, 82, 36));
        clientRebootPushButton->setFont(font);
        clientRebootPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/restat.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        configFileSelectionLabel = new QLabel(deviceManagewidget);
        configFileSelectionLabel->setObjectName(QString::fromUtf8("configFileSelectionLabel"));
        configFileSelectionLabel->setGeometry(QRect(10, 300, 101, 25));
        configFileSelectionLabel->setFont(font);
        configFileSelectionLabel->setStyleSheet(QString::fromUtf8(""));
        cameraLabel = new QLabel(deviceManagewidget);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(750, 272, 61, 24));
        cameraLabel->setFont(font);
        cameraLabel->setStyleSheet(QString::fromUtf8(""));
        contrastLabel = new QLabel(deviceManagewidget);
        contrastLabel->setObjectName(QString::fromUtf8("contrastLabel"));
        contrastLabel->setGeometry(QRect(820, 315, 52, 24));
        contrastLabel->setFont(font);
        contrastLabel->setStyleSheet(QString::fromUtf8(""));
        configFileImportPushButton = new QPushButton(deviceManagewidget);
        configFileImportPushButton->setObjectName(QString::fromUtf8("configFileImportPushButton"));
        configFileImportPushButton->setGeometry(QRect(50, 370, 82, 37));
        configFileImportPushButton->setFont(font);
        configFileImportPushButton->setFocusPolicy(Qt::ClickFocus);
        configFileImportPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/daoru.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        devConfigLabel = new QLabel(deviceManagewidget);
        devConfigLabel->setObjectName(QString::fromUtf8("devConfigLabel"));
        devConfigLabel->setGeometry(QRect(40, 240, 351, 21));
        devConfigLabel->setFont(font);
        devConfigLabel->setStyleSheet(QString::fromUtf8(""));
        updateStatusLabel = new QLabel(deviceManagewidget);
        updateStatusLabel->setObjectName(QString::fromUtf8("updateStatusLabel"));
        updateStatusLabel->setGeometry(QRect(670, 5, 71, 21));
        updateStatusLabel->setFont(font);
        updateStatusLabel->setStyleSheet(QString::fromUtf8(""));
        label_18 = new QLabel(deviceManagewidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(140, 270, 67, 24));
        label_18->setFont(font);
        updateBeginPushButton = new QPushButton(deviceManagewidget);
        updateBeginPushButton->setObjectName(QString::fromUtf8("updateBeginPushButton"));
        updateBeginPushButton->setGeometry(QRect(550, 170, 112, 32));
        updateBeginPushButton->setFont(font);
        updateBeginPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/kaishigegnxin.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        downLoadLogPushButton = new QPushButton(deviceManagewidget);
        downLoadLogPushButton->setObjectName(QString::fromUtf8("downLoadLogPushButton"));
        downLoadLogPushButton->setGeometry(QRect(300, 370, 112, 32));
        downLoadLogPushButton->setFont(font);
        downLoadLogPushButton->setFocusPolicy(Qt::ClickFocus);
        downLoadLogPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/downlog.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"\n"
""));
        downLoadLogPushButton->setAutoDefault(false);
        updateStatueTextEdit = new QTextEdit(deviceManagewidget);
        updateStatueTextEdit->setObjectName(QString::fromUtf8("updateStatueTextEdit"));
        updateStatueTextEdit->setEnabled(false);
        updateStatueTextEdit->setGeometry(QRect(510, 35, 421, 120));
        updateStatueTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        configFileDisplayLineEdit_2 = new QLineEdit(deviceManagewidget);
        configFileDisplayLineEdit_2->setObjectName(QString::fromUtf8("configFileDisplayLineEdit_2"));
        configFileDisplayLineEdit_2->setGeometry(QRect(250, 330, 121, 27));
        configFileDisplayLineEdit_2->setFont(font);
        label_19 = new QLabel(deviceManagewidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(270, 300, 101, 25));
        label_19->setFont(font);
        configFilelookPushButton_2 = new QPushButton(deviceManagewidget);
        configFilelookPushButton_2->setObjectName(QString::fromUtf8("configFilelookPushButton_2"));
        configFilelookPushButton_2->setGeometry(QRect(380, 330, 112, 32));
        configFilelookPushButton_2->setFont(font);
        configFilelookPushButton_2->setFocusPolicy(Qt::ClickFocus);
        configFilelookPushButton_2->setAcceptDrops(false);
        configFilelookPushButton_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"background-image: url(:/monres/browse.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"\n"
""));
        configFilelookPushButton_2->setCheckable(false);
        configFilelookPushButton_2->setAutoRepeatDelay(300);
        configFilelookPushButton_2->setAutoRepeatInterval(100);
        groupBox_2 = new QGroupBox(deviceManagewidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(490, 0, 481, 231));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border-width:1px;\n"
"	border-style:solid;\n"
"	border-color:black;\n"
"}"));
        groupBox_3 = new QGroupBox(deviceManagewidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 0, 461, 231));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border-width:1px;\n"
"	border-style:solid;\n"
"	border-color:black;\n"
"}"));
        sysTimeAdjustLabel = new QLabel(groupBox_3);
        sysTimeAdjustLabel->setObjectName(QString::fromUtf8("sysTimeAdjustLabel"));
        sysTimeAdjustLabel->setGeometry(QRect(120, 120, 201, 27));
        sysTimeAdjustLabel->setFont(font);
        sysTimeAdjustLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 218, 226);\n"
"color: rgb(0, 0, 0);"));
        setManalTimeRadioButton = new QRadioButton(groupBox_3);
        setManalTimeRadioButton->setObjectName(QString::fromUtf8("setManalTimeRadioButton"));
        setManalTimeRadioButton->setGeometry(QRect(20, 65, 91, 30));
        setManalTimeRadioButton->setChecked(false);
        setSysTimeRadioButton = new QRadioButton(groupBox_3);
        setSysTimeRadioButton->setObjectName(QString::fromUtf8("setSysTimeRadioButton"));
        setSysTimeRadioButton->setGeometry(QRect(20, 115, 81, 30));
        setSysTimeRadioButton->setChecked(true);
        groupBox_4 = new QGroupBox(deviceManagewidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 240, 501, 181));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border-width:1px;\n"
"	border-style:solid;\n"
"	border-color:black;\n"
"}"));
        groupBox_5 = new QGroupBox(deviceManagewidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(510, 240, 464, 181));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border-width:1px;\n"
"	border-style:solid;\n"
"	border-color:black;\n"
"}"));
        timeSetLineEdit = new QLineEdit(deviceManagewidget);
        timeSetLineEdit->setObjectName(QString::fromUtf8("timeSetLineEdit"));
        timeSetLineEdit->setGeometry(QRect(130, 70, 201, 27));
        timeSetLineEdit->setFont(font);
        timeSetLineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        timeSetPushButton_2 = new QPushButton(deviceManagewidget);
        timeSetPushButton_2->setObjectName(QString::fromUtf8("timeSetPushButton_2"));
        timeSetPushButton_2->setGeometry(QRect(350, 70, 25, 25));
        timeSetPushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/res/time_set.png);"));
        groupBox_5->raise();
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        label_15->raise();
        saturationLineEdit->raise();
        imageParamSetPushButton->raise();
        saturationLabel->raise();
        brightnessLabel->raise();
        configFileSelectionLabel->raise();
        cameraLabel->raise();
        contrastLabel->raise();
        configFileImportPushButton->raise();
        devConfigLabel->raise();
        updateStatusLabel->raise();
        label_18->raise();
        updateBeginPushButton->raise();
        brightnessLineEdit->raise();
        cameraSelectionComboBox->raise();
        carriageLabel->raise();
        carriageSelectionComboBox->raise();
        clientRebootPushButton->raise();
        comboBox->raise();
        configFileDisplayLineEdit->raise();
        configFilelookPushButton->raise();
        contrastLineEdit->raise();
        label_9->raise();
        timeAdjustPushButton->raise();
        downLoadLogPushButton->raise();
        updateStatueTextEdit->raise();
        configFileDisplayLineEdit_2->raise();
        label_19->raise();
        configFilelookPushButton_2->raise();
        timeSetLineEdit->raise();
        timeSetPushButton_2->raise();
        label_6 = new QLabel(devUpdateWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 1024, 630));
        label_6->setFocusPolicy(Qt::StrongFocus);
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        PISSetcomboBox = new QComboBox(devUpdateWidget);
        PISSetcomboBox->addItem(QString());
        PISSetcomboBox->addItem(QString());
        PISSetcomboBox->addItem(QString());
        PISSetcomboBox->setObjectName(QString::fromUtf8("PISSetcomboBox"));
        PISSetcomboBox->setGeometry(QRect(650, 45, 181, 27));
        PISSetcomboBox->setFont(font);
        label_10 = new QLabel(devUpdateWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(570, 40, 67, 31));
        label_10->setFont(font);
        PISSetPushButton = new QPushButton(devUpdateWidget);
        PISSetPushButton->setObjectName(QString::fromUtf8("PISSetPushButton"));
        PISSetPushButton->setGeometry(QRect(880, 45, 112, 32));
        PISSetPushButton->setFont(font);
        PISSetPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/sure.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_6->raise();
        label_2->raise();
        pollingTimeSetRadioButton->raise();
        presetReturnTimeSetRadioButton_2->raise();
        pollingTimeSetRadioButton_4->raise();
        presetReturnTimeSetRadioButton_3->raise();
        pollingTimeSetLabel->raise();
        presetReturnTimeSetRadioButton->raise();
        presetReturnTimeSetRadioButton_4->raise();
        label_7->raise();
        pollingTimeSetRadioButton_2->raise();
        label->raise();
        trainTypeSetComboBox->raise();
        presetReturnTimeSetLineEdit->raise();
        alarmPushButton->raise();
        label_4->raise();
        trainTypeSetPushButton->raise();
        pollingTimeSetRadioButton_3->raise();
        pollingTimeSetLineEdit->raise();
        presetReturnTimeSetLabel->raise();
        canselPushButton->raise();
        permissonManagePushButton->raise();
        deviceManagewidget->raise();
        PISSetcomboBox->raise();
        label_10->raise();
        PISSetPushButton->raise();

        retranslateUi(devUpdateWidget);

        carriageSelectionComboBox->setCurrentIndex(-1);
        cameraSelectionComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(devUpdateWidget);
    } // setupUi

    void retranslateUi(QWidget *devUpdateWidget)
    {
        devUpdateWidget->setWindowTitle(QCoreApplication::translate("devUpdateWidget", "Form", nullptr));
        permissonManagePushButton->setText(QString());
        presetReturnTimeSetLabel->setText(QCoreApplication::translate("devUpdateWidget", "\350\247\206\351\242\221\347\224\273\351\235\242\350\277\224\345\233\236\351\242\204\347\275\256\347\202\271\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        pollingTimeSetLineEdit->setText(QCoreApplication::translate("devUpdateWidget", "30", nullptr));
        trainTypeSetPushButton->setText(QString());
        pollingTimeSetRadioButton_3->setText(QCoreApplication::translate("devUpdateWidget", "30\347\247\222", nullptr));
        label_2->setText(QString());
        pollingTimeSetRadioButton->setText(QCoreApplication::translate("devUpdateWidget", "10\347\247\222", nullptr));
        presetReturnTimeSetRadioButton_2->setText(QCoreApplication::translate("devUpdateWidget", "10\345\210\206\351\222\237", nullptr));
        pollingTimeSetRadioButton_4->setText(QCoreApplication::translate("devUpdateWidget", "\350\207\252\345\256\232\344\271\211", nullptr));
        presetReturnTimeSetRadioButton_3->setText(QCoreApplication::translate("devUpdateWidget", "15\345\210\206\351\222\237", nullptr));
        pollingTimeSetLabel->setText(QCoreApplication::translate("devUpdateWidget", "\345\217\227\347\224\265\345\274\223\347\233\221\346\216\247\350\275\256\350\257\242\345\210\207\346\215\242\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        presetReturnTimeSetRadioButton->setText(QCoreApplication::translate("devUpdateWidget", "5\345\210\206\351\222\237", nullptr));
        presetReturnTimeSetRadioButton_4->setText(QCoreApplication::translate("devUpdateWidget", "\350\207\252\345\256\232\344\271\211", nullptr));
        label_7->setText(QCoreApplication::translate("devUpdateWidget", "\345\210\206\351\222\237", nullptr));
        pollingTimeSetRadioButton_2->setText(QCoreApplication::translate("devUpdateWidget", "20\347\247\222", nullptr));
        label->setText(QCoreApplication::translate("devUpdateWidget", "   \350\275\246\345\236\213\350\256\276\347\275\256:   ", nullptr));
        presetReturnTimeSetLineEdit->setText(QCoreApplication::translate("devUpdateWidget", "15", nullptr));
        alarmPushButton->setText(QString());
        label_4->setText(QCoreApplication::translate("devUpdateWidget", "\347\247\222", nullptr));
        canselPushButton->setText(QString());
        brightnessLineEdit->setText(QCoreApplication::translate("devUpdateWidget", "50", nullptr));
        carriageLabel->setText(QCoreApplication::translate("devUpdateWidget", "\350\275\246\345\216\242\345\217\267:", nullptr));
        configFilelookPushButton->setText(QString());
        contrastLineEdit->setText(QCoreApplication::translate("devUpdateWidget", "50", nullptr));
        label_9->setText(QCoreApplication::translate("devUpdateWidget", "\346\211\213\345\212\250\346\240\241\346\227\266", nullptr));
        timeAdjustPushButton->setText(QString());
        label_15->setText(QCoreApplication::translate("devUpdateWidget", "\345\233\276\345\275\242\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("devUpdateWidget", "\347\273\210\347\253\257\350\275\257\344\273\266", nullptr));

        saturationLineEdit->setText(QCoreApplication::translate("devUpdateWidget", "50", nullptr));
        imageParamSetPushButton->setText(QString());
        saturationLabel->setText(QCoreApplication::translate("devUpdateWidget", "\351\245\261\345\222\214\345\272\246:", nullptr));
        brightnessLabel->setText(QCoreApplication::translate("devUpdateWidget", "\344\272\256   \345\272\246:", nullptr));
        clientRebootPushButton->setText(QString());
        configFileSelectionLabel->setText(QCoreApplication::translate("devUpdateWidget", "\351\200\211\346\213\251\351\205\215\347\275\256\346\226\207\344\273\266:", nullptr));
        cameraLabel->setText(QCoreApplication::translate("devUpdateWidget", "\346\221\204\345\203\217\346\234\272:", nullptr));
        contrastLabel->setText(QCoreApplication::translate("devUpdateWidget", "\345\257\271\346\257\224\345\272\246:", nullptr));
        configFileImportPushButton->setText(QString());
        devConfigLabel->setText(QCoreApplication::translate("devUpdateWidget", "                                         \350\256\276\345\244\207\351\205\215\347\275\256", nullptr));
        updateStatusLabel->setText(QCoreApplication::translate("devUpdateWidget", "\347\250\213\345\272\217\346\233\264\346\226\260", nullptr));
        label_18->setText(QCoreApplication::translate("devUpdateWidget", "\350\256\276\345\244\207\351\200\211\346\213\251:", nullptr));
        updateBeginPushButton->setText(QString());
        downLoadLogPushButton->setText(QString());
        label_19->setText(QCoreApplication::translate("devUpdateWidget", "\351\200\211\346\213\251\345\215\207\347\272\247\346\226\207\344\273\266:", nullptr));
        configFilelookPushButton_2->setText(QString());
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QString());
        sysTimeAdjustLabel->setText(QString());
        setManalTimeRadioButton->setText(QCoreApplication::translate("devUpdateWidget", "\346\211\213\345\212\250\346\240\241\346\227\266", nullptr));
        setSysTimeRadioButton->setText(QCoreApplication::translate("devUpdateWidget", "\347\263\273\347\273\237\346\240\241\346\227\266", nullptr));
        groupBox_4->setTitle(QString());
        groupBox_5->setTitle(QString());
        timeSetPushButton_2->setText(QString());
        label_6->setText(QString());
        PISSetcomboBox->setItemText(0, QCoreApplication::translate("devUpdateWidget", "\350\200\201\345\233\233\346\226\271\345\215\217\350\256\256", nullptr));
        PISSetcomboBox->setItemText(1, QCoreApplication::translate("devUpdateWidget", "\345\272\236\345\267\264\350\277\252\345\215\217\350\256\256", nullptr));
        PISSetcomboBox->setItemText(2, QCoreApplication::translate("devUpdateWidget", "\346\226\260\345\233\233\346\226\271\345\215\217\350\256\256", nullptr));

        label_10->setText(QCoreApplication::translate("devUpdateWidget", "PIS\350\256\276\347\275\256:", nullptr));
        PISSetPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class devUpdateWidget: public Ui_devUpdateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVUPDATEWIDGET_H
