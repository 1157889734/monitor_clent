#include "devupdatewidget.h"
#include "ctcppisclient.h"
#include "ui_devupdatewidget.h"
#include <QButtonGroup>
#include <QDebug>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include "stdio.h"
#include "log.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <QProcess>
#include <QLabel>
#include <QList>

//extern int g_iIsPBD;
static int g_ibShowKeyboard = 0;
static int g_ichagepage = 0;
static int g_iVNum = 0;
#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面

#define NVR_RESTART_PORT 11001
QButtonGroup *g_buttonGroup1 = NULL, *g_buttonGroup2 = NULL;

char* parseFileNameFromPath(char *pcSrcStr)     //根据导入文件路径全名解析得到单纯的导入文件名
{
    char *pcTmp = NULL;

    if (NULL == pcSrcStr)
    {
        return NULL;
    }

    pcTmp = strrchr(pcSrcStr, '/');
    if (NULL == pcTmp)
    {
        return NULL;
    }

    if (NULL == (pcTmp+1))
    {
        return NULL;
    }
    return pcTmp+1;
}

devUpdateWidget::devUpdateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::devUpdateWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);


    connect(ui->alarmPushButton, SIGNAL(clicked(bool)), this, SLOT(alarmPushButoonClickSlot()));   //报警按钮按键信号响应打开报警信息界面
    ui->alarmPushButton->setFocusPolicy(Qt::NoFocus);
    m_alarmHappenTimer = NULL;


    gusergroupManage = new usergroupManage(this);   //受电弓监控页面
    gusergroupManage->setGeometry(40, 120, gusergroupManage->width(), gusergroupManage->height());   //设置位置
    gusergroupManage->hide();

    ui->pollingTimeSetLineEdit->installEventFilter(this);
    ui->presetReturnTimeSetLineEdit->installEventFilter(this);
    ui->brightnessLineEdit->installEventFilter(this);
    ui->contrastLineEdit->installEventFilter(this);
    ui->saturationLineEdit->installEventFilter(this);



    connect(ui->permissonManagePushButton, SIGNAL(clicked(bool)), this, SLOT(userManageSlot()));

    connect(ui->configFilelookPushButton,   SIGNAL(released()),   this, SLOT(configFileSelectionSlot()));

    connect(ui->configFilelookPushButton_2, SIGNAL(released()), this, SLOT(configUpdateFileSLOT()));

    connect(ui->configFileImportPushButton, SIGNAL(released()), this, SLOT(configFileImportSlot()));


    connect(ui->downLoadLogPushButton, SIGNAL(released()), this, SLOT(downLoadLogSlot()));


    connect(ui->updateBeginPushButton, SIGNAL(clicked(bool)), this, SLOT(devUpdateSlot()));

    connect(ui->clientRebootPushButton, SIGNAL(clicked(bool)), this, SLOT(devRebootSlot()));

    g_buttonGroup1 = new QButtonGroup();      //轮询时间设置单选按钮组成一组，以保证改组中的单选框同时只能选一个，同时与以下其他类别的单选框之间互不影响
    g_buttonGroup1->addButton(ui->pollingTimeSetRadioButton,1);
    g_buttonGroup1->addButton(ui->pollingTimeSetRadioButton_2,2);
    g_buttonGroup1->addButton(ui->pollingTimeSetRadioButton_3,3);
    g_buttonGroup1->addButton(ui->pollingTimeSetRadioButton_4,4);

    g_buttonGroup2 = new QButtonGroup();     //预置点返回时间设置单选按钮组成一组，以保证改组中的单选框同时只能选一个，同时与其他类别的单选框之间互不影响
    g_buttonGroup2->addButton(ui->presetReturnTimeSetRadioButton,1);
    g_buttonGroup2->addButton(ui->presetReturnTimeSetRadioButton_2,2);
    g_buttonGroup2->addButton(ui->presetReturnTimeSetRadioButton_3,3);
    g_buttonGroup2->addButton(ui->presetReturnTimeSetRadioButton_4,4);


    connect(ui->canselPushButton, SIGNAL(clicked()), this, SLOT(registOutButtonClick()));

    connect(g_buttonGroup1, SIGNAL(buttonClicked(int)), this, SLOT(pollingTimeChange(int)));     //单选按钮组按键信号连接响应槽函数
    connect(g_buttonGroup2, SIGNAL(buttonClicked(int)), this, SLOT(presetReturnTimeChange(int)));

    connect(ui->pollingTimeSetLineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(lineEditpollingTimeChange(const QString &)));
    connect(ui->presetReturnTimeSetLineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(lineEditpresetReturnTimeChange(const QString &)));

    connect(ui->timeSetPushButton,SIGNAL(clicked()),this,SLOT(monitorSysTime()));
    connect(ui->timeAdjustPushButton,SIGNAL(clicked()),this,SLOT(systimeSlot()));
    connect(ui->imageParamSetPushButton, SIGNAL(clicked(bool)), this, SLOT(setCameraImageParamSlot()));     //图像参数设置

    connect(ui->carriageSelectionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(carNoChangeSlot()));  //车厢选择下拉框当前索引改变信号响应


    ui->pollingTimeSetLineEdit->setValidator(new QIntValidator(1,24*3600,this));   //只能输入1-24*3600的整数，不能输入字母或其他数字
    ui->presetReturnTimeSetLineEdit->setValidator(new QIntValidator(1,24*60,this));

    ui->brightnessLineEdit->setValidator(new QIntValidator(0,255,this));
    ui->saturationLineEdit->setValidator(new QIntValidator(0,255,this));
    ui->contrastLineEdit->setValidator(new QIntValidator(0,255,this));

    connect(ui->trainTypeSetPushButton, SIGNAL(clicked(bool)), this, SLOT(setTrainType()));
    connect(ui->PISSetPushButton,SIGNAL(clicked(bool)),this,SLOT(setPisSetting()));


    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());

