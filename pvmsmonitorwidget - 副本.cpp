#include "pvmsmonitorwidget.h"
#include "ui_pvmsmonitorwidget.h"
#include <pthread.h>
#include <QDebug>
#include <sys/sysinfo.h>
#include <QMessageBox>
#include "log.h"
#include <QEvent>
#include <QMouseEvent>
#include <qdebug.h>
#include <QUrl>

static pthread_mutex_t g_tCmpCtrlMutex;

#define PageNone 0

#define PageMonitot 1
static int g_iPNum = 0;
static int g_ifist_falg = 0;

QButtonGroup *g_buttonGroup = NULL;
#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面

typedef enum _E_CAMERA_SWITCH_STATE    //摄像机切换状态
{
    NORMAL = 0,    //正常，不切换
    LASTONE = 1,   //切换到上一个
    NEXTONE = 2    //切换到下一个
} E_CAMERA_SWITCH_STATE;

typedef enum _E_THREAD_SIGNAL_TYPE    //子线程触发的信号类型
{
    FULLSCREEN_SIGTYPE = 1,     //全屏
    SET_PRESET_STYLESHEET_SIGTYPE = 2,     //设置预置点切换时的样式，主要是当每次轮询到新摄像头时，预置点按钮切换到一号预置点被选中的样式
    OPEN_CAMERA_SIGTYPE = 3,   //摄像头开启
    CLOSE_CAMERA_SIGTYPE = 4,   //摄像头关闭
    OPEN_FILLLIGHT_SIGTYPE = 5,   //补光灯开启
    CLOSE_FILLLIGHT_SIGTYPE = 6    //补光灯关闭 受电弓视频监控系统
} E_THREAD_SIGNAL_TYPE;

#define FULLSCREEN_MONITOR_TIME 20      //全屏监控时间，单位秒
#define GET_DEVSTATE_MONITOR_TIME 10     //获取设备状态间隔时间，单位秒
#define SET_TIME_MONITOR_TIME 1   //更新设备维护界面时间显示的间隔时间，单位秒


int GetNodeFromCmpQueue(PT_CMP_QUEUE ptCmpQueue, PT_CMP_PACKET ptPkt)
{
    T_CMP_PACKET_LIST *ptTmp = NULL;

    if ((NULL == ptCmpQueue) || (NULL == ptPkt))
    {
        return 0;
    }

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_lock(ptCmpQueue->pMutex);
    }

    if (NULL == ptCmpQueue->ptFirst)
    {
        if (ptCmpQueue->pMutex)
        {
            pthread_mutex_unlock(ptCmpQueue->pMutex);
        }

        return 0;
    }

    ptTmp = ptCmpQueue->ptFirst;
    ptCmpQueue->ptFirst = ptCmpQueue->ptFirst->next;
    if (NULL == ptCmpQueue->ptFirst)
    {
        ptCmpQueue->ptLast= NULL;
    }
    ptCmpQueue->iPktCount--;
    *ptPkt = ptTmp->tPkt;
    free(ptTmp);
    ptTmp = NULL;

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_unlock(ptCmpQueue->pMutex);
    }

    return 1;
}



int PutNodeToCmpQueue(PT_CMP_QUEUE ptCmpQueue, PT_CMP_PACKET ptPkt)
{
    T_CMP_PACKET_LIST *ptPktList = NULL;

    if ((NULL == ptCmpQueue) || (NULL == ptPkt))
    {
        return -1;
    }
    ptPktList = (T_CMP_PACKET_LIST *)malloc(sizeof(T_CMP_PACKET_LIST));
    if (NULL == ptPktList)
    {
        return -1;
    }

    memset(ptPktList, 0, sizeof(T_CMP_PACKET_LIST));
    ptPktList->tPkt = *ptPkt;

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_lock(ptCmpQueue->pMutex);
    }

    if (NULL == ptCmpQueue->ptLast)
    {
        ptCmpQueue->ptFirst = ptPktList;
    }
    else
    {
        ptCmpQueue->ptLast->next = ptPktList;
    }
    ptCmpQueue->ptLast = ptPktList;
    ptCmpQueue->iPktCount++;

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_unlock(ptCmpQueue->pMutex);
    }

    return 0;
}



PT_CMP_QUEUE CreateCmpQueue(pthread_mutex_t *pMutex, INT32 iQueueType)
{
    PT_CMP_QUEUE ptCmpQueue = NULL;

    ptCmpQueue = (PT_CMP_QUEUE)malloc(sizeof(T_CMP_QUEUE));
    if (NULL == ptCmpQueue)
    {
        return NULL;
    }
    memset(ptCmpQueue, 0, sizeof(T_CMP_QUEUE));
    ptCmpQueue->pMutex = pMutex;
    ptCmpQueue->iQueueType = iQueueType;
    ptCmpQueue->ptLast = NULL;
    ptCmpQueue->ptFirst = NULL;
    ptCmpQueue->iPktCount= 0;

    return ptCmpQueue;
}

int DestroyCmpQueue(PT_CMP_QUEUE ptCmpQueue)
{
    T_CMP_PACKET_LIST *ptPktList = NULL, *ptTmp = NULL;

    if (NULL == ptCmpQueue)
    {
        return -1;
    }

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_lock(ptCmpQueue->pMutex);
    }

    ptPktList = ptCmpQueue->ptFirst;
    while (ptPktList)
    {
        ptTmp = ptPktList;
        ptPktList = ptPktList->next;
        free(ptTmp);
        ptTmp = NULL;
    }

    ptCmpQueue->ptLast = NULL;
    ptCmpQueue->ptFirst = NULL;
    ptCmpQueue->iPktCount= 0;

    if (ptCmpQueue->pMutex)
    {
        pthread_mutex_unlock(ptCmpQueue->pMutex);
    }

    free(ptCmpQueue);
    ptCmpQueue = NULL;

    return 0;
}


pvmsMonitorWidget::pvmsMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pvmsMonitorWidget)
{
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    pthread_mutexattr_t	mutexattr;
    int i = 0;
//    /*将界面所有控件加入event事件过滤器进行监听，并设置鼠标移动能捕捉到，以便进行全屏检测*/
    ui->label_3->installEventFilter(this);  //加入事件过滤器
    ui->label_3->setMouseTracking(true);   //设置鼠标移动能捕捉到
    ui->label_7->installEventFilter(this);
    ui->label_7->setMouseTracking(true);
    ui->ptzUpPushButton->installEventFilter(this);
    ui->ptzUpPushButton->setMouseTracking(true);
    ui->ptzDownPushButton->installEventFilter(this);
    ui->ptzDownPushButton->setMouseTracking(true);
    ui->ptzLeftPushButton->installEventFilter(this);
    ui->ptzLeftPushButton->setMouseTracking(true);
    ui->ptzRightPushButton->installEventFilter(this);
    ui->ptzRightPushButton->setMouseTracking(true);
    ui->zoomInPushButton->installEventFilter(this);
    ui->zoomInPushButton->setMouseTracking(true);
    ui->zoomOutPushButton->installEventFilter(this);
    ui->zoomOutPushButton->setMouseTracking(true);
    ui->focusFarPushButton->installEventFilter(this);
    ui->focusFarPushButton->setMouseTracking(true);
    ui->focusNearPushButton->installEventFilter(this);
    ui->focusNearPushButton->setMouseTracking(true);
    ui->presetSetPushButton->installEventFilter(this);
    ui->presetSetPushButton->setMouseTracking(true);
    ui->presetGetPushButton->installEventFilter(this);
    ui->presetGetPushButton->setMouseTracking(true);
    ui->cameraSwitchPushButton->installEventFilter(this);
    ui->cameraSwitchPushButton->setMouseTracking(true);
    ui->fillLightSwitchPushButton->installEventFilter(this);
    ui->fillLightSwitchPushButton->setMouseTracking(true);
    ui->startPollingPushButton->installEventFilter(this);
    ui->startPollingPushButton->setMouseTracking(true);
    ui->pausePollingPushButton->installEventFilter(this);
    ui->pausePollingPushButton->setMouseTracking(true);
    ui->pollingLastOnePushButton->installEventFilter(this);
    ui->pollingLastOnePushButton->setMouseTracking(true);
    ui->pollingNextOnePushButton->installEventFilter(this);
    ui->pollingNextOnePushButton->setMouseTracking(true);
    ui->temporarySavePushButton->installEventFilter(this);
    ui->temporarySavePushButton->setMouseTracking(true);
    ui->alarmPushButton->installEventFilter(this);
    ui->alarmPushButton->setMouseTracking(true);
    m_presetNoPushbutton[0] = ui->presetNoPushButton;
    m_presetNoPushbutton[1] = ui->presetNoPushButton_2;
    m_presetNoPushbutton[2] = ui->presetNoPushButton_3;
    m_presetNoPushbutton[3] = ui->presetNoPushButton_4;
    m_presetNoPushbutton[4] = ui->presetNoPushButton_5;
    m_presetNoPushbutton[5] = ui->presetNoPushButton_6;
    m_presetNoPushbutton[6] = ui->presetNoPushButton_7;
    m_presetNoPushbutton[7] = ui->presetNoPushButton_8;
    for (i = 0; i < 8; i++)
    {
        m_presetNoPushbutton[i]->installEventFilter(this);
        m_presetNoPushbutton[i]->setMouseTracking(true);
    }

    /*设置8个预置点按钮、预置点设置和调用按钮、预置点调焦和聚焦4个按钮、预置点方向控制4个按钮、摄像机开关按钮、补光灯开关按钮、轮询播放控制4个按钮的普通、鼠标移上等样式*/
    for (i = 0; i < 8; i++)
    {
        m_presetNoPushbutton[i]->setFocusPolicy(Qt::NoFocus); // 得到焦点时，不显示虚线框
    }
    ui->cameraSwitchPushButton->setChecked(true);
    ui->fillLightSwitchPushButton->setChecked(false);
    ui->startPollingPushButton->setChecked(true);
    ui->pausePollingPushButton->setChecked(false);

    ui->cameraSwitchPushButton->setFocusPolicy(Qt::NoFocus);
    ui->fillLightSwitchPushButton->setFocusPolicy(Qt::NoFocus);
    ui->presetSetPushButton->setFocusPolicy(Qt::NoFocus);
    ui->presetGetPushButton->setFocusPolicy(Qt::NoFocus);
    ui->zoomInPushButton->setFocusPolicy(Qt::NoFocus);
    ui->zoomOutPushButton->setFocusPolicy(Qt::NoFocus);
    ui->focusFarPushButton->setFocusPolicy(Qt::NoFocus);
    ui->focusNearPushButton->setFocusPolicy(Qt::NoFocus);
    ui->ptzUpPushButton->setFocusPolicy(Qt::NoFocus);
    ui->ptzDownPushButton->setFocusPolicy(Qt::NoFocus);
    ui->ptzLeftPushButton->setFocusPolicy(Qt::NoFocus);
    ui->ptzRightPushButton->setFocusPolicy(Qt::NoFocus);
    ui->startPollingPushButton->setFocusPolicy(Qt::NoFocus);
    ui->pausePollingPushButton->setFocusPolicy(Qt::NoFocus);
    ui->pollingLastOnePushButton->setFocusPolicy(Qt::NoFocus);
    ui->pollingNextOnePushButton->setFocusPolicy(Qt::NoFocus);
    ui->temporarySavePushButton->setFocusPolicy(Qt::NoFocus);
    ui->alarmPushButton->setFocusPolicy(Qt::NoFocus);

    g_buttonGroup = new QButtonGroup();
    g_buttonGroup->addButton(ui->presetNoPushButton,1);
    g_buttonGroup->addButton(ui->presetNoPushButton_2,2);
    g_buttonGroup->addButton(ui->presetNoPushButton_3,3);
    g_buttonGroup->addButton(ui->presetNoPushButton_4,4);
    g_buttonGroup->addButton(ui->presetNoPushButton_5,5);
    g_buttonGroup->addButton(ui->presetNoPushButton_6,6);
    g_buttonGroup->addButton(ui->presetNoPushButton_7,7);
    g_buttonGroup->addButton(ui->presetNoPushButton_8,8);

    connect(g_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(presetNoGroupButtonClickSlot(int)));     //预置点按钮组按键信号连接响应槽函数


    connect(ui->canselPushButton, SIGNAL(clicked()), this, SLOT(registOutButtonClick()));

    connect(ui->alarmPushButton, SIGNAL(clicked(bool)), this, SLOT(alarmPushButoonClickSlot()));   //报警按钮按键信号响应打开报警信息界面
    connect(ui->startPollingPushButton, SIGNAL(clicked(bool)), this, SLOT(startPollingSlot()));   //播放按钮按键信号响应开启轮询
    connect(ui->pausePollingPushButton, SIGNAL(clicked(bool)), this, SLOT(pausePollingSlot()));   //暂停按钮按键信号响应暂停轮询
    connect(ui->pollingLastOnePushButton, SIGNAL(clicked(bool)), this, SLOT(manualSwitchLastCameraSlot()));
    connect(ui->pollingNextOnePushButton, SIGNAL(clicked(bool)), this, SLOT(manualSwitchNextCameraSlot()));
    connect(ui->presetSetPushButton, SIGNAL(clicked(bool)), this, SLOT(presetSetCtrlSlot()));    //预置点设置按钮按键信号连接响应槽函数
    connect(ui->presetGetPushButton, SIGNAL(clicked(bool)), this, SLOT(presetGetCtrlSlot()));    //预置点调用按钮按键信号连接响应槽函数
    connect(ui->temporarySavePushButton, SIGNAL(clicked(bool)), this, SLOT(temporarySaveBeginSlot()));
    connect(ui->cameraSwitchPushButton,  SIGNAL(clicked(bool)), this, SLOT(cameraSwitchSlot()));  //摄像头开关按钮按键信号连接响应槽函数
    connect(ui->fillLightSwitchPushButton,  SIGNAL(clicked(bool)), this, SLOT(fillLightSwitchSlot()));  //补光灯开关按钮按键信号连接响应槽函数



    connect(this, SIGNAL(videoPollingSignal()), this, SLOT(videoPollingSignalCtrl()), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(setFullScreenSignal()), this, SLOT(setFullScreenSignalCtrl()));
    connect(this, SIGNAL(presetReturnSignal(int)), this, SLOT(presetReturnSignalCtrl(int)));
    connect(this, SIGNAL(recordPlayCtrlSignal()), this, SLOT(recordPlayCtrlSlot()));
    connect(this, SIGNAL(cmpOptionCtrlSignal(int, int)), this, SLOT(cmpOptionCtrlSlot(int, int)), Qt::BlockingQueuedConnection );
    connect(this, SIGNAL(chLabelDisplayCtrlSignal()), this, SLOT(chLabelDisplayCtrlSlot()));
    connect(this, SIGNAL(chStateLabelTextCtrlSignal(int)), this, SLOT(chStateLabelTextCtrlSlot(int)));
    connect(this, SIGNAL(camSwitchButtonTextCtrlSignal(int)), this, SLOT(camSwitchButtonTextCtrlSlot(int)));
    connect(this, SIGNAL(fillLightSwitchButtonTextCtrlSignal(int)), this, SLOT(fillLightSwitchButtonTextCtrlSlot(int)));

#ifndef mplaybin
    playerlist = new QList<QMediaPlayer*>();
    videoList = new QList<QVideoWidget*>();
    multiPlayList = new QList<QMediaPlaylist*>();
    hLayoutList = new QList<QHBoxLayout*>();

#endif
//    player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    //参数初始化
    cameraNum = 0;
    m_channelStateLabel = NULL;
    m_channelNoLabel = NULL;
    m_alarmHappenTimer = NULL;
    m_manualSwitchTimer = NULL;
    m_fillLightSwitchTimer = NULL;
    m_cameraSwitchTimer = NULL;
    m_temporarySaveTimer = NULL;
    m_iCameraSwitchState = NORMAL;   //摄像头切换状态默认为正常，表示不切换
    m_iPresetPasswdOkFlag = 0;
    m_presetPasswdConfirmPage = NULL;
    m_iCameraNum = 0;
    m_iCameraPlayNo = 0;
    m_iPollingFlag = 1;   //默认轮询开启
    m_iSelectPresetNo = 1;  //预置点选中编号默认为1
    m_iPtzMoveType = E_STOP_MOVE;
    m_iRecordPlayFlag = 0;
    m_iFullScreenFlag = 0;
    m_iAlarmNotCtrlFlag = 0;
    m_iBlackScreenFlag = 0;
    m_iPisGetFlag = 0;
    m_iOldRecordPlayFlag = 0;
#ifdef mplaybin
    m_playWin = NULL;
#endif
    memset(m_tCameraInfo, 0, sizeof(T_CAMERA_INFO)*MAX_SERVER_NUM*MAX_CAMERA_OFSERVER);

    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
    pthread_mutex_init(&tMutex, &mutexattr);
    pthread_mutex_init(&g_tCmpCtrlMutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);
    m_ptQueue = CreateCmpQueue(&tMutex, 0);


    createMedia();
}


