#include "devmanagewidget.h"
#include "ui_devmanagewidget.h"
#include <QMessageBox>
#include <QDateTime>
#include "log.h"
#include <stdio.h>
#include <netinet/in.h>
#include <QDebug>
#include <QTabWidget>

static int g_iDNum = 0;
#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面


devManageWidget::devManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::devManageWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();



    ui->devStorageTableWidget->setFocusPolicy(Qt::NoFocus);
    ui->devStorageTableWidget->setColumnCount(8);
    ui->devStorageTableWidget->setRowCount(7);
    ui->devStorageTableWidget->setShowGrid(true);
//    ui->devStorageTableWidget->setStyleSheet("QTableWidget{ gridline-color : rgb(255, 255, 255)}");
    QStringList header;
    header<<tr("序号")<<tr("设备名称")<<tr("设备位置")<<tr("设备IP")<<tr("硬盘容量")<<tr("硬盘使用量")<<tr("硬盘状态")<<tr("");
    ui->devStorageTableWidget->horizontalHeader()->setStyleSheet("background-color:white");
    ui->devStorageTableWidget->setHorizontalHeaderLabels(header);
    ui->devStorageTableWidget->horizontalHeader()->setVisible(true);//temp
    ui->devStorageTableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    ui->devStorageTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->devStorageTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->devStorageTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->devStorageTableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
//    ui->devStorageTableWidget->setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(0,50); //设置表头第一列的宽度为46
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(1,150);
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(2,150);
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(3,150);
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(4,100);
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(5,100);
    ui->devStorageTableWidget->horizontalHeader()->resizeSection(6,100);


    ui->devStatusTableWidget->setFocusPolicy(Qt::NoFocus);
    ui->devStatusTableWidget->setColumnCount(8);
    ui->devStatusTableWidget->setRowCount(7);

    ui->devStatusTableWidget->setShowGrid(true);

    QStringList header_2;
    header_2<<tr("序号")<<tr("设备名称")<<tr("设备位置")<<tr("设备IP")<<tr("设备版本")<<tr("设备状态")<<tr("设备供应商")<<tr("");
    ui->devStatusTableWidget->setHorizontalHeaderLabels(header_2);
    ui->devStatusTableWidget->horizontalHeader()->setStyleSheet("background-color:white");


    ui->devStatusTableWidget->horizontalHeader()->setVisible(true);  //temp
    ui->devStatusTableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    ui->devStatusTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->devStatusTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->devStatusTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->devStatusTableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
//    ui->devStatusTableWidget->setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(0,50); //设置表头第一列的宽度为46px
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(1,150);
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(2,150);
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(3,150);
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(4,100);
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(5,100);
    ui->devStatusTableWidget->horizontalHeader()->resizeSection(6,100);
    //ui->devStatusTableWidget->horizontalHeader()->resizeSection(7,61);

    ui->alarmPushButton->setFocusPolicy(Qt::NoFocus);
    ui->TrainNumberSetPushButton->setFocusPolicy(Qt::NoFocus);

    int i = 0, j = 0;

    for (i = 0; i < MAX_SERVER_NUM; i++)
    {
        m_aiServerIdex[i] = 0;
        m_NvrServerPhandle[i] = 0;
        m_iNoCheckDiskErrNum[i] = 0;
        m_iCheckDiskErrFlag[i] = 0;
        for (j = 0; j < MAX_CAMERA_OFSERVER; j++)
        {
            m_aiNvrOnlineFlag[i] = 0;
            m_aiCameraIdex[i][j] = 0;
            m_aiCameraOnlineFlag[i][j] = 0;
        }
    }
    m_TrainNumEditSave = "";

    connect(ui->alarmPushButton, SIGNAL(clicked(bool)), this, SLOT(alarmPushButoonClickSlot()));   //报警按钮按键信号响应打开报警信息界面
    connect(ui->TrainNumberSetPushButton, SIGNAL(clicked(bool)), this, SLOT(trainNumberButtonClickSlot()));

    connect(ui->TrainNumberLineEdit, SIGNAL(textChanged(QString)), this, SLOT(trainNumberChange(QString)));

    connect(ui->canselPushButton, SIGNAL(clicked()), this, SLOT(registOutButtonClick()));


    getTrainConfig();


    m_alarmHappenTimer = NULL;

}