//    ui->dateEdit->dumpObjectTree();
//    QLineEdit* lEdit = ui->dateEdit->findChild<QLineEdit*>();
//    if(lEdit)
//        lEdit->setReadOnly(true);

    ui->dateEdit->setLocale(QLocale::Chinese);

//    ui->timeEdit->dumpObjectTree();
//    lEdit = ui->timeEdit->findChild<QLineEdit*>();
//    if(lEdit)
//        lEdit->setReadOnly(true);


    m_sys_timer = new QTimer(this);
    connect(m_sys_timer,SIGNAL(timeout()),this,SLOT(showSysTime()));
    m_sys_timer->start(1000);

//    ui->sysDataAdjustLabel->setText();
    m_TrainType = "";

    setTrainTypeCombox();
    getTrainConfig();//获取车型配置信息，填充页面
    setPollingTimeRadioButton();  //设置轮询时间单选按钮组的样式
    setPresetReturnTimeRadioButton(); //设置预置点返回时间单选按钮组的样式

}

devUpdateWidget::~devUpdateWidget()
{
    if (gusergroupManage != NULL)
    {
        delete gusergroupManage;
        gusergroupManage = NULL;
    }

    delete g_buttonGroup1;
    g_buttonGroup1 = NULL;

    delete g_buttonGroup2;
    g_buttonGroup2 = NULL;

    delete m_sys_timer;
    m_sys_timer = NULL;
    delete ui;
}

void devUpdateWidget::KeyboardPressKeySlots(char key)
{
    if(key==BSPACE)
     {
         if(ui->pollingTimeSetLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->pollingTimeSetLineEdit->selectedText().isEmpty())
             {
                  ui->pollingTimeSetLineEdit->del();
             }
             else
             {
                 ui->pollingTimeSetLineEdit->backspace();
             }
         }
         else if(ui->presetReturnTimeSetLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->presetReturnTimeSetLineEdit->selectedText().isEmpty())
             {
                  ui->presetReturnTimeSetLineEdit->del();
             }
             else
             {
                 ui->presetReturnTimeSetLineEdit->backspace();
             }
         }
         else if(ui->brightnessLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->brightnessLineEdit->selectedText().isEmpty())
             {
                  ui->brightnessLineEdit->del();
             }
             else
             {
                 ui->brightnessLineEdit->backspace();
             }
         }
         else if(ui->contrastLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->contrastLineEdit->selectedText().isEmpty())
             {
                  ui->contrastLineEdit->del();
             }
             else
             {
                 ui->contrastLineEdit->backspace();
             }
         }
         else if(ui->saturationLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->saturationLineEdit->selectedText().isEmpty())
             {
                  ui->saturationLineEdit->del();
             }
             else
             {
                 ui->saturationLineEdit->backspace();
             }
         }

     }
    else if(key == ENTER)
    {
        ShowKeyboardSlots(0);
    }
    else
    {
     if(ui->pollingTimeSetLineEdit->hasFocus())//输入框1焦点
     {
         ui->pollingTimeSetLineEdit->insert(QString( key));
     }
     else if(ui->presetReturnTimeSetLineEdit->hasFocus())//输入框1焦点
     {
         ui->presetReturnTimeSetLineEdit->insert(QString( key));
     }
     else if(ui->brightnessLineEdit->hasFocus())//输入框1焦点
     {
         ui->brightnessLineEdit->insert(QString( key));
     }
     else if(ui->contrastLineEdit->hasFocus())//输入框1焦点
     {
         ui->contrastLineEdit->insert(QString( key));
     }
     else if(ui->saturationLineEdit->hasFocus())//输入框1焦点
     {
         ui->saturationLineEdit->insert(QString( key));
     }
    }
}

void devUpdateWidget::ShowKeyboardSlots(int nShow)
{
    if(0 == nShow)
    {
        emit show_hide_Signal(nShow);
        g_ibShowKeyboard =0;
    }
    else
    {
        if(g_ibShowKeyboard ==0)
        {
            emit show_hide_Signal(nShow);
            g_ibShowKeyboard =1;
        }
    }
}

