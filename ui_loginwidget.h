/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginWidget
{
public:
    QLineEdit *username_Edit;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *cansel;
    QLineEdit *Passwd_Edit;
    QPushButton *ensure;
    QLabel *label_3;
    QLabel *label;

    void setupUi(QWidget *loginWidget)
    {
        if (loginWidget->objectName().isEmpty())
            loginWidget->setObjectName(QString::fromUtf8("loginWidget"));
        loginWidget->resize(1024, 768);
        loginWidget->setStyleSheet(QString::fromUtf8("#loginWidget { \n"
"border-image: url(:/monres/Pantobg - \345\211\257\346\234\254.bmp); \n"
"} \n"
"#loginWidget * { \n"
"border-image:url(); \n"
"}"));
        username_Edit = new QLineEdit(loginWidget);
        username_Edit->setObjectName(QString::fromUtf8("username_Edit"));
        username_Edit->setGeometry(QRect(630, 210, 161, 41));
        username_Edit->setStyleSheet(QString::fromUtf8("QLineEdit:focus{background-color: rgb(204, 232, 207);}"));
        username_Edit->setFrame(true);
        username_Edit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_2 = new QLabel(loginWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(510, 260, 101, 41));
        QFont font;
        font.setPointSize(20);
        label_2->setFont(font);
        label_4 = new QLabel(loginWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 200, 300, 52));
        label_4->setStyleSheet(QString::fromUtf8("background-image: url(:/res/login.png);"));
        cansel = new QPushButton(loginWidget);
        cansel->setObjectName(QString::fromUtf8("cansel"));
        cansel->setGeometry(QRect(710, 570, 197, 63));
        cansel->setFont(font);
        cansel->setStyleSheet(QString::fromUtf8("background-image: url(:/res/cansel.png);"));
        Passwd_Edit = new QLineEdit(loginWidget);
        Passwd_Edit->setObjectName(QString::fromUtf8("Passwd_Edit"));
        Passwd_Edit->setGeometry(QRect(630, 260, 161, 41));
        Passwd_Edit->setStyleSheet(QString::fromUtf8("QLineEdit:focus{background-color: rgb(204, 232, 207);}"));
        ensure = new QPushButton(loginWidget);
        ensure->setObjectName(QString::fromUtf8("ensure"));
        ensure->setGeometry(QRect(150, 570, 197, 63));
        ensure->setFont(font);
        ensure->setStyleSheet(QString::fromUtf8("background-image: url(:/res/sure.png);"));
        label_3 = new QLabel(loginWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 110, 512, 56));
        label_3->setStyleSheet(QString::fromUtf8("background-image: url(:/res/title.png);"));
        label = new QLabel(loginWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(510, 210, 101, 41));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);

        retranslateUi(loginWidget);

        QMetaObject::connectSlotsByName(loginWidget);
    } // setupUi

    void retranslateUi(QWidget *loginWidget)
    {
        loginWidget->setWindowTitle(QCoreApplication::translate("loginWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("loginWidget", "\345\257\206  \347\240\201:", nullptr));
        label_4->setText(QString());
        cansel->setText(QString());
        ensure->setText(QString());
        label_3->setText(QString());
        label->setText(QCoreApplication::translate("loginWidget", "\347\224\250\346\210\267\345\220\215:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginWidget: public Ui_loginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
