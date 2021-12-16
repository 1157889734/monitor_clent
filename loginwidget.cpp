#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include <QDebug>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QSqlQuery"
#include "state.h"



loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    this->setGeometry(0,0,1024,768);
    this->showFullScreen();


    ui->username_Edit->installEventFilter(this);
    ui->Passwd_Edit->installEventFilter(this);

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/monres/Pantobg - 副本.bmp")));
    QIcon icon;
    this->setPalette(palette);

    ui->ensure->setFocusPolicy(Qt::NoFocus); // 得到焦点时，不显示虚线框
    ui->cansel->setFocusPolicy(Qt::NoFocus);

    connect(ui->ensure, SIGNAL(clicked(bool)), this, SLOT(okButtonSlot()));	   //确定按钮的按键信号连接相应槽函数
    connect(ui->cansel, SIGNAL(clicked(bool)), this, SLOT(canselButtonSlot()));	   //确定按钮的按键信号连接相应槽函数

    mCkeybord = new CKeyboard(this,1);
    mCkeybord->setGeometry(50,330,924,200);
    mCkeybord->show();


    connect(mCkeybord,SIGNAL(KeyboardPressKeySignal(char)),this,SLOT(KeyboardPressKeySlots(char)));

    ui->username_Edit->setText("admin");
    ui->username_Edit->setFont(QFont("宋体",20));
    ui->username_Edit->setAlignment(Qt::AlignCenter);
    ui->Passwd_Edit->setEchoMode(QLineEdit::Password);
    ui->Passwd_Edit->setFocus();


}

loginWidget::~loginWidget()
{
    delete  mCkeybord;
    mCkeybord = NULL;
    delete ui;
}
bool loginWidget::eventFilter(QObject *obj, QEvent *e)
{

    mCkeybord->show();

    return QWidget::eventFilter(obj, e);

}

void loginWidget::KeyboardPressKeySlots(char key)
{

    if(key==BSPACE)
    {

        if(ui->username_Edit->hasFocus())//输入框1焦点
        {
            if(!ui->username_Edit->selectedText().isEmpty())
            {
                 ui->username_Edit->del();

            }
            else
            {
                ui->username_Edit->backspace();
            }

        }
        else if(ui->Passwd_Edit->hasFocus())//输入框2焦点
        {
            if(!ui->Passwd_Edit->selectedText().isEmpty())
            {
                 ui->Passwd_Edit->del();

            }
            else
            {
                ui->Passwd_Edit->backspace();
            }
        }
    }
    else if(key == ENTER)
    {
        if (ui->Passwd_Edit->text() == "12345")
        {
            this->hide();
//            STATE_SetCurrentUserType("supperManager");
            emit gotoPvmsMenuPageSignal();

        }
    }
    else
    {
        if(ui->username_Edit->hasFocus())//输入框1焦点
        {
            ui->username_Edit->insert(QString( key));
        }
        else if(ui->Passwd_Edit->hasFocus())//输入框2焦点
        {
            ui->Passwd_Edit->insert(QString( key));
        }
    }
}



void loginWidget::okButtonSlot()
{
#if 0 //TEST

    this->hide();
    emit gotoPvmsMenuPageSignal();
#else

    int iCheckFlag = 0;
    QString urname,pwd,type;
    QSqlDatabase database;

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "login Widget okButton pressed!\n");

    /*是否已经存在一个默认的数据库连接，如果存在则通过database方法获取，不存在则通过addDatabase创建一个新的数据库连接*/
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    database.setDatabaseName("/home/data/monitorCfg/data.db");   //设置连接的数据库名称

    //打开数据库
    if(!database.open())
    {
        qDebug()<<"********database.ope---fail**********"<<__LINE__;
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "loginWidget database open error!\n");
    }
    qDebug()<<"********database.ope---ok**********"<<__LINE__;


    //QSqlQuery类提供执行和操作的SQL语句的方法。
    //可以用来执行DML（数据操作语言）语句，如SELECT、INSERT、UPDATE、DELETE
    QSqlQuery sql_query;
    QString select_sql = "";

    if (ui->username_Edit->text() == "admin")    //admin登录用户,通过检查数据库中是否存在该用户，如果存在则和数据中的密码匹配，如果不存在则默认密码12345
    {
        select_sql = "select passwd from tab where username='admin'";   //检测数据库中是否存在admin用户
        if(!sql_query.exec(select_sql))    //执行SQL语句
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "loginWidget database select error!\n");
            qDebug()<<"loginWidget database select error"<<__FUNCTION__<<__LINE__<<endl;
        }
        else
        {
            if(sql_query.first())
            {
                iCheckFlag = 1;
                pwd = sql_query.value(0).toString();
            }
        }

        if (0 == iCheckFlag)
        {
            if (ui->Passwd_Edit->text() == "12345")
            {
                this->hide();
                STATE_SetCurrentUserType("supperManager");
                emit gotoPvmsMenuPageSignal();

            }
            else
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "loginWidget username or passwd input not match!\n");
                QMessageBox box(QMessageBox::Warning,tr("信息有误"),tr("用户名或密码错误!"));     //新建消息提示框，提示错误信息
                box.setWindowFlags(Qt::FramelessWindowHint);
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,tr("OK"));     //将按钮显示改成"确 定"
                box.exec();

            }
        }
        else
        {
            if (ui->Passwd_Edit->text() != pwd)
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "loginWidget username or passwd input not match!\n");
                QMessageBox box(QMessageBox::Warning,tr("信息有误"),tr("用户名或密码错误!"));     //新建消息提示框，提示错误信息
                box.setWindowFlags(Qt::FramelessWindowHint);
                box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
                box.setButtonText (QMessageBox::Ok,tr("OK"));     //将按钮显示改成"确 定"
                box.exec();
            }
            else
            {
                this->hide();
                STATE_SetCurrentUserType("supperManager");
                emit gotoPvmsMenuPageSignal();

            }
        }
    }
    else
    {
        QString select_sql = "select username, passwd, power from tab";    //查询数据库中所有的用户名、密码和用户类型记录
        if(!sql_query.exec(select_sql))    //执行SQL语句
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "loginWidget database select error!\n");
        }
        else
        {
            while(sql_query.next())   //循环进行用户名、密码的匹配，直到匹配成功退出，否则弹出错误提示框
            {
                urname = sql_query.value(0).toString();
                pwd = sql_query.value(1).toString();
                type = sql_query.value(2).toString();

                qDebug()<<"*****urname="<<urname<<"*******pwd="<<pwd<<"*******type"<<type<<__LINE__;
                if ((ui->username_Edit->text() == urname) && (ui->Passwd_Edit->text() == pwd))    //用户名、密码匹配成功
                {
                    this->hide();
                    STATE_SetCurrentUserType(type.toLatin1().data());   //保存当前登录用户的用户类型
                    emit gotoPvmsMenuPageSignal();
                    database.close();
                    return;
                }
            }
        }

//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "loginWidget username or passwd input not match!\n");
        QMessageBox box(QMessageBox::Warning,tr("信息有误"),tr("用户名或密码错误!"));     //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK"));     //将按钮显示改成"确 定"
        box.exec();
    }
    database.close();
#endif

}
void loginWidget::canselButtonSlot()
{
    this->hide();
    emit loginCanselSignal();

}
void loginWidget::showPageSlot()
{
    this->show();
}
void loginWidget::clearSlot()
{
    ui->Passwd_Edit->clear();

}

