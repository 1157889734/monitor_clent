#ifndef CHOICELOGINDEVWIDGET_H
#define CHOICELOGINDEVWIDGET_H

#include <QWidget>

namespace Ui {
class choiceLoginDevWidget;
}

class choiceLoginDevWidget : public QWidget
{
    Q_OBJECT

public:
    explicit choiceLoginDevWidget(QWidget *parent = nullptr);
    ~choiceLoginDevWidget();

signals:
    void confirmDevTypeSignal();    //确定设备类型信号，iType:设备类型，1-车厢监控设备,2-受电弓监控设备

public slots:
    void showPageSlot();    //显示当前页面的响应槽函数
    void choiceCvmsSlot();
    void choicePvmsSlot();

private:
    Ui::choiceLoginDevWidget *ui;
};

#endif // CHOICELOGINDEVWIDGET_H
