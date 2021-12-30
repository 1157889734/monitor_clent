#include "MyApplication.h"
#include <QLineEdit>
#include "state.h"
#include "debug.h"
#include "log.h"
#include <QMouseEvent>
#include <QDebug>
#define BLACKSCREN_MONITOR_TIME 5*60    //黑屏监控时间5分钟
#define MOUSE_MONITOR_TIME 10    //鼠标监控时间10秒

static int g_iMonitorNum = 0;  //黑屏监控计数，每秒加1


void *blackScreenMonitorThread(void *param)
{
    int iBlackScreenFlag = 0;
    MyApplication *myApplication = NULL;

    if (NULL == param)
    {
        return NULL;
    }

    myApplication = (MyApplication *)param;

    while (1 == myApplication->m_iThreadRunFlag)
    {
//        DebugCmdProcess();
        if (0 == (g_iMonitorNum%5))   //每隔5秒同步一次flash日志文件
        {
            LOG_FsyncFile();
        }

        g_iMonitorNum++;

        if (g_iMonitorNum >= BLACKSCREN_MONITOR_TIME)
        {
            DebugPrint(DEBUG_UI_NOMAL_PRINT, "black screen monitor time out,trigger black screen signal!\n");
            iBlackScreenFlag = STATE_GetBlackScreenFlag();
            if (1 == iBlackScreenFlag)   //根据配置文件的配置决定是否触发黑屏信号
            {
                myApplication->triggerBlackScreenSignal();   //5分钟界面没操作，触发黑屏信号
            }
            g_iMonitorNum = 0;   //计数清0，重新一轮监测
        }
        else if (g_iMonitorNum >= MOUSE_MONITOR_TIME)
        {
            myApplication->triggerMouseHideSignal();    //10秒界面没操作，隐藏鼠标
        }

        usleep(1000*1000);
    }
    return NULL;
}

MyApplication::MyApplication(int & argc,char **argv) :
    QApplication(argc, argv)
{

    m_blackScreenWidget = new QWidget();    //创建一个黑屏界面，黑屏监控使用，5分钟程序界面未操作黑屏，即显示该界面，否则隐藏

    m_blackScreenWidget->setGeometry(0, 0, 1024, 768);   //设置位置
    m_blackScreenWidget->setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");
    m_blackScreenWidget->setWindowFlags(m_blackScreenWidget->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);  //设置窗体属性，无标题栏，总是在最上端
    m_blackScreenWidget->hide();


    QObject::connect(this, SIGNAL(blackScreenSignal()), this, SLOT(blackScreenSignalCtrl()));
    QObject::connect(this, SIGNAL(mouseHideSignal()), this, SLOT(mouseHideSignalCtrl()));


    m_threadId = 0;
    m_iThreadRunFlag = 1;
    g_iMonitorNum = 0;
    m_iAlarmFlag = 0;
    m_iMouseHideFlag = 0;
    m_iMousePosX = 0;
    m_iMousePosY = 0;
    pthread_create(&m_threadId, NULL, blackScreenMonitorThread, (void *)this);    //创建黑屏监控线程

}


MyApplication::~MyApplication()
{

    if (m_threadId != 0)
    {
        m_iThreadRunFlag = 0;
        pthread_join(m_threadId, NULL);
        m_threadId = 0;
    }
    delete m_blackScreenWidget;
    m_blackScreenWidget = NULL;

}

void MyApplication::triggerBlackScreenSignal()
{

    if ((0 == m_iAlarmFlag) && (1 == m_blackScreenWidget->isHidden()))   //只有在没有报警触发的前提下才会黑屏，有报警不会黑屏
    {
        emit blackScreenSignal();
    }
}

void MyApplication::triggerMouseHideSignal()
{

    if (0 == m_iMouseHideFlag)
    {
        emit mouseHideSignal();
    }
}

void MyApplication::blackScreenSignalCtrl()
{
//    QWSServer::sendKeyEvent(0x01000003, Qt::Key_Escape, Qt::NoModifier, true, false);  //发送一个模拟键盘ESC键，以免messagebox未关闭导致黑屏后无法单击退出黑屏
    DebugPrint(DEBUG_UI_NOMAL_PRINT, "black screen show!\n");
    this->m_blackScreenWidget->show();
}

void MyApplication::mouseHideSignalCtrl()
{
//    QWSServer::setCursorVisible(false);
//    this->setCursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(Qt::BlankCursor);
    m_iMouseHideFlag = 1;
}

void MyApplication::alarmHappenSignalCtrl()     //报警触发信号处理，退出黑屏，标志位置1以使报警未清除前不再黑屏
{
    g_iMonitorNum = 0;
    if (m_blackScreenWidget->isHidden() != 1)
    {
        DebugPrint(DEBUG_UI_NOMAL_PRINT, "alarm happen,black screen hide!\n");
        m_blackScreenWidget->hide();
    }
    m_iAlarmFlag = 1;
}

void MyApplication::alarmClearSignalCtrl()   //报警清除信号处理，标志位置0以使黑屏监控恢复正常
{
    m_iAlarmFlag = 0;
}

bool MyApplication::notify(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::MouseButtonPress || event->type()==QEvent::MouseMove) //判断界面是否有操作
    {

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

        if (1 == m_iMouseHideFlag)
        {
//            QWSServer::setCursorVisible(true);
//            this->setCursor(Qt::ArrowCursor);
            QApplication::setOverrideCursor(Qt::ArrowCursor);
            m_iMouseHideFlag = 0;
        }

        g_iMonitorNum = 0;

        if (event->type()==QEvent::MouseButtonPress)
        {
            if (m_blackScreenWidget->isHidden() != 1)
            {
                m_blackScreenWidget->hide();
                emit blackScreenExitSignal();
            }
        }
    }
    return  QApplication::notify(obj, event);
}


