
#include "usermanage.h"
#include "ui_usermanage.h"
#include "state.h"
#include "debug.h"
#include <QTextCodec>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QSqlQuery"
#include <QMessageBox>
#include <qdebug.h>
#include <stdio.h>
#include <QtPlugin>


userManage::userManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userManage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
//    QTextCodec::setCodecForLocale(codec);

    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->resizeSection(0,133);
    ui->tableWidget->horizontalHeader()->resizeSection(1,133);
    ui->tableWidget->horizontalHeader()->resizeSection(2,133);
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->userAddPushButton->setFocusPolicy(Qt::NoFocus);
    ui->userDelPushButton->setFocusPolicy(Qt::NoFocus);
    ui->userEditPushButton->setFocusPolicy(Qt::NoFocus);

    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClick()));
    connect(ui->userAddPushButton, SIGNAL(clicked(bool)), this, SLOT(addUser()));
    connect(ui->userDelPushButton, SIGNAL(clicked(bool)), this, SLOT(delUser()));
    connect(ui->userEditPushButton, SIGNAL(clicked(bool)), this, SLOT(editUser()));

    usrEditPage = new userEdit(this);
    usrEditPage->setGeometry(245, 189, usrEditPage->width(), usrEditPage->height());
    usrEditPage->hide();
    connect(this, SIGNAL(SendUsrEditMsg(QString)), usrEditPage, SLOT(recvOpenMsg(QString)));
    connect(usrEditPage, SIGNAL(sendCloseMsg()), this, SLOT(CloseUsrEdit()));

    usrAddPage = new userAdd(this);
    usrAddPage->setGeometry(245, 189, usrAddPage->width(), usrAddPage->height());
    usrAddPage->hide();
    connect(usrAddPage, SIGNAL(sendCloseMsg()), this, SLOT(CloseUsrAdd()));

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

    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else
    {
        QSqlQuery sql_query;
        int i = 0, j = 0, nColumn, nRow;
        sql_query.prepare("select name, type, info from usermanage");
        sql_query.exec();
        sql_query.last();
        nRow = sql_query.at() + 1;
        ui->tableWidget->setRowCount(nRow);
        nColumn = 3;
        sql_query.first();
        for (j = 0;j<nRow;j++)
        {
            for (i = 0; i<nColumn; i++)
            {
                ui->tableWidget->setItem(j, i, new QTableWidgetItem(sql_query.value(i).toString()));
            }
            if (sql_query.value(1).toString() == "supperManager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("超级管理员")));
            }
            else if (sql_query.value(1).toString() == "manager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("管理员")));
            }
            else if (sql_query.value(1).toString() == "operator")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("操作员")));
            }
            sql_query.next();
        }
    }
    database.close();
}

userManage::~userManage()
{
//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "delete ~userManageWidget\n");

    if (usrEditPage != NULL)
    {
        delete usrEditPage;
        usrEditPage = NULL;
    }
    if (usrAddPage != NULL)
    {
        delete usrAddPage;
        usrAddPage = NULL;
    }

    delete ui;
}

void userManage::closeButtonClick()
{
    emit SendEscape();
    return;
}

void userManage::delUser()
{
//    DebugPrint(DEBUG_UI_OPTION_PRINT, "userManageWidget user delete button pressed!\n");
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

    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
        return;
    }

    QSqlQuery sql_query;
    int rowIndex = -1;
    char acUserType[16] = {0};
    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    rowIndex = ui->tableWidget->currentRow();

    if (rowIndex != -1)
    {
        if (!strcmp(acUserType, "supperManager"))   //超级管理员不能删除超级管理员
        {
            if (0 == QString::compare(ui->tableWidget->item(rowIndex, 1)->text(), tr("超级管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget this user type has no right to delete user!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力删除此类型成员!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                return;
            }
        }
        else if (!strcmp(acUserType, "manager"))   //管理员只能删除操作员
        {
            if (0 == QString::compare(ui->tableWidget->item(rowIndex, 1)->text(), tr("超级管理员")) ||
                0 == QString::compare(ui->tableWidget->item(rowIndex, 1)->text(), tr("管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget this user type has no right to delete user!\n");
                QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力删除此类型成员!"));     //新建消息提示框，提示错误信息
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
                box.exec();
                return;
            }
        }
        else if (!strcmp(acUserType, "operator"))   //操作员不能删除任何用户
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget this user type has no right to delete user!\n");
            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力删除此类型成员!"));
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
            box.exec();
            return;
        }

        QString delName = ui->tableWidget->item(rowIndex, 0)->text();
        QString delStr = "delete from usermanage where name='"+delName+"'";
        sql_query.exec(delStr);
        int i = 0, j = 0, nColumn, nRow;
        sql_query.prepare("select name, type, info from usermanage");
        sql_query.exec();
        sql_query.last();
        nRow = sql_query.at() + 1;
        ui->tableWidget->setRowCount(nRow);
        nColumn = 3;
        sql_query.first();
        for (j = 0;j<nRow;j++)
        {
            for (i = 0; i<nColumn; i++)
            {
                ui->tableWidget->setItem(j, i, new QTableWidgetItem(sql_query.value(i).toString()));
            }
            if (sql_query.value(1).toString() == "supperManager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("超级管理员")));
            }
            else if (sql_query.value(1).toString() == "manager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("管理员")));
            }
            else if (sql_query.value(1).toString() == "operator")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("操作员")));
            }
            sql_query.next();
        }
    }
    else
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget not select the user to delete!\n");
        QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("请选择要删除的用户!")));
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.button(QMessageBox::Yes)->setText("确 定");
        msgBox.exec();
    }
    database.close();
}