devManageWidget::~devManageWidget()
{
    delete ui;
}
int devManageWidget::rs485Ctrl(char *pcData, int iDataLen)
{

    unsigned char ucMsgHead = 0;
    unsigned char ucMsgCmd = 0;
    int iMsgDataLen = 0;

    if (NULL == pcData|| 0 == iDataLen)
    {
        return -1;
    }

    ucMsgHead = (unsigned char)pcData[0];
    ucMsgCmd = (unsigned char)pcData[1];
    iMsgDataLen = pcData[2] << 8 | pcData[3];

    if (0XFF != ucMsgHead || 0x04 != ucMsgCmd || (iMsgDataLen+5) != iDataLen)    //数据准确性检测
    {
        return -1;
    }

    pisMsgCtrl(pcData+4);

    return 0;

}

void devManageWidget::pisMsgCtrl(char *pcMsgData)
{
    int i = 0, j = 0, iRet = 0, iYear = 0;
    char acTmp[32] = {0}, acTmp1[32] = {0}, acTmp2[32] = {0}, acStr[256] = {0};
    struct tm tmVal;
    time_t localTime = 0, pisTime = 0;
    T_LOG_INFO tLogInfo;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_TIME_INFO tTimeInfo;
    T_OSD_INFO tOsdInfo;
    T_PISMSG_INFO *ptPisMsgInfo = (T_PISMSG_INFO *)pcMsgData;

    memset(&tOsdInfo, 0, sizeof(tOsdInfo));
    tOsdInfo.i16Year = ptPisMsgInfo->i16Year;
    tOsdInfo.i8Mon = ptPisMsgInfo->i8Mon;
    tOsdInfo.i8day = ptPisMsgInfo->i8day;
    tOsdInfo.i8Hour = ptPisMsgInfo->i8Hour;
    tOsdInfo.i8Min = ptPisMsgInfo->i8Min;
    tOsdInfo.i8Sec = ptPisMsgInfo->i8Sec;
    tOsdInfo.i16Speed = ptPisMsgInfo->i16Speed;
    tOsdInfo.i16Mileage = ptPisMsgInfo->i16Mileage;
    strncpy(tOsdInfo.acTrainNum, ptPisMsgInfo->acTrainNum, sizeof(tOsdInfo.acTrainNum));
    snprintf(acTmp, sizeof(acTmp), "%03d", (int)ptPisMsgInfo->acInterval[2]);
    STATE_GetStationName(acTmp1, sizeof(acTmp1), acTmp);
    memset(acTmp, 0, sizeof(acTmp));
    snprintf(acTmp, sizeof(acTmp), "%03d", (int)ptPisMsgInfo->acInterval[5]);
    STATE_GetStationName(acTmp2, sizeof(acTmp2), acTmp);
    snprintf(tOsdInfo.acInterval, sizeof(tOsdInfo.acInterval), "%s-%s", acTmp1, acTmp2);

    memset(&tTimeInfo, 0, sizeof(tTimeInfo));
    tTimeInfo.year = ptPisMsgInfo->i16Year;
    tTimeInfo.mon = ptPisMsgInfo->i8Mon;
    tTimeInfo.day = ptPisMsgInfo->i8day;
    tTimeInfo.hour = ptPisMsgInfo->i8Hour;
    tTimeInfo.min = ptPisMsgInfo->i8Min;
    tTimeInfo.sec = ptPisMsgInfo->i8Sec;
    iYear = htons(ptPisMsgInfo->i16Year);

    /*pis时间与本地时间相差3s以上，则对本地进行rtc校时*/
    localTime = time(NULL);
    tmVal.tm_year = iYear - 1900;
    tmVal.tm_mon = tTimeInfo.mon - 1;
    tmVal.tm_mday = tTimeInfo.day;
    tmVal.tm_hour = tTimeInfo.hour;
    tmVal.tm_min = tTimeInfo.min;
    tmVal.tm_sec = tTimeInfo.sec;
    pisTime = mktime(&tmVal);
    if (abs(localTime - pisTime) > 3)
    {
        snprintf(acStr, sizeof(acStr), "date %02d%02d%02d%02d%4d.%02d", ptPisMsgInfo->i8Mon, ptPisMsgInfo->i8day, ptPisMsgInfo->i8Hour, ptPisMsgInfo->i8Sec,iYear, ptPisMsgInfo->i8Min);
        system(acStr);
        system("hwclock -w");

        /*系统校时记录日志*/
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "set local time %4d-%02d-%02d %02d:%02d:%02d", iYear, ptPisMsgInfo->i8Mon, ptPisMsgInfo->i8day, ptPisMsgInfo->i8Hour, ptPisMsgInfo->i8Min, ptPisMsgInfo->i8Sec);
        LOG_WriteLog(&tLogInfo);

        emit systimeSetSignal();
    }

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        iRet = PMSG_SendPmsgData(m_NvrServerPhandle[i], CLI_SERV_MSG_TYPE_CHECK_TIME, (char *)&tTimeInfo, sizeof(T_TIME_INFO));    //发送校时命令
        if (iRet < 0)
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d\n",iRet);
        }
        else
        {
            memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
            tLogInfo.iLogType = 0;
            snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "notify server %d Time Check OK, %4d-%02d-%02d %02d:%02d:%02d!", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,
                iYear, ptPisMsgInfo->i8Mon, ptPisMsgInfo->i8day, ptPisMsgInfo->i8Hour, ptPisMsgInfo->i8Min, ptPisMsgInfo->i8Sec);
            LOG_WriteLog(&tLogInfo);
        }

        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            tOsdInfo.i8CarriageNo = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            tOsdInfo.i8PvmsCarriageNO = 8+j;
            iRet = PMSG_SendPmsgData(m_NvrServerPhandle[i], CLI_SERV_MSG_TYPE_SET_OSD, (char *)&tOsdInfo, sizeof(T_OSD_INFO));
            if (iRet < 0)
            {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_SET_OSD error!iRet=%d,server=%d\n", __FUNCTION__, iRet,i+1);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), " camera %d.%d set osd", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+j);
                LOG_WriteLog(&tLogInfo);
            }
        }
    }

    ui->TrainNumberLineEdit->setText(QString(QLatin1String(tOsdInfo.acTrainNum)));
}

void devManageWidget::getIpcStatusCtrl(PMSG_HANDLE pHandle, char *pcMsgData)
{
    int i = 0;
    char actmp[16] = {0}, acVersion[32] = {0};
    QString devStatus = "";
    T_LOG_INFO tLogInfo;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_IPC_STATUS *ptIpcstaus = (T_IPC_STATUS *)pcMsgData;

    if ((ptIpcstaus->i8DevPos != 8) && (ptIpcstaus->i8DevPos != 9))   //过滤掉非受电弓摄像机的状态信息
    {
        return;
    }

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    snprintf(actmp, sizeof(actmp), "%d", htons(ptIpcstaus->i16Version));
//    snprintf(acVersion, sizeof(acVersion), "V%c.%c.%c",actmp[0],actmp[1],actmp[2]);
    snprintf(acVersion, sizeof(acVersion), "V0.0.%c",actmp[0]);
    devStatus = (ptIpcstaus->i8OnLine == 1)?tr("在线"):tr("离线");

    for (i =0; i < MAX_SERVER_NUM; i++)
    {
        if (pHandle == m_NvrServerPhandle[i])
        {
            if(8 == ptIpcstaus->i8DevPos)
            {
                ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 5, new QTableWidgetItem(devStatus));
                ui->devStatusTableWidget->item(m_aiCameraIdex[i][0]-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                if (1 == ptIpcstaus->i8OnLine)
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d camera %d status is online\n", __FUNCTION__, i+1, 1);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 4, new QTableWidgetItem(QString(QLatin1String(acVersion))));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][0]-1, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 6, new QTableWidgetItem(QString(QLatin1String(ptIpcstaus->acFactory))));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][0]-1, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    if (0 == m_aiCameraOnlineFlag[i][0])    //相机从离线到在线，记录日志
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.200 online", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
                        LOG_WriteLog(&tLogInfo);
                    }
                }
                else  //相机为离线状态时不显示厂商及版本号和报警信息
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d camera %d status is offline\n", __FUNCTION__, i+1, 1);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 4, new QTableWidgetItem(""));
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 6, new QTableWidgetItem(""));
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 7, new QTableWidgetItem(""));

                    if (1 == m_aiCameraOnlineFlag[i][0])    //相机从在线到离线，记录日志
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.200 offline", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
                        LOG_WriteLog(&tLogInfo);
                    }
                }

                m_aiCameraOnlineFlag[i][0] = ptIpcstaus->i8OnLine;
            }
            else if ((9 == ptIpcstaus->i8DevPos) && (m_aiCameraIdex[i][1] > 0))
            {
                ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 5, new QTableWidgetItem(devStatus));
                ui->devStatusTableWidget->item(m_aiCameraIdex[i][1]-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                if (1 == ptIpcstaus->i8OnLine)
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d camera %d status is online\n", __FUNCTION__, i+1, 2);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 4, new QTableWidgetItem(QString(QLatin1String(acVersion))));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][1]-1, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 6, new QTableWidgetItem(QString(QLatin1String(ptIpcstaus->acFactory))));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][1]-1, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                    if (0 == m_aiCameraOnlineFlag[i][1])    //相机从离线到在线，记录日志
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.201 online", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
                        LOG_WriteLog(&tLogInfo);
                    }
                }
                else  //相机为离线状态时不显示厂商及版本号和报警信息
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d camera %d status is offline\n", __FUNCTION__, i+1, 2);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 4, new QTableWidgetItem(""));
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 6, new QTableWidgetItem(""));
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 7, new QTableWidgetItem(""));

                    if (1 == m_aiCameraOnlineFlag[i][1])    //相机从在线到离线，记录日志
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.201 offline", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
                        LOG_WriteLog(&tLogInfo);
                    }
                }
                m_aiCameraOnlineFlag[i][1] = ptIpcstaus->i8OnLine;
            }
            break;
        }
    }
}

void devManageWidget::getNvrStatusCtrl(PMSG_HANDLE pHandle, char *pcMsgData)
{
    int i = 0, iDevType = 0;
    char actmp[16] = {0}, acVersion[32] = {0};
    char acDiskFull[16] = {0}, acDiskUsed[16] = {0};
    QString acDeviceTp =  "";
    T_NVR_STATUS *ptNvrstaus = (T_NVR_STATUS *)pcMsgData;

    iDevType = (int)ptNvrstaus->i8DevType;
    acDeviceTp = (iDevType==1)?tr("受电弓监控服务器"):tr("智能分析主机");
    snprintf(actmp, sizeof(actmp), "%d", htons(ptNvrstaus->i16Version));
    snprintf(acVersion, sizeof(acVersion), "V%c.%c.%c",actmp[0],actmp[1],actmp[2]);
    snprintf(acDiskFull, sizeof(acDiskFull), "%dG", htons(ptNvrstaus->i16HdiskTotalSize));
    snprintf(acDiskUsed, sizeof(acDiskUsed), "%dG", htons(ptNvrstaus->i16HdiskUsedSize));

    for (i =0; i < MAX_SERVER_NUM; i++)
    {
        if ((pHandle == m_NvrServerPhandle[i]) && (m_aiServerIdex[i] >= 1))
        {
            ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 4, new QTableWidgetItem(QString(QLatin1String(acVersion))));
            ui->devStatusTableWidget->item(m_aiServerIdex[i]-1, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

            ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 6, new QTableWidgetItem(QString(QLatin1String(ptNvrstaus->acFactory))));
            ui->devStatusTableWidget->item(m_aiServerIdex[i]-1, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

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

            if (htons(ptNvrstaus->i16HdiskTotalSize) <= 0)
            {
                if (1 == m_iCheckDiskErrFlag[i])
                {
                    ui->devStorageTableWidget->setItem(i, 4, new QTableWidgetItem("0G"));
                    ui->devStorageTableWidget->item(i, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->devStorageTableWidget->setItem(i, 5, new QTableWidgetItem("0G"));
                    ui->devStorageTableWidget->item(i, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->devStorageTableWidget->setItem(i, 6, new QTableWidgetItem(QString(tr("硬盘异常"))));
                    ui->devStorageTableWidget->item(i, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
            }
            else
            {
                ui->devStorageTableWidget->setItem(i, 4, new QTableWidgetItem(QString(QLatin1String(acDiskFull))));
                ui->devStorageTableWidget->item(i, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                ui->devStorageTableWidget->setItem(i, 5, new QTableWidgetItem(QString(QLatin1String(acDiskUsed))));
                ui->devStorageTableWidget->item(i, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                ui->devStorageTableWidget->setItem(i, 6, new QTableWidgetItem(QString(tr("正常"))));
                ui->devStorageTableWidget->item(i, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
            break;
        }
    }
}
void devManageWidget::videoAlarmCtrl(PMSG_HANDLE pHandle, char *pcMsgData)
{
    int i = 0;
    QString devStatus = "";
//    T_LOG_INFO tLogInfo;

    T_VIDEO_ALARM_STATUS *ptVideoAlarmStatus = (T_VIDEO_ALARM_STATUS *)pcMsgData;
    if (1 == ptVideoAlarmStatus->i8VideoShade)
    {
//        DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "devManageWidget [%s] recv video shade alarm pmsg\n", __FUNCTION__);
        devStatus = tr("遮挡");
    }
    else
    {
        if (1 == ptVideoAlarmStatus->i8VideoLost)
        {
//            DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "devManageWidget [%s] recv video lost alarm pmsg\n", __FUNCTION__);
            devStatus = tr("丢失");
        }
        else
        {
            devStatus = "";
        }
    }

    for (i = 0; i < MAX_SERVER_NUM; i++)
    {
        if (pHandle == m_NvrServerPhandle[i])
        {
            if (8 == ptVideoAlarmStatus->i8DevPos)   //1号相机
            {
                if (1 == m_aiCameraOnlineFlag[i][0])
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "devManageWidget [%s] add camera video alarm info to devStatusTableWidget row:%d, column:%d\n", __FUNCTION__, i+1, 1);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 7, new QTableWidgetItem(devStatus));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][0]-1, 7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
                else  //相机为离线状态时不显示报警信息
                {
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][0]-1, 7, new QTableWidgetItem(""));
                }
                break;
            }
            else if ((9 == ptVideoAlarmStatus->i8DevPos) && (m_aiCameraIdex[i][1] > 0))   //2号相机
            {
                if (1 == m_aiCameraOnlineFlag[i][1])
                {
//                    DebugPrint(DEBUG_UI_NOMAL_PRINT, "devManageWidget [%s] add camera video alarm info to devStatusTableWidget row:%d, column:%d\n", __FUNCTION__, i+1, 1);
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 7, new QTableWidgetItem(devStatus));
                    ui->devStatusTableWidget->item(m_aiCameraIdex[i][1]-1, 7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
                else  //相机为离线状态时不显示报警信息
                {
                    ui->devStatusTableWidget->setItem(m_aiCameraIdex[i][1]-1, 7, new QTableWidgetItem(""));
                }
                break;
            }
        }
    }
}

void devManageWidget::alarmPushButoonClickSlot()
{
    emit alarmPushButoonClickSignal();
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);

    g_iDNum = 0;
}
void devManageWidget::alarmHappenSlot()
{
    if (NULL == m_alarmHappenTimer)
    {
        m_alarmHappenTimer = new QTimer(this);
        connect(m_alarmHappenTimer,SIGNAL(timeout()), this,SLOT(alarmHappenCtrlSlot()));
        m_alarmHappenTimer->start(500);
    }
}

void devManageWidget::alarmHappenCtrlSlot()
{
    if (this->isHidden() != 1)
    {
        if (0 == g_iDNum%2)
        {
            ui->alarmPushButton->setChecked(true);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alerton.bmp);background-color: rgb(255, 255, 255);}");
        }
        else
        {
            ui->alarmPushButton->setChecked(false);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");

        }
        g_iDNum++;
    }
}

void devManageWidget::alarmClearSlot()
{
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);
    ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");


    g_iDNum = 0;
}
void devManageWidget::trainNumberButtonClickSlot()
{

    trainNumberSetSlot_fuction();

    ui->TrainNumberLineEdit->setEnabled(true);
    ui->TrainNumberLineEdit->setFocus();

    m_TrainNumEditSave = ui->TrainNumberLineEdit->text();


}

