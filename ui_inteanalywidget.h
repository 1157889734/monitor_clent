/********************************************************************************
** Form generated from reading UI file 'inteanalywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEANALYWIDGET_H
#define UI_INTEANALYWIDGET_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inteAnalyWidget
{
public:
    QPushButton *pushButton_15;
    QComboBox *comboBox_4;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QPushButton *pushButton_8;
    QLabel *label_6;
    QPushButton *pushButton_17;
    QComboBox *comboBox_5;
    QLabel *label_12;
    QPushButton *pushButton_16;
    QPushButton *pushButton_11;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_14;
    QTableWidget *recordFileTableWidget;
    QLabel *label_2;
    QLabel *label_7;
    QPushButton *pushButton_33;
    QLabel *label_15;
    QLabel *label;
    QPushButton *alarmPushButton;
    QPushButton *canselPushButton;
    QLabel *label_11;
    QComboBox *StartcomboBox;
    QComboBox *EndcomboBox;
    QDateEdit *StartdateEdit;
    QDateEdit *EnddateEdit;

    void setupUi(QWidget *inteAnalyWidget)
    {
        if (inteAnalyWidget->objectName().isEmpty())
            inteAnalyWidget->setObjectName(QString::fromUtf8("inteAnalyWidget"));
        inteAnalyWidget->resize(1024, 630);
        pushButton_15 = new QPushButton(inteAnalyWidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(90, 240, 112, 32));
        QFont font;
        font.setPointSize(12);
        pushButton_15->setFont(font);
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/search.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        comboBox_4 = new QComboBox(inteAnalyWidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(220, 172, 71, 27));
        comboBox_4->setFont(font);
        label_3 = new QLabel(inteAnalyWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 41, 71, 41));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(" #label_3 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_3 * { \n"
"     background-color:; \n"
" }"));
        comboBox_3 = new QComboBox(inteAnalyWidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(50, 172, 91, 27));
        comboBox_3->setFont(font);
        pushButton_8 = new QPushButton(inteAnalyWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(0, 580, 161, 46));
        pushButton_8->setFont(font);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/faultmapdownload.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_6 = new QLabel(inteAnalyWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 164, 51, 41));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8(" #label_6 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_6 * { \n"
"     background-color:; \n"
" }"));
        pushButton_17 = new QPushButton(inteAnalyWidget);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(680, 575, 51, 51));
        pushButton_17->setStyleSheet(QString::fromUtf8("background-image: url(:/monres/next.bmp);"));
        pushButton_17->setIconSize(QSize(41, 41));
        pushButton_17->setFlat(true);
        comboBox_5 = new QComboBox(inteAnalyWidget);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(80, 205, 91, 27));
        comboBox_5->setFont(font);
        label_12 = new QLabel(inteAnalyWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(300, 0, 724, 561));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/playerbk.png);"));
        pushButton_16 = new QPushButton(inteAnalyWidget);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(165, 580, 161, 46));
        pushButton_16->setFont(font);
        pushButton_16->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/erroconfig.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        pushButton_11 = new QPushButton(inteAnalyWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(610, 575, 51, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-image: url(:/monres/before.bmp);"));
        pushButton_11->setIconSize(QSize(41, 41));
        pushButton_11->setFlat(true);
        label_4 = new QLabel(inteAnalyWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(6, 82, 71, 41));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(" #label_4 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_4 * { \n"
"     background-color:; \n"
" }"));
        label_5 = new QLabel(inteAnalyWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 130, 281, 31));
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
        label_14 = new QLabel(inteAnalyWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 197, 71, 41));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8(" #label_14 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_14 * { \n"
"     background-color:; \n"
" }"));
        recordFileTableWidget = new QTableWidget(inteAnalyWidget);
        recordFileTableWidget->setObjectName(QString::fromUtf8("recordFileTableWidget"));
        recordFileTableWidget->setGeometry(QRect(0, 280, 291, 281));
        recordFileTableWidget->setFont(font);
        recordFileTableWidget->setStyleSheet(QString::fromUtf8("border-style: none;\n"
"background-color: rgb(255,255,255);\n"
"gridline-color: rgb(130, 135, 144);\n"
"border-color: rgb(130, 135, 144);\n"
"border-width: 1px;border-style: solid;"));
        recordFileTableWidget->setShowGrid(false);
        recordFileTableWidget->setColumnCount(0);
        recordFileTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        recordFileTableWidget->horizontalHeader()->setDefaultSectionSize(100);
        recordFileTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        recordFileTableWidget->horizontalHeader()->setStretchLastSection(true);
        recordFileTableWidget->verticalHeader()->setVisible(false);
        label_2 = new QLabel(inteAnalyWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 2, 111, 46));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8(" #label_2 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_2 * { \n"
"     background-color:; \n"
" }"));
        label_7 = new QLabel(inteAnalyWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 164, 71, 41));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8(" #label_7 { \n"
"	color: rgb(0, 0, 0);\n"
"    background-color: rgb(255, 255, 255);\n"
"  } \n"
" #label_7 * { \n"
"     background-color:; \n"
" }"));
        pushButton_33 = new QPushButton(inteAnalyWidget);
        pushButton_33->setObjectName(QString::fromUtf8("pushButton_33"));
        pushButton_33->setGeometry(QRect(400, 580, 180, 43));
        pushButton_33->setFont(font);
        pushButton_33->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/replacevideo.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_15 = new QLabel(inteAnalyWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(190, 92, 41, 21));
        label = new QLabel(inteAnalyWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 55, 31, 21));
        alarmPushButton = new QPushButton(inteAnalyWidget);
        alarmPushButton->setObjectName(QString::fromUtf8("alarmPushButton"));
        alarmPushButton->setGeometry(QRect(800, 590, 82, 36));
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
        canselPushButton = new QPushButton(inteAnalyWidget);
        canselPushButton->setObjectName(QString::fromUtf8("canselPushButton"));
        canselPushButton->setGeometry(QRect(920, 590, 82, 36));
        canselPushButton->setFont(font);
        canselPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/cancel.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_11 = new QLabel(inteAnalyWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 0, 1024, 630));
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        StartcomboBox = new QComboBox(inteAnalyWidget);
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->addItem(QString());
        StartcomboBox->setObjectName(QString::fromUtf8("StartcomboBox"));
        StartcomboBox->setGeometry(QRect(225, 50, 71, 25));
        EndcomboBox = new QComboBox(inteAnalyWidget);
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->addItem(QString());
        EndcomboBox->setObjectName(QString::fromUtf8("EndcomboBox"));
        EndcomboBox->setGeometry(QRect(225, 90, 71, 25));
        StartdateEdit = new QDateEdit(inteAnalyWidget);
        StartdateEdit->setObjectName(QString::fromUtf8("StartdateEdit"));
        StartdateEdit->setGeometry(QRect(80, 50, 101, 31));
        StartdateEdit->setDate(QDate(2020, 1, 1));
        EnddateEdit = new QDateEdit(inteAnalyWidget);
        EnddateEdit->setObjectName(QString::fromUtf8("EnddateEdit"));
        EnddateEdit->setGeometry(QRect(80, 90, 101, 31));
        EnddateEdit->setDate(QDate(2020, 1, 1));
        label_11->raise();
        pushButton_15->raise();
        label_3->raise();
        label_6->raise();
        pushButton_17->raise();
        label_12->raise();
        pushButton_11->raise();
        label_4->raise();
        label_5->raise();
        label_14->raise();
        label_2->raise();
        label_7->raise();
        pushButton_33->raise();
        comboBox_4->raise();
        comboBox_5->raise();
        comboBox_3->raise();
        pushButton_8->raise();
        recordFileTableWidget->raise();
        label_15->raise();
        label->raise();
        alarmPushButton->raise();
        canselPushButton->raise();
        pushButton_16->raise();
        StartcomboBox->raise();
        EndcomboBox->raise();
        StartdateEdit->raise();
        EnddateEdit->raise();

        retranslateUi(inteAnalyWidget);

        QMetaObject::connectSlotsByName(inteAnalyWidget);
    } // setupUi

    void retranslateUi(QWidget *inteAnalyWidget)
    {
        inteAnalyWidget->setWindowTitle(QCoreApplication::translate("inteAnalyWidget", "Form", nullptr));
        pushButton_15->setText(QString());
        comboBox_4->setItemText(0, QCoreApplication::translate("inteAnalyWidget", "\351\242\204\350\255\246", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("inteAnalyWidget", "\345\221\212\350\255\246", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("inteAnalyWidget", "\346\212\245\350\255\246", nullptr));

        label_3->setText(QCoreApplication::translate("inteAnalyWidget", " \350\265\267\345\247\213\346\227\266\351\227\264", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("inteAnalyWidget", "1\350\275\246\345\216\242", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("inteAnalyWidget", "2\350\275\246\345\216\242", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("inteAnalyWidget", "3\350\275\246\345\216\242", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("inteAnalyWidget", "4\350\275\246\345\216\242", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("inteAnalyWidget", "5\350\275\246\345\216\242", nullptr));

        pushButton_8->setText(QString());
        label_6->setText(QCoreApplication::translate("inteAnalyWidget", " \350\275\246\345\216\242\345\217\267", nullptr));
        pushButton_17->setText(QString());
        comboBox_5->setItemText(0, QCoreApplication::translate("inteAnalyWidget", "\347\201\253\350\212\261\346\224\276\347\224\265", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("inteAnalyWidget", "\347\201\253\350\212\261\351\242\221\347\216\207\350\276\203\351\253\230", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("inteAnalyWidget", "\347\201\253\350\212\261\350\276\203\345\244\247", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("inteAnalyWidget", "\346\225\264\344\275\223\347\273\223\346\236\204\345\274\202\345\270\270", nullptr));

        label_12->setText(QString());
        pushButton_16->setText(QString());
        pushButton_11->setText(QString());
        label_4->setText(QCoreApplication::translate("inteAnalyWidget", " \347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_5->setText(QCoreApplication::translate("inteAnalyWidget", " \344\275\215\347\275\256\345\217\212\346\225\205\351\232\234\347\261\273\345\236\213\351\200\211\346\213\251", nullptr));
        label_14->setText(QCoreApplication::translate("inteAnalyWidget", " \346\225\205\351\232\234\347\261\273\345\236\213", nullptr));
        label_2->setText(QCoreApplication::translate("inteAnalyWidget", " \346\243\200\347\264\242\350\256\276\347\275\256", nullptr));
        label_7->setText(QCoreApplication::translate("inteAnalyWidget", " \346\225\205\351\232\234\347\255\211\347\272\247", nullptr));
        pushButton_33->setText(QString());
        label_15->setText(QCoreApplication::translate("inteAnalyWidget", "\346\227\266\351\227\264", nullptr));
        label->setText(QCoreApplication::translate("inteAnalyWidget", "\346\227\266\351\227\264", nullptr));
        alarmPushButton->setText(QString());
        canselPushButton->setText(QString());
        label_11->setText(QString());
        StartcomboBox->setItemText(0, QCoreApplication::translate("inteAnalyWidget", "0\346\227\266", nullptr));
        StartcomboBox->setItemText(1, QCoreApplication::translate("inteAnalyWidget", "1\346\227\266", nullptr));
        StartcomboBox->setItemText(2, QCoreApplication::translate("inteAnalyWidget", "2\346\227\266", nullptr));
        StartcomboBox->setItemText(3, QCoreApplication::translate("inteAnalyWidget", "3\346\227\266", nullptr));
        StartcomboBox->setItemText(4, QCoreApplication::translate("inteAnalyWidget", "4\346\227\266", nullptr));
        StartcomboBox->setItemText(5, QCoreApplication::translate("inteAnalyWidget", "5\346\227\266", nullptr));
        StartcomboBox->setItemText(6, QCoreApplication::translate("inteAnalyWidget", "6\346\227\266", nullptr));
        StartcomboBox->setItemText(7, QCoreApplication::translate("inteAnalyWidget", "7\346\227\266", nullptr));
        StartcomboBox->setItemText(8, QCoreApplication::translate("inteAnalyWidget", "8\346\227\266", nullptr));
        StartcomboBox->setItemText(9, QCoreApplication::translate("inteAnalyWidget", "9\346\227\266", nullptr));
        StartcomboBox->setItemText(10, QCoreApplication::translate("inteAnalyWidget", "10\346\227\266", nullptr));
        StartcomboBox->setItemText(11, QCoreApplication::translate("inteAnalyWidget", "11\346\227\266", nullptr));
        StartcomboBox->setItemText(12, QCoreApplication::translate("inteAnalyWidget", "12\346\227\266", nullptr));
        StartcomboBox->setItemText(13, QCoreApplication::translate("inteAnalyWidget", "13\346\227\266", nullptr));
        StartcomboBox->setItemText(14, QCoreApplication::translate("inteAnalyWidget", "14\346\227\266", nullptr));
        StartcomboBox->setItemText(15, QCoreApplication::translate("inteAnalyWidget", "15\346\227\266", nullptr));
        StartcomboBox->setItemText(16, QCoreApplication::translate("inteAnalyWidget", "16\346\227\266", nullptr));
        StartcomboBox->setItemText(17, QCoreApplication::translate("inteAnalyWidget", "17\346\227\266", nullptr));
        StartcomboBox->setItemText(18, QCoreApplication::translate("inteAnalyWidget", "18\346\227\266", nullptr));
        StartcomboBox->setItemText(19, QCoreApplication::translate("inteAnalyWidget", "19\346\227\266", nullptr));
        StartcomboBox->setItemText(20, QCoreApplication::translate("inteAnalyWidget", "20\346\227\266", nullptr));
        StartcomboBox->setItemText(21, QCoreApplication::translate("inteAnalyWidget", "21\346\227\266", nullptr));
        StartcomboBox->setItemText(22, QCoreApplication::translate("inteAnalyWidget", "22\346\227\266", nullptr));
        StartcomboBox->setItemText(23, QCoreApplication::translate("inteAnalyWidget", "23\346\227\266", nullptr));

        EndcomboBox->setItemText(0, QCoreApplication::translate("inteAnalyWidget", "0\346\227\266", nullptr));
        EndcomboBox->setItemText(1, QCoreApplication::translate("inteAnalyWidget", "1\346\227\266", nullptr));
        EndcomboBox->setItemText(2, QCoreApplication::translate("inteAnalyWidget", "2\346\227\266", nullptr));
        EndcomboBox->setItemText(3, QCoreApplication::translate("inteAnalyWidget", "3\346\227\266", nullptr));
        EndcomboBox->setItemText(4, QCoreApplication::translate("inteAnalyWidget", "4\346\227\266", nullptr));
        EndcomboBox->setItemText(5, QCoreApplication::translate("inteAnalyWidget", "5\346\227\266", nullptr));
        EndcomboBox->setItemText(6, QCoreApplication::translate("inteAnalyWidget", "6\346\227\266", nullptr));
        EndcomboBox->setItemText(7, QCoreApplication::translate("inteAnalyWidget", "7\346\227\266", nullptr));
        EndcomboBox->setItemText(8, QCoreApplication::translate("inteAnalyWidget", "8\346\227\266", nullptr));
        EndcomboBox->setItemText(9, QCoreApplication::translate("inteAnalyWidget", "9\346\227\266", nullptr));
        EndcomboBox->setItemText(10, QCoreApplication::translate("inteAnalyWidget", "10\346\227\266", nullptr));
        EndcomboBox->setItemText(11, QCoreApplication::translate("inteAnalyWidget", "11\346\227\266", nullptr));
        EndcomboBox->setItemText(12, QCoreApplication::translate("inteAnalyWidget", "12\346\227\266", nullptr));
        EndcomboBox->setItemText(13, QCoreApplication::translate("inteAnalyWidget", "13\346\227\266", nullptr));
        EndcomboBox->setItemText(14, QCoreApplication::translate("inteAnalyWidget", "14\346\227\266", nullptr));
        EndcomboBox->setItemText(15, QCoreApplication::translate("inteAnalyWidget", "15\346\227\266", nullptr));
        EndcomboBox->setItemText(16, QCoreApplication::translate("inteAnalyWidget", "16\346\227\266", nullptr));
        EndcomboBox->setItemText(17, QCoreApplication::translate("inteAnalyWidget", "17\346\227\266", nullptr));
        EndcomboBox->setItemText(18, QCoreApplication::translate("inteAnalyWidget", "18\346\227\266", nullptr));
        EndcomboBox->setItemText(19, QCoreApplication::translate("inteAnalyWidget", "19\346\227\266", nullptr));
        EndcomboBox->setItemText(20, QCoreApplication::translate("inteAnalyWidget", "20\346\227\266", nullptr));
        EndcomboBox->setItemText(21, QCoreApplication::translate("inteAnalyWidget", "21\346\227\266", nullptr));
        EndcomboBox->setItemText(22, QCoreApplication::translate("inteAnalyWidget", "22\346\227\266", nullptr));
        EndcomboBox->setItemText(23, QCoreApplication::translate("inteAnalyWidget", "23\346\227\266", nullptr));

        StartdateEdit->setDisplayFormat(QCoreApplication::translate("inteAnalyWidget", "yyyy-MM-dd", nullptr));
        EnddateEdit->setDisplayFormat(QCoreApplication::translate("inteAnalyWidget", "yyyy-MM-dd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inteAnalyWidget: public Ui_inteAnalyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEANALYWIDGET_H