void userManage::addUser()
{
//    DebugPrint(DEBUG_UI_OPTION_PRINT, "userManageWidget user add button pressed!\n");
    if (usrAddPage == NULL)
    {
        usrAddPage = new userAdd(this);
        usrAddPage->setGeometry(245, 189, usrAddPage->width(), usrAddPage->height());
        usrAddPage->show();
        connect(usrAddPage, SIGNAL(sendCloseMsg()), this, SLOT(CloseUsrAdd()));
    }
    else
    {
        usrAddPage->show();
    }
}

void userManage::editUser()
{
    int rowIndex = -1;
    rowIndex = ui->tableWidget->currentRow();

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "userManageWidget user edit button pressed!\n");

    if (rowIndex != -1)
    {
        if (usrEditPage == NULL)
        {
            usrEditPage = new userEdit(this);
            usrEditPage->setGeometry(245, 189, usrEditPage->width(), usrEditPage->height());
            usrEditPage->show();
            connect(this, SIGNAL(SendUsrEditMsg(QString)), usrEditPage, SLOT(recvOpenMsg(QString)));
            connect(usrEditPage, SIGNAL(sendCloseMsg()), this, SLOT(CloseUsrEdit()));
        }
        else
        {
            usrEditPage->show();
        }
        emit SendUsrEditMsg(ui->tableWidget->item(rowIndex, 0)->text());
    }
    else
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget not select the user to edit!\n");
        QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("请选择要编辑的用户!")));
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.button(QMessageBox::Yes)->setText("确 定");
        msgBox.exec();
    }
}

void userManage::CloseUsrEdit()
{
    if(NULL==this->usrEditPage)
    {
        return;
    }
    else
    {
        delete this->usrEditPage;
    }
    this->usrEditPage=NULL;

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

    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else
    {
        QSqlQuery sql_query;
        int i = 0, j = 0, nColumn, nRow;
        sql_query.prepare("select name, type, info from usermanage");
        sql_query.exec();
        sql_query.last();
        nRow = sql_query.at() + 1;
        ui->tableWidget->setRowCount(nRow);
        nColumn = 3;
        sql_query.first();
        for (j = 0;j<nRow;j++)
        {
            for (i = 0; i<nColumn; i++)
            {
                ui->tableWidget->setItem(j, i, new QTableWidgetItem(sql_query.value(i).toString()));
            }
            if (sql_query.value(1).toString() == "supperManager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("超级管理员")));
            }
            else if (sql_query.value(1).toString() == "manager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("管理员")));
            }
            else if (sql_query.value(1).toString() == "operator")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("操作员")));
            }
            sql_query.next();
        }
    }
    database.close();
}

void userManage::CloseUsrAdd()
{
    if(NULL==this->usrAddPage)
    {
        return;
    }
    else
    {
        delete this->usrAddPage;
    }
    this->usrAddPage=NULL;

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

    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else
    {
        QSqlQuery sql_query;
        int i = 0, j = 0, nColumn, nRow;
        sql_query.prepare("select name, type, info from usermanage");
        sql_query.exec();
        sql_query.last();
        nRow = sql_query.at() + 1;
        ui->tableWidget->setRowCount(nRow);
        nColumn = 3;
        sql_query.first();
        for (j = 0;j<nRow;j++)
        {
            for (i = 0; i<nColumn; i++)
            {
                ui->tableWidget->setItem(j, i, new QTableWidgetItem(sql_query.value(i).toString()));
            }
            if (sql_query.value(1).toString() == "supperManager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("超级管理员")));
            }
            else if (sql_query.value(1).toString() == "manager")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("管理员")));
            }
            else if (sql_query.value(1).toString() == "operator")
            {
                ui->tableWidget->setItem(j, 1, new QTableWidgetItem(tr("操作员")));
            }
            sql_query.next();
        }
    }
    database.close();
}
