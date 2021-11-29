#ifndef PVMSMENUWIDGET_H
#define PVMSMENUWIDGET_H

#include <QWidget>
#include "pvmsmonitorwidget.h"
#include "recordplaywidget.h"
#include "inteanalywidget.h"
#include "devmanagewidget.h"
#include "devupdatewidget.h"
#include "alarmwidget.h"
#include <QTimer>
#include "rs485serv.h"



namespace Ui {
class pvmsMenuWidget;
}

class pvmsMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pvmsMenuWidget(QWidget *parent = 0);
    ~pvmsMenuWidget();

    void recvRs485Ctrl(char *pcData, int iDataLen);
    void recvPmsgCtrl(PMSG_HANDLE pHandle, unsigned char ucMsgCmd, char *pcMsgData, int iMsgDataLen);
    PRS485_HANDLE m_pRs485Handle;


public slots:
    void registOutButtonClick(int page);
    void menuButtonClick();
    void alarmPageShowSlot();
    void closeAlarmWidget();
    void alarmHappenSlot();
    void alarmClearSlot();
    void serverOffLineSlot(int iDex);

    void hideAlarmWidgetSlot();
    void showAlarmWidgetSlot();

    void blackScreenCtrlSlot();
    void blackScreenExitCtrlSlot();

signals:
    void registOutSignal();     //注销信号，iType:表示执行注销的页面类型，这里应该为2，表示受电弓监控页面,
    void reflushAlarmPageSignal(int iAlarmType, int iCarriageNO, int iDevPos);
    void alarmHappenSignal();
    void alarmClearSignal();


    void blackScreenSignal();
    void blackScreenExitSignal();


private:
    Ui::pvmsMenuWidget *ui;
    pvmsMonitorWidget *m_pvmsMonitorPage;
    recordPlayWidget *m_recordPlayPage;
    inteAnalyWidget *m_inteAnalyPage;
    devManageWidget *m_devManagePage;
    devUpdateWidget *m_devUpdatePage;
    alarmWidget *m_alarmPage;
    int m_iAlarmPageOpenFlag;
    int m_iCheckDiskErrFlag[MAX_SERVER_NUM];  //是否检查服务器硬盘错误标志
    int m_iNoCheckDiskErrNum[MAX_SERVER_NUM];   //不检测服务器硬盘错误计数，每10秒加1

    QTimer *m_Rs485Timer;
    QTimer *m_PmsgTimer;

public slots:
    void showPageSlot();
    void rs485TimerFunc();
    void pmsgTimerFunc();


};

#endif // PVMSMENUWIDGET_H
