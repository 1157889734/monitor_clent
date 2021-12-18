#include "pvmsmenuwidget.h"
#include "ui_pvmsmenuwidget.h"
#include <QDebug>
#include <netinet/in.h>
#include <QIcon>
#include <QTextCodec>
#include <QMessageBox>


#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面
#define PAGENONE    0
#define PAGEMONITOR 1
#define PAGERCORDE  2
#define PAGEMANAGE  3
#define PAGEUPDATE  4
#define PAGEALAGE   5

static int g_ipageValue = 0;

pvmsMenuWidget::pvmsMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pvmsMenuWidget)
{
    ui->setupUi(this);

    this->showFullScreen();
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/monres/Pantobg.bmp")));
    QIcon icon;
    this->setPalette(palette);

    g_ipageValue = 0;


    icon.addFile(QString::fromUtf8(":/monres/PantoMonitor1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->pvmsMonitorMenuPushButton->setIcon(icon);
    ui->pvmsMonitorMenuPushButton->setIconSize(QSize(203,102));

    icon.addFile(QString::fromUtf8(":/monres/PantoPlay.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->recordPlayMenuPushButton->setIcon(icon);
    ui->recordPlayMenuPushButton->setIconSize(QSize(203,102));

    icon.addFile(QString::fromUtf8(":/monres/PantoIntell.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->inteAnalyMenuPushButton->setIcon(icon);
    ui->inteAnalyMenuPushButton->setIconSize(QSize(203,102));

    icon.addFile(QString::fromUtf8(":/monres/Pantoequip.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->devManageMenuPushButton->setIcon(icon);
    ui->devManageMenuPushButton->setIconSize(QSize(203,102));

    icon.addFile(QString::fromUtf8(":/monres/PantoMantain.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->devUpdateMenuPushButton->setIcon(icon);
    ui->devUpdateMenuPushButton->setIconSize(QSize(203,102));

    m_pvmsMonitorPage = new pvmsMonitorWidget(this);   //受电弓监控页面
    m_pvmsMonitorPage->setGeometry(0, 138, m_pvmsMonitorPage->width(), m_pvmsMonitorPage->height());   //设置位置
    m_recordPlayPage = new recordPlayWidget(this);     //录像回放页面
    m_recordPlayPage->setGeometry(0, 138, m_recordPlayPage->width(), m_recordPlayPage->height());
    m_inteAnalyPage = new inteAnalyWidget(this);		 //智能分析页面
    m_inteAnalyPage->setGeometry(0, 138, m_inteAnalyPage->width(), m_inteAnalyPage->height());
    m_devManagePage = new devManageWidget(this);       //设备管理页面
    m_devManagePage->setGeometry(0, 138, m_devManagePage->width(), m_devManagePage->height());
    m_devUpdatePage = new devUpdateWidget(this);       //设备更新页面
    m_devUpdatePage->setGeometry(0, 138, m_devUpdatePage->width(), m_devUpdatePage->height());


    mCkeybord = new CKeyboard(this,0);
    mCkeybord->setGeometry(50,330,924,200);
    mCkeybord->hide();
    connect(mCkeybord,SIGNAL(KeyboardPressKeySignal(char)),m_devUpdatePage,SLOT(KeyboardPressKeySlots(char)));

    connect(mCkeybord,SIGNAL(KeyboardPressKeySignal(char)),m_devManagePage,SLOT(KeyboardPressKeySlots(char)));

    connect(m_devUpdatePage,SIGNAL(show_hide_Signal(int)),this,SLOT(show_hide_Funtion(int)));

    connect(m_devManagePage,SIGNAL(show_hide_Signal(int)),this,SLOT(show_hide_Funtion(int)));


    box = new MsgBox(this);
    box->setWindowModality(Qt::ApplicationModal);
    box->setStyleSheet("background-color: rgb(51, 153, 223);");
    box->move(350,300);
    box->hide();




    m_pvmsMonitorPage->hide();
    m_recordPlayPage->hide();
    m_inteAnalyPage->hide();
    m_devManagePage->hide();
    m_devUpdatePage->hide();
    m_alarmPage = NULL;
    m_iAlarmPageOpenFlag = 0;

    for (int i = 0; i < MAX_SERVER_NUM; i++)
    {
        m_iNoCheckDiskErrNum[i] = 0;
        m_iCheckDiskErrFlag[i] = 0;
    }


    ui->pvmsMonitorMenuPushButton->setFocusPolicy(Qt::NoFocus); // 得到焦点时，不显示虚线框
    ui->recordPlayMenuPushButton->setFocusPolicy(Qt::NoFocus);
    ui->inteAnalyMenuPushButton->setFocusPolicy(Qt::NoFocus);
    ui->devManageMenuPushButton->setFocusPolicy(Qt::NoFocus);
    ui->devUpdateMenuPushButton->setFocusPolicy(Qt::NoFocus);
//    ui->loginOutPushButton->setFocusPolicy(Qt::NoFocus);


    connect(m_pvmsMonitorPage, SIGNAL(getDevStateSignal()), m_devManagePage, SLOT(getDevStateSignalCtrl()));
    connect(m_devManagePage, SIGNAL(serverOffLine(int)), this, SLOT(serverOffLineSlot(int)));
    connect(m_recordPlayPage, SIGNAL(setRecordPlayFlagSignal(int)), m_pvmsMonitorPage, SLOT(setRecordPlayFlag(int)));
    connect(m_pvmsMonitorPage, SIGNAL(setTimeSignal()), m_devUpdatePage, SLOT(setTimeSignalCtrl()));
    connect(m_devUpdatePage, SIGNAL(systimeSetSignal()), m_pvmsMonitorPage, SLOT(systimeSetSlot()));
    connect(m_devManagePage, SIGNAL(systimeSetSignal()), m_pvmsMonitorPage, SLOT(systimeSetSlot()));
    connect(m_pvmsMonitorPage, SIGNAL(hideAlarmWidgetSignal()), this, SLOT(hideAlarmWidgetSlot()));
    connect(m_pvmsMonitorPage, SIGNAL(showAlarmWidgetSignal()), this, SLOT(showAlarmWidgetSlot()));
    connect(this, SIGNAL(blackScreenSignal()), m_pvmsMonitorPage, SLOT(blackScreenCtrlSlot()));
    connect(this, SIGNAL(blackScreenExitSignal()), m_pvmsMonitorPage, SLOT(blackScreenExitCtrlSlot()));





//    connect(ui->loginOutPushButton, SIGNAL(clicked()), this, SLOT(registOutButtonClick()));
    connect(ui->pvmsMonitorMenuPushButton, SIGNAL(clicked()), this, SLOT(menuButtonClick()));     //连接受电弓监控菜单按钮的按键信号和响应函数
    connect(ui->recordPlayMenuPushButton, SIGNAL(clicked()), this, SLOT(menuButtonClick()));	  //连接录像回放菜单按钮的按键信号和响应函数
    connect(ui->inteAnalyMenuPushButton, SIGNAL(clicked()), this, SLOT(menuButtonClick()));		  //连接智能分析菜单按钮的按键信号和响应函数
    connect(ui->devManageMenuPushButton, SIGNAL(clicked()), this, SLOT(menuButtonClick()));		  //连接设备管理菜单按钮的按键信号和响应函数
    connect(ui->devUpdateMenuPushButton, SIGNAL(clicked()), this, SLOT(menuButtonClick()));		  //连接设备更新菜单按钮的按键信号和响应函数

    connect(m_pvmsMonitorPage,SIGNAL(registOutSignal(int)),this,SLOT(registOutButtonClick(int)));
    connect(m_recordPlayPage,SIGNAL(registOutSignal(int)),this,SLOT(registOutButtonClick(int)));
    connect(m_inteAnalyPage,SIGNAL(registOutSignal(int)),this,SLOT(registOutButtonClick(int)));
    connect(m_devUpdatePage,SIGNAL(registOutSignal(int)),this,SLOT(registOutButtonClick(int)));
    connect(m_devManagePage,SIGNAL(registOutSignal(int)),this,SLOT(registOutButtonClick(int)));




    connect(m_pvmsMonitorPage, SIGNAL(alarmPushButoonClickSignal()), this, SLOT(alarmPageShowSlot()));
    connect(m_recordPlayPage, SIGNAL(alarmPushButoonClickSignal()), this, SLOT(alarmPageShowSlot()));
    connect(m_devManagePage, SIGNAL(alarmPushButoonClickSignal()), this, SLOT(alarmPageShowSlot()));
    connect(m_devUpdatePage, SIGNAL(alarmPushButoonClickSignal()), this, SLOT(alarmPageShowSlot()));
    connect(m_inteAnalyPage, SIGNAL(alarmPushButoonClickSignal()), this, SLOT(alarmPageShowSlot()));



    ui->pvmsMonitorMenuPushButton->setChecked(true);
    ui->recordPlayMenuPushButton->setChecked(false);
    ui->inteAnalyMenuPushButton->setChecked(false);
    ui->devManageMenuPushButton->setChecked(false);
    ui->devUpdateMenuPushButton->setChecked(false);

//    m_Rs485Timer = new QTimer(this);
//    m_Rs485Timer->start(100);
//    connect(m_Rs485Timer, SIGNAL(timeout()), this, SLOT(rs485TimerFunc()));


    m_PmsgTimer = new QTimer(this);
    m_PmsgTimer->start(50);
    connect(m_PmsgTimer, SIGNAL(timeout()), this, SLOT(pmsgTimerFunc()));
}


pvmsMenuWidget::~pvmsMenuWidget()
{

    if (m_PmsgTimer != NULL)
    {
        if (m_PmsgTimer ->isActive())
        {
            m_PmsgTimer ->stop();
        }
        delete m_PmsgTimer;
        m_PmsgTimer  = NULL;
    }

    if (m_Rs485Timer != NULL)
    {
        if (m_Rs485Timer ->isActive())
        {
            m_Rs485Timer ->stop();
        }
        delete m_Rs485Timer;
        m_Rs485Timer  = NULL;
    }
    delete mCkeybord;
    mCkeybord = NULL;
    delete m_pvmsMonitorPage;
    m_pvmsMonitorPage = NULL;
    delete m_recordPlayPage;
    m_recordPlayPage = NULL;
    delete m_inteAnalyPage;
    m_inteAnalyPage = NULL;
    delete m_devManagePage;
    m_devManagePage = NULL;
    delete m_devUpdatePage;
    m_devUpdatePage = NULL;
    if (m_alarmPage!= NULL)
    {
        delete m_alarmPage;
    }

    delete box;
    box = NULL;

    delete ui;

}

void pvmsMenuWidget::show_hide_Funtion(int value)
{
    if(0 == value)
    {
        mCkeybord->hide();
    }
    else
    {
        mCkeybord->show();
    }
}


void pvmsMenuWidget::recvRs485Ctrl(char *pcData, int iDataLen)
{
    if (m_devManagePage != NULL)
    {
        m_devManagePage->rs485Ctrl(pcData, iDataLen);
    }

}

void pvmsMenuWidget::rs485TimerFunc()
{
    int iRet = 0;
     T_RS485_PACKET tPkt;

     iRet = RS485_GetDataFromRs485Queue(m_pRs485Handle, &tPkt);
     if (iRet < 0)
     {
//         DebugPrint(DEBUG_RS485_DATA_PRINT, "get rs485 data error\n");
//         qDebug()<<"get rs485 data error"<<__FUNCTION__<<__LINE__<<endl;
         return;
     }

     if (NULL == tPkt.pcData || 0 == tPkt.iDataLen)
     {
         return;
     }

     recvRs485Ctrl(tPkt.pcData, tPkt.iDataLen);
     if (tPkt.pcData)
     {
         free(tPkt.pcData);
         tPkt.pcData = NULL;
     }

}
void pvmsMenuWidget::pmsgTimerFunc()
{
    int i = 0, iRet = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_PMSG_PACKET tPkt;
    PMSG_HANDLE pmsgHandle = 0;

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        memset(&tPkt, 0, sizeof(T_PMSG_PACKET));
        pmsgHandle = STATE_GetNvrServerPmsgHandle(i);
        iRet = PMSG_GetDataFromPmsgQueue(pmsgHandle, &tPkt);
        if (iRet < 0)
        {
//            DebugPrint(DEBUG_PMSG_ERROR_PRINT, "get server 192.168.%d.81 pmsg data error\n", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
//            qDebug()<<"get server 192.168.%d.81 pmsg data error"<<100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO<<endl;
            continue;
        }
//        DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pmsgTimerFunc get pmsg message 0x%x, msgDataLen=%d\n",(int)tPkt.ucMsgCmd, tPkt.iMsgDataLen);
//        qDebug()<<"pmsgTimerFunc get pmsg message 0x%x, msgDataLen="<<tPkt.ucMsgCmd<<tPkt.iMsgDataLen<<endl;

        recvPmsgCtrl(tPkt.PHandle, tPkt.ucMsgCmd, tPkt.pcMsgData, tPkt.iMsgDataLen);
        if (tPkt.pcMsgData)
        {
            free(tPkt.pcMsgData);
            tPkt.pcMsgData = NULL;
        }
    }


}

void pvmsMenuWidget::recvPmsgCtrl(PMSG_HANDLE pHandle, unsigned char ucMsgCmd, char *pcMsgData, int iMsgDataLen)  //与服务器通信消息的分发处理
{
    int iAlarmType = 0, iDevPos = 0, iShadeAlarmEnableFlag = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    int iCarriageNO;
    switch(ucMsgCmd)    //不同的应答消息类型分发给不同的页面处理
    {
        case SERV_CLI_MSG_TYPE_SET_PTZ_RESP:
        case SERV_CLI_MSG_TYPE_SET_PRESETS_RESP:
        case SERV_CLI_MSG_TYPE_PVMS_IPC_CTRL_RESP:
        case SERV_CLI_MSG_TYPE_PVMS_LIGHT_CTRL_RESP:
        case SERV_CLI_MSG_TYPE_PVMS_UPDOWN_REPORT:
        case SERV_CLI_MSG_TYPE_PVMS_UP_DOWN_CTRL:
        {
//            DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMenu Widget get pmsg message 0x%x, msgDataLen=%d\n",(int)ucMsgCmd, iMsgDataLen);
            if (m_pvmsMonitorPage != NULL)
            {
                m_pvmsMonitorPage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
            }
            break;
        }
        case SERV_CLI_MSG_TYPE_GET_RECORD_TIME_LEN_RESP:
        case SERV_CLI_MSG_TYPE_GET_RECORD_FILE_RESP:
        {
//            DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMenu Widget get pmsg message 0x%x, msgDataLen=%d\n",(int)ucMsgCmd, iMsgDataLen);
            if (m_recordPlayPage != NULL)
            {
                m_recordPlayPage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
            }
            break;
        }
        case SERV_CLI_MSG_TYPE_GET_NVR_STATUS_RESP:
        {
            if (pcMsgData == NULL || iMsgDataLen != 18)
            {
                break;
            }
            else
            {
                if (m_devManagePage != NULL)
                {
                    m_devManagePage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
                }

                memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
                STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
                for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
                {
                    if (pHandle == STATE_GetNvrServerPmsgHandle(i))
                    {
                        /*第一次连上服务器的3分钟之内不检测硬盘是否异常*/
                        if (0 == m_iCheckDiskErrFlag[i])
                        {
                            m_iNoCheckDiskErrNum[i]++;
                            if (18 == m_iNoCheckDiskErrNum[i])
                            {
                                m_iCheckDiskErrFlag[i] = 1;
                                m_iNoCheckDiskErrNum[i] = 0;
                            }
                        }

                        T_NVR_STATUS *ptNvrstaus = (T_NVR_STATUS *)pcMsgData;
                        if (htons(ptNvrstaus->i16HdiskTotalSize) <= 0)
                        {
                            if (1 == m_iCheckDiskErrFlag[i])
                            {
                                iAlarmType = ALARM_HDISK_ERR;
                                m_pvmsMonitorPage->HDiskState = ALARM_HDISK_ERR;

                            }
                        }
                        else
                        {
                            iAlarmType = ALARM_HDISK_CLEAR;
                            m_pvmsMonitorPage->HDiskState = ALARM_HDISK_CLEAR;

                        }

                        if (tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO <= 0)
                        {
                            break;
                        }
                        emit reflushAlarmPageSignal(iAlarmType, tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 0);
                        break;
                    }
                }
            }
            break;
        }
        case SERV_CLI_MSG_TYPE_GET_IPC_STATUS_RESP:
        case SERV_CLI_MSG_TYPE_PISMSG_REPORT:
        {
//            DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMenu Widget get pmsg message 0x%x, msgDataLen=%d\n",(int)ucMsgCmd, iMsgDataLen);
            if (m_devManagePage != NULL)
            {
                m_devManagePage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
            }
            break;
        }
        case SERV_CLI_MSG_TYPE_VIDEO_ALARM_REPORT:
        {
//            DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMenu Widget get pmsg message 0x%x, msgDataLen=%d\n",(int)ucMsgCmd, iMsgDataLen);
            if (pcMsgData == NULL || iMsgDataLen != 4)
            {
                break;
            }
            else
            {
                if (m_devManagePage != NULL)
                {
                    m_devManagePage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
                }

                T_VIDEO_ALARM_STATUS *ptVideoAlarmStatus = (T_VIDEO_ALARM_STATUS *)pcMsgData;
                if (8 == ptVideoAlarmStatus->i8DevPos)
                {
                    iDevPos = 1;
                }
                else if (9 == ptVideoAlarmStatus->i8DevPos)
                {
                    iDevPos = 2;
                }

                if (1 == ptVideoAlarmStatus->i8VideoShade)
                {
                    iAlarmType = ALARM_VIDEO_SHADE;  //iAlarmType=1,表示遮挡报警
                    iShadeAlarmEnableFlag = STATE_GetShadeAlarmEnableFlag();
                    if (iShadeAlarmEnableFlag != 1)   //根据配置文件中的遮挡报警使能决定是否处理遮挡报警
                    {
                        break;
                    }
                }
                else
                {
                    if (1 == ptVideoAlarmStatus->i8VideoLost)
                    {
                        iAlarmType = ALARM_VIDEO_LOST;   //iAlarmType=2,表示丢失报警
                    }
                    else
                    {
                        iAlarmType = ALARM_VIDEO_CLEAR;  //iAlarmType=0,表示报警恢复
                    }
                }

                memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
                STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
                for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
                {
                    if (pHandle == STATE_GetNvrServerPmsgHandle(i))
                    {
                        if (tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO <= 0 || (iDevPos != 1 && iDevPos != 2))
                        {
                            break;
                        }
                        emit reflushAlarmPageSignal(iAlarmType, tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, iDevPos);
                        break;
                    }
                }
                break;
            }
        }
        #if 1
        case SERV_CLI_MSG_TYPE_HDISK_ALARM_REPORT:
        {
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "pvmsMenu Widget get pmsg message data:\n%s\n",pcMsgData);

            if (pcMsgData == NULL || iMsgDataLen != 2)
            {
                break;
            }
            else
            {
                if (m_devManagePage != NULL)
                {
                    m_devManagePage->pmsgCtrl(pHandle, ucMsgCmd, pcMsgData, iMsgDataLen);
                }

                T_HDISK_ALARM_STATUS *ptHdiskAlarmStatus = (T_HDISK_ALARM_STATUS *)pcMsgData;

                if (1 == ptHdiskAlarmStatus->i8HdiskLost)
                {
                    iAlarmType = ALARM_HDISK_LOST;
                }
                else if (1 == ptHdiskAlarmStatus->i8HdiskBad)
                {
                    iAlarmType = ALARM_HDISK_ERR;
                }
                else
                {
                    iAlarmType = ALARM_HDISK_CLEAR;
                }

                memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
                STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
                for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
                {
                    if (pHandle == STATE_GetNvrServerPmsgHandle(i))
                    {
                        iCarriageNO = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
                        break;
                    }
                }
                if (iCarriageNO <= 0)
                {
                    break;
                }

                emit reflushAlarmPageSignal(iAlarmType, iCarriageNO, 0);
            }
            break;
        }
        #endif
        default:
            break;
    }
}

void pvmsMenuWidget::alarmPageShowSlot()
{
    if (m_alarmPage== NULL)
    {
        m_alarmPage = new alarmWidget(this);      //新建报警信息显示窗体
        m_alarmPage->setGeometry(195, 189, m_alarmPage->width(), m_alarmPage->height());
        m_alarmPage->show();
//        connect(m_alarmPage, SIGNAL(SendEscape()), this, SLOT(closeAlarmWidget()));

        connect(m_alarmPage, SIGNAL(SendEscape()), this, SLOT(closeAlarmWidget()));
        connect(this, SIGNAL(reflushAlarmPageSignal(int, int, int)), m_alarmPage, SLOT(reflushAlarmPageSlot(int, int, int)));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), this, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), this, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_pvmsMonitorPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_pvmsMonitorPage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_recordPlayPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_recordPlayPage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_devManagePage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_devManagePage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_devUpdatePage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_devUpdatePage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_inteAnalyPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_inteAnalyPage, SLOT(alarmClearSlot()));

    }
    else
    {
        m_alarmPage->show();
    }
    m_iAlarmPageOpenFlag = 1;
    m_alarmPage->triggerAlarmCleanSignal();
}
void pvmsMenuWidget::showPageSlot()
{
    this->show();
    m_pvmsMonitorPage->pageType = g_ipageValue;

    m_pvmsMonitorPage->startVideoPolling();   //启动视频轮询

    if(g_ipageValue == PAGENONE){
        m_pvmsMonitorPage->show();
        m_recordPlayPage->hide();
        m_inteAnalyPage->hide();
        m_devManagePage->hide();
        m_devUpdatePage->hide();
        m_pvmsMonitorPage->showPlayWindow(1);
        m_pvmsMonitorPage->enableVideoPlay(1);   //运行受电弓监控页面解码的显示

    }
    else if (g_ipageValue == PAGEMONITOR) {
        m_pvmsMonitorPage->show();
        m_recordPlayPage->hide();
        m_devManagePage->hide();
        m_inteAnalyPage->hide();
        m_devUpdatePage->hide();
        m_pvmsMonitorPage->showPlayWindow(1);
        m_pvmsMonitorPage->enableVideoPlay(1);   //运行受电弓监控页面解码的显示

    }
    else if (g_ipageValue == PAGERCORDE) {
        m_pvmsMonitorPage->hide();
        m_pvmsMonitorPage->showPlayWindow(0);
        m_pvmsMonitorPage->enableVideoPlay(0);

        m_inteAnalyPage->hide();
        m_recordPlayPage->show();
        m_devManagePage->hide();
        m_devUpdatePage->hide();


    }
    else if (g_ipageValue == PAGEMANAGE) {
        m_pvmsMonitorPage->hide();
        m_pvmsMonitorPage->showPlayWindow(0);
        m_pvmsMonitorPage->enableVideoPlay(0);


        m_inteAnalyPage->hide();
        m_recordPlayPage->hide();
        m_devManagePage->show();
        m_devUpdatePage->hide();
    }
    else if (g_ipageValue == PAGEUPDATE) {
        m_pvmsMonitorPage->hide();
        m_pvmsMonitorPage->showPlayWindow(0);
        m_pvmsMonitorPage->enableVideoPlay(0);


        m_inteAnalyPage->hide();
        m_recordPlayPage->hide();
        m_devManagePage->hide();
        m_devUpdatePage->show();
    }
    else if (g_ipageValue == PAGEALAGE) {
        m_pvmsMonitorPage->hide();
        m_recordPlayPage->hide();
        m_inteAnalyPage->show();
        m_pvmsMonitorPage->m_playWin->hide();
        m_devManagePage->hide();
        m_devUpdatePage->hide();
    }

    if(g_ipageValue > 1)
    {
        m_pvmsMonitorPage->m_channelStateLabel->hide();
        m_pvmsMonitorPage->m_channelNoLabel->hide();
    }

    if (NULL == m_alarmPage)
    {
        m_alarmPage = new alarmWidget(this);
        m_alarmPage->setGeometry(195, 189, m_alarmPage->width(), m_alarmPage->height());
        m_alarmPage->hide();

        connect(m_alarmPage, SIGNAL(SendEscape()), this, SLOT(closeAlarmWidget()));
        connect(this, SIGNAL(reflushAlarmPageSignal(int, int, int)), m_alarmPage, SLOT(reflushAlarmPageSlot(int, int, int)));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), this, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), this, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_pvmsMonitorPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_pvmsMonitorPage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_recordPlayPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_recordPlayPage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_devManagePage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_devManagePage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_devUpdatePage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_devUpdatePage, SLOT(alarmClearSlot()));
        connect(m_alarmPage, SIGNAL(alarmHappenSignal()), m_inteAnalyPage, SLOT(alarmHappenSlot()));
        connect(m_alarmPage, SIGNAL(alarmClearSignal()), m_inteAnalyPage, SLOT(alarmClearSlot()));
    }

}
void pvmsMenuWidget::alarmHappenSlot()     //报警触发，触发报警信号通知上一层的MyApplication界面
{
    emit alarmHappenSignal();
}

void pvmsMenuWidget::alarmClearSlot()  //报警清除，触发报警清除信号通知上一层的MyApplication界面
{
    emit alarmClearSignal();
}


void pvmsMenuWidget::closeAlarmWidget()
{
    m_iAlarmPageOpenFlag = 0;
    m_alarmPage->hide();
}
void pvmsMenuWidget::registOutButtonClick(int page)
{
    g_ipageValue = page;
    m_pvmsMonitorPage->closePlayWin();   //关闭受电弓监控界面的播放窗口
    m_recordPlayPage->closePlayWin();   //关闭录像回放界面的播放窗口
    m_pvmsMonitorPage->m_iPresetPasswdOkFlag = 0;


    this->hide();
    emit registOutSignal();    //触发注销信号，带上当前设备类型

}

void pvmsMenuWidget::serverOffLineSlot(int iDex)   //服务器离线后将服务器检测硬盘错误标志及不检测计数清0，使得再次连上服务器后头3分钟依然不处理硬盘报警
{
//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMenuWidget server %d OffLine\n", iDex);

    T_TRAIN_CONFIG tTrainConfigInfo;

    m_iCheckDiskErrFlag[iDex] = 0;
    m_iNoCheckDiskErrNum[iDex] = 0;

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    emit reflushAlarmPageSignal(ALARM_SERVER_OFFLINE, tTrainConfigInfo.tNvrServerInfo[iDex].iCarriageNO, 0);   //触发服务器离线报警信息，清除所有与服务器相关的报警及其附属相机相关的报警
}

void pvmsMenuWidget::hideAlarmWidgetSlot()
{
    if (m_alarmPage != NULL)
    {
        m_alarmPage->hide();
    }
}

void pvmsMenuWidget::showAlarmWidgetSlot()
{
    if ((m_alarmPage != NULL) && (1 == m_iAlarmPageOpenFlag))
    {
        m_alarmPage->show();
    }
}

void pvmsMenuWidget::blackScreenCtrlSlot()   //黑屏触发，触发黑屏信号通知m_pvmsMonitorPage子界面
{
    emit blackScreenSignal();
}

void pvmsMenuWidget::blackScreenExitCtrlSlot()  //黑屏退出，触发黑屏退出信号通知m_pvmsMonitorPage子界面
{
    this->update();
    emit blackScreenExitSignal();
}


void pvmsMenuWidget::menuButtonClick()
{
    char acUserType[16] = {0};

    STATE_GetCurrentUserType(acUserType, sizeof(acUserType));

    QObject* Sender = sender();     //Sender->objectName(),可区分不同的信号来源，也就是不同的按钮按键


    if(Sender==0)
    {
        return ;
    }
    if (Sender->objectName() == "pvmsMonitorMenuPushButton")     //受电弓监控按钮被按，则切换到受电弓监控页面
    {
        m_recordPlayPage->closePlayWin();   //关闭录像回放界面的播放窗口
        m_recordPlayPage->hide();
        m_devManagePage->hide();
        m_devUpdatePage->hide();
        m_inteAnalyPage->hide();
        m_pvmsMonitorPage->show();

        m_pvmsMonitorPage->showPlayWindow(1);

        m_pvmsMonitorPage->enableVideoPlay(1);   //运行受电弓监控页面解码的显示

        m_pvmsMonitorPage->m_channelStateLabel->show();
        m_pvmsMonitorPage->m_channelNoLabel->show();

        ui->pvmsMonitorMenuPushButton->setChecked(true);
        ui->recordPlayMenuPushButton->setChecked(false);
        ui->inteAnalyMenuPushButton->setChecked(false);
        ui->devManageMenuPushButton->setChecked(false);
        ui->devUpdateMenuPushButton->setChecked(false);


    }
    else if (Sender->objectName() == "recordPlayMenuPushButton")     //录像回放按钮被按，则切换到录像回放页面
    {

        m_pvmsMonitorPage->m_channelStateLabel->hide();
        m_pvmsMonitorPage->m_channelNoLabel->hide();

        m_pvmsMonitorPage->showPlayWindow(0);
        m_pvmsMonitorPage->enableVideoPlay(0);   //禁止受电弓监控页面解码显示
        m_inteAnalyPage->hide();
        m_pvmsMonitorPage->hide();
        m_devManagePage->hide();
        m_devUpdatePage->hide();

        m_recordPlayPage->pageShowCtrl();


        ui->pvmsMonitorMenuPushButton->setChecked(false);
        ui->recordPlayMenuPushButton->setChecked(true);
        ui->devManageMenuPushButton->setChecked(false);
        ui->devUpdateMenuPushButton->setChecked(false);
        ui->inteAnalyMenuPushButton->setChecked(false);

        m_recordPlayPage->show();


    }
    else if (Sender->objectName() == "devManageMenuPushButton")      //设备管理按钮被按，则切换到设备管理页面
    {
        if (!strcmp(acUserType, "operator"))   //操作员不能查看此界面
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "pvmsMenu Widget this user type has not this right!\n");
//            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("该用户没有查看权限!"));
//            box.setWindowFlags(Qt::FramelessWindowHint);
//            box.setStandardButtons (QMessageBox::Ok);
//            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));
//            box.exec();
//            return;
            box->setInfo(QString("提示："),QString("该用户没有查看权限!"),true);
            box->show();
        }
        m_pvmsMonitorPage->enableVideoPlay(0);   //禁止受电弓监控页面解码显示
        m_pvmsMonitorPage->m_channelStateLabel->hide();
        m_pvmsMonitorPage->m_channelNoLabel->hide();
        m_pvmsMonitorPage->hide();
        m_recordPlayPage->hide();
        m_devUpdatePage->hide();
        m_devManagePage->show();


        m_pvmsMonitorPage->showPlayWindow(0);

        m_recordPlayPage->closePlayWin();   //关闭录像回放界面的播放窗口


        ui->pvmsMonitorMenuPushButton->setChecked(false);
        ui->recordPlayMenuPushButton->setChecked(false);
        ui->devManageMenuPushButton->setChecked(true);
        ui->devUpdateMenuPushButton->setChecked(false);

    }
    else if (Sender->objectName() == "inteAnalyMenuPushButton")      //智能分析按钮被按，则切换到智能分析页面
    {
        m_pvmsMonitorPage->enableVideoPlay(0);   //禁止受电弓监控页面解码显示

        m_pvmsMonitorPage->m_channelStateLabel->hide();
        m_pvmsMonitorPage->m_channelNoLabel->hide();
        m_pvmsMonitorPage->hide();
        m_recordPlayPage->hide();
        m_devManagePage->hide();
        m_devUpdatePage->hide();
        m_inteAnalyPage->show();

        m_pvmsMonitorPage->showPlayWindow(0);

        m_recordPlayPage->closePlayWin();   //关闭录像回放界面的播放窗口

        m_inteAnalyPage->pageShowCtrl();


        ui->pvmsMonitorMenuPushButton->setChecked(false);
        ui->recordPlayMenuPushButton->setChecked(false);
        ui->inteAnalyMenuPushButton->setChecked(true);
        ui->devManageMenuPushButton->setChecked(false);
        ui->devUpdateMenuPushButton->setChecked(false);

    }
    else if (Sender->objectName() == "devUpdateMenuPushButton")     //设备更新按钮被按，则切换到设备更新页面
    {
        if (!strcmp(acUserType, "operator"))   //操作员不能查看此界面
        {
//            DebugPrint(DEBUG_UI_MESSAGE_PRINT, "pvmsMenu Widget this user type has not this right!\n");
//            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("该用户没有查看权限!"));
//            box.setWindowFlags(Qt::FramelessWindowHint);
//            box.setStandardButtons (QMessageBox::Ok);
//            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));
//            box.exec();
//            return;
            box->setInfo(QString("提示："),QString("该用户没有查看权限!"),true);
            box->show();
        }
        m_pvmsMonitorPage->enableVideoPlay(0);   //禁止受电弓监控页面解码显示
        m_pvmsMonitorPage->m_channelStateLabel->hide();
        m_pvmsMonitorPage->m_channelNoLabel->hide();
        m_pvmsMonitorPage->hide();
        m_recordPlayPage->hide();
        m_devManagePage->hide();
        m_inteAnalyPage->hide();
        m_devUpdatePage->show();


        m_pvmsMonitorPage->showPlayWindow(0);

        m_recordPlayPage->closePlayWin();   //关闭录像回放界面的播放窗口

        ui->pvmsMonitorMenuPushButton->setChecked(false);
        ui->inteAnalyMenuPushButton->setChecked(false);
        ui->recordPlayMenuPushButton->setChecked(false);
        ui->devManageMenuPushButton->setChecked(false);
        ui->devUpdateMenuPushButton->setChecked(true);

    }

    QIcon icon;
    if (Sender->objectName() == "pvmsMonitorMenuPushButton")     //受电弓监控按钮被按，则切换到受电弓监控页面
        icon.addFile(QString::fromUtf8(":/monres/PantoMonitor1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    else
        icon.addFile(QString::fromUtf8(":/monres/PantoMonitor.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->pvmsMonitorMenuPushButton->setIcon(icon);
    ui->pvmsMonitorMenuPushButton->setIconSize(QSize(203,102));


    if (Sender->objectName() == "recordPlayMenuPushButton")     //录像回放按钮被按，则切换到录像回放页面
        icon.addFile(QString::fromUtf8(":/monres/PantoPlay1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    else
        icon.addFile(QString::fromUtf8(":/monres/PantoPlay.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->recordPlayMenuPushButton->setIcon(icon);
    ui->recordPlayMenuPushButton->setIconSize(QSize(203,102));

    if (Sender->objectName() == "devManageMenuPushButton")      //设备管理按钮被按，则切换到设备管理页面
        icon.addFile(QString::fromUtf8(":/monres/Pantoequip1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    else
        icon.addFile(QString::fromUtf8(":/monres/Pantoequip.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->devManageMenuPushButton->setIcon(icon);
    ui->devManageMenuPushButton->setIconSize(QSize(203,102));


    if (Sender->objectName() == "devUpdateMenuPushButton")     //设备更新按钮被按，则切换到设备更新页面
        icon.addFile(QString::fromUtf8(":/monres/PantoMantain1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    else
        icon.addFile(QString::fromUtf8(":/monres/PantoMantain.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->devUpdateMenuPushButton->setIcon(icon);
    ui->devUpdateMenuPushButton->setIconSize(QSize(203,102));



    if (Sender->objectName() == "inteAnalyMenuPushButton")     //设备更新按钮被按，则切换到设备更新页面
        icon.addFile(QString::fromUtf8(":/monres/PantoIntell1.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    else
        icon.addFile(QString::fromUtf8(":/monres/PantoIntell.bmp"),QSize(),QIcon::Normal,QIcon::Off);
    ui->inteAnalyMenuPushButton->setIcon(icon);
    ui->inteAnalyMenuPushButton->setIconSize(QSize(203,102));

}

