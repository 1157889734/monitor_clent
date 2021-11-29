/********************************************************************************
** Form generated from reading UI file 'useradd.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERADD_H
#define UI_USERADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userAdd
{
public:
    QPushButton *closePushButton;
    QLineEdit *userNameLineEdit;
    QLabel *userTypeLabel;
    QLabel *userNameLabel;
    QLabel *label_2;
    QLineEdit *passwdLineEdit;
    QPushButton *confirmPushButton;
    QLabel *passwdLabel;
    QComboBox *userTypeComboBox;
    QLabel *passWdWarnLabel;
    QLabel *userNoteLabel;
    QLineEdit *userNoteLineEdit;
    QLabel *userNameWarnLabel;
    QPushButton *canclePushButton;

    void setupUi(QWidget *userAdd)
    {
        if (userAdd->objectName().isEmpty())
            userAdd->setObjectName(QString::fromUtf8("userAdd"));
        userAdd->resize(535, 390);
        closePushButton = new QPushButton(userAdd);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(508, 1, 23, 20));
        closePushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/close.png);"));
        userNameLineEdit = new QLineEdit(userAdd);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));
        userNameLineEdit->setGeometry(QRect(220, 56, 171, 27));
        userNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        userNameLineEdit->setReadOnly(false);
        userNameLineEdit->setPlaceholderText(QString::fromUtf8("\345\277\205\345\241\253"));
        userTypeLabel = new QLabel(userAdd);
        userTypeLabel->setObjectName(QString::fromUtf8("userTypeLabel"));
        userTypeLabel->setGeometry(QRect(130, 160, 67, 17));
        userNameLabel = new QLabel(userAdd);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(130, 60, 67, 17));
        label_2 = new QLabel(userAdd);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 535, 22));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(88, 124, 224);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        passwdLineEdit = new QLineEdit(userAdd);
        passwdLineEdit->setObjectName(QString::fromUtf8("passwdLineEdit"));
        passwdLineEdit->setGeometry(QRect(220, 106, 171, 27));
        passwdLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        passwdLineEdit->setEchoMode(QLineEdit::Normal);
        passwdLineEdit->setReadOnly(false);
        passwdLineEdit->setPlaceholderText(QString::fromUtf8("\345\277\205\345\241\253"));
        confirmPushButton = new QPushButton(userAdd);
        confirmPushButton->setObjectName(QString::fromUtf8("confirmPushButton"));
        confirmPushButton->setGeometry(QRect(130, 270, 99, 27));
        confirmPushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        passwdLabel = new QLabel(userAdd);
        passwdLabel->setObjectName(QString::fromUtf8("passwdLabel"));
        passwdLabel->setGeometry(QRect(130, 110, 67, 17));
        userTypeComboBox = new QComboBox(userAdd);
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->setObjectName(QString::fromUtf8("userTypeComboBox"));
        userTypeComboBox->setGeometry(QRect(220, 156, 171, 27));
        passWdWarnLabel = new QLabel(userAdd);
        passWdWarnLabel->setObjectName(QString::fromUtf8("passWdWarnLabel"));
        passWdWarnLabel->setGeometry(QRect(400, 110, 131, 17));
        passWdWarnLabel->setStyleSheet(QString::fromUtf8("color: rgb(240, 10, 10);"));
        userNoteLabel = new QLabel(userAdd);
        userNoteLabel->setObjectName(QString::fromUtf8("userNoteLabel"));
        userNoteLabel->setGeometry(QRect(130, 210, 61, 17));
        userNoteLineEdit = new QLineEdit(userAdd);
        userNoteLineEdit->setObjectName(QString::fromUtf8("userNoteLineEdit"));
        userNoteLineEdit->setGeometry(QRect(220, 206, 171, 27));
        userNoteLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        userNoteLineEdit->setEchoMode(QLineEdit::Normal);
        userNoteLineEdit->setReadOnly(false);
        userNoteLineEdit->setPlaceholderText(QString::fromUtf8("\345\217\257\344\270\215\345\241\253"));
        userNameWarnLabel = new QLabel(userAdd);
        userNameWarnLabel->setObjectName(QString::fromUtf8("userNameWarnLabel"));
        userNameWarnLabel->setGeometry(QRect(400, 60, 131, 17));
        userNameWarnLabel->setStyleSheet(QString::fromUtf8("color: rgb(240, 10, 10);"));
        canclePushButton = new QPushButton(userAdd);
        canclePushButton->setObjectName(QString::fromUtf8("canclePushButton"));
        canclePushButton->setGeometry(QRect(290, 270, 99, 27));
        canclePushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));

        retranslateUi(userAdd);

        QMetaObject::connectSlotsByName(userAdd);
    } // setupUi

    void retranslateUi(QWidget *userAdd)
    {
        userAdd->setWindowTitle(QCoreApplication::translate("userAdd", "Form", nullptr));
        closePushButton->setText(QString());
        userNameLineEdit->setText(QString());
        userTypeLabel->setText(QCoreApplication::translate("userAdd", "\347\224\250\346\210\267\347\261\273\345\236\213", nullptr));
        userNameLabel->setText(QCoreApplication::translate("userAdd", "\347\224\250\346\210\267\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("userAdd", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        passwdLineEdit->setText(QString());
        confirmPushButton->setText(QCoreApplication::translate("userAdd", "\347\241\256\345\256\232", nullptr));
        passwdLabel->setText(QCoreApplication::translate("userAdd", "\347\224\250\346\210\267\345\257\206\347\240\201", nullptr));
        userTypeComboBox->setItemText(0, QCoreApplication::translate("userAdd", "\350\266\205\347\272\247\347\256\241\347\220\206\345\221\230", nullptr));
        userTypeComboBox->setItemText(1, QCoreApplication::translate("userAdd", "\347\256\241\347\220\206\345\221\230", nullptr));
        userTypeComboBox->setItemText(2, QCoreApplication::translate("userAdd", "\346\223\215\344\275\234\345\221\230", nullptr));

        passWdWarnLabel->setText(QString());
        userNoteLabel->setText(QCoreApplication::translate("userAdd", "\347\224\250\346\210\267\346\263\250\351\207\212", nullptr));
        userNoteLineEdit->setText(QString());
        userNameWarnLabel->setText(QString());
        canclePushButton->setText(QCoreApplication::translate("userAdd", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userAdd: public Ui_userAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERADD_H
