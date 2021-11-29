/********************************************************************************
** Form generated from reading UI file 'presetpasswdconfirm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESETPASSWDCONFIRM_H
#define UI_PRESETPASSWDCONFIRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_presetPasswdConfirm
{
public:
    QPushButton *confirmPushButton;
    QPushButton *canclePushButton;
    QLineEdit *passwordLineEdit;
    QLabel *passwordLabel;
    QLabel *label_2;
    QPushButton *closePushButton;

    void setupUi(QWidget *presetPasswdConfirm)
    {
        if (presetPasswdConfirm->objectName().isEmpty())
            presetPasswdConfirm->setObjectName(QString::fromUtf8("presetPasswdConfirm"));
        presetPasswdConfirm->resize(400, 207);
        confirmPushButton = new QPushButton(presetPasswdConfirm);
        confirmPushButton->setObjectName(QString::fromUtf8("confirmPushButton"));
        confirmPushButton->setGeometry(QRect(80, 140, 99, 27));
        confirmPushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        canclePushButton = new QPushButton(presetPasswdConfirm);
        canclePushButton->setObjectName(QString::fromUtf8("canclePushButton"));
        canclePushButton->setGeometry(QRect(220, 140, 99, 27));
        canclePushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        passwordLineEdit = new QLineEdit(presetPasswdConfirm);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(140, 73, 171, 27));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        passwordLineEdit->setReadOnly(false);
        passwordLabel = new QLabel(presetPasswdConfirm);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setGeometry(QRect(80, 80, 41, 17));
        label_2 = new QLabel(presetPasswdConfirm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 400, 22));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(88, 124, 224);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        closePushButton = new QPushButton(presetPasswdConfirm);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(374, 0, 23, 20));
        closePushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/close.png);"));

        retranslateUi(presetPasswdConfirm);

        QMetaObject::connectSlotsByName(presetPasswdConfirm);
    } // setupUi

    void retranslateUi(QWidget *presetPasswdConfirm)
    {
        presetPasswdConfirm->setWindowTitle(QCoreApplication::translate("presetPasswdConfirm", "Form", nullptr));
        confirmPushButton->setText(QCoreApplication::translate("presetPasswdConfirm", "\347\241\256\345\256\232", nullptr));
        canclePushButton->setText(QCoreApplication::translate("presetPasswdConfirm", "\345\217\226\346\266\210", nullptr));
        passwordLabel->setText(QCoreApplication::translate("presetPasswdConfirm", "\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("presetPasswdConfirm", "\351\242\204\347\275\256\347\202\271\350\256\276\347\275\256", nullptr));
        closePushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class presetPasswdConfirm: public Ui_presetPasswdConfirm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESETPASSWDCONFIRM_H
