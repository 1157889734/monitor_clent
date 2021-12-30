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
#include "ckeyboard.h"
#include "timeset.h"



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
    bool eventFilter(QObject *obj, QEvent *e);
    void ShowKeyboardSlots(int nShow);
    timeset *timeSetWidget;    //时间设置控制窗体

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
    void systimeSlot();
    void registOutButtonClick();
    void closeUserManageWidget();

    void setCameraImageParamSlot();
    void carNoChangeSlot();

    void setTrainType();
    void setPisSetting();

    void setTimeSignalCtrl();
    void KeyboardPressKeySlots(char key);

    void timeSetRecvMsg(QString year, QString month, QString day, QString hour, QString min, QString sec);
    void openTimeSetWidgetSlot();


signals:
    void alarmPushButoonClickSignal();
    void registOutSignal(int page);     //注销信号，iType:表示执行注销的页面类型，这里应该为2，表示受电弓监控页面,
    void systimeSetSignal();
    void show_hide_Signal(int value);

private:
    Ui::devUpdateWidget *ui;
    QTimer *m_alarmHappenTimer;
    PMSG_HANDLE m_Phandle[MAX_SERVER_NUM];    //服务器PMSG通信句柄
    void getTrainConfig();     //获取车型配置信息
    void setTrainTypeCombox();
    void setPollingTimeRadioButton();	  //设置轮询时间单选按钮组的样式
    void setPresetReturnTimeRadioButton();	   //设置预置点返回时间单选按钮组的样式
    CKeyboard *mCkeybord;

    QString m_TrainType;
    QString m_pollingtTimeText;
    QString m_presetReturnTimeText;
    QString m_brightNessText;
    QString m_saturationText;
    QString m_contrastText;
    usergroupManage *gusergroupManage;


};

#endif // DEVUPDATEWIDGET_H
