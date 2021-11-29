#include "usergroupmanage.h"
#include "ui_usergroupmanage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QButtonGroup>
#include "state.h"



static int g_curTextState = 0;

usergroupManage::usergroupManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usergroupManage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setColumnCount(2);


    QStringList header;
    header<<tr("用户名")<<tr("类型");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setVisible(true);//temp
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
//    ui->tableWidget->setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    ui->tableWidget->horizontalHeader()->resizeSection(0,60); //设置表头第一列的宽度为46
    ui->tableWidget->horizontalHeader()->resizeSection(1,100);
//    ui->tableWidget->horizontalHeader()->resizeSection(2,136);

    ui->passwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->surelineEdit->setEchoMode(QLineEdit::Password);

    g_buttonGroup = new QButtonGroup();      //轮询时间设置单选按钮组成一组，以保证改组中的单选框同时只能选一个，同时与以下其他类别的单选框之间互不影响
    g_buttonGroup->addButton(ui->radioButton,1);
    g_buttonGroup->addButton(ui->radioButton_2,2);
    g_buttonGroup->addButton(ui->radioButton_3,3);

    connect(g_buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(choose_type_function(int)));

    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(table_choose_fuction(QTableWidgetItem*)));



}

usergroupManage::~usergroupManage()
{
    delete g_buttonGroup;
    g_buttonGroup = NULL;

    delete ui;
}

void usergroupManage::init_datavase()
{
    QSqlDatabase db;
    bool query_OK=0;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("/home/data/data.db");
    query_OK=db.open();
    if(query_OK)
    {
//        QMessageBox::information(this,"Information","open sucessfully");
    }
    else
    {
        QMessageBox::information(this,"Information","open fail");
    }
    update_database_function();
    db.close();

}


void usergroupManage::on_addpushButton_clicked()
{
    ui->passwdlineEdit->clear();
    ui->usernamelineEdit->clear();
    ui->surelineEdit->clear();
    ui->usernamelineEdit->setFocus();
}

void usergroupManage::update_database_function()
{
    QSqlQuery sql_query;
    int i = 0, j = 0, nColumn, nRow;
    sql_query.prepare("select username, power from tab");
    sql_query.exec();
    sql_query.last();
    nRow = sql_query.at() + 1;
    ui->tableWidget->setRowCount(nRow);
    nColumn = 3;
    sql_query.first();
    QString data;
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

    ui->passwdlineEdit->clear();
    ui->usernamelineEdit->clear();
    ui->surelineEdit->clear();
}

void usergroupManage::on_savepushButton_clicked()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    db = QSqlDatabase::database("qt_sql_default_connection");
    else
    db = QSqlDatabase::addDatabase("QSQLITE");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
         else qDebug() << "open";

    QString value_name = ui->usernamelineEdit->text();
    QString value_passwd = ui->passwdlineEdit->text();
    QString value_ensure_passwd = ui->surelineEdit->text();

    if(ui->usernamelineEdit->text().isEmpty())
    {
        return;
    }

    if(ui->passwdlineEdit->text().isEmpty() || ui->surelineEdit->text().isEmpty())
    {
        QMessageBox::information(this ,tr("提示") , tr("密码不能为空!"));
        return;
    }


    QSqlQuery query;
    query.exec("select username from tab");
    query.isActive();
    bool T2=true;
    while(query.next())
   {

       QString id1= query.value(1).toString();
       if(ui->usernamelineEdit->text().compare(id1)==0)
        {
            QMessageBox::information(this ,tr("提示") , tr("该用户已存在不允许再次添加!"));
            T2=false;
            return;
        }
   }


    if(1 == g_curTextState)
    {

       if(value_passwd != value_ensure_passwd)
       {
           QMessageBox::information(this ,tr("提示") , tr("两次密码不一致!"));
           return;
       }
       QString sql;
       sql = QString("update tab set passwd = ('%1') where username = ('%2')")
          .arg(value_passwd).arg(value_name);
      bool ok = query.exec(sql);
      if(ok)
      {
        QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        g_curTextState = 0;
      }
      else
      {
        QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
      }
      db.close();
      return;
    }
    if(T2==true)
    {
         QString sql;
        if(value_passwd != value_ensure_passwd)
        {
            QMessageBox::information(this ,tr("提示") , tr("两次密码不一致!"));
            return;
        }

         QString value_type;
         if(!gtype_text.isEmpty())
        {
            value_type = gtype_text;
        }
        else
        {
            value_type = "operator";
        }
         sql = QString("insert into tab values ('%1', '%2', '%3' )")
            .arg(value_name).arg(value_passwd).arg(value_type);
        bool ok = query.exec(sql);
      if(ok)
      {
        QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
      }
      else
      {
        QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
      }
   }

    update_database_function();
    db.close();

}



void usergroupManage::on_deletepushButton_clicked()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else
        qDebug() << "open";

    QList<QTableWidgetItem*>items=ui->tableWidget->selectedItems();
    int cout = items.count();
    if(!cout)
    {
        return;
    }
    QTableWidgetItem *item = items.at(0);
    QString text = item->text(); //获取内容
    QSqlQuery query;
    QString sql;
    char acUserType[16] = {0};
    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    int rowIndex = -1;
    rowIndex = ui->tableWidget->currentRow();
    if (rowIndex != -1)
    {
        if (!strcmp(acUserType, "supperManager"))   //超级管理员不能删除超级管理员
        {
            if (0 == QString::compare(ui->tableWidget->item(rowIndex, 1)->text(), tr("超级管理员")))
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget this user type has no right to delete user!\n");
                qDebug()<<"userManageWidget this user type has no right to delete user!"<<__FUNCTION__<<__LINE__<<endl;
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
                qDebug()<<"userManageWidget this user type has no right to delete user!"<<__FUNCTION__<<__LINE__<<endl;
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
            qDebug()<<"userManageWidget this user type has no right to delete user!"<<__FUNCTION__<<__LINE__<<endl;

            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("没有权力删除此类型成员!"));
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
            box.exec();
            return;
        }

        sql = QString("delete from tab where username = '%1'").arg(text);
        bool ok = query.exec(sql);
        if(ok)
        {
            QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
        }
        update_database_function();


    }
    else
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "userManageWidget not select the user to delete!\n");
        qDebug()<<"userManageWidget not select the user to delete!"<<__FUNCTION__<<__LINE__<<endl;
        QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("请选择要删除的用户!")));
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.button(QMessageBox::Yes)->setText("确 定");
        msgBox.exec();
    }
    db.close();

}

void usergroupManage::table_choose_fuction(QTableWidgetItem *item)
{
    g_curTextState = 1;
    QList<QTableWidgetItem*>items=ui->tableWidget->selectedItems();
    int cout = items.count();
    if(!cout)
    {
        return;
    }
    QTableWidgetItem *mitem = items.at(0);
    QString text = mitem->text(); //获取内容
    ui->usernamelineEdit->setText(text);
    ui->passwdlineEdit->clear();
    ui->surelineEdit->clear();
}



void usergroupManage::choose_type_function(int type)
{
    static int iOldId = 0;
    if (type != iOldId)
    {
        switch (type) //根据单选按钮组按键信号传入的单选按钮编号区分不同的单选按钮，做出不同的设置
        {
            case 1:
            {
                gtype_text = "超级管理员";
                break;
            }
            case 2:
            {
                gtype_text = "管理员";
                break;
            }
            case 3:
            {
                gtype_text = "操作员";
                break;
            }
            default:
                break;
        }
        iOldId = type;
    }

}
