#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QWidget>

typedef enum _E_ALARM_TYPE
{
    ALARM_VIDEO_CLEAR,
    ALARM_VIDEO_SHADE,
    ALARM_VIDEO_LOST,
    ALARM_HDISK_CLEAR,
    ALARM_HDISK_LOST,
    ALARM_HDISK_ERR,
    ALARM_SERVER_OFFLINE
} E_ALARM_TYPE;

namespace Ui {
class alarmWidget;
}

class alarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit alarmWidget(QWidget *parent = 0);
    ~alarmWidget();
    void triggerAlarmCleanSignal();

public slots:
    void closeButtonClick();
    void clearAllSlot();
    void reflushAlarmPageSlot(int iAlarmType, int iCarriageNO, int iDevPos);

signals:
    void alarmClearSignal();
    void alarmHappenSignal();
    void SendEscape();

private:
    Ui::alarmWidget *ui;
};

#endif // ALARMWIDGET_H
