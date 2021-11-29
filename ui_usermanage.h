/********************************************************************************
** Form generated from reading UI file 'usermanage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGE_H
#define UI_USERMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userManage
{
public:
    QLabel *label_2;
    QTableWidget *tableWidget;
    QPushButton *closePushButton;
    QPushButton *userDelPushButton;
    QPushButton *userEditPushButton;
    QPushButton *userAddPushButton;

    void setupUi(QWidget *userManage)
    {
        if (userManage->objectName().isEmpty())
            userManage->setObjectName(QString::fromUtf8("userManage"));
        userManage->resize(535, 390);
        label_2 = new QLabel(userManage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 535, 22));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(88, 124, 224);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidget = new QTableWidget(userManage);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(38, 40, 461, 251));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableWidget->verticalHeader()->setVisible(false);
        closePushButton = new QPushButton(userManage);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(508, 1, 23, 20));
        closePushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/res/close.png);"));
        userDelPushButton = new QPushButton(userManage);
        userDelPushButton->setObjectName(QString::fromUtf8("userDelPushButton"));
        userDelPushButton->setGeometry(QRect(230, 310, 61, 27));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        userDelPushButton->setFont(font);
        userDelPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        userEditPushButton = new QPushButton(userManage);
        userEditPushButton->setObjectName(QString::fromUtf8("userEditPushButton"));
        userEditPushButton->setGeometry(QRect(360, 310, 61, 27));
        userEditPushButton->setFont(font);
        userEditPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        userAddPushButton = new QPushButton(userManage);
        userAddPushButton->setObjectName(QString::fromUtf8("userAddPushButton"));
        userAddPushButton->setGeometry(QRect(100, 310, 61, 27));
        userAddPushButton->setFont(font);
        userAddPushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/res/anniubk.png);\n"
"border-color: rgb(33, 131, 229);\n"
"border-width: 1px;\n"
"border-style: solid;"));

        retranslateUi(userManage);

        QMetaObject::connectSlotsByName(userManage);
    } // setupUi

    void retranslateUi(QWidget *userManage)
    {
        userManage->setWindowTitle(QCoreApplication::translate("userManage", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("userManage", "\347\224\250\346\210\267\346\235\203\351\231\220\347\256\241\347\220\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("userManage", "\347\224\250\346\210\267\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("userManage", "\347\224\250\346\210\267\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("userManage", "\347\224\250\346\210\267\346\263\250\351\207\212", nullptr));
        closePushButton->setText(QString());
        userDelPushButton->setText(QCoreApplication::translate("userManage", "\345\210\240\351\231\244", nullptr));
        userEditPushButton->setText(QCoreApplication::translate("userManage", "\344\277\256\346\224\271", nullptr));
        userAddPushButton->setText(QCoreApplication::translate("userManage", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userManage: public Ui_userManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGE_H
