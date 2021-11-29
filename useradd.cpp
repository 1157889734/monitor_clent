#include "useradd.h"
#include "ui_useradd.h"
#include "state.h"
#include "debug.h"
#include <QTextCodec>
#include <QMessageBox>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QSqlQuery"
#include <QMessageBox>
#include <qdebug.h>
#include <stdio.h>
#include <QtPlugin>




userAdd::userAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userAdd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);


//    ui->userNameLineEdit->installEventFilter(this);
//    ui->passwdLineEdit->installEventFilter(this);
//    ui->userNoteLineEdit->installEventFilter(this);

    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(closeWidgetSlot()));
    connect(ui->confirmPushButton, SIGNAL(clicked(bool)), this, SLOT(confirmSlot()));
    connect(ui->canclePushButton, SIGNAL(clicked(bool)), this, SLOT(cancleSlot()));

}

userAdd::~userAdd()
{
    delete ui;
}
void userAdd::closeWidgetSlot()
{
//    if (p_ipmethod->p_inputwidget != NULL)
//    {
//        p_ipmethod->p_inputwidget->hide();
//    }
    emit sendCloseMsg();
}


void userAdd::confirmSlot()
{
    char acUserType[16] = {0};
    int nRow = 0, i = 0;

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));

    if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("超级管理员")))
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userAddWidget this user type has no right to add supperManager!\n");
        QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力添加此类型成员!"));     //新建消息提示框，提示错误信息
        box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
        box.exec();
        return;
    }

    if (!strcmp(acUserType, "manager"))   //管理员只能添加操作员
    {
        if (0 == QString::compare(ui->userTypeComboBox->currentText(), tr("管理员")))
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userAddWidget this user type has no right to add manager!\n");
            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力添加此类型成员!"));     //新建消息提示框，提示错误信息
            box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
            box.exec();
            return;
        }
    }
    else if (!strcmp(acUserType, "operator"))   //操作员不能添加任何用户
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userAddWidget this user type has no right to add user!\n");
        QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力添加成员!"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
        box.exec();
        return;
    }

    ui->userNameWarnLabel->setText("");
    ui->passWdWarnLabel->setText("");

    if (ui->userNameLineEdit->text() == "")
    {
//        if (p_ipmethod->p_inputwidget != NULL)
//        {
//            p_ipmethod->p_inputwidget->hide();
//        }
        ui->userNameWarnLabel->setText(QObject::tr("*用户名不能为空"));
        ui->userNameWarnLabel->setFocus();
        return;
    }
    if (ui->passwdLineEdit->text() == "")
    {
//        if (p_ipmethod->p_inputwidget != NULL)
//        {
//            p_ipmethod->p_inputwidget->hide();
//        }
        ui->passWdWarnLabel->setText(QObject::tr("*密码不能为空"));
        ui->passWdWarnLabel->setFocus();
        return;
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
    sql_query.prepare("select name, type, info from usermanage");
    sql_query.exec();
    sql_query.last();
    nRow = sql_query.at() + 1;

    sql_query.first();
    for (i = 0; i<nRow; i++)
    {
        if (0 == QString::compare(sql_query.value(0).toString(), ui->userNameLineEdit->text()))
        {
//            if (p_ipmethod->p_inputwidget != NULL)
//            {
//                p_ipmethod->p_inputwidget->hide();
//            }
            ui->userNameWarnLabel->setText(QObject::tr("*该用户名已存在"));
            ui->userNameWarnLabel->setFocus();
            database.close();
            return;
        }
        sql_query.next();
    }

    sql_query.last();
    QString insertStr = "insert into usermanage (type, info, name, passwd) values ('"+type+"',"+"'"+ui->userNoteLineEdit->text()+"',"+"'"+ui->userNameLineEdit->text()+"',"+"'"+ui->passwdLineEdit->text()+"')";
    if(!sql_query.exec(insertStr))
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

bool userAdd::eventFilter(QObject *target, QEvent *event)
{



}

void userAdd::cancleSlot()
{
//    if (p_ipmethod->p_inputwidget != NULL)
//    {
//        p_ipmethod->p_inputwidget->hide();
//    }
    emit sendCloseMsg();
}
