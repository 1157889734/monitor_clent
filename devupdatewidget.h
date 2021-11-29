#ifndef DEVUPDATEWIDGET_H
#define DEVUPDATEWIDGET_H

#include <QEvent>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "state.h"
#include "pmsgcli.h"
#include "timeset.h"
#include "pvmsmonitorwidget.h"

#include "usergroupmanage.h"




namespace Ui {
class devUpdateWidget;
}

class devUpdateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit devUpdateWidget(QWidget *parent = 0);
    ~devUpdateWidget();
    QDateTime timeTd;


public slots:

    void userManageSlot();
    void configFileSelectionSlot();
    void configUpdateFileSLOT();

    void configFileImportSlot();
    void downLoadLogSlot();
    void devUpdateSlot();
    void devRebootSlot();
    void alarmPushButoonClickSlot();
    void alarmHappenCtrlSlot();
    void alarmHappenSlot();
    void alarmClearSlot();
    void presetReturnTimeChange(int iComboBoxId);
    void lineEditpresetReturnTimeChange(const QString &);
    void pollingTimeChange(int iComboBoxId);
    void lineEditpollingTimeChange(const QString &);
    void showSysTime();
    void monitorSysTime();
    void systimeSlot();
    void registOutButtonClick();
    void closeUserManageWidget();

    void setCameraImageParamSlot();

    void setTrainType();

    void setTimeSignalCtrl();


signals:
    void alarmPushButoonClickSignal();
    void registOutSignal(int page);     //注销信号，iType:表示执行注销的页面类型，这里应该为2，表示受电弓监控页面,
    void systimeSetSignal();


private:
    Ui::devUpdateWidget *ui;
    QTimer *m_alarmHappenTimer;
    QTimer *m_sys_timer;
    PMSG_HANDLE m_Phandle[MAX_SERVER_NUM];    //服务器PMSG通信句柄
    void getTrainConfig();     //获取车型配置信息
    void setTrainTypeCombox();
    void setPollingTimeRadioButton();	  //设置轮询时间单选按钮组的样式
    void setPresetReturnTimeRadioButton();	   //设置预置点返回时间单选按钮组的样式

    QString m_TrainType;
    QString m_pollingtTimeText;
    QString m_presetReturnTimeText;
    QString m_brightNessText;
    QString m_saturationText;
    QString m_contrastText;
    usergroupManage *gusergroupManage;


};

#endif // DEVUPDATEWIDGET_H
