/********************************************************************************
** Form generated from reading UI file 'recordplaywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDPLAYWIDGET_H
#define UI_RECORDPLAYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_recordPlayWidget
{
public:
    QComboBox *cameraSelectionComboBox;
    QLabel *label_5;
    QPushButton *playNextOnePushButton;
    QPushButton *stopPushButton;
    QLabel *label_7;
    QPushButton *alarmPushButton;
    QLabel *label_8;
    QTableWidget *recordFileTableWidget;
    QPushButton *playLastOnePushButton;
    QPushButton *queryPushButton;
    QLabel *label_2;
    QLabel *label_11;
    QPushButton *downLoadPushButton;
    QPushButton *minusStepPushButton;
    QPushButton *playPushButton;
    QLabel *label_6;
    QLabel *label_4;
    QPushButton *fastForwardPushButton;
    QLabel *label_9;
    QPushButton *slowForwardPushButton;
    QLabel *label_3;
    QComboBox *carSeletionComboBox;
    QPushButton *plusStepPushButton;
    QPushButton *canselPushButton;
    QPushButton *pushButton;
    QLabel *label_12;
    QProgressBar *fileDownloadProgressBar;
    QLabel *startTimeLabel;
    QPushButton *startTimeSetPushButton;
    QLabel *endTimeLabel;
    QPushButton *stopTimeSetPushButton;

    void setupUi(QWidget *recordPlayWidget)
    {
        if (recordPlayWidget->objectName().isEmpty())
            recordPlayWidget->setObjectName(QString::fromUtf8("recordPlayWidget"));
        recordPlayWidget->resize(1024, 630);
        recordPlayWidget->setStyleSheet(QString::fromUtf8(""));
        cameraSelectionComboBox = new QComboBox(recordPlayWidget);
        cameraSelectionComboBox->setObjectName(QString::fromUtf8("cameraSelectionComboBox"));
        cameraSelectionComboBox->setGeometry(QRect(205, 150, 76, 27));
        QFont font;
        font.setPointSize(12);
        cameraSelectionComboBox->setFont(font);
        cameraSelectionComboBox->setFocusPolicy(Qt::NoFocus);
        label_5 = new QLabel(recordPlayWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 110, 111, 33));
        QFont font1;
        font1.setPointSize(18);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8(" #label_5 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_5 * { \n"
"     background-color:; \n"
" }"));
        playNextOnePushButton = new QPushButton(recordPlayWidget);
        playNextOnePushButton->setObjectName(QString::fromUtf8("playNextOnePushButton"));
        playNextOnePushButton->setGeometry(QRect(640, 565, 51, 51));
        playNextOnePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/next.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}"));
        playNextOnePushButton->setIconSize(QSize(41, 41));
        playNextOnePushButton->setFlat(true);
        stopPushButton = new QPushButton(recordPlayWidget);
        stopPushButton->setObjectName(QString::fromUtf8("stopPushButton"));
        stopPushButton->setGeometry(QRect(520, 565, 51, 51));
        stopPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/stop.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        stopPushButton->setIconSize(QSize(41, 41));
        stopPushButton->setFlat(true);
        label_7 = new QLabel(recordPlayWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(140, 140, 151, 41));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8(" #label_7 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_7 * { \n"
"     background-color:; \n"
" }"));
        alarmPushButton = new QPushButton(recordPlayWidget);
        alarmPushButton->setObjectName(QString::fromUtf8("alarmPushButton"));
        alarmPushButton->setGeometry(QRect(700, 575, 82, 36));
        alarmPushButton->setFont(font);
        alarmPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/alertoff.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        alarmPushButton->setCheckable(true);
        label_8 = new QLabel(recordPlayWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 190, 281, 41));
        QFont font2;
        font2.setPointSize(15);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8(" #label_8 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_8 * { \n"
"     background-color:; \n"
" }"));
        recordFileTableWidget = new QTableWidget(recordPlayWidget);
        if (recordFileTableWidget->columnCount() < 3)
            recordFileTableWidget->setColumnCount(3);
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font3);
        __qtablewidgetitem->setBackground(QColor(255, 255, 255));
        recordFileTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font3);
        __qtablewidgetitem1->setBackground(QColor(255, 255, 255));
        recordFileTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font3);
        __qtablewidgetitem2->setBackground(QColor(255, 255, 255));
        recordFileTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        recordFileTableWidget->setObjectName(QString::fromUtf8("recordFileTableWidget"));
        recordFileTableWidget->setGeometry(QRect(10, 250, 281, 291));
        recordFileTableWidget->setFont(font);
        recordFileTableWidget->setStyleSheet(QString::fromUtf8("border-style: none;\n"
"background-color: rgb(255, 255, 255);\n"
"gridline-color: rgb(130, 135, 144);\n"
"border-color: rgb(130, 135, 144);\n"
"border-width: 1px;border-style: solid;\n"
"\n"
""));
        recordFileTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        recordFileTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        recordFileTableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        recordFileTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        recordFileTableWidget->setShowGrid(false);
        recordFileTableWidget->setColumnCount(3);
        recordFileTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        recordFileTableWidget->horizontalHeader()->setDefaultSectionSize(100);
        recordFileTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        recordFileTableWidget->horizontalHeader()->setStretchLastSection(true);
        recordFileTableWidget->verticalHeader()->setVisible(false);
        playLastOnePushButton = new QPushButton(recordPlayWidget);
        playLastOnePushButton->setObjectName(QString::fromUtf8("playLastOnePushButton"));
        playLastOnePushButton->setGeometry(QRect(280, 565, 51, 51));
        playLastOnePushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/before.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        playLastOnePushButton->setIconSize(QSize(41, 41));
        playLastOnePushButton->setFlat(true);
        queryPushButton = new QPushButton(recordPlayWidget);
        queryPushButton->setObjectName(QString::fromUtf8("queryPushButton"));
        queryPushButton->setGeometry(QRect(90, 185, 112, 32));
        queryPushButton->setFont(font);
        queryPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/search.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_2 = new QLabel(recordPlayWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 101, 30));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8(" #label_2 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_2 * { \n"
"     background-color:; \n"
" }"));
        label_11 = new QLabel(recordPlayWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 640, 311, 31));
        label_11->setFont(font2);
        label_11->setStyleSheet(QString::fromUtf8(" #label_11 { \n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_11 * { \n"
"     background-color:; \n"
" }"));
        downLoadPushButton = new QPushButton(recordPlayWidget);
        downLoadPushButton->setObjectName(QString::fromUtf8("downLoadPushButton"));
        downLoadPushButton->setGeometry(QRect(30, 575, 207, 44));
        downLoadPushButton->setFont(font);
        downLoadPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/videodownload.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        minusStepPushButton = new QPushButton(recordPlayWidget);
        minusStepPushButton->setObjectName(QString::fromUtf8("minusStepPushButton"));
        minusStepPushButton->setGeometry(QRect(880, 560, 68, 58));
        minusStepPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/mslow.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        minusStepPushButton->setIconSize(QSize(41, 41));
        minusStepPushButton->setFlat(true);
        playPushButton = new QPushButton(recordPlayWidget);
        playPushButton->setObjectName(QString::fromUtf8("playPushButton"));
        playPushButton->setGeometry(QRect(400, 565, 51, 51));
        playPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/start.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        playPushButton->setIconSize(QSize(41, 41));
        playPushButton->setFlat(true);
        label_6 = new QLabel(recordPlayWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 140, 141, 41));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8(" #label_6 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_6 * { \n"
"     background-color:; \n"
" }"));
        label_4 = new QLabel(recordPlayWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 80, 71, 30));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(" #label_4 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_4 * { \n"
"     background-color:; \n"
" }"));
        fastForwardPushButton = new QPushButton(recordPlayWidget);
        fastForwardPushButton->setObjectName(QString::fromUtf8("fastForwardPushButton"));
        fastForwardPushButton->setGeometry(QRect(580, 565, 51, 51));
        fastForwardPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/fast.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        fastForwardPushButton->setIconSize(QSize(41, 41));
        fastForwardPushButton->setFlat(true);
        label_9 = new QLabel(recordPlayWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(0, 210, 101, 41));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8(" #label_9 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_9 * { \n"
"     background-color:; \n"
" }"));
        slowForwardPushButton = new QPushButton(recordPlayWidget);
        slowForwardPushButton->setObjectName(QString::fromUtf8("slowForwardPushButton"));
        slowForwardPushButton->setGeometry(QRect(340, 565, 51, 51));
        slowForwardPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/slow.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        slowForwardPushButton->setIconSize(QSize(41, 41));
        slowForwardPushButton->setFlat(true);
        label_3 = new QLabel(recordPlayWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 40, 71, 30));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(" #label_3 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_3 * { \n"
"     background-color:; \n"
" }"));
        carSeletionComboBox = new QComboBox(recordPlayWidget);
        carSeletionComboBox->setObjectName(QString::fromUtf8("carSeletionComboBox"));
        carSeletionComboBox->setGeometry(QRect(55, 150, 81, 27));
        carSeletionComboBox->setFont(font);
        carSeletionComboBox->setFocusPolicy(Qt::NoFocus);
        plusStepPushButton = new QPushButton(recordPlayWidget);
        plusStepPushButton->setObjectName(QString::fromUtf8("plusStepPushButton"));
        plusStepPushButton->setGeometry(QRect(950, 560, 68, 58));
        plusStepPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/mfast.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        plusStepPushButton->setIconSize(QSize(41, 41));
        plusStepPushButton->setFlat(true);
        canselPushButton = new QPushButton(recordPlayWidget);
        canselPushButton->setObjectName(QString::fromUtf8("canselPushButton"));
        canselPushButton->setGeometry(QRect(790, 575, 84, 38));
        canselPushButton->setFont(font);
        canselPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/cancel.bmp);\n"
"background-repeat: no-repeat;\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        canselPushButton->setCheckable(true);
        pushButton = new QPushButton(recordPlayWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(460, 565, 51, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/pause1.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(170, 170, 170);\n"
"border-width: 2px;border-style: solid;}\n"
""));
        label_12 = new QLabel(recordPlayWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 0, 1024, 630));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        fileDownloadProgressBar = new QProgressBar(recordPlayWidget);
        fileDownloadProgressBar->setObjectName(QString::fromUtf8("fileDownloadProgressBar"));
        fileDownloadProgressBar->setGeometry(QRect(10, 550, 271, 23));
        fileDownloadProgressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	background-color: rgb(0, 193, 37);\n"
"   border: 1px solid grey;\n"
"   border-radius: 2px;\n"
"   background-color: #FFFFFF;\n"
"}\n"
" \n"
"QProgressBar::chunk {\n"
"   background-color: #4FEE9C;\n"
"   width: 20px;\n"
"}\n"
" \n"
"QProgressBar {\n"
"   border: 1px solid grey;\n"
"   border-radius: 2px;\n"
"   text-align: center;\n"
"}"));
        fileDownloadProgressBar->setValue(0);
        startTimeLabel = new QLabel(recordPlayWidget);
        startTimeLabel->setObjectName(QString::fromUtf8("startTimeLabel"));
        startTimeLabel->setGeometry(QRect(70, 38, 181, 27));
        startTimeLabel->setFont(font);
        startTimeLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        startTimeSetPushButton = new QPushButton(recordPlayWidget);
        startTimeSetPushButton->setObjectName(QString::fromUtf8("startTimeSetPushButton"));
        startTimeSetPushButton->setGeometry(QRect(260, 40, 25, 25));
        startTimeSetPushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/time_set.png);"));
        endTimeLabel = new QLabel(recordPlayWidget);
        endTimeLabel->setObjectName(QString::fromUtf8("endTimeLabel"));
        endTimeLabel->setGeometry(QRect(70, 78, 181, 27));
        endTimeLabel->setFont(font);
        endTimeLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        stopTimeSetPushButton = new QPushButton(recordPlayWidget);
        stopTimeSetPushButton->setObjectName(QString::fromUtf8("stopTimeSetPushButton"));
        stopTimeSetPushButton->setGeometry(QRect(260, 80, 25, 25));
        stopTimeSetPushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/time_set.png);"));
        label_12->raise();
        label_5->raise();
        stopPushButton->raise();
        label_7->raise();
        alarmPushButton->raise();
        label_8->raise();
        playLastOnePushButton->raise();
        label_2->raise();
        label_11->raise();
        minusStepPushButton->raise();
        playPushButton->raise();
        label_6->raise();
        label_4->raise();
        fastForwardPushButton->raise();
        label_9->raise();
        slowForwardPushButton->raise();
        label_3->raise();
        carSeletionComboBox->raise();
        plusStepPushButton->raise();
        cameraSelectionComboBox->raise();
        recordFileTableWidget->raise();
        downLoadPushButton->raise();
        playNextOnePushButton->raise();
        canselPushButton->raise();
        pushButton->raise();
        queryPushButton->raise();
        fileDownloadProgressBar->raise();
        startTimeLabel->raise();
        startTimeSetPushButton->raise();
        endTimeLabel->raise();
        stopTimeSetPushButton->raise();

        retranslateUi(recordPlayWidget);

        QMetaObject::connectSlotsByName(recordPlayWidget);
    } // setupUi

    void retranslateUi(QWidget *recordPlayWidget)
    {
        recordPlayWidget->setWindowTitle(QCoreApplication::translate("recordPlayWidget", "Form", nullptr));
        label_5->setText(QCoreApplication::translate("recordPlayWidget", " \344\275\215\347\275\256\351\200\211\346\213\251", nullptr));
        playNextOnePushButton->setText(QString());
        stopPushButton->setText(QString());
        label_7->setText(QCoreApplication::translate("recordPlayWidget", "   \346\221\204\345\203\217\346\234\272", nullptr));
        alarmPushButton->setText(QString());
        label_8->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = recordFileTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("recordPlayWidget", "\351\200\211\344\270\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = recordFileTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("recordPlayWidget", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = recordFileTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("recordPlayWidget", "\350\247\206\351\242\221", nullptr));
        playLastOnePushButton->setText(QString());
        queryPushButton->setText(QString());
        label_2->setText(QCoreApplication::translate("recordPlayWidget", " \345\233\236\346\224\276\350\256\276\347\275\256", nullptr));
        label_11->setText(QString());
        downLoadPushButton->setText(QString());
        minusStepPushButton->setText(QString());
        playPushButton->setText(QString());
        label_6->setText(QCoreApplication::translate("recordPlayWidget", " \350\275\246\345\216\242\345\217\267", nullptr));
        label_4->setText(QCoreApplication::translate("recordPlayWidget", " \347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        fastForwardPushButton->setText(QString());
        label_9->setText(QCoreApplication::translate("recordPlayWidget", " \346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        slowForwardPushButton->setText(QString());
        label_3->setText(QCoreApplication::translate("recordPlayWidget", " \350\265\267\345\247\213\346\227\266\351\227\264", nullptr));
        plusStepPushButton->setText(QString());
        canselPushButton->setText(QString());
        pushButton->setText(QString());
        label_12->setText(QString());
        startTimeLabel->setText(QString());
        startTimeSetPushButton->setText(QString());
        endTimeLabel->setText(QString());
        stopTimeSetPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class recordPlayWidget: public Ui_recordPlayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDPLAYWIDGET_H