bool devUpdateWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        if((obj == ui->pollingTimeSetLineEdit && ui->pollingTimeSetLineEdit->isEnabled()) || (obj ==  ui->presetReturnTimeSetLineEdit && ui->presetReturnTimeSetLineEdit->isEnabled())
        ||  (obj == ui->brightnessLineEdit &&  ui->brightnessLineEdit->isEnabled()) || (obj == ui->contrastLineEdit && ui->contrastLineEdit->isEnabled())
        ||  (obj == ui->saturationLineEdit &&  ui->saturationLineEdit->isEnabled()))                    //判断是不是我创建的label触发了事件
        {
            ShowKeyboardSlots(1);
        }

    }
    else if(e->type() == QEvent::FocusOut)
    {
        if(obj == ui->pollingTimeSetLineEdit || obj == ui->presetReturnTimeSetLineEdit || obj == ui->brightnessLineEdit ||
           obj == ui->contrastLineEdit  || obj == ui->saturationLineEdit)
        {
            ShowKeyboardSlots(0);
        }

    }
    return QWidget::eventFilter(obj, e);

}



void devUpdateWidget::registOutButtonClick()
{
    int update_page = 4;
    this->hide();
    emit registOutSignal(update_page);    //触发注销信号，带上当前设备类型

}


void devUpdateWidget::monitorSysTime()
{
     char acTimeStr[128] = {0};
    timeTd = QDateTime::currentDateTime();

    timeTd.setDate(ui->dateEdit->date());
    timeTd.setTime(ui->timeEdit->time());


    time_t tt = (time_t)timeTd.toTime_t();
    stime(&tt);

    QDateTime time = QDateTime::currentDateTime(); // 获取当前时间
    int year = time.date().year(); // 年
    int month = time.date().month(); // 月
    int day = time.date().day(); // 日
//    int hour = time.time().hour(); // 时
//    int sec = time.time().second(); // 分
//    int msec = time.time().msec(); // 秒

    int h=ui->timeEdit->time().hour();
    int m =ui->timeEdit->time().minute();
    int s =ui->timeEdit->time().second();


    snprintf(acTimeStr, sizeof(acTimeStr), "date %02d%02d%02d%02d%4d.%02d", month, day, h, m,year, s);
    system(acTimeStr);
    system("hwclock -w");

}

void devUpdateWidget::showSysTime()
{
    timeTd = QDateTime::currentDateTime();
    QString str_data = timeTd.toString("yyyy-MM-dd");
    QString str_time = timeTd.toString("hh:mm:ss");

    ui->sysDataAdjustLabel->setText(str_data);
    ui->systimeAdjustLabel->setText(str_time);

}

void devUpdateWidget::systimeSlot()
{
    char acUserType[64] = {0};
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, i = 0, iRet = 0;
    short yr = 0;
    char acTimeStr[256] = {0};
    T_TIME_INFO tTimeInfo;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;
    ui->timeAdjustPushButton->setEnabled(false);
    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
//        DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget set sys time!\n");
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to set system time!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
        ui->timeAdjustPushButton->setEnabled(true);

    }
    else
    {

        if (strlen(ui->dateEdit->text().toLatin1().data()) > 0)
        {
            sscanf(ui->dateEdit->text().toLatin1().data(), "%4d-%02d-%02d", &year, &month, &day);
        }
        if (strlen(ui->timeEdit->text().toLatin1().data()) > 0)
        {
            sscanf(ui->timeEdit->text().toLatin1().data(), "%2d:%02d:%02d", &hour, &minute, &second);
        }

        /*系统校时记录日志*/
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "set local time %4d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
        LOG_WriteLog(&tLogInfo);

        emit systimeSetSignal();


        if (year >= 1970 && (month >= 1 && month <= 12) && (day >= 1 && day <= 31) &&
            (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59) && (second >= 0 && second <= 59))
        {
            memset(&tTimeInfo, 0, sizeof(T_TIME_INFO));
            yr = year;
            tTimeInfo.year = htons(yr);
            tTimeInfo.mon = month;
            tTimeInfo.day = day;
            tTimeInfo.hour = hour;
            tTimeInfo.min = minute;
            tTimeInfo.sec = second;
            memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
            STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
            //printf("%d-%d-%d %d:%d:%d\n",timeInfo.year, (int)timeInfo.mon, (int)timeInfo.day, (int)timeInfo.hour, (int)timeInfo.min, (int)timeInfo.sec);
            for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
            {
                iRet = PMSG_SendPmsgData(m_Phandle[i], CLI_SERV_MSG_TYPE_CHECK_TIME, (char *)&tTimeInfo, sizeof(T_TIME_INFO));    //发送校时命令
                if (iRet < 0)
                {
//                    DebugPrint(DEBUG_UI_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d\n",iRet);
                }
                else
                {
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "notify server %d Time Check OK, %4d-%02d-%02d %02d:%02d:%02d!", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, year, month, day, hour, minute, second);
                    LOG_WriteLog(&tLogInfo);

                    QMessageBox box(QMessageBox::Information,QString::fromUtf8("注意"),QString::fromUtf8("校时成功!"));
                    box.setWindowFlags(Qt::FramelessWindowHint);
                    box.setStandardButtons (QMessageBox::Ok);
                    box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));
                    box.exec();
                }
            }
        }
        ui->timeAdjustPushButton->setEnabled(true);

    }


}

void devUpdateWidget::setTrainTypeCombox()     //读取系统配置文件，获取系统当前设置的车型，以使得车型设置下拉框显示的是当前系统车型
{
    T_TRAIN_TYPE_LIST tTrainTypeList;
    int iRet = 0, i = 0;

    memset(&tTrainTypeList, 0, sizeof(tTrainTypeList));
    iRet = STATE_GetTrainTypeList(&tTrainTypeList);
    if (iRet < 0)
    {
        return;
    }

    for(i = 0; i < tTrainTypeList.iTypeNum; i++)
    {
        ui->trainTypeSetComboBox->addItem(QString(QLatin1String(tTrainTypeList.acTrainTypeName[i])));
    }
}

void devUpdateWidget::getTrainConfig()
{   

    int i = 0,j = 0;
    QString item = "";

    ui->carriageSelectionComboBox->setCurrentIndex(-1);
    ui->carriageSelectionComboBox->clear();

    ui->cameraSelectionComboBox->setCurrentIndex(-1);
    ui->cameraSelectionComboBox->clear();


    char acTrainType[16] = {0};
    T_TRAIN_CONFIG tTrainConfigInfo;
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    STATE_GetCurrentTrainType(acTrainType, sizeof(acTrainType));

    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        item = "";
        item = QString::number(tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
        item += tr("号车厢");
        ui->carriageSelectionComboBox->addItem(item);


        m_Phandle[i] = STATE_GetNvrServerPmsgHandle(i);
//        if(i == 0)
//        {
//            for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
//            {
//                item = "";
//                item = QString::number(1+j);
//                item += tr("号摄像机");
//                ui->cameraSelectionComboBox->addItem(item);
////                qDebug()<<"DEBUG_UI_NOMAL_PRINT tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum ="<<i<<"=:"<<tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum<<__FUNCTION__<<__LINE__<<endl;

//            }

//        }

    }


    for (i = 0; i < ui->trainTypeSetComboBox->count(); i++)
    {
        if (ui->trainTypeSetComboBox->itemText(i) == QString(QLatin1String(acTrainType)))
        {
            ui->trainTypeSetComboBox->setCurrentIndex(i);
            m_TrainType = ui->trainTypeSetComboBox->currentText();
            break;
        }
    }


    g_iIsPBD = ui->PISSetcomboBox->currentIndex();
}

void devUpdateWidget::setPollingTimeRadioButton()     //获取轮询时间，设置轮询时间单选按钮组的样式
{
    int iPollingTime = 0;
    iPollingTime = STATE_GetPollingTime();

    ui->pollingTimeSetLineEdit->setText(QString::number(iPollingTime));
    m_pollingtTimeText = ui->pollingTimeSetLineEdit->text();

    if (10 == iPollingTime)   //轮询时间为10秒，则第一个表示10秒的RadioButton被选中
    {
        ui->pollingTimeSetRadioButton->setChecked(true);
        ui->pollingTimeSetLineEdit->setReadOnly(true);
    }
    else if (20 == iPollingTime)
    {
        ui->pollingTimeSetRadioButton_2->setChecked(true);
        ui->pollingTimeSetLineEdit->setReadOnly(true);
    }
    else if (30 == iPollingTime)
    {
        ui->pollingTimeSetRadioButton_3->setChecked(true);
        ui->pollingTimeSetLineEdit->setReadOnly(true);
    }
    else
    {
        ui->pollingTimeSetRadioButton_4->setChecked(true);
        ui->pollingTimeSetLineEdit->setReadOnly(false);
    }
}

void devUpdateWidget::setPresetReturnTimeRadioButton()     //获取预置点返回时间，设置预置点返回时间单选按钮组的样式
{
    int iReturnTime = 0;
    iReturnTime = STATE_GetPresetReturnTime();

    ui->presetReturnTimeSetLineEdit->setText(QString::number(iReturnTime));
    m_presetReturnTimeText = ui->presetReturnTimeSetLineEdit->text();

    if (5 == iReturnTime)   //预置点返回时间为5分钟，则第一个表示5分钟的RadioButton被选中
    {
        ui->presetReturnTimeSetRadioButton->setChecked(true);
        ui->presetReturnTimeSetLineEdit->setReadOnly(true);
    }
    else if (10 == iReturnTime)
    {
        ui->presetReturnTimeSetRadioButton_2->setChecked(true);
        ui->presetReturnTimeSetLineEdit->setReadOnly(true);
    }
    else if (15 == iReturnTime)
    {
        ui->presetReturnTimeSetRadioButton_3->setChecked(true);
        ui->presetReturnTimeSetLineEdit->setReadOnly(true);
    }
    else
    {
        ui->presetReturnTimeSetRadioButton_4->setChecked(true);
        ui->presetReturnTimeSetLineEdit->setReadOnly(false);
    }
}
void devUpdateWidget::setTimeSignalCtrl()
{
    char acTimeStr[128] = {0};
    QDateTime current_date_time ;

    current_date_time = QDateTime::currentDateTime();
    snprintf(acTimeStr, sizeof(acTimeStr), "%4d-%02d-%02d %02d:%02d:%02d", current_date_time.date().year(), current_date_time.date().month(), current_date_time.date().day(), current_date_time.time().hour(), current_date_time.time().minute(), current_date_time.time().second());
//    ui->sysTimeAdjustLabel->setText(QString(QLatin1String(acTimeStr)));

    return;
}

