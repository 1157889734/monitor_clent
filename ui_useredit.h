/********************************************************************************
** Form generated from reading UI file 'useredit.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USEREDIT_H
#define UI_USEREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userEdit
{
public:
    QLabel *passwdLabel;
    QPushButton *canclePushButton;
    QLabel *userNoteLabel;
    QLabel *userNameLabel;
    QLabel *label_2;
    QLineEdit *userNoteLineEdit;
    QComboBox *userTypeComboBox;
    QPushButton *closePushButton;
    QLabel *userTypeLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *passwdLineEdit;
    QPushButton *confirmPushButton;

    void setupUi(QWidget *userEdit)
    {
        if (userEdit->objectName().isEmpty())
            userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->resize(535, 390);
        passwdLabel = new QLabel(userEdit);
        passwdLabel->setObjectName(QString::fromUtf8("passwdLabel"));
        passwdLabel->setGeometry(QRect(130, 110, 67, 17));
        canclePushButton = new QPushButton(userEdit);
        canclePushButton->setObjectName(QString::fromUtf8("canclePushButton"));
        canclePushButton->setGeometry(QRect(290, 270, 99, 27));
        canclePushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        userNoteLabel = new QLabel(userEdit);
        userNoteLabel->setObjectName(QString::fromUtf8("userNoteLabel"));
        userNoteLabel->setGeometry(QRect(130, 210, 61, 17));
        userNameLabel = new QLabel(userEdit);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(130, 60, 67, 17));
        label_2 = new QLabel(userEdit);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, -4, 535, 22));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(88, 124, 224);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        userNoteLineEdit = new QLineEdit(userEdit);
        userNoteLineEdit->setObjectName(QString::fromUtf8("userNoteLineEdit"));
        userNoteLineEdit->setGeometry(QRect(220, 206, 171, 27));
        userNoteLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        userNoteLineEdit->setEchoMode(QLineEdit::Normal);
        userNoteLineEdit->setReadOnly(false);
        userTypeComboBox = new QComboBox(userEdit);
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->setObjectName(QString::fromUtf8("userTypeComboBox"));
        userTypeComboBox->setGeometry(QRect(220, 156, 171, 27));
        closePushButton = new QPushButton(userEdit);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(510, -4, 23, 20));
        closePushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/close.png);"));
        userTypeLabel = new QLabel(userEdit);
        userTypeLabel->setObjectName(QString::fromUtf8("userTypeLabel"));
        userTypeLabel->setGeometry(QRect(130, 160, 67, 17));
        userNameLineEdit = new QLineEdit(userEdit);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));
        userNameLineEdit->setGeometry(QRect(220, 56, 171, 27));
        userNameLineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        userNameLineEdit->setReadOnly(true);
        passwdLineEdit = new QLineEdit(userEdit);
        passwdLineEdit->setObjectName(QString::fromUtf8("passwdLineEdit"));
        passwdLineEdit->setGeometry(QRect(220, 106, 171, 27));
        passwdLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        passwdLineEdit->setEchoMode(QLineEdit::Password);
        passwdLineEdit->setReadOnly(false);
        confirmPushButton = new QPushButton(userEdit);
        confirmPushButton->setObjectName(QString::fromUtf8("confirmPushButton"));
        confirmPushButton->setGeometry(QRect(130, 270, 99, 27));
        confirmPushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));

        retranslateUi(userEdit);

        QMetaObject::connectSlotsByName(userEdit);
    } // setupUi

    void retranslateUi(QWidget *userEdit)
    {
        userEdit->setWindowTitle(QCoreApplication::translate("userEdit", "Form", nullptr));
        passwdLabel->setText(QCoreApplication::translate("userEdit", "\347\224\250\346\210\267\345\257\206\347\240\201", nullptr));
        canclePushButton->setText(QCoreApplication::translate("userEdit", "\345\217\226\346\266\210", nullptr));
        userNoteLabel->setText(QCoreApplication::translate("userEdit", "\347\224\250\346\210\267\346\263\250\351\207\212", nullptr));
        userNameLabel->setText(QCoreApplication::translate("userEdit", "\347\224\250\346\210\267\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("userEdit", "\344\277\256\346\224\271\347\224\250\346\210\267", nullptr));
        userTypeComboBox->setItemText(0, QCoreApplication::translate("userEdit", "\350\266\205\347\272\247\347\256\241\347\220\206\345\221\230", nullptr));
        userTypeComboBox->setItemText(1, QCoreApplication::translate("userEdit", "\347\256\241\347\220\206\345\221\230", nullptr));
        userTypeComboBox->setItemText(2, QCoreApplication::translate("userEdit", "\346\223\215\344\275\234\345\221\230", nullptr));

        closePushButton->setText(QString());
        userTypeLabel->setText(QCoreApplication::translate("userEdit", "\347\224\250\346\210\267\347\261\273\345\236\213", nullptr));
        confirmPushButton->setText(QCoreApplication::translate("userEdit", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userEdit: public Ui_userEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USEREDIT_H
