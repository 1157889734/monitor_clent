#include "useredit.h"
#include "ui_useredit.h"

#include "state.h"
#include "debug.h"
#include <QTextCodec>
#include <QMessageBox>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QSqlQuery"
#include <qdebug.h>
#include <QtPlugin>
#include <stdio.h>
#include <QtGui/qinputmethod.h>

userEdit::userEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userEdit)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

//    ui->passwdLineEdit->installEventFilter(this);
//    ui->userNoteLineEdit->installEventFilter(this);

    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(closeWidgetSlot()));
    connect(ui->confirmPushButton, SIGNAL(clicked(bool)), this, SLOT(confirmSlot()));
    connect(ui->canclePushButton, SIGNAL(clicked(bool)), this, SLOT(cancleSlot()));
}

void userEdit::closeWidgetSlot()
{
//    if (p_ipmethod->p_inputwidget != NULL)
//    {
//        p_ipmethod->p_inputwidget->hide();
//    }
    emit sendCloseMsg();
}

void userEdit::cancleSlot()
{
//    if (p_ipmethod->p_inputwidget != NULL)
//    {
//        p_ipmethod->p_inputwidget->hide();
//    }
    emit sendCloseMsg();
}

void userEdit::recvOpenMsg(QString userName)
{
    if (0 == QString::compare(userName, "admin"))    //admin的用户类型不能修改
    {
        ui->userTypeComboBox->setEnabled(false);
    }

    ui->userNameLineEdit->setText(userName);
    QSqlDatabase database;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    database.setDatabaseName("database.db");

    //打开数据库
    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
        return;
    }
    QSqlQuery sql_query;
    QString selectStr = "select passwd, type, info from usermanage where name='"+userName+"'";
    if(!sql_query.exec(selectStr))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {
            ui->passwdLineEdit->setText(sql_query.value(0).toString());
            ui->userNoteLineEdit->setText(sql_query.value(2).toString());
            QString type = sql_query.value(1).toString();
            if (0 == QString::compare(type, "supperManager"))
            {
                ui->userTypeComboBox->setCurrentIndex(0);
            }
            else if (0 == QString::compare(type, "manager"))
            {
                ui->userTypeComboBox->setCurrentIndex(1);
            }
            else if (0 == QString::compare(type, "operator"))
            {
                ui->userTypeComboBox->setCurrentIndex(2);
            }
        }
    }
    database.close();
}

void userEdit::confirmSlot()
{
    char acUserType[16] = {0};
    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));

    QSqlDatabase database;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    database.setDatabaseName("database.db");

    //打开数据库
    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
        return;
    }
    QSqlQuery sql_query;
    QString userType = "";
    QString selectStr = "select passwd, type, info from usermanage where name='"+ui->userNameLineEdit->text()+"'";
    if(!sql_query.exec(selectStr))
    {
        qDebug()<<sql_query.lastError();
        database.close();
        return;
    }
    else
    {
        if(sql_query.first())
        {
            userType = sql_query.value(1).toString();
        }
    }

    if (!strcmp(acUserType, "supperManager"))  //超级管理员也不能修改管理员和操作员的用户类型为超级管理员
    {
        if (0 == QString::compare(userType, "manager") || 0 == QString::compare(userType, "operator"))
        {
            if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("超级管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user type to supperManager!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("不能修改此成员为该类型!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                database.close();
                return;
            }
        }
    }
    else if (!strcmp(acUserType, "manager"))
    {
        if (0 == QString::compare(userType, "supperManager"))  //管理员只能编辑管理员和操作员
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user!\n");
            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力修改此类型成员!"));     //新建消息提示框，提示错误信息
            box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
            box.exec();
            database.close();
            return;
        }
        else if (0 == QString::compare(userType, "manager"))   //修改管理员时不能修改用户类型为超级管理员
        {
            if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("超级管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user type to supperManager!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("不能修改此成员为该类型!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                database.close();
                return;
            }
        }
        else if (0 == QString::compare(userType, "operator"))   //修改操作员时不能修改用户类型为超级管理员和管理员
        {
            if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("超级管理员")) ||
                0 == QString::compare(ui->userTypeComboBox->currentText(), tr("管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user type to supperManager!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("不能修改此成员为该类型!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                database.close();
                return;
            }
        }
    }
    else if (!strcmp(acUserType, "operator"))
    {
        if (0 == QString::compare(userType, "supperManager") || 0 == QString::compare(userType, "manager") )   //操作员只能编辑操作员
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user!\n");
            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("不能修改此类型成员!"));
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
            box.exec();
            database.close();
            return;
        }
        else  //修改操作员时不能修改用户类型为超级管理员和管理员
        {
            if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("超级管理员")) ||
                0 == QString::compare(ui->userTypeComboBox->currentText(), tr("管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userEditWidget this user type has no right to modify user type to supperManager!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("不能修改此成员为该类型!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                database.close();
                return;
            }
        }
    }

    QString type = "";
    if (0 == ui->userTypeComboBox->currentIndex())
    {
        type = "supperManager";
    }
    else if (1 == ui->userTypeComboBox->currentIndex())
    {
        type = tr("manager");
    }
    else if (2 == ui->userTypeComboBox->currentIndex())
    {
        type = tr("operator");
    }
    QString updateStr = "update usermanage set passwd='"+ui->passwdLineEdit->text()+"',"+"info='"+ui->userNoteLineEdit->text()+"',"+"type='"+type+"' where name='"+ui->userNameLineEdit->text()+"'";
    if(!sql_query.exec(updateStr))
    {
        qDebug()<<sql_query.lastError();
    }

//    if (p_ipmethod->p_inputwidget != NULL)
//    {
//        p_ipmethod->p_inputwidget->hide();
//    }
    database.close();
    emit sendCloseMsg();
}
bool userEdit::eventFilter(QObject *target, QEvent *event)
{



}
userEdit::~userEdit()
{
    delete ui;
}