void devUpdateWidget::setPisSetting()
{
    char acUserType[16] = {0};


    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))   //操作员不能设置车型
    {
        QMessageBox box(QMessageBox::Warning,QString::fromUtf8("提示"),QString::fromUtf8("无权限设置!"));     //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));     //将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        g_iIsPBD = ui->PISSetcomboBox->currentIndex();

    }

}

void devUpdateWidget::setTrainType()
{
    char acUserType[16] = {0}, acTrainType[128] = {0};
    int iRet = 0;
    T_LOG_INFO tLogInfo;

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget trainTypeSet button pressed!\n");

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))   //操作员不能设置车型
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to set train type!\n");
        QMessageBox box(QMessageBox::Warning,QString::fromUtf8("提示"),QString::fromUtf8("无权限设置!"));     //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));     //将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        if (m_TrainType != ui->trainTypeSetComboBox->currentText())   //只有当车型选择被改变才进行设置
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget set train type will reboot client, confirm?\n");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("提示")),QString(tr("将重启使车型设置生效，是否继续？")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.button(QMessageBox::Yes)->setText("Yes");
            msgBox.button(QMessageBox::No)->setText("NO");
            iRet=msgBox.exec();
            if(iRet != QMessageBox::Yes)
            {
                return;
            }
            snprintf(acTrainType, sizeof(acTrainType), "%s", ui->trainTypeSetComboBox->currentText().toLatin1().data());
            STATE_SetCurrentTrainType(acTrainType);
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] set currernt traintype to %s\n", __FUNCTION__, acTrainType);

            memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
            tLogInfo.iLogType = 0;
            snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "change traintype to %s and monitor Client reboot!", acTrainType);
            LOG_WriteLog(&tLogInfo);

            system("reboot");
            system("sync");
        }
    }
}

void devUpdateWidget::carNoChangeSlot()   //车厢号切换信号响应槽函数
{
    int i = 0, idex = ui->carriageSelectionComboBox->currentIndex();    //获取当前车厢选择下拉框的索引
    QString item = "";
    T_TRAIN_CONFIG tTrainConfigInfo;
//    DebugPrint(DEBUG_UI_OPTION_PRINT, "recordPlayWidget change server carriage No!\n");

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    ui->cameraSelectionComboBox->setCurrentIndex(-1);
    ui->cameraSelectionComboBox->clear();

    qDebug()<<"*****---carNoChangeSlot--=:"<<idex<<tTrainConfigInfo.tNvrServerInfo[idex].iPvmsCameraNum<<__FUNCTION__<<__LINE__<<endl;
    for (i = 0; i < tTrainConfigInfo.tNvrServerInfo[idex].iPvmsCameraNum; i++)        //根据不同车厢位置的NVR服务器的摄像机数量个数跟新摄像机选择下拉框
    {
        item = "";
        item = QString::number(1+i);
        item += tr("号摄像机");
        ui->cameraSelectionComboBox->addItem(item);
    }

}

void devUpdateWidget::setCameraImageParamSlot()
{

    int idex = 0, iRet = 0;
    char acUserType[64] = {0};
    T_PIC_ATTRIBUTE picParam;
    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to set CameraImage Param!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        idex = ui->carriageSelectionComboBox->currentIndex();
        if (idex < 0)
        {
            return;
        }

        if(ui->brightnessLineEdit->text().toInt() > 255 || ui->saturationLineEdit->text().toInt() > 255 || ui->contrastLineEdit->text().toInt() > 255)
        {
            QMessageBox box(QMessageBox::Warning,tr("提示"),tr("输入数字不能超过255!"));	  //新建消息提示框，提示错误信息
            box.setWindowFlags(Qt::FramelessWindowHint);
            box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
            box.exec();
            return;

        }

        memset(&picParam, 0, sizeof(T_PIC_ATTRIBUTE));
        picParam.iBrightness = ui->brightnessLineEdit->text().toInt();
        picParam.iSaturation = ui->saturationLineEdit->text().toInt();
        picParam.iContrast = ui->contrastLineEdit->text().toInt();


        iRet = PMSG_SendPmsgData(m_Phandle[idex], CLI_SERV_MSG_TYPE_SET_PIC_ATTRIBUTE, (char *)&picParam, sizeof(T_PIC_ATTRIBUTE));    //发送设置图像效果参数命令
        if (iRet < 0)
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_SET_PIC_ATTRIBUTE error!iRet=%d,server=%d\n", __FUNCTION__, iRet, idex+1);
        }

    }

}

void devUpdateWidget::closeUserManageWidget()
{
    if(NULL==this->gusergroupManage)
    {
        return;
    }
    else
    {
        delete this->gusergroupManage;
    }
    this->gusergroupManage=NULL;
}


void devUpdateWidget::userManageSlot()  //点击用户管理按钮响应函数，弹出用户管理界面
{
    if( g_ichagepage == 0)
     {
        g_ichagepage = 1;
        gusergroupManage->show();
        ui->deviceManagewidget->hide();
        gusergroupManage->init_datavase();
    }
    else
    {
        g_ichagepage = 0;
        gusergroupManage->hide();
        ui->deviceManagewidget->show();

    }

}