void devManageWidget::registOutButtonClick()
{
    int manage_page = 3;
    this->hide();
    emit registOutSignal(manage_page);    //触发注销信号，带上当前设备类型

}

void devManageWidget::trainNumberChange(QString TrainNumberStr)
{
    char acTrainNumber[128] = {0};
    if (TrainNumberStr.length() > 7)
    {
        strncpy(acTrainNumber, TrainNumberStr.toLatin1().data(), 7);
        ui->TrainNumberLineEdit->setText(QString(QLatin1String(acTrainNumber)));
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "devManageWidget input train number len can't over 7!\n");
        QMessageBox box(QMessageBox::Warning,QString::fromUtf8("提示"),QString::fromUtf8("输入的车次字符数不能超过7!"));     //提示框
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
        box.exec();
    }
}
void devManageWidget::getDevStateSignalCtrl()
{
    int iRet = 0, i = 0, j = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] getDevState\n", __FUNCTION__);
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        if (m_aiServerIdex[i] >= 1)
        {
            if (E_SERV_STATUS_CONNECT == PMSG_GetConnectStatus(m_NvrServerPhandle[i]))    //获取到服务器状态为在线
            {
//                DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d status is online\n", __FUNCTION__, i+1);
                ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 5, new QTableWidgetItem(tr("在线")));
                ui->devStatusTableWidget->item(m_aiServerIdex[i]-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                iRet = PMSG_SendPmsgData(m_NvrServerPhandle[i], CLI_SERV_MSG_TYPE_GET_NVR_STATUS, NULL, 0);
                if (iRet < 0)
                {
//                    DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_GET_NVR_STATUS error!iRet=%d,server=%d\n", __FUNCTION__, iRet,i+1);
                }

                iRet = PMSG_SendPmsgData(m_NvrServerPhandle[i], CLI_SERV_MSG_TYPE_GET_IPC_STATUS, NULL, 0);
                if (iRet < 0)
                {
//                    DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_GET_IPC_STATUS error!iRet=%d,server=%d\n", __FUNCTION__, iRet,i+1);
                }

                m_aiNvrOnlineFlag[i] = 1;
            }
            else
            {
//                DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server %d status is offline\n", __FUNCTION__, i+1);
                ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 5, new QTableWidgetItem(tr("离线")));
                ui->devStatusTableWidget->item(m_aiServerIdex[i]-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 4, new QTableWidgetItem(""));
                ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 6, new QTableWidgetItem(""));
//                ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1, 7, new QTableWidgetItem(""));
                for (j = 0; j < ui->devStorageTableWidget->rowCount(); j++)  //设备存储列表里找到同一个服务器的那一行，把后三列显示硬盘总容量、使用量和状态清空
                {
                    if (0 == QString::compare(ui->devStatusTableWidget->item(m_aiServerIdex[i]-1, 3)->text(), ui->devStorageTableWidget->item(j, 3)->text()))
                    {
                        ui->devStorageTableWidget->setItem(j, 4, new QTableWidgetItem(""));
                        ui->devStorageTableWidget->setItem(j, 5, new QTableWidgetItem(""));
                        ui->devStorageTableWidget->setItem(j, 6, new QTableWidgetItem(""));
                        break;
                    }
                }
                for (j = 1; j <= tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
                {
                    ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1+j, 5, new QTableWidgetItem(tr("离线")));
                    ui->devStatusTableWidget->item(m_aiServerIdex[i]-1+j, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1+j, 4, new QTableWidgetItem(""));
                    ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1+j, 6, new QTableWidgetItem(""));
//                    ui->devStatusTableWidget->setItem(m_aiServerIdex[i]-1+j, 7, new QTableWidgetItem(""));
                    if (1 == m_aiCameraOnlineFlag[i][j-1])
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d offline", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+j-1);
                        LOG_WriteLog(&tLogInfo);   //相机离线记录日志
                        m_aiCameraOnlineFlag[i][j-1] = 0;
                    }

                }
                if (1 == m_aiNvrOnlineFlag[i])
                {
                    m_iCheckDiskErrFlag[i] = 0;  //服务器离线后将服务器检测硬盘错误标志及不检测计数清0，使得再次连上服务器后头3分钟依然不处理硬盘报警
                    m_iNoCheckDiskErrNum[i] = 0;
                    m_aiNvrOnlineFlag[i] = 0;
                    emit serverOffLine(i);
                }
            }
        }
    }
}

void devManageWidget::trainNumberSetSlot_fuction()
{

    int i = 0, j = 0, iRet = 0;
    short year = 0;
    char acTrainNumber[128] = {0};
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_OSD_INFO tOsdInfo;
    T_LOG_INFO tLogInfo;
    memset(&tOsdInfo, 0, sizeof(T_OSD_INFO));
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] send CLI_SERV_MSG_TYPE_SET_OSD msg to all server to set train number\n", __FUNCTION__);

    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    snprintf(acTrainNumber, sizeof(acTrainNumber), "%s", ui->TrainNumberLineEdit->text().toLatin1().data());
    STATE_SetTrainNumber(acTrainNumber);

    QDateTime time = QDateTime::currentDateTime();
    year = time.date().year();
    tOsdInfo.i16Year = htons(year);
    tOsdInfo.i8Mon = time.date().month();
    tOsdInfo.i8day = time.date().day();
    tOsdInfo.i8Hour = time.time().hour();
    tOsdInfo.i8Min = time.time().minute();
    tOsdInfo.i8Sec = time.time().second();
    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            tOsdInfo.i8CarriageNo = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            tOsdInfo.i8PvmsCarriageNO = 8+j;
            strncpy((char *)tOsdInfo.acTrainNum, acTrainNumber, strlen(acTrainNumber));
            iRet = PMSG_SendPmsgData(m_NvrServerPhandle[i], CLI_SERV_MSG_TYPE_SET_OSD, (char *)&tOsdInfo, sizeof(T_OSD_INFO));
            if (iRet < 0)
            {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_SET_OSD error!iRet=%d,server=%d\n", __FUNCTION__, iRet,i+1);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), " camera %d.%d set train number to %s", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+j, acTrainNumber);
                LOG_WriteLog(&tLogInfo);
            }
        }
    }
//    emit enterKeyPressSignal();
    ui->TrainNumberLineEdit->setEnabled(false);




}

void devManageWidget::getTrainConfig()   //获取车型配置信息，填充页面
{
    int i = 0, j = 0, row = 0;
    QString item = "";
    QString devStatus = tr("离线");     //设备状态初始默认值为离线
    T_TRAIN_CONFIG tTrainConfigInfo;

    /*设备状态和设备存储列表清空*/
    row = ui->devStorageTableWidget->rowCount();
    for (i = 0; i < row; i++)
    {
        ui->devStorageTableWidget->removeRow(i);
    }
    ui->devStorageTableWidget->setRowCount(0);

    row = ui->devStatusTableWidget->rowCount();
    ui->devStorageTableWidget->setRowCount(0);
    for (i = 0; i < row; i++)
    {
        ui->devStatusTableWidget->removeRow(i);
    }
    ui->devStatusTableWidget->setRowCount(0);

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

//    /*获取编组信息，再填充编组设置单选框*/
//    if (1 == tTrainConfigInfo.iFormationType)
//    {
//        ui->groupSetRadioButton->setChecked(true);
//        ui->groupSetRadioButton_2->setChecked(false);
//    }
//    else if (2 == tTrainConfigInfo.iFormationType)
//    {
//        ui->groupSetRadioButton->setChecked(false);
//        ui->groupSetRadioButton_2->setChecked(true);
//    }

    /*获取各服务器即摄像机信息，填充相应的列表控件*/
    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        m_NvrServerPhandle[i] = STATE_GetNvrServerPmsgHandle(i);
        row = ui->devStatusTableWidget->rowCount();//获取表格中当前总行数
        ui->devStatusTableWidget->insertRow(row);//添加一行
        m_aiServerIdex[i] = row+1;
        item = "";
        item = QString::number(row+1);
        ui->devStatusTableWidget->setItem(row, 0, new QTableWidgetItem(item));  //新建一个文本列并插入到列表中
        ui->devStatusTableWidget->item(row, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);    //设置列文件对齐方式为居中对齐
        ui->devStatusTableWidget->setItem(row, 1, new QTableWidgetItem(tr("受电弓监控服务器")));
        ui->devStatusTableWidget->item(row, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item = "";
        item = QString::number(tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
        item += tr("车视频监控服务器");
        ui->devStatusTableWidget->setItem(row, 2, new QTableWidgetItem(item));
        ui->devStatusTableWidget->item(row, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item = "";
        item = "192.168.";
        item += QString::number(100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
        item += ".81";
        ui->devStatusTableWidget->setItem(row, 3, new QTableWidgetItem(item));
        ui->devStatusTableWidget->item(row, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->devStatusTableWidget->setItem(row, 5, new QTableWidgetItem(devStatus));
        ui->devStatusTableWidget->item(row, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            row = ui->devStatusTableWidget->rowCount();//获取表格中当前总行数
            ui->devStatusTableWidget->insertRow(row);//添加一行
            m_aiCameraIdex[i][j] = row+1;
            item = "";
            item = QString::number(row+1);
            ui->devStatusTableWidget->setItem(row, 0, new QTableWidgetItem(item));
            ui->devStatusTableWidget->item(row, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->devStatusTableWidget->setItem(row, 1, new QTableWidgetItem(tr("受电弓摄像机")));
            ui->devStatusTableWidget->item(row, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            item = "";
            item = QString::number(tTrainConfigInfo.tNvrServerInfo[i].iPvmsCarriageNO);
            item += tr("车");
            item += QString::number(j+1);
            item += "号相机";
            ui->devStatusTableWidget->setItem(row, 2, new QTableWidgetItem(item));
            ui->devStatusTableWidget->item(row, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            item = "";
            item = "192.168.";
            item += QString::number(100+tTrainConfigInfo.tNvrServerInfo[i].iPvmsCarriageNO);
            item += ".";
            item += QString::number(200+j);
            ui->devStatusTableWidget->setItem(row, 3, new QTableWidgetItem(item));
            ui->devStatusTableWidget->item(row, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->devStatusTableWidget->setItem(row, 5, new QTableWidgetItem(devStatus));
            ui->devStatusTableWidget->item(row, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }


        row = ui->devStorageTableWidget->rowCount();//获取表格中当前总行数
        ui->devStorageTableWidget->insertRow(row);//添加一行
        item = "";
        item = QString::number(row+1);
        ui->devStorageTableWidget->setItem(row, 0, new QTableWidgetItem(item));
        ui->devStorageTableWidget->item(row, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->devStorageTableWidget->setItem(row, 1, new QTableWidgetItem(tr("受电弓监控服务器")));
        ui->devStorageTableWidget->item(row, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item = "";
        item = QString::number(tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
        item += tr("车视频监控服务器");
        ui->devStorageTableWidget->setItem(row, 2, new QTableWidgetItem(item));
        ui->devStorageTableWidget->item(row, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item = "";
        item = "192.168.";
        item += QString::number(100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
        item += ".81";
        ui->devStorageTableWidget->setItem(row, 3, new QTableWidgetItem(item));
        ui->devStorageTableWidget->item(row, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}


int devManageWidget::pmsgCtrl(PMSG_HANDLE pHandle, unsigned char ucMsgCmd, char *pcMsgData, int iMsgDataLen)    //与服务器通信消息的处理
{
    switch(ucMsgCmd)
    {
        case SERV_CLI_MSG_TYPE_PISMSG_REPORT:
        {
            if (pcMsgData == NULL || iMsgDataLen != 52)
            {
                break;
            }
            else
            {
                pisMsgCtrl(pcMsgData);
                break;
            }
        }
        case SERV_CLI_MSG_TYPE_VIDEO_ALARM_REPORT:
        {
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "devManage Widget get pmsg response cmd 0x%x data:0x%x 0x%x 0x%x 0x%x\n", ucMsgCmd, pcMsgData[0], pcMsgData[1], pcMsgData[2],pcMsgData[3]);

            if (pcMsgData == NULL || iMsgDataLen != 4)
            {
                break;
            }
            else
            {
                videoAlarmCtrl(pHandle, pcMsgData);
                break;
            }
        }
        case SERV_CLI_MSG_TYPE_GET_NVR_STATUS_RESP:
        {
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "devManage Widget get pmsg response cmd 0x%x data:\n", ucMsgCmd);
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", pcMsgData[0],pcMsgData[1],pcMsgData[2],pcMsgData[3],
//                    pcMsgData[4],pcMsgData[5],pcMsgData[6],pcMsgData[7],pcMsgData[8],pcMsgData[9],pcMsgData[10],pcMsgData[11],pcMsgData[12],
//                    pcMsgData[13],pcMsgData[14],pcMsgData[15],pcMsgData[16],pcMsgData[17]);

            if (pcMsgData == NULL || iMsgDataLen != 18)
            {
                break;
            }
            else
            {
                getNvrStatusCtrl(pHandle, pcMsgData);
                break;
            }
        }
        case SERV_CLI_MSG_TYPE_GET_IPC_STATUS_RESP:
        {
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "devManage Widget get pmsg response cmd 0x%x data:\n", ucMsgCmd);
//            DebugPrint(DEBUG_PMSG_DATA_PRINT, "0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", pcMsgData[0],pcMsgData[1],pcMsgData[2],pcMsgData[3],
//                pcMsgData[4],pcMsgData[5],pcMsgData[6],pcMsgData[7],pcMsgData[8],pcMsgData[9],pcMsgData[10],pcMsgData[11],pcMsgData[12],
//                pcMsgData[13],pcMsgData[14],pcMsgData[15]);

            if (pcMsgData == NULL || iMsgDataLen != 16)
            {
                break;
            }
            else
            {
                getIpcStatusCtrl(pHandle, pcMsgData);
                break;
            }
        }
        default:
            break;
    }

    return 0;
}

