/********************************************************************************
** Form generated from reading UI file 'usergroupmanage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERGROUPMANAGE_H
#define UI_USERGROUPMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usergroupManage
{
public:
    QLabel *label_2;
    QTableWidget *tableWidget;
    QPushButton *addpushButton;
    QPushButton *deletepushButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *usernamelineEdit;
    QLineEdit *passwdlineEdit;
    QLineEdit *surelineEdit;
    QPushButton *savepushButton;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *usergroupManage)
    {
        if (usergroupManage->objectName().isEmpty())
            usergroupManage->setObjectName(QString::fromUtf8("usergroupManage"));
        usergroupManage->resize(944, 401);
        label_2 = new QLabel(usergroupManage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(470, 25, 67, 17));
        tableWidget = new QTableWidget(usergroupManage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(30, 60, 341, 231));
        tableWidget->setStyleSheet(QString::fromUtf8("border-style: none;\n"
"background-color: rgb(204, 232, 207);\n"
"gridline-color: rgb(255, 255, 255);\n"
"border-color: rgb(130, 135, 144);\n"
"border-width: 1px;border-style: solid;"));
        addpushButton = new QPushButton(usergroupManage);
        addpushButton->setObjectName(QString::fromUtf8("addpushButton"));
        addpushButton->setGeometry(QRect(50, 340, 137, 39));
        addpushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"background-image: url(:/monres/useradd.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        deletepushButton = new QPushButton(usergroupManage);
        deletepushButton->setObjectName(QString::fromUtf8("deletepushButton"));
        deletepushButton->setGeometry(QRect(230, 340, 137, 39));
        deletepushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"background-image: url(:/monres/userdel.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        radioButton = new QRadioButton(usergroupManage);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(570, 80, 112, 23));
        radioButton_2 = new QRadioButton(usergroupManage);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(570, 120, 112, 23));
        radioButton_3 = new QRadioButton(usergroupManage);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(570, 160, 112, 23));
        label_3 = new QLabel(usergroupManage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(510, 200, 67, 17));
        label_4 = new QLabel(usergroupManage);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(510, 245, 67, 17));
        label_5 = new QLabel(usergroupManage);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(510, 290, 67, 17));
        usernamelineEdit = new QLineEdit(usergroupManage);
        usernamelineEdit->setObjectName(QString::fromUtf8("usernamelineEdit"));
        usernamelineEdit->setGeometry(QRect(580, 195, 161, 30));
        usernamelineEdit->setStyleSheet(QString::fromUtf8("QLineEdit:focus{background-color: rgb(204, 232, 207);}"));
        passwdlineEdit = new QLineEdit(usergroupManage);
        passwdlineEdit->setObjectName(QString::fromUtf8("passwdlineEdit"));
        passwdlineEdit->setGeometry(QRect(580, 240, 161, 30));
        passwdlineEdit->setStyleSheet(QString::fromUtf8("QLineEdit:focus{background-color: rgb(204, 232, 207);}"));
        surelineEdit = new QLineEdit(usergroupManage);
        surelineEdit->setObjectName(QString::fromUtf8("surelineEdit"));
        surelineEdit->setGeometry(QRect(580, 285, 161, 30));
        surelineEdit->setStyleSheet(QString::fromUtf8("QLineEdit:focus{background-color: rgb(204, 232, 207);}"));
        savepushButton = new QPushButton(usergroupManage);
        savepushButton->setObjectName(QString::fromUtf8("savepushButton"));
        savepushButton->setGeometry(QRect(610, 340, 137, 39));
        savepushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"background-image: url(:/monres/usersave.bmp);\n"
"border-color: rgb(255, 255, 255);\n"
"border-width: 1px;\n"
"border-style: solid;}\n"
"QPushButton:pressed\n"
"{background-color: rgb(86, 164, 246);color: rgb(255, 255, 255);border-color: rgb(170, 170, 170);border-width: 2px;border-style: solid;}"));
        label_7 = new QLabel(usergroupManage);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 35, 67, 17));
        lineEdit = new QLineEdit(usergroupManage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(10, 5, 901, 391));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label = new QLabel(usergroupManage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 1024, 401));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->raise();
        lineEdit->raise();
        label_2->raise();
        addpushButton->raise();
        deletepushButton->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        usernamelineEdit->raise();
        passwdlineEdit->raise();
        surelineEdit->raise();
        savepushButton->raise();
        label_7->raise();
        tableWidget->raise();

        retranslateUi(usergroupManage);

        QMetaObject::connectSlotsByName(usergroupManage);
    } // setupUi

    void retranslateUi(QWidget *usergroupManage)
    {
        usergroupManage->setWindowTitle(QCoreApplication::translate("usergroupManage", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("usergroupManage", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        addpushButton->setText(QString());
        deletepushButton->setText(QString());
        radioButton->setText(QCoreApplication::translate("usergroupManage", "\350\266\205\347\272\247\347\256\241\347\220\206\345\221\230", nullptr));
        radioButton_2->setText(QCoreApplication::translate("usergroupManage", "\347\256\241\347\220\206\345\221\230\347\224\250\346\210\267", nullptr));
        radioButton_3->setText(QCoreApplication::translate("usergroupManage", "\346\223\215\344\275\234\345\221\230\347\224\250\346\210\267", nullptr));
        label_3->setText(QCoreApplication::translate("usergroupManage", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_4->setText(QCoreApplication::translate("usergroupManage", "\345\257\206    \347\240\201:", nullptr));
        label_5->setText(QCoreApplication::translate("usergroupManage", "\347\241\256    \350\256\244:", nullptr));
        savepushButton->setText(QString());
        label_7->setText(QCoreApplication::translate("usergroupManage", "\347\224\250\346\210\267\345\210\227\350\241\250", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class usergroupManage: public Ui_usergroupManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERGROUPMANAGE_H