void devUpdateWidget::configFileSelectionSlot()
{

    QString filename = "";
    char acUserType[64] = {0};

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget configFileSelection button pressed!\n");

        STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
        if (!strcmp(acUserType, "operator"))	 //操作员无权校时
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to select config file!\n");
            QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
            box.setWindowFlags(Qt::FramelessWindowHint);
            box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
            box.exec();
        }
        else
        {
            if (access("/media/usb0/", F_OK) < 0)
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
                msgBox.setWindowFlags(Qt::FramelessWindowHint);
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.button(QMessageBox::Yes)->setText("OK");
                msgBox.exec();
                return;
            }
            else
            {
                if (0 == STATE_FindUsbDev())   //这里处理一个特殊情况:U盘拔掉时umount失败，/mnt/usb/u/路径还存在，但是实际U盘是没有再插上的
                {
//                    DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                    QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
                    msgBox.setWindowFlags(Qt::FramelessWindowHint);
                    msgBox.setStandardButtons(QMessageBox::Yes);
                    msgBox.button(QMessageBox::Yes)->setText("OK");
                    msgBox.exec();
                    return;
                }
            }
            char *pcfileName = NULL;

            QFileDialog *dialog = new QFileDialog;
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            dialog->setWindowFlag(Qt::FramelessWindowHint);
            dialog->setDirectory("/media/usb0/");
            dialog->setFilter(QDir::Files);
            dialog->setFixedSize(800,600);
            dialog->show();

            QDir file = dialog->directory();
            QDir *dir = NULL;
            if(dir ==NULL)
            {
                dir = new QDir(file);
            }
            QStringList filter;
            QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
           for(int i = 0;i<fileInfo->count(); i++)
           {
//               qDebug()<<fileInfo->at(i).filePath();
//               qDebug()<<fileInfo->at(i).fileName();
               if(fileInfo->at(i).fileName() == "Station.ini")
               {
                    filename =fileInfo->at(i).filePath();

               }
           }
//            filename = QFileDialog::getOpenFileName(this, "打开文件", "/media/usb0/", "ini文件(*.ini)");
            if (!filename.isNull())
            {
                ui->configFileDisplayLineEdit->setText(filename);
            }
            pcfileName = parseFileNameFromPath(ui->configFileDisplayLineEdit->text().toLatin1().data());
            if (NULL == pcfileName)
            {
                return;
            }
        }

}

void devUpdateWidget::configUpdateFileSLOT()
{

    char *pcfileName = NULL;

    QString filename = "";
    char acUserType[64] = {0};

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget configFileSelection button pressed!\n");

        STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
        if (!strcmp(acUserType, "operator"))	 //操作员无权校时
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to select config file!\n");
            QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
            box.setWindowFlags(Qt::FramelessWindowHint);
            box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
            box.exec();
        }
        else
        {
            if (access("/media/usb0/", F_OK) < 0)
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
                msgBox.setWindowFlags(Qt::FramelessWindowHint);
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.button(QMessageBox::Yes)->setText("OK");
                msgBox.exec();
                return;
            }
            else
            {
                if (0 == STATE_FindUsbDev())   //这里处理一个特殊情况:U盘拔掉时umount失败，/mnt/usb/u/路径还存在，但是实际U盘是没有再插上的
                {
//                    DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                    QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
                    msgBox.setWindowFlags(Qt::FramelessWindowHint);
                    msgBox.setStandardButtons(QMessageBox::Yes);
                    msgBox.button(QMessageBox::Yes)->setText("OK");
                    msgBox.exec();
                    return;
                }
            }

            QFileDialog *dialog = new QFileDialog;
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            dialog->setWindowFlag(Qt::FramelessWindowHint);
            dialog->setDirectory("/media/usb0/");
            dialog->setFilter(QDir::Files);
            dialog->setFixedSize(800,600);
            dialog->show();

            QDir file = dialog->directory();
            QDir *dir = NULL;
            if(dir ==NULL)
            {
                dir = new QDir(file);
            }
            QStringList filter;
            QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
           for(int i = 0;i<fileInfo->count(); i++)
           {
//               qDebug()<<fileInfo->at(i).filePath();
//               qDebug()<<fileInfo->at(i).fileName();
               if(fileInfo->at(i).fileName() == "monitor")
               {
                    filename =fileInfo->at(i).filePath();
//                    qDebug()<<"*************filename="<<filename<<__LINE__;

               }
           }

//            filename = QFileDialog::getOpenFileName(this, "打开文件", "/media/usb0/", "文件(*)");
            if (!filename.isNull())
            {
                ui->configFileDisplayLineEdit_2->setText(filename);
            }

            pcfileName = parseFileNameFromPath(ui->configFileDisplayLineEdit_2->text().toLatin1().data());
            if (NULL == pcfileName)
            {
                return;
            }

            if (strncmp(pcfileName, "monitor", strlen(pcfileName)) != 0)
            {
                QMessageBox msgBox(QMessageBox::Question,QString(tr("注意")),QString(tr("升级文件选择错误")));
                msgBox.setWindowFlags(Qt::FramelessWindowHint);
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.button(QMessageBox::Yes)->setText("OK");
                msgBox.exec();
                return;
            }
        }

}