void *monitorThread(void *param)     //实时监控线程，对通道轮询、全屏、预置点返回、设备状态等进行循环监控
{
    int i = 0, iRet = 0;
    int iPollingTime = 0, iPresetReturnTime = 0;
    int iCameraIdex = 0;  //摄像头索引
    int iPollingFlag = 0;
    int err = 0;
    time_t tPollingCurTime = 0;
    time_t tPresetReturnCurTime = 0;
    time_t tFullScreenCurTime = 0;
    time_t tGetDevStateCurTime = 0, tGetDevStateOldTime = 0;
    time_t tSetTimeCurTime = 0, tSetTimeOldTime = 0;
    T_CMP_PACKET tCmpPkt;
    struct sysinfo s_info;


    pvmsMonitorWidget *pvmsMonitorPage = (pvmsMonitorWidget *)param;
    if (NULL == pvmsMonitorPage)
    {
        return NULL;
    }
    iCameraIdex = pvmsMonitorPage->m_iCameraPlayNo;
    err = sysinfo(&s_info);
    if(err)
    {
        printf("\n\ncode error=%d\n",err);
    }
    tPollingCurTime = s_info.uptime;
    iPollingTime = STATE_GetPollingTime();
    if (iPollingTime > 0)
    {
        pvmsMonitorPage->tPollingOparateTime = tPollingCurTime - iPollingTime;//保证线程一进来，就进行一次循环处理
    }

    tPresetReturnCurTime = s_info.uptime;
    tFullScreenCurTime = s_info.uptime;
    tGetDevStateCurTime = s_info.uptime;
    tSetTimeCurTime = s_info.uptime;
    tGetDevStateOldTime = tGetDevStateCurTime;
    tSetTimeOldTime = tSetTimeCurTime;

    while (1 == pvmsMonitorPage->m_iThreadRunFlag)
    {
        memset(&tCmpPkt, 0, sizeof(T_CMP_PACKET));
        iRet = GetNodeFromCmpQueue(pvmsMonitorPage->m_ptQueue, &tCmpPkt);   //读取cmp队列，对解码通道进行相应处理
        if (iRet > 0)
        {
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "MonitorPlayThread get cmpctrl cmd:%d, ch=%d\n", tCmpPkt.iMsgCmd, tCmpPkt.iCh);
            pvmsMonitorPage->triggerCmpOptionCtrlSinal(tCmpPkt.iMsgCmd, tCmpPkt.iCh);
        }


    iPollingTime = STATE_GetPollingTime();
    if (iPollingTime < 0)
    {
        usleep(100*1000);
        continue;
    }

    iPresetReturnTime = STATE_GetPresetReturnTime();
    if (iPresetReturnTime < 0)
    {
        usleep(100*1000);
        continue;
    }
    iPresetReturnTime = iPresetReturnTime*60;
    iPollingFlag = 0;  //轮询标志复位

    /*检测轮询*/
    if ((1 == pvmsMonitorPage->m_iPollingFlag) && ((tPollingCurTime-pvmsMonitorPage->tPollingOparateTime) >= iPollingTime))   //只有轮询标记为1并且时间到了轮询时间时才轮询
    {
        iCameraIdex += 1;  //更新摄像头索引
        if (iCameraIdex > (pvmsMonitorPage->m_iCameraNum - 1))    //iCameraIdex达到最大值，表示轮询完了一轮，将索引置位，开始重新一轮的轮询
        {
            iCameraIdex = 0;
        }
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread polling to camera, %d !\n",iCameraIdex);

        iPollingFlag = 1;
    }

    if (LASTONE == pvmsMonitorPage->m_iCameraSwitchState)  //外部操作了摄像头切换到上一个，状态更新为上一个，这里进行切换操作
    {
        iCameraIdex -= 1;
        if (iCameraIdex < 0)
        {
            iCameraIdex = pvmsMonitorPage->m_iCameraNum - 1;
        }
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread polling to last camera no=%d !\n",iCameraIdex);

        pvmsMonitorPage->m_iCameraSwitchState = NORMAL;   //摄像头切换状态恢复到正常不切换状态
        iPollingFlag = 1;
    }
    else if (NEXTONE == pvmsMonitorPage->m_iCameraSwitchState) //外部操作了摄像头切换到下一个，状态更新为下一个，这里进行切换操作
    {
        iCameraIdex += 1;
        if (iCameraIdex > (pvmsMonitorPage->m_iCameraNum - 1))
        {
            iCameraIdex = 0;
        }
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread polling to next camera, no=%d !\n",iCameraIdex);

        pvmsMonitorPage->m_iCameraSwitchState = NORMAL;   //摄像头切换状态恢复到正常不切换状态
        iPollingFlag = 1;
    }

    if (1 == iPollingFlag)
    {
        pvmsMonitorPage->m_iCameraPlayNo = iCameraIdex;  //更新当前摄像头编号，方便后续的各项操作能对准摄像头
        pvmsMonitorPage->tPollingOparateTime = tPollingCurTime;
        pvmsMonitorPage->triggerVideoPollingSignal();

    }
    else
    {
        /*非轮询状态下也要实时监控摄像头码流状态的，如果有变换需进行通道状态和通道号的处理，如果状态变成1(有流)则需要隐藏通道状态和通道号，变成0需要显示*/
        pvmsMonitorPage->noPollingChOption();
    }

    /*检测回放状态是否改变*/
    if (pvmsMonitorPage->m_iOldRecordPlayFlag != pvmsMonitorPage->m_iRecordPlayFlag)
    {
        pvmsMonitorPage->triggerRecordPlayCtrlSignal();
        pvmsMonitorPage->m_iOldRecordPlayFlag = pvmsMonitorPage->m_iRecordPlayFlag;
    }

    /*检测预置点返回*/
    for (i = 0; i < pvmsMonitorPage->m_iCameraNum; i++)
    {
        if ((pvmsMonitorPage->m_tCameraInfo[i].iPresetNo != 1) && ((tPresetReturnCurTime-pvmsMonitorPage->m_tCameraInfo[i].tPtzOprateTime) >= iPresetReturnTime) && (pvmsMonitorPage->m_tCameraInfo[i].phandle != 0))   //检测预置点返回操作
        {
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread presetReturn timeOut, no=%d !\n",i);
            pvmsMonitorPage->triggerPresetReturnSignal(i);
            pvmsMonitorPage->m_tCameraInfo[i].tPtzOprateTime = tPresetReturnCurTime;
        }
    }

    /*检测是否要全屏*/
    if ((tFullScreenCurTime-pvmsMonitorPage->m_lastActionTime) >= FULLSCREEN_MONITOR_TIME && 0 == pvmsMonitorPage->m_iFullScreenFlag)    //界面20秒无操作,全屏
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread fullScreen timeOut!\n");
        //printf("tFullScreenCurTime=%d,pvmsMonitorPage->m_lastActionTime=%d\n",tFullScreenCurTime,pvmsMonitorPage->m_lastActionTime);
        if (pvmsMonitorPage->isHidden() != 1)   //只有当前处于受电弓监控界面时才做触发全屏处理
        {
            pvmsMonitorPage->triggerFullScreenSignal();
        }
        pvmsMonitorPage->m_lastActionTime = tFullScreenCurTime;
    }

    /*检测设备状态*/
    if ((tGetDevStateCurTime - tGetDevStateOldTime) >= GET_DEVSTATE_MONITOR_TIME)
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread get device state timeOut!\n");
//        qDebug()<<" DEBUG_UI_NOMAL_PRINT pvmsMonitorWidget monitor thread get device state timeOut--"<<__FUNCTION__<<__LINE__<<endl;
        pvmsMonitorPage->triggerGetDevStateSignal();
        tGetDevStateOldTime = tGetDevStateCurTime;
    }

    /*检测系统时间*/
    if ((tSetTimeCurTime - tSetTimeOldTime) >= SET_TIME_MONITOR_TIME)
    {
        //DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget monitor thread set devUpdatePage time timeOut!\n");
        pvmsMonitorPage->triggerSetTimeSignal();
        tSetTimeOldTime = tSetTimeCurTime;
    }

    usleep(50*1000);
    if(sysinfo(&s_info))
    {
        printf("\n\ncode error=%d\n",err);
    }
    tPollingCurTime = s_info.uptime;
    tPresetReturnCurTime = s_info.uptime;
    tFullScreenCurTime = s_info.uptime;
    tGetDevStateCurTime = s_info.uptime;
    tSetTimeCurTime = s_info.uptime;
   }
    return NULL;

}

void pvmsMonitorWidget::startVideoPolling()    //开启视频轮询的处理
{
    static int iFirstFlag = 1;
    int i = 0, j = 0, iRet = 0;
    char acSendBuf[4] = {0};
    char acRtspUrl[128] = {0};
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;
    T_CMP_PACKET tPkt;
    QString chStr = tr("通道");

    struct sysinfo s_info;
    memset(&s_info,0,sizeof(s_info));
    sysinfo(&s_info);
    m_lastActionTime = s_info.uptime;

    m_iFullScreenFlag = 1;

    memset(m_tCameraInfo, 0, sizeof(T_CAMERA_INFO)*MAX_SERVER_NUM*MAX_CAMERA_OFSERVER);

#ifdef mplaybin
    m_playWin = new QVideoWidget(this->parentWidget());   //新建一个与目前窗体同属一个父窗体的播放子窗体，方便实现全屏
//    m_playWin->setGeometry(0, 0, 1024, 768);      //设置窗体在父窗体中的位置，默认一开始为全屏
    m_playWin->setGeometry(0, 138, 782, 630);
    m_playWin->show();  //默认显示
    m_playWin->setObjectName("m_playWin");
    m_playWin->setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");     //设置播放窗口背景色为黑色
    m_playWin->installEventFilter(this);     //播放窗体注册进事件过滤器
    m_playWin->setMouseTracking(true);
    player.setVideoOutput(m_playWin);
#endif

    m_channelStateLabel = new QLabel(this->parentWidget());
    m_channelStateLabel->setGeometry(452, 360, 130, 50);
    m_channelStateLabel->setStyleSheet("QLabel{color:rgb(55, 82, 103);font: 24pt;background-color: rgb(0, 0, 0);}");
    m_channelStateLabel->setAttribute(Qt::WA_TranslucentBackground, true); //设置控件背景透明
    m_channelStateLabel->show();

    m_channelNoLabel = new QLabel(this->parentWidget());
    m_channelNoLabel->setGeometry(20, 690, 100, 50);
    m_channelNoLabel->setStyleSheet("QLabel{color:rgb(55, 82, 103);font: 24pt;background-color: rgb(0, 0, 0);}");
    m_channelNoLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    m_channelNoLabel->show();
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {

//        memset(acRtspUrl, 0, sizeof(acRtspUrl));
//        snprintf(acRtspUrl, sizeof(acRtspUrl), "rtsp://192.168.%d.200", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);

//        snprintf(acRtspUrl, sizeof(acRtspUrl), "168.168.102.%d", 70+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);

//        qDebug()<<"tTrainConfigInfo.iNvrServerCount"<<tTrainConfigInfo.iNvrServerCount<<endl;
//        qDebug()<<"acRtspUrl****"<<acRtspUrl;

//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server:%s has camera num=%d\n",__FUNCTION__,acRtspUrl, tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum);
        m_NvrServerPhandle[i] = STATE_GetNvrServerPmsgHandle(i);

        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            memset(acRtspUrl, 0, sizeof(acRtspUrl));
            if(j == 1)
                snprintf(acRtspUrl, sizeof(acRtspUrl), "rtsp://admin:admin123@192.168.%d.%d", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,200+j);
            else
                snprintf(acRtspUrl, sizeof(acRtspUrl), "rtsp://192.168.%d.%d", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,200+j);


//            printf("*****************************acRtspUrl**********=%s\n",acRtspUrl);
            /*保存所有摄像机的信息*/
            m_tCameraInfo[m_iCameraNum].phandle = STATE_GetNvrServerPmsgHandle(i);
            m_tCameraInfo[m_iCameraNum].iPosNO = 8+j;
            if(j == 1)
                snprintf(m_tCameraInfo[m_iCameraNum].acCameraRtspUrl, sizeof(m_tCameraInfo[m_iCameraNum].acCameraRtspUrl), "%s:554",acRtspUrl);
            else
                snprintf(m_tCameraInfo[m_iCameraNum].acCameraRtspUrl, sizeof(m_tCameraInfo[m_iCameraNum].acCameraRtspUrl), "%s:554/%d",acRtspUrl, 8+j);
            printf("##############i=%d, rtspurl:%s\n-------m_iCameraNum=%d",m_iCameraNum,m_tCameraInfo[m_iCameraNum].acCameraRtspUrl,m_iCameraNum);

//            mlist<<m_tCameraInfo[m_iCameraNum].acCameraRtspUrl;
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] camer %d rtspUrl=%s\n",__FUNCTION__,m_iCameraNum, m_tCameraInfo[m_iCameraNum].acCameraRtspUrl);
            tPkt.iCh = m_iCameraNum;
            if(m_iCameraNum == 0)
                tPkt.iMsgCmd = CMP_CMD_CREATE_CH;
            else
                tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;

            PutNodeToCmpQueue(m_ptQueue, &tPkt);

            struct sysinfo s_info;
            sysinfo(&s_info);
            m_tCameraInfo[m_iCameraNum].tPtzOprateTime = s_info.uptime;
            m_iCameraNum++;


        }

    }

    if (1 == iFirstFlag)    //程序运行起来第一次进当前界面，需要把所有的摄像头打开,摄像头开关状态为开，补光灯开关状态为开，预置点编号为0
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] send CLI_SERV_MSG_TYPE_PVMS_IPC_CTRL to server to open all camera%d\n",__FUNCTION__);
        for (i = 0; i < m_iCameraNum; i++)
        {
            acSendBuf[0] = 1;  //发送消息的第2个字节表示操作类型，这里为开启摄像头
            acSendBuf[1] = m_tCameraInfo[i].iPosNO;	  //发送消息的第2个字节表示受电弓摄像机位置号
            iRet = PMSG_SendPmsgData(m_tCameraInfo[i].phandle, CLI_SERV_MSG_TYPE_PVMS_IPC_CTRL, acSendBuf, 2);    //发送摄像头开关控制命令
            if (iRet < 0)
            {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_IPC_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, i);
            }
            else
            {
                for (j = 0; j < tTrainConfigInfo.iNvrServerCount; j++)
                {
                    if (m_tCameraInfo[i].phandle == STATE_GetNvrServerPmsgHandle(j))
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "open camera %d.%d stream", 100+tTrainConfigInfo.tNvrServerInfo[j].iCarriageNO, 200+m_tCameraInfo[i].iPosNO-8);
                        LOG_WriteLog(&tLogInfo);
                        break;
                    }
                }
            }


            acSendBuf[0] = 1;  //发送消息的第2个字节表示操作类型,这里开启补光灯
            acSendBuf[1] = m_tCameraInfo[i].iPosNO;	  //发送消息的第2个字节表示受电弓摄像机位置号
            iRet = PMSG_SendPmsgData(m_tCameraInfo[i].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
            if (iRet < 0)
            {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, i);
            }
            else
            {
                for (j = 0; j < tTrainConfigInfo.iNvrServerCount; j++)
                {
                    if (m_tCameraInfo[i].phandle == STATE_GetNvrServerPmsgHandle(j))
                    {
                        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                        tLogInfo.iLogType = 0;
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "open camera %d.%d fillLight", 100+tTrainConfigInfo.tNvrServerInfo[j].iCarriageNO, 200+m_tCameraInfo[i].iPosNO-8);
                        LOG_WriteLog(&tLogInfo);
                        break;
                    }
                }
            }

            m_tCameraInfo[i].iCameraSwitchState = CAMERA_ON;
            m_tCameraInfo[i].iFillLightSwitchState = FILLLIGHT_ON;
            m_tCameraInfo[i].iPresetNo = 0;
        }

        m_channelStateLabel->setText(tr("摄像头开启"));
        m_channelNoLabel->setText(tr("通道1"));
        m_iCameraPlayNo = -1;
        iFirstFlag = 0;

    }
    else    //非第一次，则保持摄像头开关状态、补光灯开关状态不变，也不用发开关摄像头的命令到服务器，并且根据不同的摄像头开关状态显示不同的通道状态
    {
        if (CAMERA_ON == m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState)
        {
            m_channelStateLabel->setText(tr("摄像头开启"));
        }
        else
        {
            m_channelStateLabel->setText(tr("摄像头关闭"));
        }
        chStr += QString::number(m_iCameraPlayNo+1);
        m_channelNoLabel->setText(chStr);

    }

    m_PisServerPhandle = STATE_GetPisPmsgHandle();
    tPollingOparateTime = s_info.uptime;
    m_threadId = 0;
    m_iThreadRunFlag = 1;
    m_iDisplayEnable = 1;  //全局显示使能开启，使轮询线程正常轮询

    pthread_create(&m_threadId, NULL, monitorThread, (void *)this);    //创建监控线程



}

void pvmsMonitorWidget::enableVideoPlay(int iFlag)    //对摄像头进行解码显示使能，允许显示或禁止显示
{
    int i = 0;
    static int iPollFlag = 0;
    T_CMP_PACKET tPkt;

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] set enableVideoPlay flag to %d!\n",__FUNCTION__,iFlag);

    if (1 == iFlag)  //只使能当前轮询到的摄像头，设置全局使能标志，使轮询线程按正常轮询
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] enable the polling camera's vdec channel!\n",__FUNCTION__);
        for (i = 0; i < m_iCameraNum; i++)
        {
            if (i == m_iCameraPlayNo)
            {
                tPkt.iMsgCmd = CMP_CMD_ENABLE_CH;
                tPkt.iCh = i;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);
            }
            else
            {
                tPkt.iMsgCmd = CMP_CMD_DISABLE_CH;
                tPkt.iCh = i;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);
            }
        }

        m_iDisplayEnable = 1;  //全局显示使能开启，使轮询线程正常轮询

        emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号

        if (1 == iPollFlag)    //切换到本界面时，如果之前是轮询的则恢复轮询
        {
            iPollFlag = 0;
            m_iPollingFlag = 1;
            struct sysinfo s_info;
            memset(&s_info,0,sizeof(s_info));
            sysinfo(&s_info);
            tPollingOparateTime = s_info.uptime;
        }

        struct sysinfo s_info;
        memset(&s_info,0,sizeof(s_info));
        sysinfo(&s_info);
        m_lastActionTime = s_info.uptime;    //切换到受电弓监控页面，复位最后操作时间
    }

    else if (0 == iFlag)    //全部禁止，并且设置全局使能标志，使轮询线程也一直不显示解码
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] diable all camera's vdec channel!\n",__FUNCTION__);
        for (i = 0; i < m_iCameraNum; i++)
        {
            tPkt.iMsgCmd = CMP_CMD_DISABLE_CH;
            tPkt.iCh = i;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
        }

        m_iDisplayEnable = 0;  //全局显示使能关闭，使轮询线程不管轮询到哪个摄像头都不显示

        emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号

        if (1 == m_iPollingFlag)
        {
            iPollFlag = 1;
            m_iPollingFlag = 0;   //在切换到其他界面时，先暂时停止轮询
            struct sysinfo s_info;
            sysinfo(&s_info);
            tPollingOparateTime = s_info.uptime;
        }
    }

}



void pvmsMonitorWidget::registOutButtonClick()
{
    int monitor_page = 1;
    this->hide();
    emit registOutSignal(monitor_page);    //触发注销信号，带上当前设备类型

}

void pvmsMonitorWidget::presetNoGroupButtonClickSlot(int iButtonNo)   //预置点编号按钮组按键信号响应槽函数，iButtonNo为按钮编号
{
    m_iSelectPresetNo = iButtonNo;   //保存选中的预置点编号
}
void pvmsMonitorWidget::alarmPushButoonClickSlot()
{
    emit alarmPushButoonClickSignal();
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);

    m_iAlarmNotCtrlFlag = 0;
    g_iPNum = 0;

}
void pvmsMonitorWidget::startPollingSlot()
{
    m_iPollingFlag = 1;

    /*开始轮询按钮按下，设置开始按钮为按下时样式，暂停按钮恢复正常样式*/
    ui->startPollingPushButton->setChecked(true);
    ui->pausePollingPushButton->setChecked(false);

    struct sysinfo s_info;
    sysinfo(&s_info);
    tPollingOparateTime = s_info.uptime;

    setPlayButtonStyleSheet();

}
void pvmsMonitorWidget::pausePollingSlot()
{
    m_iPollingFlag = 0;

    /*暂停轮询按钮按下，设置暂停按钮为按下时样式，开始按钮恢复正常样式*/
    ui->startPollingPushButton->setChecked(false);
    ui->pausePollingPushButton->setChecked(true);

    struct sysinfo s_info;
    sysinfo(&s_info);
    tPollingOparateTime = s_info.uptime;
    setPlayButtonStyleSheet();

}
void pvmsMonitorWidget::manualSwitchLastCameraSlot()
{
    m_iCameraSwitchState = LASTONE;

//    if(--cameraNum < 0)
//    {
//        cameraNum = 3;
//    }
//    qDebug()<<"******cameraNum*****"<<cameraNum<<endl;

//    video = videoList->value(cameraNum);
//    mplayer = playerlist->value(cameraNum);
//    if(video && mplayer){
////        mplayer->setVideoOutput(video);
//        video->show();
////        mplayer->play();

//    }
//    for(int i=0; i<mlist.count(); i++){
//        if(i != cameraNum){
//            video = videoList->value(i);
//            video->hide();
//            }
//     }

    ui->pollingLastOnePushButton->setEnabled(false);
    ui->pollingNextOnePushButton->setEnabled(false);
    if (NULL == m_manualSwitchTimer)
    {
        m_manualSwitchTimer = new QTimer(this);
    }
    m_manualSwitchTimer->start(1*1000);
    connect(m_manualSwitchTimer,SIGNAL(timeout()), this,SLOT(manualSwitchEndSlot()));

}
void pvmsMonitorWidget::manualSwitchNextCameraSlot()
{
    m_iCameraSwitchState = NEXTONE;
//    if(++cameraNum > 3)
//    {
//        cameraNum = 0;
//    }
//    qDebug()<<"******cameraNum*****"<<cameraNum<<endl;
//    video = videoList->value(cameraNum);
//    mplayer = playerlist->value(cameraNum);
//    if(video && mplayer){
////        mplayer->setVideoOutput(video);
//        video->show();
////        mplayer->play();

//    }
//    for(int i=0; i<mlist.count(); i++){
//        if(i != cameraNum){
//            video = videoList->value(i);
//            video->hide();
//            }
//     }


    ui->pollingLastOnePushButton->setEnabled(false);
    ui->pollingNextOnePushButton->setEnabled(false);
    if (NULL == m_manualSwitchTimer)
    {
        m_manualSwitchTimer = new QTimer(this);
    }
    m_manualSwitchTimer->start(1*1000);
    connect(m_manualSwitchTimer,SIGNAL(timeout()), this,SLOT(manualSwitchEndSlot()));

}
void pvmsMonitorWidget::manualSwitchEndSlot()
{
    ui->pollingLastOnePushButton->setEnabled(true);
    ui->pollingNextOnePushButton->setEnabled(true);

    if (m_manualSwitchTimer != NULL)
    {
        if (m_manualSwitchTimer->isActive())
        {
            m_manualSwitchTimer->stop();
        }
        delete m_manualSwitchTimer;
        m_manualSwitchTimer = NULL;
    }
}

void pvmsMonitorWidget::presetSetCtrlSlot()
{
    int iRet = 0;
    char acSendBuf[4] = {0};

    if (0 == m_iPresetPasswdOkFlag)
    {
        if (NULL == m_presetPasswdConfirmPage)
        {
            m_presetPasswdConfirmPage = new presetPasswdConfirm(this);  //新建一个确认密码的子窗体
        }
        m_presetPasswdConfirmPage->move(300, 270);
        m_presetPasswdConfirmPage->show();
        connect(m_presetPasswdConfirmPage, SIGNAL(sendCloseSignal()), this, SLOT(closePresetPasswdPageSlot()));  //密码验证不通过会受到close信号，closePresetPasswdPageSlot里只会关闭密码验证界面
        connect(m_presetPasswdConfirmPage, SIGNAL(sendOkSignal()), this, SLOT(setPresetSlot()));  //密码验证正确会受到OK信号，setPresetSlot里会关闭密码验证界面，并执行预置点设置操作

    }
    else
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget preset set option ctrl!\n");

        /*发送调用或设置预置点的消息给服务器，消息内容为3个字节，第一个字节表示控制类型:设置还是调用预置点，第二个字节表示预置点号，第三个字节表示受电弓摄像机位置号*/
        acSendBuf[0] = E_PRESET_SET;
        acSendBuf[1] = m_iSelectPresetNo;
        acSendBuf[2] = this->m_tCameraInfo[m_iCameraPlayNo].iPosNO;      //发送消息的第3个字节表示受电弓摄像机位置号
        iRet = PMSG_SendPmsgData(this->m_tCameraInfo[m_iCameraPlayNo].phandle, CLI_SERV_MSG_TYPE_SET_PRESETS, acSendBuf, 3);    //发送预置点控制命令
        if (iRet < 0)
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] camera %d send CLI_SERV_MSG_TYPE_SET_PRESETS failed,iRet=%d\n", __FUNCTION__, m_iCameraPlayNo, iRet);
        }
        struct sysinfo s_info;
        sysinfo(&s_info);
        this->m_tCameraInfo[m_iCameraPlayNo].tPtzOprateTime = s_info.uptime;
        this->m_tCameraInfo[m_iCameraPlayNo].iPresetNo = m_iSelectPresetNo;
//        DebugPrint(DEBUG_UI_MESSAGE_PRINT, "pvmsMonitorWidget set preserNo %d success!\n", m_iSelectPresetNo);
        QMessageBox box(QMessageBox::Information,QString::fromUtf8("注意"),QString::fromUtf8("预置点设置成功!"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
        box.exec();

    }

}
void pvmsMonitorWidget::presetGetCtrlSlot()
{
    int iRet = 0;
      char acSendBuf[4] = {0};

//      DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget preset get button pressed! PresetNo=%d\n", m_iSelectPresetNo);


      /*发送调用或设置预置点的消息给服务器，消息内容为3个字节，第一个字节表示控制类型:设置还是调用预置点，第二个字节表示预置点号，第三个字节表示受电弓摄像机位置号*/
      acSendBuf[0] = E_PRESET_GET;
      acSendBuf[1] = m_iSelectPresetNo;
      acSendBuf[2] = this->m_tCameraInfo[m_iCameraPlayNo].iPosNO;	  //发送消息的第3个字节表示受电弓摄像机位置号
      iRet = PMSG_SendPmsgData(this->m_tCameraInfo[m_iCameraPlayNo].phandle, CLI_SERV_MSG_TYPE_SET_PRESETS, acSendBuf, 3);	//发送预置点控制命令
      if (iRet < 0)
      {
//          DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_SET_PRESETS error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, m_iCameraPlayNo);
      }
      struct sysinfo s_info;
      memset(&s_info,0,sizeof(s_info));
      sysinfo(&s_info);
      this->m_tCameraInfo[m_iCameraPlayNo].tPtzOprateTime = s_info.uptime;
      this->m_tCameraInfo[m_iCameraPlayNo].iPresetNo = m_iSelectPresetNo;

      QMessageBox box(QMessageBox::Information,QString::fromUtf8("注意"),QString::fromUtf8("预置点调用成功!"));
      box.setStandardButtons (QMessageBox::Ok);
      box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));
      box.exec();


}

void pvmsMonitorWidget::cameraSwitchEndSlot()
{
    ui->cameraSwitchPushButton->setEnabled(true);

    if (m_cameraSwitchTimer != NULL)
    {
        if (m_cameraSwitchTimer->isActive())
        {
            m_cameraSwitchTimer->stop();
        }
        delete m_cameraSwitchTimer;
        m_cameraSwitchTimer = NULL;
    }
}

void pvmsMonitorWidget::temporarySaveEndSlot()
{
    ui->temporarySavePushButton->setStyleSheet("background-image:url(:/monres/savevedio.bmp)");

    ui->temporarySavePushButton->setEnabled(true);


    if (m_temporarySaveTimer != NULL)
    {
        if (m_temporarySaveTimer->isActive())   //判断定时器是否正在运行，是则停止运行
        {
            m_temporarySaveTimer->stop();
        }
        delete m_temporarySaveTimer;
        m_temporarySaveTimer = NULL;
    }
}
void pvmsMonitorWidget::temporarySaveBeginSlot()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0, j = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;
    PMSG_HANDLE pmsgHandle = 0;

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget temporarySave button pressed!\n");

//    DebugPrint(DEBUG_UI_MESSAGE_PRINT, "pvmsMonitorWidget temporarySave confirm!\n");
    QMessageBox msgBox(QMessageBox::Information,QString(tr("提示")),QString(tr("是否立即保存!")));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("确 定");
    msgBox.button(QMessageBox::No)->setText("取 消");
    iRet = msgBox.exec();
    if(iRet != QMessageBox::Yes)
    {
//        DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget temporarySave cancle!\n");
        return;
    }
//    DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget temporarySave confirm!\n");

    ui->temporarySavePushButton->setStyleSheet("background-image:url(:/monres/saveing.bmp)");
    ui->temporarySavePushButton->setEnabled(false);

    if (NULL == m_temporarySaveTimer)
    {
        m_temporarySaveTimer = new QTimer(this);
    }
    m_temporarySaveTimer->start(30*1000);
    connect(m_temporarySaveTimer,SIGNAL(timeout()), this,SLOT(temporarySaveEndSlot()));


    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] server%d's PvmsCameraNum=%d\n",__FUNCTION__,i, tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum);
        acSendBuf[0] = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;	  //发送消息的第1个字节表示受电弓服务器车厢号
        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            acSendBuf[1] = 8+j;   //发送消息的第2个字节表示受电弓摄像机位置号
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] camera %d, no=%d send CLI_SERV_MSG_TYPE_SEND_TEMPORARY_SAVE\n", __FUNCTION__, j, 8+j);
            pmsgHandle = STATE_GetNvrServerPmsgHandle(i);
            iRet = PMSG_SendPmsgData(pmsgHandle, CLI_SERV_MSG_TYPE_SEND_TEMPORARY_SAVE, acSendBuf, 2);    //发送临时存储命令
            if (iRet <= 0)
            {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] camera %d, no=%d send CLI_SERV_MSG_TYPE_SEND_TEMPORARY_SAVE failed\n", __FUNCTION__, j, 8+j);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d temporary save OK", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+j);
                LOG_WriteLog(&tLogInfo);
//                DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] camera %d, no=%d send CLI_SERV_MSG_TYPE_SEND_TEMPORARY_SAVE Ok\n", __FUNCTION__, j, 8+j);
            }
        }
    }

}
void pvmsMonitorWidget::cameraSwitchSlot()
{
    char acSendBuf[4] = {0};
        int iRet = 0, i = 0;
        int iFlag = 0;
        T_TRAIN_CONFIG tTrainConfigInfo;
        T_LOG_INFO tLogInfo;
        T_CMP_PACKET tPkt;

        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

//        DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget cameraSwitch button pressed!\n");

        if (1 == m_iPollingFlag)
        {
            m_iPollingFlag = 0;   //如果开启了轮询，先将轮询标志置0，保证这一刻不轮询，以免造成m_iCameraPlayNo瞬间变化而导致以下操作针对的相机不匹配
            iFlag = 1;
        }

        if (CAMERA_ON == m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState)
        {
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget close camera!\n");
            QString  strr = QString("%1%2%3").arg("是否关闭").arg(m_iCameraPlayNo+1).arg("号受电弓摄像机?");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("")),QString(strr));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.button(QMessageBox::Yes)->setText("确 定");
            msgBox.button(QMessageBox::No)->setText("取 消");
            iRet=msgBox.exec();
            if(iRet != QMessageBox::Yes)
            {
                return;
            }


            emit chStateLabelTextCtrlSignal(0);  //触发让通道状态标签显示文本的信号
            emit camSwitchButtonTextCtrlSignal(1);  //触发让摄像头开关按钮显示文本的信号

            acSendBuf[0] = 2; //操作类型为关闭摄像头
            m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState = CAMERA_OFF;

            tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;
            tPkt.iCh = m_iCameraPlayNo;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
            cameFlag = 1;
            /*把相机的状态切换成关闭状态时，同时需显示通道状态和通道号*/
            emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号
//            qDebug()<<"********m_iCameraPlayNo**********"<<m_iCameraPlayNo<<__FUNCTION__<<__LINE__<<endl;

        }
        else
        {

            QString  strr = QString("%1%2%3").arg("是否开启").arg(m_iCameraPlayNo+1).arg("号受电弓摄像机?");
            QMessageBox msgBox(QMessageBox::Question,QString(tr("")),QString(strr));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.button(QMessageBox::Yes)->setText("确 定");
            msgBox.button(QMessageBox::No)->setText("取 消");
            iRet=msgBox.exec();
            if(iRet != QMessageBox::Yes)
            {
                return;
            }
//                DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget open camera!\n");
            emit chStateLabelTextCtrlSignal(1);  //触发让通道状态标签显示文本的信号
            emit camSwitchButtonTextCtrlSignal(0);  //触发让摄像头开关按钮显示文本的信号

            acSendBuf[0] = 1;  //操作类型为开启摄像头
            m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState = CAMERA_ON;
            cameFlag = 0;
//            qDebug()<<"********m_iCameraPlayNo**********"<<m_iCameraPlayNo<<__FUNCTION__<<__LINE__<<endl;

            if (0 == m_tCameraInfo[i].iCmpOpenFlag)
            {
                tPkt.iMsgCmd = CMP_CMD_CREATE_CH;
                tPkt.iCh = m_iCameraPlayNo;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);

                tPkt.iMsgCmd = CMP_CMD_ENABLE_CH;
                tPkt.iCh = m_iCameraPlayNo;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);
            }

            emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号
        }

        acSendBuf[1] = this->m_tCameraInfo[m_iCameraPlayNo].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号

        iRet = PMSG_SendPmsgData(this->m_tCameraInfo[m_iCameraPlayNo].phandle, CLI_SERV_MSG_TYPE_PVMS_IPC_CTRL, acSendBuf, 2);    //发送摄像头开关控制命令
        if (iRet < 0)
        {
//                DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_IPC_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, m_iCameraPlayNo);
        }
        else
        {

            for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
            {
                if (m_tCameraInfo[m_iCameraPlayNo].phandle == STATE_GetNvrServerPmsgHandle(i))
                {
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    if (1 == acSendBuf[0])
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "open camera %d.%d stream", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[m_iCameraPlayNo].iPosNO-8);
                    }
                    else
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "close camera %d.%d stream", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[m_iCameraPlayNo].iPosNO-8);
                    }
                    LOG_WriteLog(&tLogInfo);
                    break;
                }
            }

            ui->cameraSwitchPushButton->setEnabled(false);
            if (NULL == m_cameraSwitchTimer)
            {
                m_cameraSwitchTimer = new QTimer(this);
            }
            m_cameraSwitchTimer->start(2*1000);
            connect(m_cameraSwitchTimer,SIGNAL(timeout()), this,SLOT(cameraSwitchEndSlot()));
        }
        if (1 == iFlag)
        {
            m_iPollingFlag = 1;   //如果上面手动将轮询标志清0，这里需要恢复为1
        }
}
void pvmsMonitorWidget::fillLightSwitchSlot()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

//    DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget fillLightSwitch button pressed!\n");


    /*发送开关补光灯的消息给服务器，消息内容为2个字节，第一个字节表示操作类型:开启还是关闭补光灯，第二个字节表示受电弓摄像机位置号*/
    if (FILLLIGHT_ON == m_tCameraInfo[m_iCameraPlayNo].iFillLightSwitchState)
    {
        QString  strr = QString("%1%2%3").arg("是否关闭").arg(m_iCameraPlayNo+1).arg("号受电弓摄像机闪光灯?");
        QMessageBox msgBox(QMessageBox::Question,QString(tr("")),QString(strr));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.button(QMessageBox::Yes)->setText("确 定");
        msgBox.button(QMessageBox::No)->setText("取 消");
        iRet=msgBox.exec();
        if(iRet != QMessageBox::Yes)
        {
            return;
        }


//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget close fillLight!\n");
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号

        acSendBuf[0] = 2;  //操作类型为关闭补光灯
        m_tCameraInfo[m_iCameraPlayNo].iFillLightSwitchState = FILLLIGHT_OFF;
    }
    else
    {
        QString  strr = QString("%1%2%3").arg("是否开启").arg(m_iCameraPlayNo+1).arg("号受电弓摄像机闪光灯?");
        QMessageBox msgBox(QMessageBox::Question,QString(tr("")),QString(strr));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.button(QMessageBox::Yes)->setText("确 定");
        msgBox.button(QMessageBox::No)->setText("取 消");
        iRet=msgBox.exec();
        if(iRet != QMessageBox::Yes)
        {
            return;
        }



//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "pvmsMonitorWidget open fillLight!\n");
        emit fillLightSwitchButtonTextCtrlSignal(0);  //触发让补光灯开关按钮显示文本的信号

        acSendBuf[0] = 1;  //操作类型为开启补光灯
        m_tCameraInfo[m_iCameraPlayNo].iFillLightSwitchState = FILLLIGHT_ON;
    }
    acSendBuf[1] = this->m_tCameraInfo[m_iCameraPlayNo].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
    iRet = PMSG_SendPmsgData(this->m_tCameraInfo[m_iCameraPlayNo].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, m_iCameraPlayNo);
    }
    else
    {
        if (0 == m_tCameraInfo[m_iCameraPlayNo].iManualFillLightCtrlFlag)
        {
            m_tCameraInfo[m_iCameraPlayNo].iManualFillLightCtrlFlag = 1;
        }
        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

        for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
        {
            if (m_tCameraInfo[m_iCameraPlayNo].phandle == STATE_GetNvrServerPmsgHandle(i))
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                if (1 == acSendBuf[0])
                {
                    snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "open camera %d.%d fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[m_iCameraPlayNo].iPosNO-8);
                }
                else
                {
                    snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "close camera %d.%d fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[m_iCameraPlayNo].iPosNO-8);
                }
                LOG_WriteLog(&tLogInfo);
                break;
            }
        }

        ui->fillLightSwitchPushButton->setEnabled(false);
        if (NULL == m_fillLightSwitchTimer)
        {
            m_fillLightSwitchTimer = new QTimer(this);
        }
        m_fillLightSwitchTimer->start(2*1000);
        connect(m_fillLightSwitchTimer,SIGNAL(timeout()), this,SLOT(fillLightSwitchEndSlot()));
    }

}

void pvmsMonitorWidget::fillLightSwitchEndSlot()
{
    ui->fillLightSwitchPushButton->setEnabled(true);

    if (m_fillLightSwitchTimer != NULL)
    {
        if (m_fillLightSwitchTimer->isActive())
        {
            m_fillLightSwitchTimer->stop();
        }
        delete m_fillLightSwitchTimer;
        m_fillLightSwitchTimer = NULL;
    }
}

void pvmsMonitorWidget::closePresetPasswdPageSlot()    //关闭预置点密码确认界面
{
    if(NULL==this->m_presetPasswdConfirmPage)
    {
        return;
    }
    else
    {
        delete this->m_presetPasswdConfirmPage;
    }
    this->m_presetPasswdConfirmPage=NULL;
}
void pvmsMonitorWidget::setPresetSlot()
{

    m_iPresetPasswdOkFlag = 1;

    if(NULL==this->m_presetPasswdConfirmPage)
    {
        return;
    }
    else
    {
        delete this->m_presetPasswdConfirmPage;
    }
    this->m_presetPasswdConfirmPage=NULL;


}

void pvmsMonitorWidget::getChStreamState(int iCh)
{
    if (iCh < 0)
    {
        return;
    }
    pthread_mutex_lock(&g_tCmpCtrlMutex);
//    m_tCameraInfo[iCh].iStreamState = CMP_GetStreamState(m_tCameraInfo[iCh].cmpHandle);     ????????
//     m_tCameraInfo[iCh].iStreamState ;
    pthread_mutex_unlock(&g_tCmpCtrlMutex);
}


void pvmsMonitorWidget::setRecordPlayFlag(int iFlag)
{
    int i = 0;
    T_CMP_PACKET tPkt;

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] set record flag to %d!\n", __FUNCTION__, iFlag);
    m_iRecordPlayFlag = iFlag;

    if (1 == m_iRecordPlayFlag)   //录像回放使禁止实时的所有使能，确保回放能正常打开并使能显示
    {
        for (i = 0; i < m_iCameraNum; i++)
        {

            tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;
            tPkt.iCh = i;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
        }
    }
}

void pvmsMonitorWidget::videoPollingSignalCtrl()
{
    QString ChannelNoStr = tr("通道");
    char acChNo[32] = {0};
    char acSendBuf[4] = {0};
    int i = 0, iLastCamaraNo = 0;
    T_CMP_PACKET tPkt;

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] camera %d Polling Ctrl!\n", __FUNCTION__, m_iCameraPlayNo);

    /*只有全局使能情况下的当前摄像头使能显示，其他摄像头全部禁止显示*/
    for (i = 0; i < m_iCameraNum; i++)
    {
        if(i != m_iCameraPlayNo)
        {
            tPkt.iCh = i;
            tPkt.iMsgCmd = CMP_CMD_DISABLE_CH;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
        }
    }
    for (i = 0; i < m_iCameraNum; i++)
    {
        if ((1 == m_iDisplayEnable) && (i == m_iCameraPlayNo))
        {
            tPkt.iCh = i;
            tPkt.iMsgCmd = CMP_CMD_ENABLE_CH;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
        }
    }

    if (m_iPtzMoveType != E_STOP_MOVE)   //切换相机，检测之前是否有云台控制未停止，检测到了就手动停止
    {
        acSendBuf[0] = E_STOP_MOVE;
        acSendBuf[1] = m_iPtzCtrType;
        iLastCamaraNo = m_iCameraPlayNo-1;
        if (iLastCamaraNo < 0)
        {
            iLastCamaraNo = m_iCameraNum - 1;
        }
        acSendBuf[2] = m_tCameraInfo[iLastCamaraNo].iPosNO;      //发送消息的第3个字节表示受电弓摄像机位置号
        PMSG_SendPmsgData(m_tCameraInfo[iLastCamaraNo].phandle, CLI_SERV_MSG_TYPE_SET_PTZ, acSendBuf, 3);    //发送云台控制命令

        m_iPtzMoveType = E_STOP_MOVE;
    }

    /*设置对应预置点按钮为按下样式*/
    for (i = 1; i <= 8; i++)
    {
        if (i == m_tCameraInfo[m_iCameraPlayNo].iPresetNo)
        {
            m_presetNoPushbutton[i-1]->setChecked(true);
        }
    }
    m_iSelectPresetNo = m_tCameraInfo[m_iCameraPlayNo].iPresetNo;

    snprintf(acChNo, sizeof(acChNo), "%d", m_iCameraPlayNo + 1);
    ChannelNoStr += QString(QLatin1String(acChNo));
    m_channelNoLabel->setText(ChannelNoStr);

    /*检测当前摄像头码流状态(是否有码流)，状态为1(有流)则需要隐藏通道状态和通道号，否则需要显示*/
    emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号

    if (CAMERA_ON == m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState)
    {
        emit chStateLabelTextCtrlSignal(1);  //触发让通道状态标签显示文本的信号
        emit camSwitchButtonTextCtrlSignal(0);  //触发让摄像头开关按钮显示文本的信号
    }
    else
    {
        emit chStateLabelTextCtrlSignal(0);  //触发让通道状态标签显示文本的信号
        emit camSwitchButtonTextCtrlSignal(1);  //触发让摄像头开关按钮显示文本的信号
    }

    if (FILLLIGHT_ON == m_tCameraInfo[m_iCameraPlayNo].iFillLightSwitchState)
    {
        emit fillLightSwitchButtonTextCtrlSignal(0);  //触发让补光灯开关按钮显示文本的信号
    }
    else
    {
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号
    }

    if (m_presetPasswdConfirmPage != NULL)    //摄像头切换了，如果弹出了预置点密码确认界面，则关闭，避免出现跨云台设置预置点的问题
    {
        delete m_presetPasswdConfirmPage;
        m_presetPasswdConfirmPage = NULL;
    }

    if (this->isHidden() != 1)
    {
    }

    videoChannelCtrl();   //通道视频开关处理
}

void pvmsMonitorWidget::setFullScreenSignalCtrl()
{
    T_CMP_PACKET tPkt;
//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] fullScreen Ctrl!\n", __FUNCTION__);
    if ((this->isHidden() != 1)  && (m_iAlarmNotCtrlFlag != 1) && (m_iBlackScreenFlag != 1))    //当前未显示，不做全屏监视处理,有报警信息未处理也不做全屏监视处理,处于黑屏状态也不做全屏监视处理
    {
#ifdef mplaybin
        m_playWin->move(0, 0);
        m_playWin->resize(1024, 768);
#endif

        tPkt.iMsgCmd = CMP_CMD_CHG_ALL_VIDEOWIN;
        tPkt.iCh = 0;
        PutNodeToCmpQueue(m_ptQueue, &tPkt);

        m_channelStateLabel->setGeometry(452, 230, 130, 50);
        m_channelNoLabel->setGeometry(20, 550, 100, 50);
        if (m_presetPasswdConfirmPage != NULL)
        {
            m_presetPasswdConfirmPage->hide();

        }
        emit hideAlarmWidgetSignal();
        m_iFullScreenFlag = 1;
    }

}

void pvmsMonitorWidget::presetReturnSignalCtrl(int iCameraNO)
{
    char acSendBuf[4] = {0};
    int iRet = 0;

//    DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] camera %d presetReturn Ctrl!\n", __FUNCTION__, iCameraNO);

    /*发送调用预置点1的消息给服务器，消息内容为3个字节，第一个字节表示控制类型:设置还是调用预置点，第二个字节表示预置点号，第三个字节表示受电弓摄像机位置号*/
    acSendBuf[0] = E_PRESET_GET;
    acSendBuf[1] = 1;
    acSendBuf[2] = m_tCameraInfo[iCameraNO].iPosNO;
    iRet = PMSG_SendPmsgData(m_tCameraInfo[iCameraNO].phandle, CLI_SERV_MSG_TYPE_SET_PRESETS, acSendBuf, 3);    //发送预置点控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_SET_PRESETS prestNo 1 error!iRet=%d!cameraNo=%d\n", __FUNCTION__, iRet, iCameraNO);
    }
    else
    {
        m_tCameraInfo[iCameraNO].iPresetNo = 1;
        m_iSelectPresetNo = 1;
    }
}
void pvmsMonitorWidget::noPollingChOption()
{
    static int iDecOldState = 0;
    T_CMP_PACKET tPkt;
    /*非轮询状态下也要实时监控摄像头码流状态的，如果有变换需进行通道状态和通道号的处理，如果状态变成1(有流)则需要隐藏通道状态和通道号，变成0需要显示*/
    if ((1 == m_iDisplayEnable) && (CAMERA_ON == m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState))
    {

        tPkt.iMsgCmd = CMP_CMD_GET_STREAM_STATE;
        tPkt.iCh = m_iCameraPlayNo;
        PutNodeToCmpQueue(m_ptQueue, &tPkt);

        getChStreamState(m_iCameraPlayNo);

        if (iDecOldState != m_tCameraInfo[m_iCameraPlayNo].iStreamState)
        {
            emit chLabelDisplayCtrlSignal();  //触发通道状态和通道号标签显示处理信号
            iDecOldState = m_tCameraInfo[m_iCameraPlayNo].iStreamState;
        }
    }
//    qDebug()<<"********m_iCameraPlayNo**********"<<m_iCameraPlayNo<<__FUNCTION__<<__LINE__<<endl;


}
void pvmsMonitorWidget::triggerCmpOptionCtrlSinal(int iType, int iCh)
{
    emit cmpOptionCtrlSignal(iType, iCh);
}

void pvmsMonitorWidget::triggerVideoPollingSignal()
{
    emit videoPollingSignal();
}

void pvmsMonitorWidget::triggerFullScreenSignal()
{
    emit setFullScreenSignal();
}

void pvmsMonitorWidget::triggerPresetReturnSignal(int iCameraNO)
{
    emit presetReturnSignal(iCameraNO);
}

void pvmsMonitorWidget::triggerGetDevStateSignal()
{
    emit getDevStateSignal();
}

void pvmsMonitorWidget::triggerSetTimeSignal()
{
    emit setTimeSignal();
}

void pvmsMonitorWidget::triggerRecordPlayCtrlSignal()
{
    emit recordPlayCtrlSignal();
}

void pvmsMonitorWidget::setPlayButtonStyleSheet()
{
    if(m_iPollingFlag == 1)
    {
        ui->startPollingPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/start1.bmp);background-color: rgb(255, 255, 255);}"
                                                  /*"QPushButton:pressed{border-image: url(:/monres/start.bmp);background-color: rgb(255, 255, 255);}"*/);

        ui->pausePollingPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/pause.bmp);background-color: rgb(255, 255, 255);}"
                                                  /*"QPushButton:pressed{border-image: url(:/monres/pause1.bmp);background-color: rgb(255, 255, 255);}"*/);
    }
    else
    {
        ui->startPollingPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/start.bmp);background-color: rgb(255, 255, 255);}"
                                                  /*"QPushButton:pressed{border-image: url(:/monres/start.bmp);background-color: rgb(255, 255, 255);}"*/);

        ui->pausePollingPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/pause1.bmp);background-color: rgb(255, 255, 255);}"
                                                  /*"QPushButton:pressed{border-image: url(:/monres/pause1.bmp);background-color: rgb(255, 255, 255);}"*/);

    }


}


void pvmsMonitorWidget::recordPlayCtrlSlot()
{
    videoChannelCtrl();   //通道视频开关处理
}

void pvmsMonitorWidget::cmpOptionCtrlSlot(int iType, int iCh)
{
//    int iRet = 0, i = 0;
    char rtspStr[128]={0};
    QStringList list;

//    CMPHandle cmpHandle = NULL;

    if (iCh > (MAX_SERVER_NUM*MAX_CAMERA_OFSERVER - 1))
    {
        return;
    }
    if (CMP_CMD_CREATE_CH == iType)
    {
        sprintf(rtspStr,"%s",m_tCameraInfo[iCh].acCameraRtspUrl);
        list<<rtspStr;

//        qDebug()<<"******open*******"<<m_tCameraInfo[iCh].acCameraRtspUrl<<"ich="<<iCh<<endl;
        openMedia(rtspStr,list,iCh);

        m_tCameraInfo[iCh].iCmpOpenFlag = 1;

    }
    else if (CMP_CMD_DESTORY_CH == iType)
    {
        sprintf(rtspStr,"%s",m_tCameraInfo[iCh].acCameraRtspUrl);
        list<<rtspStr;
//        if(1 == cameFlag)
        {
//        closeMedia(rtspStr,list,iCh);
//            qDebug()<<"******close*******"<<m_tCameraInfo[iCh].acCameraRtspUrl<<"ich="<<iCh<<endl;

        }
        m_tCameraInfo[iCh].iCmpOpenFlag = 0;

    }
    else if(CMP_CMD_ENABLE_CH == iType)
    {

        showMedia(iCh);
    }
    else if(CMP_CMD_DISABLE_CH == iType)
    {

        hideMedia(iCh);

    }
}

void pvmsMonitorWidget::chLabelDisplayCtrlSlot()   //通道状态和通道号标签是否显示的处理函数
{
#if 1
    T_CMP_PACKET tPkt;

    if (1 == m_iDisplayEnable)
    {

        tPkt.iMsgCmd = CMP_CMD_GET_STREAM_STATE;
        tPkt.iCh = m_iCameraPlayNo;
        PutNodeToCmpQueue(m_ptQueue, &tPkt);

        getChStreamState(m_iCameraPlayNo);

        if (1 == m_tCameraInfo[m_iCameraPlayNo].iStreamState)
        {
            if (CAMERA_ON == m_tCameraInfo[m_iCameraPlayNo].iCameraSwitchState)   //状态为1时需要进一步判断相机状态，来决定是否需要显示通道状态和通道号,相机状态为开启时隐藏，否则显示
            {
                m_channelStateLabel->hide();
                m_channelNoLabel->hide();
            }
            else
            {
                if(pageType == PageMonitot || pageType == PageNone)
                {
                    m_channelStateLabel->show();
                    m_channelNoLabel->show();
                }
            }
        }
        else
        {
            if(pageType == PageMonitot || pageType == PageNone)
            {
                m_channelStateLabel->show();
                m_channelNoLabel->show();
            }
        }
    }
    else  		//播放窗体全部禁止时，通道状态和通道号也需同时隐藏
    {
        m_channelStateLabel->hide();
        m_channelNoLabel->hide();
    }
//    qDebug()<<"********m_iCameraPlayNo**********"<<m_iCameraPlayNo<<__FUNCTION__<<__LINE__<<endl;

#endif
}

void pvmsMonitorWidget::chStateLabelTextCtrlSlot(int iFlag)   //通道状态标签文本显示的处理函数，0-显示关闭，1-显示开启
{
    if (0 == iFlag)
    {
        m_channelStateLabel->setText(tr("摄像头关闭"));
    }
    else
    {
        m_channelStateLabel->setText(tr("摄像头开启"));
    }
}

void pvmsMonitorWidget::camSwitchButtonTextCtrlSlot(int iFlag)   //摄像机开关状态按钮文本显示的处理函数，0-显示关闭，1-显示开启
{
    if (0 == iFlag)
    {
        ui->cameraSwitchPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/cameraoff.bmp);background-color: rgb(255, 255, 255);}");
        ui->cameraSwitchPushButton->setChecked(true);
    }
    else
    {
        ui->cameraSwitchPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/cameraon.bmp);background-color: rgb(255, 255, 255);}");
        ui->cameraSwitchPushButton->setChecked(false);
    }
}

void pvmsMonitorWidget::fillLightSwitchButtonTextCtrlSlot(int iFlag)  //补光灯开关状态按钮文本显示的处理函数，0-显示关闭，1-显示开启
{
    if (0 == iFlag)
    {
        ui->fillLightSwitchPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/lighton.bmp);background-color: rgb(255, 255, 255);}");
        ui->fillLightSwitchPushButton->setChecked(true);
    }
    else
    {
        ui->fillLightSwitchPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/ligtoff.bmp);background-color: rgb(255, 255, 255);}");
        ui->fillLightSwitchPushButton->setChecked(false);
    }
}


void pvmsMonitorWidget::videoChannelCtrl()
{
    int i = 0, iLastCamaraNo = 0, iNextCamaraNo = 0;
    T_CMP_PACKET tPkt;

    /*根据是否在回放来决定打开那些相机的流。如果在回放，则只打开当前相机的流。如果没有在回放，则打开当前以及上一个和下一个三个相机的流*/
    iLastCamaraNo = m_iCameraPlayNo-1;
    if (iLastCamaraNo < 0)
    {
        iLastCamaraNo = m_iCameraNum - 1;
    }
    iNextCamaraNo = m_iCameraPlayNo+1;
    if (iNextCamaraNo > (m_iCameraNum-1))
    {
        iNextCamaraNo = 0;
    }
    for (i = 0; i < m_iCameraNum; i++)
    {
        if (1 == m_iRecordPlayFlag)
        {
            if (i == m_iCameraPlayNo)
            {
                if (0 == m_tCameraInfo[i].iCmpOpenFlag)
                {
                    tPkt.iMsgCmd = CMP_CMD_CREATE_CH;
                    tPkt.iCh = i;
                    PutNodeToCmpQueue(m_ptQueue, &tPkt);
                }
                else
                {
                    tPkt.iMsgCmd = CMP_CMD_DISABLE_CH;
                    tPkt.iCh = i;
                    PutNodeToCmpQueue(m_ptQueue, &tPkt);  //保证回放时当前实时通道也不使能，确保不存在回放和实时同时使能的情况
                }
            }
            else
            {
                if (1 == m_tCameraInfo[i].iCmpOpenFlag)
                {
                    tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;
                    tPkt.iCh = i;
                    PutNodeToCmpQueue(m_ptQueue, &tPkt);
                }
            }
        }
        else
        {

            if ((i == m_iCameraPlayNo) || (i == iLastCamaraNo) || (i == iNextCamaraNo))
            {
//                qDebug()<<"11111111111--i="<<i<<"*****m_tCameraInfo[i].iCmpOpenFlag******"<<m_tCameraInfo[i].iCmpOpenFlag<<endl;
                if (0 == m_tCameraInfo[i].iCmpOpenFlag)
                {
                    tPkt.iMsgCmd = CMP_CMD_CREATE_CH;
                    tPkt.iCh = i;
                    PutNodeToCmpQueue(m_ptQueue, &tPkt);
                }

            }
            else
            {
//                qDebug()<<"2222222222--i="<<i<<"***m_tCameraInfo[i].iCmpOpenFlag****"<<m_tCameraInfo[i].iCmpOpenFlag<<endl;
                if (1 == m_tCameraInfo[i].iCmpOpenFlag)
                {
                    tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;
                    tPkt.iCh = i;
                    PutNodeToCmpQueue(m_ptQueue, &tPkt);
                }
            }
        }
    }
//    qDebug()<<"********m_iCameraPlayNo**********"<<m_iCameraPlayNo<<__FUNCTION__<<__LINE__<<endl;
}


void pvmsMonitorWidget::closePlayWin()
{
    T_CMP_PACKET tPkt;


    if (m_threadId != 0)
    {
        m_iThreadRunFlag = 0;
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] monitor thread join begin !\n", __FUNCTION__);
        pthread_join(m_threadId, NULL);
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] monitor thread join end !\n", __FUNCTION__);
        m_threadId = 0;
    }

    for (int i = 0; i < m_iCameraNum; i++)
    {
        if (1 == m_tCameraInfo[i].iCmpOpenFlag)
        {
            tPkt.iMsgCmd = CMP_CMD_DESTORY_CH;
            tPkt.iCh = i;
            PutNodeToCmpQueue(m_ptQueue, &tPkt);
        }
    }
    m_iCameraNum = 0;

    if (m_channelStateLabel != NULL)
    {
        delete m_channelStateLabel;
        m_channelStateLabel = NULL;
    }
    if (m_channelNoLabel != NULL)
    {
        delete m_channelNoLabel;
        m_channelNoLabel = NULL;
    }
#ifdef mplaybin
    if (m_playWin != NULL)
    {
        delete m_playWin;
        m_playWin = NULL;
    }
#endif
}

void pvmsMonitorWidget::alarmHappenSlot()
{
    T_CMP_PACKET tPkt;
#ifdef mplaybin
    if ((1 == m_iFullScreenFlag) && (m_playWin != NULL))  //有报警发生时退出全屏
#else
    if ((1 == m_iFullScreenFlag) /*&& (m_playWin != NULL)*/)  //有报警发生时退出全屏
#endif
    {
        struct sysinfo s_info;
        sysinfo(&s_info);
        m_lastActionTime = s_info.uptime;  //更新最后一次操作计时
#ifdef mplaybin
        m_playWin->move(0, 138);
        m_playWin->resize(782, 630);
#endif
        m_iFullScreenFlag = 0;

        tPkt.iMsgCmd = CMP_CMD_CHG_ALL_VIDEOWIN;
        tPkt.iCh = 0;
        PutNodeToCmpQueue(m_ptQueue, &tPkt);

        if (m_channelStateLabel != NULL)
        {
            m_channelStateLabel->setGeometry(320, 385, 121, 50);
        }
        if (m_channelNoLabel != NULL)
        {
            m_channelNoLabel->setGeometry(20, 690, 100, 50);
        }

//        if (m_presetPasswdConfirmPage != NULL)
//        {
//            m_presetPasswdConfirmPage->show();
//            if ((m_presetPasswdConfirmPage->p_ipmethod != NULL) && (m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget != NULL))
//            {
//                m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget->show();
//            }
 //       }
    }

    m_iAlarmNotCtrlFlag = 1;

    /*当报警触发时，启动一个定时器，每500ms刷新一下报警按钮的背景色，以达到报警按钮闪烁的效果*/
    if (NULL == m_alarmHappenTimer)
    {
        m_alarmHappenTimer = new QTimer(this);
        connect(m_alarmHappenTimer,SIGNAL(timeout()), this,SLOT(alarmHappenCtrlSlot()));
        m_alarmHappenTimer->start(500);
    }

}
void pvmsMonitorWidget::alarmHappenCtrlSlot()
{
    if (this->isHidden() != 1)
    {
        if (0 == g_iPNum%2)
        {
            ui->alarmPushButton->setChecked(true);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alerton.bmp);background-color: rgb(255, 255, 255);}");

        }
        else
        {
            ui->alarmPushButton->setChecked(false);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");
        }
        g_iPNum++;
    }
}
void pvmsMonitorWidget::alarmClearSlot()
{
    /*删除样式刷新定时器，并恢复报警按钮样式为正常样式*/
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);
    ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");

    m_iAlarmNotCtrlFlag = 0;
    g_iPNum = 0;
}

bool pvmsMonitorWidget::eventFilter(QObject *target, QEvent *event)    //事件过滤器，过滤处理不同控件的不同事件
{

    int iRet = 0;
    T_CMP_PACKET tPkt;
    if (event->type()==QEvent::MouseButtonPress || event->type()==QEvent::MouseMove) //判断界面操作
    {
            //DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] a mousemove or movebuttonpress or a keypress is checked!\n", __FUNCTION__);
            if (event->type()==QEvent::MouseMove)
            {
                QMouseEvent *mEvent = (QMouseEvent *)event;

                if ((m_iMousePosX != mEvent->globalPos().x()) || (m_iMousePosY != mEvent->globalPos().y()))    //防止实际没动鼠标而系统生成了mouseMove事件
                {
                    m_iMousePosX = mEvent->globalPos().x();
                    m_iMousePosY = mEvent->globalPos().y();
                }
                else
                {
                    return true;
                }
            }

            struct sysinfo s_info;
            sysinfo(&s_info);
            m_lastActionTime = s_info.uptime;  //更新最后一次操作计时  //更新最后一次操作计时

            /*当播放窗体处于全屏状态时，再次单击退出全屏,全屏标志清0，并恢复播放窗体原始播放状态*/
#ifdef mplaybin
            if ((1 == m_iFullScreenFlag) && (target == m_playWin) && (event->type()==QEvent::MouseButtonPress))
#else
            if ((1 == m_iFullScreenFlag) /*&& (target == m_playWin)*/ && (event->type()==QEvent::MouseButtonPress))
#endif
            {
//                DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget quit full screen!\n");
                QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
                if(mouseEvent->button()==Qt::RightButton)    //只响应鼠标左击
                {
                    return true;
                }

                m_iFullScreenFlag = 0;
#ifdef mplaybin
                m_playWin->move(0, 138);
                m_playWin->resize(782, 630);
#endif


                tPkt.iMsgCmd = CMP_CMD_CHG_ALL_VIDEOWIN;
                tPkt.iCh = 0;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);

                m_channelStateLabel->setGeometry(320, 385, 130, 50);
                m_channelNoLabel->setGeometry(20, 550, 100, 50);
//                if (m_presetPasswdConfirmPage != NULL)
//                {
//                    m_presetPasswdConfirmPage->show();
//                    if ((m_presetPasswdConfirmPage->p_ipmethod != NULL) && (m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget != NULL))
//                    {
//                        m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget->show();
//                    }
//                }
                emit showAlarmWidgetSignal();
            }
    }
#ifdef mplaybin
    if (target == m_playWin)
#endif
    {
        if (event->type()==QEvent::MouseButtonDblClick && (m_iAlarmNotCtrlFlag != 1))   //双击全屏,但是如何有报警未处理也不全屏
        {
            if (0 == m_iFullScreenFlag)
            {
//                DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget mouse double click to full screen!\n");
#ifdef mplaybin
                m_playWin->move(0, 0);
                m_playWin->resize(1024, 768);
#endif
                tPkt.iMsgCmd = CMP_CMD_CHG_ALL_VIDEOWIN;
                tPkt.iCh = 0;
                PutNodeToCmpQueue(m_ptQueue, &tPkt);

                m_channelStateLabel->setGeometry(452, 360, 130, 50);
                m_channelNoLabel->setGeometry(20, 690, 100, 50);

//                if (m_presetPasswdConfirmPage != NULL)
//                {
//                    m_presetPasswdConfirmPage->hide();
//                    if ((m_presetPasswdConfirmPage->p_ipmethod != NULL) && (m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget != NULL))
//                    {
//                        m_presetPasswdConfirmPage->p_ipmethod->p_inputwidget->hide();
//                    }
//               }
                m_iFullScreenFlag = 1;
            }
        }
    }
    if ((target == ui->ptzUpPushButton) || (target == ui->ptzDownPushButton) || (target == ui->ptzLeftPushButton) ||
        (target == ui->ptzRightPushButton) || (target == ui->zoomInPushButton) || (target == ui->zoomOutPushButton) ||
        (target == ui->focusFarPushButton) || (target == ui->focusNearPushButton))     //云台控制类按钮事件触发，发送云台控制消息到服务器
    {
        /*发送云台控制的消息给服务器，消息内容为3个字节:
          第一个字节表示控制类型（云台上：01；云台下：02；云台左：03；云台右：04；调焦伸：05；调焦缩：06；聚焦远：07；聚焦近：08），
          第二个字节表示移动类型（开始移动：01；停止移动：02），
          第三个字节表示受电弓摄像机位置号
        */
        if (m_iCameraPlayNo < 0)
        {
            return 0;
        }
        T_PTZ_OPT t_ptzOption;
        memset(&t_ptzOption, 0, sizeof(T_PTZ_OPT));
        char acSendBuf[4] = {0};

        if (event->type()==QEvent::MouseButtonPress)     //按钮按下，i8MoveType移动类型值置1，表示开始移动
        {
            t_ptzOption.i8MoveType = E_START_MOVE;
        }
        else if (event->type()==QEvent::MouseButtonRelease)    //按钮松开，i8MoveType移动类型值置2，表示停止移动
        {
            t_ptzOption.i8MoveType = E_STOP_MOVE;
        }
        else
        {
            return 0;
        }
        /*根据操作的按键不同设置不同的控制命令*/
        if (target == ui->ptzUpPushButton)
        {
            t_ptzOption.i8CtrlType = E_PTZ_UP;
        }
        else if (target == ui->ptzDownPushButton)
        {
            t_ptzOption.i8CtrlType = E_PTZ_DOWN;
        }
        else if (target == ui->ptzLeftPushButton)
        {
            t_ptzOption.i8CtrlType = E_PTZ_LEFT;
        }
        else if (target == ui->ptzRightPushButton)
        {
            t_ptzOption.i8CtrlType = E_PTZ_RIGHT;
        }
        else if (target == ui->zoomInPushButton)
        {
            t_ptzOption.i8CtrlType = E_ZOOM_OUT;
        }
        else if (target == ui->zoomOutPushButton)
        {
            t_ptzOption.i8CtrlType = E_ZOOM_IN;
        }
        else if (target == ui->focusFarPushButton)
        {
            t_ptzOption.i8CtrlType = E_FOCUS_FAR;
        }
        else if (target == ui->focusNearPushButton)
        {
            t_ptzOption.i8CtrlType = E_FOCUS_NEAR;
        }
        acSendBuf[0] = t_ptzOption.i8CtrlType;
        acSendBuf[1] = t_ptzOption.i8MoveType;
        acSendBuf[2] = this->m_tCameraInfo[m_iCameraPlayNo].iPosNO;      //发送消息的第3个字节表示受电弓摄像机位置号

//        DebugPrint(DEBUG_UI_OPTION_PRINT, "pvmsMonitorWidget ptz option, CtrlType=%d, MoveType=%d, camera no=%d!\n",t_ptzOption.i8CtrlType, t_ptzOption.i8MoveType, m_iCameraPlayNo);
        iRet = PMSG_SendPmsgData(this->m_tCameraInfo[m_iCameraPlayNo].phandle, CLI_SERV_MSG_TYPE_SET_PTZ, acSendBuf, 3);    //发送云台控制命令
        if (iRet < 0)
        {
//            DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] camera %d send CLI_SERV_MSG_TYPE_SET_PTZ failed,iRet=%d\n", __FUNCTION__, m_iCameraPlayNo, iRet);
        }
        else
        {
            struct sysinfo s_info;
            memset(&s_info,0,sizeof(s_info));
            sysinfo(&s_info);
            m_tCameraInfo[m_iCameraPlayNo].tPtzOprateTime = s_info.uptime;
            m_tCameraInfo[m_iCameraPlayNo].iPresetNo = 0;   //云台控制成功，将预置点编号清空
            m_iPtzCtrType = t_ptzOption.i8CtrlType;
            m_iPtzMoveType = t_ptzOption.i8MoveType;
        }
    }

    return QWidget::eventFilter(target, event);


}
void pvmsMonitorWidget::pvmsDownEndSlot1()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

    if ((0 == m_iPollingFlag) && (0 == m_iCameraPlayNo))   //轮询暂停时，要根据当前相机的补光灯状态来手动刷新按钮样式，正常轮询不需要在这里手动刷新
    {
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号
    }

    acSendBuf[0] = 2;  //操作类型为关闭补光灯
    acSendBuf[1] = m_tCameraInfo[0].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
    iRet = PMSG_SendPmsgData(m_tCameraInfo[0].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, 0);
    }
    else
    {
        m_tCameraInfo[0].iManualFillLightCtrlFlag = 0;
        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

        for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
        {
            if (m_tCameraInfo[0].phandle == STATE_GetNvrServerPmsgHandle(i))
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "get camera %d.%d pvms down signal, close fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[0].iPosNO-8);
                LOG_WriteLog(&tLogInfo);
                break;
            }
        }
    }
    m_tCameraInfo[0].iFillLightSwitchState = FILLLIGHT_OFF;

    if (m_tCameraInfo[0].pvmsDownMonitorTimer != NULL)
    {
        if (m_tCameraInfo[0].pvmsDownMonitorTimer ->isActive())
        {
            m_tCameraInfo[0].pvmsDownMonitorTimer ->stop();
        }
        delete m_tCameraInfo[0].pvmsDownMonitorTimer ;
        m_tCameraInfo[0].pvmsDownMonitorTimer  = NULL;
    }
}

void pvmsMonitorWidget::pvmsDownEndSlot2()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

    if ((0 == m_iPollingFlag) && (1 == m_iCameraPlayNo))   //轮询暂停时，要根据当前相机的补光灯状态来手动刷新按钮样式，正常轮询不需要在这里手动刷新
    {
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号
    }

    acSendBuf[0] = 2;  //操作类型为关闭补光灯
    acSendBuf[1] = m_tCameraInfo[1].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
    iRet = PMSG_SendPmsgData(m_tCameraInfo[1].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, 1);
    }
    else
    {
        m_tCameraInfo[1].iManualFillLightCtrlFlag = 0;
        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

        for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
        {
            if (m_tCameraInfo[1].phandle == STATE_GetNvrServerPmsgHandle(i))
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "get camera %d.%d pvms down signal, close fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[1].iPosNO-8);
                LOG_WriteLog(&tLogInfo);
                break;
            }
        }
    }
    m_tCameraInfo[1].iFillLightSwitchState = FILLLIGHT_OFF;

    if (m_tCameraInfo[1].pvmsDownMonitorTimer != NULL)
    {
        if (m_tCameraInfo[1].pvmsDownMonitorTimer ->isActive())
        {
            m_tCameraInfo[1].pvmsDownMonitorTimer ->stop();
        }
        delete m_tCameraInfo[1].pvmsDownMonitorTimer ;
        m_tCameraInfo[1].pvmsDownMonitorTimer  = NULL;
    }
}

void pvmsMonitorWidget::pvmsDownEndSlot3()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

    if ((0 == m_iPollingFlag) && (2 == m_iCameraPlayNo))   //轮询暂停时，要根据当前相机的补光灯状态来手动刷新按钮样式，正常轮询不需要在这里手动刷新
    {
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号
    }

    acSendBuf[0] = 2;  //操作类型为关闭补光灯
    acSendBuf[1] = m_tCameraInfo[2].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
    iRet = PMSG_SendPmsgData(m_tCameraInfo[2].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, 2);
    }
    else
    {
        m_tCameraInfo[2].iManualFillLightCtrlFlag = 0;
        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

        for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
        {
            if (m_tCameraInfo[2].phandle == STATE_GetNvrServerPmsgHandle(i))
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "get camera %d.%d pvms down signal, close fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[2].iPosNO-8);
                LOG_WriteLog(&tLogInfo);
                break;
            }
        }
    }
    m_tCameraInfo[2].iFillLightSwitchState = FILLLIGHT_OFF;

    if (m_tCameraInfo[2].pvmsDownMonitorTimer != NULL)
    {
        if (m_tCameraInfo[2].pvmsDownMonitorTimer ->isActive())
        {
            m_tCameraInfo[2].pvmsDownMonitorTimer ->stop();
        }
        delete m_tCameraInfo[2].pvmsDownMonitorTimer ;
        m_tCameraInfo[2].pvmsDownMonitorTimer  = NULL;
    }
}

void pvmsMonitorWidget::pvmsDownEndSlot4()
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;

    if ((0 == m_iPollingFlag) && (3 == m_iCameraPlayNo))   //轮询暂停时，要根据当前相机的补光灯状态来手动刷新按钮样式，正常轮询不需要在这里手动刷新
    {
        emit fillLightSwitchButtonTextCtrlSignal(1);  //触发让补光灯开关按钮显示文本的信号
    }

    acSendBuf[0] = 2;  //操作类型为关闭补光灯
    acSendBuf[1] = m_tCameraInfo[3].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
    iRet = PMSG_SendPmsgData(m_tCameraInfo[3].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
    if (iRet < 0)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, 3);
    }
    else
    {
        m_tCameraInfo[3].iManualFillLightCtrlFlag = 0;
        memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
        STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

        for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
        {
            if (m_tCameraInfo[3].phandle == STATE_GetNvrServerPmsgHandle(i))
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "get camera %d.%d pvms down signal, close fillLight", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO, 200+m_tCameraInfo[3].iPosNO-8);
                LOG_WriteLog(&tLogInfo);
                break;
            }
        }
    }
    m_tCameraInfo[3].iFillLightSwitchState = FILLLIGHT_OFF;

    if (m_tCameraInfo[3].pvmsDownMonitorTimer != NULL)
    {
        if (m_tCameraInfo[3].pvmsDownMonitorTimer ->isActive())
        {
            m_tCameraInfo[3].pvmsDownMonitorTimer ->stop();
        }
        delete m_tCameraInfo[3].pvmsDownMonitorTimer ;
        m_tCameraInfo[3].pvmsDownMonitorTimer  = NULL;
    }
}
void pvmsMonitorWidget::createMedia()
{

#if 1
//    char rtspStr[256];
    int i = 0, j = 0;
    int num = 0;
    mlist<<"rtsp://192.168.104.200"<<"rtsp://192.168.104.200"<<"rtsp://admin:admin123@192.168.104.201"<<"rtsp://admin:admin123@192.168.104.201";

//    if(mlist.count() > 0){
//        num = qSqrt(mlist.count());
//        if(qreal(num) < qSqrt(mlist.count())){
//            num++;
//        }
//    }
//    for(i=0; i<num; i++){
//        QHBoxLayout *layout = new QHBoxLayout;
//        hLayoutList->append(layout);
//    }
  
//    mainLayout->setMargin(0);
//    mainLayout->setSpacing(0);
    for(int i=0; i <mlist.count(); i++)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QMediaPlayer *player = new QMediaPlayer(this, QMediaPlayer::LowLatency);
        playerlist->append(player);
        QVideoWidget *video = new QVideoWidget();
        videoList->append(video);
        QMediaPlaylist *playlist = new QMediaPlaylist(this);
        multiPlayList->append(playlist);
        QString str = mlist.at(i);
        QFile f(mlist.at(i));

        QUrl u(str);
        if(f.exists()){
            playlist->addMedia(QUrl::fromLocalFile(str));
        }else if(u.isValid()){
            playlist->addMedia(u);
        }
        playlist->setCurrentIndex(1);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playlist);

        mainLayout->addWidget(video);
        player->setVideoOutput(video);
        //player->play();
		video->show();

        player->stop();
        player->play();
		playwidget = new QWidget(this);
		playwidget->setGeometry(0, 0, 782, 630);
		playwidget->show();  //默认显示
        playwidget->setLayout(mainLayout);
        m_lstPlayWidget.append(playwidget);
		//    playwidget->setObjectName("m_playWin");
		playwidget->setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");     //设置播放窗口背景色为黑色
        qDebug()<<"*******************mainLayout addWidget"<<"******i:***"<<"index="<<i<<endl;
    }
   

#endif

}
void pvmsMonitorWidget::showMedia(int ch)
{
    QVideoWidget *pLocalVideo = videoList->value(ch);
    QMediaPlayer *pLocalplayer = playerlist->value(ch);
	QWidget		 *pLocalWidget = m_lstPlayWidget.value(ch);
    for(int i=0;i<4;i++)
    {
        if(ch!=i)
        {
            m_lstPlayWidget.value(i)->hide();
        }

    }

    if(  pLocalplayer){
        auto playStatue = pLocalplayer->state();
       //pLocalplayer->stop();
//         pLocalVideo->hide();
        pLocalWidget->show();
        pLocalVideo->show();
        //pLocalVideo->show();
        pLocalplayer->setVideoOutput(pLocalVideo);
        //pLocalplayer->play();
        QHBoxLayout *pLayout =hLayoutList->value(ch);
        bool bShow = m_lstPlayWidget.value(ch)->isVisible();
        if(bShow)
        {
             qDebug()<<"state:"<<pLocalplayer->state()<<"show-media1111**************ich="<<ch<<"video show rect:"<<m_lstPlayWidget.value(ch)->rect()\
                    <<"pLayout:"<<pLayout<<"videorect:"<<pLocalVideo->rect()<<"video----"<<pLocalVideo<<endl;
        }
        qDebug()<<"show-media**************ich="<<ch<<"parent widget is show:"<<bShow<<"playStatue:"<<playStatue<<endl;

    }

    m_lstPlayWidget.value(ch)->show();

    for(int i=0;i<4;i++)
    {
        bool bParentShow = m_lstPlayWidget.value(i)->isVisible();
        QWidget *video = m_lstPlayWidget.value(i);
        qDebug()<<"show-media**************ich="<<i<<"video bParentShow show :"<<bParentShow<<"video  show :"<<video->isVisible()<<endl;
    }
}
void pvmsMonitorWidget::hideMedia(int ch)
{
   QMediaPlayer *pLocalmplayer = playerlist->value(ch);
   auto *pLocalWidget = m_lstPlayWidget.value(ch);
    QVideoWidget *pLocalVideo = videoList->value(ch);
    if( pLocalmplayer){
        pLocalWidget->hide();
         pLocalVideo->show();
        qDebug()<<"hide-media**************ich="<<ch<<endl;
       }

}

int pvmsMonitorWidget::openMedia(const char *pcRtspFile,QStringList list,int ch)
{
#ifdef mplaybin
    player.stop();
    const QString str = QString::fromUtf8(pcRtspFile);
//    qDebug()<<"*******************play---mlist"<<pcRtspFile<<"******i***"<<"ich="<<ch<<endl;
    player.setVideoOutput(m_playWin);
    QUrl url(str);
    player.setMedia(url);
    player.setMuted(true);
    player.play();
#else
    qDebug()<<"*******************play---mlist"<<"******i***"<<"ich="<<ch<<endl;

///*    for(int i=0; i<mlist.count(); i++)*/{
//        video = videoList->value(ch);
//        mplayer = playerlist->value(ch);
//        if(video && mplayer){
//            mplayer->setVideoOutput(video);
//            mplayer->play();
//        }
//    }


#endif
    return 0;

}

int pvmsMonitorWidget::closeMedia(const char *pcRtspFile,QStringList list,int ch)
{
#ifdef mplaybin
    const QString str = QString::fromUtf8(pcRtspFile);
    QUrl url(str);
    player.setMedia(url);
    player.stop();
//    player.pause();

#else
    return 0;
    for(int i=0; i<mlist.count(); i++){
        video = videoList->value(i);
        mplayer = playerlist->value(i);
        if(video && mplayer){
            if(i == ch){
            mplayer->setVideoOutput(video);
            mplayer->stop();
            }
        }
    }
//    video = videoList->value(ch);
//    video->hide();
    qDebug()<<"*******************close---mlist"<<"******i***"<<"ich="<<ch<<endl;

#endif

    return 0;


}


void pvmsMonitorWidget::systimeSetSlot()
{
    m_iSystimeChangeFlag = 1;
}

void pvmsMonitorWidget::blackScreenCtrlSlot()     //黑屏触发信号处理，如果处于全屏时则退出全屏，m_iBlackScreenFlag标志置1，全屏监控暂时无效
{
    T_CMP_PACKET tPkt;
#ifdef mplaybin
    if ((1 == m_iFullScreenFlag) && (m_playWin != NULL))
#else
    if ((1 == m_iFullScreenFlag) /*&& (m_playWin != NULL)*/)
#endif
    {
        struct sysinfo s_info;
        memset(&s_info,0,sizeof(s_info));
        sysinfo(&s_info);
        m_lastActionTime = s_info.uptime;  //更新最后一次操作计时
#ifdef mplaybin
        m_playWin->move(0, 138);
        m_playWin->resize(782, 630);
#endif
        m_iFullScreenFlag = 0;

        tPkt.iMsgCmd = CMP_CMD_CHG_ALL_VIDEOWIN;
        tPkt.iCh = 0;
        PutNodeToCmpQueue(m_ptQueue, &tPkt);

        if (m_channelStateLabel != NULL)
        {
            m_channelStateLabel->setGeometry(320, 385, 121, 50);
        }
        if (m_channelNoLabel != NULL)
        {
            m_channelNoLabel->setGeometry(20, 690, 100, 50);
        }
        if (m_presetPasswdConfirmPage != NULL)
        {
            m_presetPasswdConfirmPage->show();
        }

        emit showAlarmWidgetSignal();
    }
    m_iBlackScreenFlag = 1;
}

void pvmsMonitorWidget::blackScreenExitCtrlSlot()  //黑屏退出触发信号处理，m_iBlackScreenFlag标志置0，全屏监控恢复
{
    struct sysinfo s_info;
    sysinfo(&s_info);
    m_lastActionTime = s_info.uptime;  //更新最后一次操作计时
    m_iBlackScreenFlag = 0;
}


void pvmsMonitorWidget::pvmsUpdownCtrl(char *pcMsgData)
{
    char acSendBuf[4] = {0};
    int iRet = 0, i = 0, j = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    T_LOG_INFO tLogInfo;
    T_PVMS_UPDOWN_INFO *ptPvmsUpdownInfo = (T_PVMS_UPDOWN_INFO *)pcMsgData;

    for (i = 0; i < 4; i++)
    {
        m_tCameraInfo[i].iPvmsUpdownState = ptPvmsUpdownInfo->i8PvmsUpdownFlag[i];
    }

    for (i = 0; i < 4; i++)
    {
        if (PVMS_UP == m_tCameraInfo[i].iPvmsUpdownState)
        {
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] get cameraNo%d pvms updown signal,state is up\n",__FUNCTION__, i);
            if (m_tCameraInfo[i].pvmsDownMonitorTimer != NULL)   //收到了升弓信号就删除降弓监控定时器，取消重新开始
            {
                if (m_tCameraInfo[i].pvmsDownMonitorTimer ->isActive())
                {
                    m_tCameraInfo[i].pvmsDownMonitorTimer ->stop();
                }
                delete m_tCameraInfo[i].pvmsDownMonitorTimer ;
                m_tCameraInfo[i].pvmsDownMonitorTimer  = NULL;
            }

            if ((FILLLIGHT_OFF == m_tCameraInfo[i].iFillLightSwitchState) && (0 == m_tCameraInfo[i].iManualFillLightCtrlFlag))
            {
                if ((0 == m_iPollingFlag) && (i == m_iCameraPlayNo))   //轮询暂停时，要根据当前相机的补光灯状态来手动刷新按钮样式，正常轮询不需要在这里手动刷新
                {
                    emit fillLightSwitchButtonTextCtrlSignal(0);  //触发让补光灯开关按钮显示文本的信号
                }
                acSendBuf[0] = 1;  //操作类型为开启补光灯
                acSendBuf[1] = m_tCameraInfo[i].iPosNO;      //发送消息的第2个字节表示受电弓摄像机位置号
                iRet = PMSG_SendPmsgData(m_tCameraInfo[i].phandle, CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL, acSendBuf, 2);    //发送补光灯开关控制命令
                if (iRet < 0)
                {
//                    DebugPrint(DEBUG_UI_ERROR_PRINT, "[%s] PMSG_SendPmsgData CLI_SERV_MSG_TYPE_PVMS_LIGHT_CTRL error!iRet=%d, cameraNo=%d\n",__FUNCTION__,iRet, i);
                }
                else
                {
                    m_tCameraInfo[i].iManualFillLightCtrlFlag = 0;
                    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
                    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

                    for (j = 0; j < tTrainConfigInfo.iNvrServerCount; j++)
                    {
                        if (m_tCameraInfo[i].phandle == STATE_GetNvrServerPmsgHandle(j))
                        {
                            memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                            tLogInfo.iLogType = 0;
                            snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "get camera %d.%d pvms up signal, open fillLight", 100+tTrainConfigInfo.tNvrServerInfo[j].iCarriageNO, 200+m_tCameraInfo[i].iPosNO-8);
                            LOG_WriteLog(&tLogInfo);
                            break;
                        }
                    }
                }
                m_tCameraInfo[i].iFillLightSwitchState = FILLLIGHT_ON;
            }
        }
        else if ((PVMS_DOWN == m_tCameraInfo[i].iPvmsUpdownState)  && (FILLLIGHT_ON == m_tCameraInfo[i].iFillLightSwitchState))
        {
//            DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] get cameraNo%d pvms updown signal,state is down\n",__FUNCTION__, i);

            if (NULL == m_tCameraInfo[i].pvmsDownMonitorTimer)
            {
                m_tCameraInfo[i].pvmsDownMonitorTimer = new QTimer(this);
                m_tCameraInfo[i].pvmsDownMonitorTimer->start(10*60*1000);	//收到降弓信号10分钟后关闭相应补光灯

                if (0 == i)
                {
                    connect(m_tCameraInfo[i].pvmsDownMonitorTimer,SIGNAL(timeout()), this,SLOT(pvmsDownEndSlot1()));
                }
                else if (1 == i)
                {
                    connect(m_tCameraInfo[i].pvmsDownMonitorTimer,SIGNAL(timeout()), this,SLOT(pvmsDownEndSlot2()));
                }
                else if (2 == i)
                {
                    connect(m_tCameraInfo[i].pvmsDownMonitorTimer,SIGNAL(timeout()), this,SLOT(pvmsDownEndSlot3()));
                }
                else
                {
                    connect(m_tCameraInfo[i].pvmsDownMonitorTimer,SIGNAL(timeout()), this,SLOT(pvmsDownEndSlot4()));
                }
            }
        }
    }
}
int pvmsMonitorWidget::pmsgCtrl(PMSG_HANDLE pHandle, unsigned char ucMsgCmd, char *pcMsgData, int iMsgDataLen)   //与服务器通信消息处理
{
    int i = 0;
        T_PVMS_UPDOWN_INFO tPvmsUpdownInfo;
        if (0 == pHandle)
        {
            return 0;
        }

        switch(ucMsgCmd)
        {
            case SERV_CLI_MSG_TYPE_SET_PTZ_RESP:
            case SERV_CLI_MSG_TYPE_SET_PRESETS_RESP:
            case SERV_CLI_MSG_TYPE_PVMS_IPC_CTRL_RESP:
            case SERV_CLI_MSG_TYPE_PVMS_LIGHT_CTRL_RESP:
            {
                if ((NULL == pcMsgData) || (iMsgDataLen != 1))
                {
                    break;
                }
//                DebugPrint(DEBUG_PMSG_DATA_PRINT, "pvmsMonitorWidget Widget get pmsg response cmd 0x%x data:%d\n", ucMsgCmd, pcMsgData[0]);
                break;
            }
            case SERV_CLI_MSG_TYPE_PVMS_UPDOWN_REPORT:
            {
                if ((NULL == pcMsgData) || (iMsgDataLen != 6))
                {
                    break;
                }
                else
                {
//                    DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMonitorWidget Widget get pmsg cmd 0x%x\n", ucMsgCmd);

                    /*没收到PIS发送的升降弓命令之前，PIS和NVR发过来的升降弓命令都处理，一旦收到过PIS发过来的，之后对NVR发过来的命令就不处理了*/
                    if (pHandle == m_PisServerPhandle)
                    {
                        if (0 == m_iPisGetFlag)
                        {
                            m_iPisGetFlag = 1;   //收到过PIS发送的升降弓命令了,之后对NVR发过来的SERV_CLI_MSG_TYPE_PVMS_UP_DOWN_CTRL命令就不处理了
                        }

                        pvmsUpdownCtrl(pcMsgData);
                    }
                    break;
                }
            }
            case SERV_CLI_MSG_TYPE_PVMS_UP_DOWN_CTRL:
            {
                if ((NULL == pcMsgData) || (iMsgDataLen != 2))
                {
                    break;
                }
                else
                {
                    if (m_iPisGetFlag != 1)   //只有没收到过PIS发送的升降弓命令才进行这条命令的处理
                    {
//                        DebugPrint(DEBUG_PMSG_NORMAL_PRINT, "pvmsMonitorWidget Widget get pmsg cmd 0x%x %d-%d\n", ucMsgCmd, m_iPisGetFlag, pcMsgData[0]);
                        memset(&tPvmsUpdownInfo, 0, sizeof(T_PVMS_UPDOWN_INFO));

                        if (1 == pcMsgData[0])   //升弓
                        {
                            for (i = 0; i < 4; i++)
                            {
                                tPvmsUpdownInfo.i8PvmsUpdownFlag[i] = 1;
                            }
                        }
                        else   //降弓
                        {
                            for (i = 0; i < 4; i++)
                            {
                                tPvmsUpdownInfo.i8PvmsUpdownFlag[i] = 0;
                            }
                        }
                        pvmsUpdownCtrl((char *)&tPvmsUpdownInfo);
                    }
                }
                break;
            }
            default:
                break;
        }

        return 0;





}

pvmsMonitorWidget::~pvmsMonitorWidget()
{
    closePlayWin();

    pthread_mutex_destroy(&g_tCmpCtrlMutex);

    if (m_ptQueue != NULL)
    {
        DestroyCmpQueue(m_ptQueue);
        pthread_mutex_destroy(&tMutex);
    }

    if (m_presetPasswdConfirmPage != NULL)
    {
        delete m_presetPasswdConfirmPage;
        m_presetPasswdConfirmPage = NULL;
    }
    delete g_buttonGroup;
    g_buttonGroup = NULL;

    delete m_channelStateLabel;
    m_channelStateLabel = NULL;

    delete m_channelNoLabel;
    m_channelNoLabel = NULL;
#ifdef mplaybin
    delete m_playWin;
    m_playWin = NULL;
#endif

    delete playwidget;
    playwidget = NULL;
//   delete player;
//    player = NULL;
    delete ui;
}
