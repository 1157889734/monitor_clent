#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class loginWidget;
}

typedef enum _E_DEVTYPE
{
    E_CVMSTYPE = 1,     //车厢监控设备
    E_PVMSTYPE = 2      //受电弓监控设备
} E_DEVTYPE;

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginWidget(QWidget *parent = nullptr);
    ~loginWidget();

signals:
    void loginCanselSignal();
    void gotoPvmsMenuPageSignal();


public slots:
    void okButtonSlot();
    void canselButtonSlot();
    void showPageSlot();  //显示当前页面的响应槽函数，这里iType代表接收到的参数，表示页面类型，1-车厢监控页面，2-受电弓监控页面
    void clearSlot();

private:
    Ui::loginWidget *ui;
    int m_iLoginType;

};

#endif // LOGINWIDGET_H