void devUpdateWidget::devUpdateSlot()
{
    char acUserType[64] = {0};

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget update device!\n");

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to update device!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));   //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        ui->updateStatueTextEdit->clear();

        if (access("/media/usb0/", F_OK) < 0)
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
            ui->clientRebootPushButton->setEnabled(true);
            ui->updateStatueTextEdit->append(tr("没有发现USB"));

            return;
        }
        else
        {
            if (0 == STATE_FindUsbDev())   //这里处理一个特殊情况:U盘拔掉时umount失败，/mnt/usb/u/路径还存在，但是实际U盘是没有再插上的
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                ui->clientRebootPushButton->setEnabled(true);
                ui->updateStatueTextEdit->append(tr("没有发现USB"));

                return;
            }
        }
        ui->updateStatueTextEdit->append(tr("发现USB，已准备好"));
#if 0
        if (0 == strlen(ui->configFileDisplayLineEdit_2->text().toLatin1().data()))
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget not select any config file!\n");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("注意")),QString(tr("请选升级文件")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.button(QMessageBox::Yes)->setText("OK");
            msgBox.exec();
            return;
        }
#endif

        if (access("/media/usb0/monitor", F_OK) < 0)
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget not find update file in USB device!\n");
            QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("U盘中未检测更新文件!")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.button(QMessageBox::Yes)->setText("OK");
            msgBox.exec();
            ui->clientRebootPushButton->setEnabled(true);
            return;
        }

        ui->clientRebootPushButton->setEnabled(false);    //更新开始，设置重启按钮不可操作

        ui->updateStatueTextEdit->append(tr("正在复制文件..."));
        if (access("/home/data/backup",F_OK) < 0)
        {
            system("mkdir /home/data/backup");
        }

        system("cp /home/user/bin/monitor /home/data/backup/");
        system("rm /home/user/bin/monitor");
        system("cp /media/usb0/monitor /home/user/bin/monitor");
        system("sync");

        ui->updateStatueTextEdit->append(tr("复制文件完成"));
        ui->updateStatueTextEdit->append(tr("更新完成，请重启!"));
        ui->clientRebootPushButton->setEnabled(true);    //更新完成，恢复重启按钮可操作
    }

}
void devUpdateWidget::devRebootSlot()
{
    char acUserType[64] = {0};
    T_LOG_INFO tLogInfo;

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget client reboot!\n");

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to reboot client!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "monitor Client reboot!");
        LOG_WriteLog(&tLogInfo);

        system("reboot");
        system("sync");

    }


}

void devUpdateWidget::downLoadLogSlot()
{
    int iRet = 0;
    char *pcfileName = NULL;
    char acUserType[64] = {0};

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget configFileImport button pressed!\n");

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to import config file!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
    }
    else
    {

        if (access("/media/usb0/", F_OK) < 0)
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
            QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.button(QMessageBox::Yes)->setText("OK");
            msgBox.exec();
            return;
        }
        else
        {
            if (0 == STATE_FindUsbDev())   //这里处理一个特殊情况:U盘拔掉时umount失败，/mnt/usb/u/路径还存在，但是实际U盘是没有再插上的
            {
//                DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget::%s %d not get USB device!\n",__FUNCTION__,__LINE__);
                QMessageBox msgBox(QMessageBox::Warning,QString(tr("注意")),QString(tr("未检测到U盘,请插入!")));
                msgBox.setWindowFlags(Qt::FramelessWindowHint);
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.button(QMessageBox::Yes)->setText("OK");
                msgBox.exec();
                return;
            }
        }


        system("cp /home/data/sys.log /media/usb0/");
        system("sync");

        QMessageBox msgBox2(QMessageBox::Information,QString(tr("注意")),QString(tr("导入成功，请拔出U盘!")));
        msgBox2.setWindowFlags(Qt::FramelessWindowHint);
        msgBox2.setStandardButtons(QMessageBox::Yes);
        msgBox2.button(QMessageBox::Yes)->setText("OK");
        msgBox2.exec();
        return;
    }
}

void devUpdateWidget::configFileImportSlot()
{

    int iRet = 0;
    char *pcfileName = NULL;
    char acUserType[64] = {0};

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "devUpdateWidget configFileImport button pressed!\n");

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));
    if (!strcmp(acUserType, "operator"))	 //操作员无权校时
    {
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget this user type has no right to import config file!\n");
        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("无权限设置!"));	  //新建消息提示框，提示错误信息
        box.setWindowFlags(Qt::FramelessWindowHint);
        box.setStandardButtons (QMessageBox::Ok);	//设置提示框只有一个标准按钮
        box.setButtonText (QMessageBox::Ok,tr("OK")); 	//将按钮显示改成"确 定"
        box.exec();
    }
    else
    {
        if (0 == strlen(ui->configFileDisplayLineEdit->text().toLatin1().data()))
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget not select any config file!\n");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("注意")),QString(tr("请选择配置文件")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.button(QMessageBox::Yes)->setText("OK");
            msgBox.exec();
            return;
        }

        pcfileName = parseFileNameFromPath(ui->configFileDisplayLineEdit->text().toLatin1().data());
        if (NULL == pcfileName)
        {
            return;
        }

        if (strncmp(pcfileName, "Station.ini", strlen(pcfileName)) != 0)
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devUpdateWidget select error config file!\n");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("注意")),QString(tr("配置文件选择错误")));
            msgBox.setWindowFlags(Qt::FramelessWindowHint);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.button(QMessageBox::Yes)->setText("OK");
            msgBox.exec();
            return;
        }

        system("cp /media/usb0/Station.ini /home/data/monitorCfg/Station.ini");
        system("sync");

        QMessageBox msgBox2(QMessageBox::Information,QString(tr("注意")),QString(tr("导入成功，请拔出U盘!")));
        msgBox2.setStandardButtons(QMessageBox::Yes);
        msgBox2.button(QMessageBox::Yes)->setText("确 定");
        msgBox2.exec();
        return;
    }


}

