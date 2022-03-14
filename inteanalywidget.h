#ifndef INTEANALYWIDGET_H
#define INTEANALYWIDGET_H

#include <QWidget>
#include "pvmsmonitorwidget.h"
#include "timeset.h"

namespace Ui {
class inteAnalyWidget;
}

class inteAnalyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit inteAnalyWidget(QWidget *parent = 0);
    ~inteAnalyWidget();
    void pageShowCtrl();
    timeset *timeSetWidget;    //时间设置控制窗体

public slots:
    void registOutButtonClick();
    void alarmPushButoonClickSlot();
    void alarmHappenSlot();
    void alarmHappenCtrlSlot();
    void alarmClearSlot();
    void timeSetRecvMsg(QString year, QString month, QString day, QString hour, QString min, QString sec);
    void openStartTimeSetWidgetSlot();
    void openStopTimeSetWidgetSlot();
    void recordQuerySlot();


signals:
    void registOutSignal(int page);     //注销信号，iType:表示执行注销的页面类型，这里应该为2，表示受电弓监控页面,
    void alarmPushButoonClickSignal();

private:
    Ui::inteAnalyWidget *ui;
    QTimer *m_alarmHappenTimer;

};

#endif // INTEANALYWIDGET_H
