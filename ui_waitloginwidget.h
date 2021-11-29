/********************************************************************************
** Form generated from reading UI file 'waitloginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITLOGINWIDGET_H
#define UI_WAITLOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_waitLoginWidget
{
public:
    QLabel *coutDownDisplayLabel;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *okPushButton;
    QLabel *versionLabel;

    void setupUi(QWidget *waitLoginWidget)
    {
        if (waitLoginWidget->objectName().isEmpty())
            waitLoginWidget->setObjectName(QString::fromUtf8("waitLoginWidget"));
        waitLoginWidget->resize(1024, 768);
        waitLoginWidget->setStyleSheet(QString::fromUtf8("#waitLoginWidget { \n"
"border-image: url(:/monres/background.bmp); \n"
"} \n"
"#waitLoginWidget * { \n"
"border-image:url(); \n"
"}"));
        coutDownDisplayLabel = new QLabel(waitLoginWidget);
        coutDownDisplayLabel->setObjectName(QString::fromUtf8("coutDownDisplayLabel"));
        coutDownDisplayLabel->setGeometry(QRect(710, 290, 31, 31));
        QFont font;
        font.setPointSize(18);
        coutDownDisplayLabel->setFont(font);
        label_3 = new QLabel(waitLoginWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(740, 290, 31, 31));
        label_3->setFont(font);
        label_2 = new QLabel(waitLoginWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 290, 290, 31));
        label_2->setFont(font);
        okPushButton = new QPushButton(waitLoginWidget);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));
        okPushButton->setGeometry(QRect(390, 380, 274, 101));
        okPushButton->setFont(font);
        okPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/qxdd.bmp);}\n"
"\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}\n"
"QPushButton:release\n"
"{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
""));
        versionLabel = new QLabel(waitLoginWidget);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setGeometry(QRect(880, 700, 81, 21));
        QFont font1;
        font1.setPointSize(16);
        versionLabel->setFont(font1);

        retranslateUi(waitLoginWidget);

        QMetaObject::connectSlotsByName(waitLoginWidget);
    } // setupUi

    void retranslateUi(QWidget *waitLoginWidget)
    {
        waitLoginWidget->setWindowTitle(QCoreApplication::translate("waitLoginWidget", "Form", nullptr));
        coutDownDisplayLabel->setText(QCoreApplication::translate("waitLoginWidget", "12", nullptr));
        label_3->setText(QCoreApplication::translate("waitLoginWidget", "\347\247\222", nullptr));
        label_2->setText(QCoreApplication::translate("waitLoginWidget", "\347\233\221\346\216\247\347\250\213\345\272\217\346\255\243\345\234\250\345\220\257\345\212\250\357\274\214\350\257\267\347\250\215\345\220\216 . . . . . .", nullptr));
        okPushButton->setText(QString());
        versionLabel->setText(QCoreApplication::translate("waitLoginWidget", "V1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class waitLoginWidget: public Ui_waitLoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITLOGINWIDGET_H
