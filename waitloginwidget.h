#ifndef WAITLOGINWIDGET_H
#define WAITLOGINWIDGET_H

#include <QWidget>
#include <pthread.h>
#include <QLabel>

namespace Ui {
class waitLoginWidget;
}

class waitLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit waitLoginWidget(QWidget *parent = 0);
    ~waitLoginWidget();
    void pageRedirect();
    pthread_t m_threadId;    //倒计时线程ID
    int m_iThreadRunFlag;    //线程运行标识
    void triggerSetCountDownValueSignal(QString timeStr);
    int g_ilaybel_width;
    void chage_label_function();

signals:
    void pageRedirectSignal();    //页面跳转信号
    void setCountDownValueSignal(QString timeStr);    //设置倒计时显示控件内容更新信号

public slots:
    void okButtonClickSlot();    //确认按钮按键信号相应槽函数
    void setCountDownValueSlot(QString timeStr);  //设置倒计时的值
private:
    Ui::waitLoginWidget *ui;
};

#endif // WAITINGLOGIN_H
