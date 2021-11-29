/********************************************************************************
** Form generated from reading UI file 'choicelogindevwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICELOGINDEVWIDGET_H
#define UI_CHOICELOGINDEVWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choiceLoginDevWidget
{
public:
    QPushButton *pvmsPushButton;
    QPushButton *cvmsPushButton;
    QLabel *versionLabel;

    void setupUi(QWidget *choiceLoginDevWidget)
    {
        if (choiceLoginDevWidget->objectName().isEmpty())
            choiceLoginDevWidget->setObjectName(QString::fromUtf8("choiceLoginDevWidget"));
        choiceLoginDevWidget->resize(1024, 768);
        choiceLoginDevWidget->setStyleSheet(QString::fromUtf8("#choiceLoginDevWidget { \n"
"border-image: url(:/monres/background.bmp); \n"
"} \n"
"#choiceLoginDevWidget * { \n"
"border-image:url(); \n"
"}"));
        pvmsPushButton = new QPushButton(choiceLoginDevWidget);
        pvmsPushButton->setObjectName(QString::fromUtf8("pvmsPushButton"));
        pvmsPushButton->setGeometry(QRect(550, 330, 274, 97));
        QFont font;
        font.setPointSize(18);
        pvmsPushButton->setFont(font);
        pvmsPushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-image: url(:/monres/preview.bmp);}\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        cvmsPushButton = new QPushButton(choiceLoginDevWidget);
        cvmsPushButton->setObjectName(QString::fromUtf8("cvmsPushButton"));
        cvmsPushButton->setEnabled(true);
        cvmsPushButton->setGeometry(QRect(180, 330, 274, 97));
        cvmsPushButton->setFont(font);
        cvmsPushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/monres/playback.bmp);}\n"
"\n"
"QPushButton:hover{background-color: rgb(246, 246, 246);color: rgb(86, 164, 246);border-color: rgb(255, 255, 255);border-width: 2px;border-style: solid;}\n"
"\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        versionLabel = new QLabel(choiceLoginDevWidget);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setGeometry(QRect(870, 680, 81, 21));
        QFont font1;
        font1.setPointSize(16);
        versionLabel->setFont(font1);

        retranslateUi(choiceLoginDevWidget);

        QMetaObject::connectSlotsByName(choiceLoginDevWidget);
    } // setupUi

    void retranslateUi(QWidget *choiceLoginDevWidget)
    {
        choiceLoginDevWidget->setWindowTitle(QCoreApplication::translate("choiceLoginDevWidget", "Form", nullptr));
        pvmsPushButton->setText(QString());
        cvmsPushButton->setText(QString());
        versionLabel->setText(QCoreApplication::translate("choiceLoginDevWidget", "V1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choiceLoginDevWidget: public Ui_choiceLoginDevWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICELOGINDEVWIDGET_H
