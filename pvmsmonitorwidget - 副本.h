#ifndef PVMSMONITORWIDGET_H
#define PVMSMONITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QButtonGroup>
#include "presetpasswdconfirm.h"
#include "pmsgcli.h"
#include "state.h"
#include <QtCore/qmath.h>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "qplayer.h"


namespace Ui {
class pvmsMonitorWidget;
}

//#define mplaybin

typedef enum _E_CAMERA_STATE    //摄像机状态
{
    CAMERA_ON = 1,    //开启状态
    CAMERA_OFF = 2    //关闭状态
} E_CAMERA_STATUE;

typedef enum _E_FILLLIGHT_STATE     //补光灯状态
{
    FILLLIGHT_ON = 1,    //开启状态
    FILLLIGHT_OFF = 2   //关闭状态
} E_FILLLIGHT_STATUE;

typedef enum _E_PVMSUPDOWN_STATE    //升降弓状态
{
    PVMS_DOWN = 0,   //降弓
    PVMS_UP = 1    //升弓
} E_PVMSUPDOWN_STATE;

typedef enum _E_CMP_CMD
{
    CMP_CMD_CREATE_CH,
    CMP_CMD_DESTORY_CH,
    CMP_CMD_ENABLE_CH,
    CMP_CMD_DISABLE_CH,
    CMP_CMD_CHG_ALL_VIDEOWIN,
    CMP_CMD_GET_STREAM_STATE
} E_CMP_CMD;

typedef struct _T_CMP_PACKET
{
    int iMsgCmd;  //E_CMP_CMD
    int iCh;
} T_CMP_PACKET, *PT_CMP_PACKET;

typedef struct _T_CMP_PACKET_LIST
{
    T_CMP_PACKET tPkt;
    struct _T_CMP_PACKET_LIST *next;
} T_CMP_PACKET_LIST;

typedef struct _T_CMP_QUEUE
{
    T_CMP_PACKET_LIST *ptFirst, *ptLast;
    INT32 iQueueType;  // 0:先进先出(FIFO)，1:后进先出(LIFO)
    INT32 iPktCount;
    pthread_mutex_t *pMutex;
} T_CMP_QUEUE, *PT_CMP_QUEUE;

typedef struct _T_CAMERA_INFO
{
    char acCameraRtspUrl[256];    //保存rtsp地址
    int iPosNO;    //位置号
    int iCameraSwitchState;    //摄像头开关状态，E_CAMERA_STATUE
    int iFillLightSwitchState;   //补光灯开关状态，E_FILLLIGHT_STATUE
    int iPvmsUpdownState;   //升降弓状态，E_PVMSUPDOWN_STATE
    QTimer *pvmsDownMonitorTimer;    //降弓监控定时器，收到降弓信号10分钟无升弓则要关闭补光灯
    int iPresetNo;  //预置点编号
    int iCmpOpenFlag;    //摄像头打开标志
    int iManualFillLightCtrlFlag;   //手动操作补光灯标志
    int iStreamState;
    time_t tPtzOprateTime;    //云台操作时间
    PMSG_HANDLE phandle;   //所属服务器的通信句柄
/*    CMPHandle cmpHandle;    //客户端媒体播放句柄*/
} __attribute__((packed)) T_CAMERA_INFO, *PT_CAMERA_INFO;


class pvmsMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pvmsMonitorWidget(QWidget *parent = 0);
    ~pvmsMonitorWidget();
    bool eventFilter(QObject *target, QEvent *event);  //事件过滤器
    QPushButton *m_presetNoPushbutton[8];
    QButtonGroup *g_buttonGroup;
    time_t m_lastActionTime;    //界面最后一次操作时间
    int pmsgCtrl(PMSG_HANDLE pHandle, unsigned char ucMsgCmd, char *pcMsgData, int iMsgDataLen);   //与服务器通信消息处理
    void pvmsUpdownCtrl(char *pcMsgData);
    void createMedia();
    int  openMedia(const char *pcRtspFile,QStringList list,int ch);
    int  closeMedia(const char *pcRtspFile,QStringList list,int ch);
    void showMedia(int ch);
    void hideMedia(int ch);
    QWidget *playwidget;

    QLabel *m_channelStateLabel;
    QLabel *m_channelNoLabel;
    int pageType;

    int cameFlag;
    int cameraNum;
    int m_iSelectPresetNo;   //保存选中的预置点编号
    int m_iAlarmNotCtrlFlag;   //有报警信息未处理标志
    time_t tPollingOparateTime;  //轮询操作时间
    int m_iPollingFlag;   //轮询标识
    int m_iCameraSwitchState;//
    int m_iPresetPasswdOkFlag;
    int m_iCameraPlayNo;   //正在播放的摄像机编号，与m_tCameraRtspUrl的下标对应
    int m_iDisplayEnable;  //显示全局使能标识
    int m_iCameraNum;  //摄像机总数
    int m_iRecordPlayFlag;   //是否在回放标志，1-在回放，0-未回放
    int m_iBlackScreenFlag;   //黑屏标志
    int m_iFullScreenFlag;   //全屏标识
    int m_iPtzMoveType;   //正在进行的云台操作类型类型，开始或停止
    int m_iPtzCtrType;   //正在进行的云台控制类型
    PMSG_HANDLE m_NvrServerPhandle[MAX_SERVER_NUM];    //nvr服务器PMSG通信句柄
    pthread_t m_threadId;    //线程ID
    int m_iThreadRunFlag;   //线程运行标识
    int m_iPisGetFlag;   //从PIS接收过消息的标志
    int m_iOldRecordPlayFlag;

    int m_iSystimeChangeFlag;   //系统时间改变标志

    PMSG_HANDLE m_PisServerPhandle;    //pis服务器PMSG通信句柄
#ifdef mplaybin
    QVideoWidget *m_playWin;    //播放窗体
#endif
    int m_iMousePosX;
    int m_iMousePosY;

    T_CAMERA_INFO m_tCameraInfo[MAX_SERVER_NUM*MAX_CAMERA_OFSERVER];    //保存的所有摄像机信息

    PT_CMP_QUEUE m_ptQueue;
    pthread_mutex_t tMutex;

    void startVideoPolling();
    void enableVideoPlay(int iFlag);  //设置显示全局使能标识

    void videoChannelCtrl();
    void getChStreamState(int iCh);
    void closePlayWin();

    void triggerCmpOptionCtrlSinal(int iType, int iCh);
    void noPollingChOption();

    void triggerVideoPollingSignal();
    void triggerFullScreenSignal();
    void triggerPresetReturnSignal(int iCameraNO);
    void triggerGetDevStateSignal();
    void triggerSetTimeSignal();
    void triggerRecordPlayCtrlSignal();
    void setPlayButtonStyleSheet();


signals:
    void alarmPushButoonClickSignal();
    void registOutSignal(int page);     //注销信号，iType:表示执行注销的页面类型，这里应该为2，表示受电弓监控页面,
    void chStateLabelTextCtrlSignal(int iFlag);   //通道状态标签文本显示的处理信号，0-显示关闭，1-显示开启
    void camSwitchButtonTextCtrlSignal(int iFlag);   //摄像机开关状态按钮文本显示的处理信号，0-显示关闭，1-显示开启
    void chLabelDisplayCtrlSignal();   //通道状态和通道号标签是否显示的处理信号
    void fillLightSwitchButtonTextCtrlSignal(int iFlag);   //补光灯开关状态按钮文本显示的处理信号，0-显示关闭，1-显示开启
    void recordPlayCtrlSignal();
    void setFullScreenSignal();
    void hideAlarmWidgetSignal();
    void showAlarmWidgetSignal();
    void videoPollingSignal();
    void presetReturnSignal(int iCameraNO);
    void cmpOptionCtrlSignal(int iType, int iCh);

    void getDevStateSignal();
    void setTimeSignal();


public slots:
    void presetNoGroupButtonClickSlot(int iButtonNo);     //预置点编号按钮组按键信号响应槽函数，iButtonNo为按钮编号
    void alarmPushButoonClickSlot();
    void startPollingSlot();
    void pausePollingSlot();
    void manualSwitchLastCameraSlot();
    void manualSwitchNextCameraSlot();
    void presetSetCtrlSlot();
    void presetGetCtrlSlot();
    void temporarySaveBeginSlot();
    void temporarySaveEndSlot();
    void cameraSwitchSlot();
    void fillLightSwitchSlot();
    void manualSwitchEndSlot();
    void closePresetPasswdPageSlot();   //关闭预置点密码确认界面槽函数
    void setPresetSlot();
    void registOutButtonClick();
    void fillLightSwitchEndSlot();
    void chLabelDisplayCtrlSlot();   //通道状态和通道号标签是否显示的处理函数
    void alarmHappenSlot();
    void alarmClearSlot();
    void alarmHappenCtrlSlot();
    void setRecordPlayFlag(int iFlag);
    void videoPollingSignalCtrl();


    void setFullScreenSignalCtrl();
    void presetReturnSignalCtrl(int iCameraNO);
    void recordPlayCtrlSlot();
    void chStateLabelTextCtrlSlot(int iFlag);   //通道状态标签文本显示的处理函数，0-显示关闭，1-显示开启
    void camSwitchButtonTextCtrlSlot(int iFlag);   //摄像机开关状态按钮文本显示的处理函数，0-显示关闭，1-显示开启
    void fillLightSwitchButtonTextCtrlSlot(int iFlag);   //补光灯开关状态按钮文本显示的处理函数，0-显示关闭，1-显示开启
    void cmpOptionCtrlSlot(int iType, int iCh);

    void pvmsDownEndSlot1();
    void pvmsDownEndSlot2();
    void pvmsDownEndSlot3();
    void pvmsDownEndSlot4();

    void systimeSetSlot();
    void blackScreenCtrlSlot();
    void blackScreenExitCtrlSlot();
    void cameraSwitchEndSlot();



private:
    Ui::pvmsMonitorWidget *ui;
    QTimer *m_alarmHappenTimer;
    QTimer *m_manualSwitchTimer;
    QTimer *m_temporarySaveTimer;
    presetPasswdConfirm *m_presetPasswdConfirmPage;    //预置点密码确认界面
    QTimer *m_fillLightSwitchTimer;
    QTimer *m_cameraSwitchTimer;

    QVideoWidget *video;
#ifdef mplaybin
    QMediaPlayer player;
#endif
    QMediaPlayer *mplayer;

    QMediaPlaylist *list;
    QList<QMediaPlaylist*> *multiPlayList;
    QList<QMediaPlayer*> *playerlist;
    QList<QVideoWidget*> *videoList;
    QList<QHBoxLayout*> *hLayoutList;
	QList<QWidget*>		m_lstPlayWidget;
    QStringList mlist;


};

#endif // PVMSMONITORWIDGET_H