void devUpdateWidget::alarmPushButoonClickSlot()  //点击报警按钮的响应函数，删除报警定时器并恢复按钮为正常不闪烁样式
{
    emit alarmPushButoonClickSignal();
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);

    g_iVNum = 0;
}
void devUpdateWidget::alarmHappenCtrlSlot()    //报警触发定时器处理函数，间隔的切换按钮样式，达到闪烁效果
{
    if (this->isHidden() != 1)
    {
        if (0 == g_iVNum%2)
        {
            ui->alarmPushButton->setChecked(true);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alerton.bmp);background-color: rgb(255, 255, 255);}");

        }
        else
        {
            ui->alarmPushButton->setChecked(false);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");

        }
        g_iVNum++;
    }
}
void devUpdateWidget::alarmHappenSlot()    //报警触发的响应函数
{
    if (NULL == m_alarmHappenTimer)    //启动一个定时器，每500毫秒切换按钮样式，达到闪烁效果
    {
        m_alarmHappenTimer = new QTimer(this);
        connect(m_alarmHappenTimer,SIGNAL(timeout()), this,SLOT(alarmHappenCtrlSlot()));
        m_alarmHappenTimer->start(500);
    }
}
void devUpdateWidget::alarmClearSlot()     //报警清除的响应函数，删除报警定时器并恢复按钮为正常不闪烁样式
{
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);
    ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");


    g_iVNum = 0;
}

void devUpdateWidget::lineEditpresetReturnTimeChange(const QString &)
{
    m_presetReturnTimeText = ui->presetReturnTimeSetLineEdit->text();
    STATE_SetPresetReturnTime(m_presetReturnTimeText.toInt());
}
void devUpdateWidget::lineEditpollingTimeChange(const QString &)
{
     m_pollingtTimeText =  ui->pollingTimeSetLineEdit->text();
     STATE_SetPollingTime(m_pollingtTimeText.toInt());
}

void devUpdateWidget::pollingTimeChange(int iComboBoxId)
{
    static int iOldId = 0;
    if (iComboBoxId != iOldId)
    {
        switch (iComboBoxId) //根据单选按钮组按键信号传入的单选按钮编号区分不同的单选按钮，做出不同的设置
        {
            case 1:
            {
                ui->pollingTimeSetLineEdit->setReadOnly(true);   //非自定义单选按钮被选中时，轮询时间设置输入框设置为只读
                ui->pollingTimeSetLineEdit->setText("10");
                break;
            }
            case 2:
            {
                ui->pollingTimeSetLineEdit->setReadOnly(true);
                ui->pollingTimeSetLineEdit->setText("20");
                break;
            }
            case 3:
            {
                ui->pollingTimeSetLineEdit->setReadOnly(true);
                ui->pollingTimeSetLineEdit->setText("30");
                break;
            }
            case 4:
            {
                ui->pollingTimeSetLineEdit->setReadOnly(false);    //自定义单选按钮被选中时，轮询时间设置输入框设置为可读写
                break;
            }
            default:
                break;
        }
        iOldId = iComboBoxId;
    }
    m_pollingtTimeText = ui->pollingTimeSetLineEdit->text();
    STATE_SetPollingTime(m_pollingtTimeText.toInt());

}

void devUpdateWidget::presetReturnTimeChange(int iComboBoxId)
{
    static int iOldId = 0;
    if (iComboBoxId != iOldId)
    {
        switch (iComboBoxId)  //根据单选按钮组按键信号传入的单选按钮编号区分不同的单选按钮，做出不同的设
        {
            case 1:
            {
                ui->presetReturnTimeSetLineEdit->setReadOnly(true);    //非自定义单选按钮被选中时，预置点返回时间设置输入框设置为只读
                ui->presetReturnTimeSetLineEdit->setText("5");
                break;
            }
            case 2:
            {
                ui->presetReturnTimeSetLineEdit->setReadOnly(true);
                ui->presetReturnTimeSetLineEdit->setText("10");
                break;
            }
            case 3:
            {
                ui->presetReturnTimeSetLineEdit->setReadOnly(true);
                ui->presetReturnTimeSetLineEdit->setText("15");
                break;
            }
            case 4:
            {
                ui->presetReturnTimeSetLineEdit->setReadOnly(false);   //自定义单选按钮被选中时，预置点返回时间设置输入框设置为可读写
                break;
            }
            default:
                break;
        }
        iOldId = iComboBoxId;
    }
    m_presetReturnTimeText = ui->presetReturnTimeSetLineEdit->text();
    STATE_SetPresetReturnTime(m_presetReturnTimeText.toInt());
}

