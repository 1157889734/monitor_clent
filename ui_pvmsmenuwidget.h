/********************************************************************************
** Form generated from reading UI file 'pvmsmenuwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVMSMENUWIDGET_H
#define UI_PVMSMENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pvmsMenuWidget
{
public:
    QPushButton *recordPlayMenuPushButton;
    QPushButton *devManageMenuPushButton;
    QPushButton *devUpdateMenuPushButton;
    QPushButton *pvmsMonitorMenuPushButton;
    QPushButton *inteAnalyMenuPushButton;

    void setupUi(QWidget *pvmsMenuWidget)
    {
        if (pvmsMenuWidget->objectName().isEmpty())
            pvmsMenuWidget->setObjectName(QString::fromUtf8("pvmsMenuWidget"));
        pvmsMenuWidget->resize(1024, 768);
        pvmsMenuWidget->setFocusPolicy(Qt::StrongFocus);
        pvmsMenuWidget->setLayoutDirection(Qt::LeftToRight);
        pvmsMenuWidget->setStyleSheet(QString::fromUtf8("#pvmsMenuWidget { \n"
"border-image: url(:/monres/Pantobg.bmp); \n"
"} \n"
"#pvmsMenuWidget * { \n"
"border-image:url(); \n"
"}\n"
""));
        recordPlayMenuPushButton = new QPushButton(pvmsMenuWidget);
        recordPlayMenuPushButton->setObjectName(QString::fromUtf8("recordPlayMenuPushButton"));
        recordPlayMenuPushButton->setGeometry(QRect(205, 35, 203, 102));
        QFont font;
        font.setPointSize(18);
        recordPlayMenuPushButton->setFont(font);
        recordPlayMenuPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(5, 135, 167);}\n"
"\n"
"QPushButton:hover{border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        recordPlayMenuPushButton->setCheckable(true);
        recordPlayMenuPushButton->setFlat(false);
        devManageMenuPushButton = new QPushButton(pvmsMenuWidget);
        devManageMenuPushButton->setObjectName(QString::fromUtf8("devManageMenuPushButton"));
        devManageMenuPushButton->setGeometry(QRect(615, 35, 203, 102));
        devManageMenuPushButton->setFont(font);
        devManageMenuPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(5, 135, 167);}\n"
"\n"
"QPushButton:hover{border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        devManageMenuPushButton->setCheckable(true);
        devManageMenuPushButton->setFlat(false);
        devUpdateMenuPushButton = new QPushButton(pvmsMenuWidget);
        devUpdateMenuPushButton->setObjectName(QString::fromUtf8("devUpdateMenuPushButton"));
        devUpdateMenuPushButton->setEnabled(true);
        devUpdateMenuPushButton->setGeometry(QRect(820, 35, 203, 102));
        devUpdateMenuPushButton->setFont(font);
        devUpdateMenuPushButton->setCursor(QCursor(Qt::ArrowCursor));
        devUpdateMenuPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(5, 135, 167);}\n"
"\n"
"QPushButton:hover{border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        devUpdateMenuPushButton->setIconSize(QSize(203, 102));
        devUpdateMenuPushButton->setCheckable(true);
        devUpdateMenuPushButton->setFlat(false);
        pvmsMonitorMenuPushButton = new QPushButton(pvmsMenuWidget);
        pvmsMonitorMenuPushButton->setObjectName(QString::fromUtf8("pvmsMonitorMenuPushButton"));
        pvmsMonitorMenuPushButton->setGeometry(QRect(0, 35, 203, 102));
        pvmsMonitorMenuPushButton->setFont(font);
        pvmsMonitorMenuPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(5, 135, 167);}\n"
"\n"
"QPushButton:hover{border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        pvmsMonitorMenuPushButton->setCheckable(true);
        pvmsMonitorMenuPushButton->setFlat(false);
        inteAnalyMenuPushButton = new QPushButton(pvmsMenuWidget);
        inteAnalyMenuPushButton->setObjectName(QString::fromUtf8("inteAnalyMenuPushButton"));
        inteAnalyMenuPushButton->setEnabled(true);
        inteAnalyMenuPushButton->setGeometry(QRect(410, 35, 203, 102));
        inteAnalyMenuPushButton->setFont(font);
        inteAnalyMenuPushButton->setCursor(QCursor(Qt::ArrowCursor));
        inteAnalyMenuPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(5, 135, 167);}\n"
"\n"
"QPushButton:hover{border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        inteAnalyMenuPushButton->setIconSize(QSize(203, 102));
        inteAnalyMenuPushButton->setCheckable(true);
        inteAnalyMenuPushButton->setFlat(false);

        retranslateUi(pvmsMenuWidget);

        QMetaObject::connectSlotsByName(pvmsMenuWidget);
    } // setupUi

    void retranslateUi(QWidget *pvmsMenuWidget)
    {
        pvmsMenuWidget->setWindowTitle(QCoreApplication::translate("pvmsMenuWidget", "Form", nullptr));
        recordPlayMenuPushButton->setText(QString());
        devManageMenuPushButton->setText(QString());
        devUpdateMenuPushButton->setText(QString());
        pvmsMonitorMenuPushButton->setText(QString());
        inteAnalyMenuPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pvmsMenuWidget: public Ui_pvmsMenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVMSMENUWIDGET_H
