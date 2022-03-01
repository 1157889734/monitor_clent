#include "inteanalywidget.h"
#include "ui_inteanalywidget.h"
#include <QLineEdit>
#include <QDateTime>
#include "debug.h"
#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面

static int g_iDNum = 0;
int g_intenaiDateEditNo = 0;      //要显示时间的不同控件的编号

inteAnalyWidget::inteAnalyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inteAnalyWidget)
{
    char timestr[128] = {0};
    int iYear = 0, iMonth= 0, iDay = 0;
    QString string = "";
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    timeSetWidget = new timeset(this);
    timeSetWidget->hide();
    timeSetWidget->setWindowModality(Qt::ApplicationModal);

    connect(timeSetWidget, SIGNAL(timeSetSendMsg(QString,QString,QString,QString,QString,QString)), this, SLOT(timeSetRecvMsg(QString,QString,QString,QString,QString,QString)));  //时间设置窗体控件设置信号响应

    connect(ui->startTimeSetPushButton, SIGNAL(clicked(bool)), this, SLOT(openStartTimeSetWidgetSlot()));   //开始时间设置按钮按键信号响应
    connect(ui->startTimeSetPushButton_2, SIGNAL(clicked(bool)), this, SLOT(openStopTimeSetWidgetSlot()));  //结束时间设置按钮按键信号响应


    QDateTime time = QDateTime::currentDateTime();
    snprintf(timestr, sizeof(timestr), "%4d-%02d-%02d %02d:%02d:%02d", time.date().year(), time.date().month(), time.date().day(), time.time().hour(), time.time().minute(), time.time().second());
    string = QString(QLatin1String(timestr)) ;
    ui->endTimeLabel->setText(string);		 //结束时间控件初始显示当前系统时间

    memset(&timestr, 0, sizeof(timestr));
    iYear = time.date().year();
    iMonth = time.date().month();
    iDay = time.date().day()-1;
    if (0 == iDay)
    {
        iMonth = time.date().month()-1;
        if (0 == iMonth)
        {
            iMonth = 12;
            iYear = time.date().year() - 1;
        }
        if (1 == iMonth || 3 == iMonth || 5 == iMonth || 7 == iMonth || 8 == iMonth || 10 == iMonth || 12 == iMonth)
        {
            iDay = 31;
        }
        else if (4 == iMonth || 6 == iMonth || 9 == iMonth || 11 == iMonth)
        {
            iDay = 30;
        }
        else
        {
            if((0 == iYear%4 && 0 == iYear%100)||(0 == iYear%400))
            {
                iDay = 29;
            }
            else
            {
                iDay = 28;
            }
        }
    }

    snprintf(timestr, sizeof(timestr), "%4d-%02d-%02d %02d:%02d:%02d", iYear, iMonth, iDay, time.time().hour(), time.time().minute(), time.time().second());
    string = QString(QLatin1String(timestr)) ;
    ui->startTimeLabel->setText(string);     //起始时间控件初始显示当前系统时间前一天

    //recordFileTableWidget

    ui->recordFileTableWidget->setFocusPolicy(Qt::NoFocus);
    ui->recordFileTableWidget->setColumnCount(3);
    ui->recordFileTableWidget->setRowCount(8);
//    ui->recordFileTableWidget->setShowGrid(true);
//    ui->devStorageTableWidget->setStyleSheet("QTableWidget{ gridline-color : rgb(255, 255, 255)}");
    QStringList header;
    header<<tr("选中")<<tr("序号")<<tr("文件名");
    ui->recordFileTableWidget->horizontalHeader()->setStyleSheet("background-color:white");
    ui->recordFileTableWidget->setHorizontalHeaderLabels(header);
    ui->recordFileTableWidget->horizontalHeader()->setVisible(true);//temp
    ui->recordFileTableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    ui->recordFileTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->recordFileTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->recordFileTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->recordFileTableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
//    ui->recordFileTableWidget->setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    ui->recordFileTableWidget->horizontalHeader()->resizeSection(0,50); //设置表头第一列的宽度为46
    ui->recordFileTableWidget->horizontalHeader()->resizeSection(1,100);
    ui->recordFileTableWidget->horizontalHeader()->resizeSection(2,150);



    connect(ui->canselPushButton, SIGNAL(clicked()), this, SLOT(registOutButtonClick()));
    connect(ui->alarmPushButton, SIGNAL(clicked(bool)), this, SLOT(alarmPushButoonClickSlot()));   //报警按钮按键信号响应打开报警信息界面

    m_alarmHappenTimer = NULL;



}

inteAnalyWidget::~inteAnalyWidget()
{
    delete timeSetWidget;
    timeSetWidget = NULL;

    delete ui;
}

void inteAnalyWidget::pageShowCtrl()  //每次切换到当前页面，则更新查询起始和结束时间控件显示
{
    char timestr[128] = {0};
    int iYear = 0, iMonth= 0, iDay = 0;
    QString string = "";
    QDateTime time = QDateTime::currentDateTime();
    snprintf(timestr, sizeof(timestr), "%4d-%02d-%02d %02d:%02d:%02d", time.date().year(), time.date().month(), time.date().day(), time.time().hour(), time.time().minute(), time.time().second());
    string = QString(QLatin1String(timestr)) ;
    ui->endTimeLabel->setText(string);		 //结束时间控件初始显示当前系统时间

    memset(&timestr, 0, sizeof(timestr));
    iYear = time.date().year();
    iMonth = time.date().month();
    iDay = time.date().day()-1;
    if (0 == iDay)
    {
        iMonth = time.date().month()-1;
        if (0 == iMonth)
        {
            iMonth = 12;
            iYear = time.date().year() - 1;
        }
        if (1 == iMonth || 3 == iMonth || 5 == iMonth || 7 == iMonth || 8 == iMonth || 10 == iMonth || 12 == iMonth)
        {
            iDay = 31;
        }
        else if (4 == iMonth || 6 == iMonth || 9 == iMonth || 11 == iMonth)
        {
            iDay = 30;
        }
        else
        {
            if((0 == iYear%4 && 0 == iYear%100)||(0 == iYear%400))
            {
                iDay = 29;
            }
            else
            {
                iDay = 28;
            }
        }
    }
    snprintf(timestr, sizeof(timestr), "%4d-%02d-%02d %02d:%02d:%02d", iYear, iMonth, iDay, time.time().hour(), time.time().minute(), time.time().second());
    string = QString(QLatin1String(timestr)) ;
    ui->startTimeLabel->setText(string);     //起始时间控件初始显示当前系统时间前一天

}

void inteAnalyWidget::timeSetRecvMsg(QString year, QString month, QString day, QString hour, QString min, QString sec)     //响应时间设置控件信号，更新起始、结束时间显示label的显示文本
{
    char timestr[128] = {0};
    snprintf(timestr, sizeof(timestr), "%s-%s-%s %s:%s:%s", year.toStdString().data(), month.toStdString().data(), day.toStdString().data(),
            hour.toStdString().data(), min.toStdString().data(), sec.toStdString().data());
    QString string = QString(QLatin1String(timestr)) ;
    if (1 == g_intenaiDateEditNo)
    {
        ui->startTimeLabel->setText(string);
    }
    else if (2 == g_intenaiDateEditNo)
    {
        ui->endTimeLabel->setText(string);
    }
}


void inteAnalyWidget::openStartTimeSetWidgetSlot()
{
    QString timeStr = ui->startTimeLabel->text();
    char acTimeStr[256] = {0};
    int iYear = 0, iMonth = 0, iDay = 0, iHour = 0, iMin = 0, iSec = 0;

    DebugPrint(DEBUG_UI_OPTION_PRINT, "recordPlayWidget startTimeSetPushButton pressed!\n");
    strcpy(acTimeStr, timeStr.toLatin1().data());
    if (strlen(acTimeStr) != 0)
    {
        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] timeStr:%s!\n", __FUNCTION__, acTimeStr);
        sscanf(acTimeStr, "%4d-%02d-%02d %02d:%02d:%02d", &iYear, &iMonth, &iDay, &iHour, &iMin, &iSec);
        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] %d-%d-%d %d:%d:%d!\n", __FUNCTION__, iYear, iMonth, iDay, iHour, iMin, iSec);
    }
    timeSetWidget->setGeometry(290, 65, timeSetWidget->width(), timeSetWidget->height());
    g_intenaiDateEditNo = 1;
    timeSetWidget->setTimeLabelText(iYear, iMonth, iDay, iHour, iMin, iSec);
    timeSetWidget->show();

}


void inteAnalyWidget::openStopTimeSetWidgetSlot()
{
    QString timeStr = ui->endTimeLabel->text();
    char acTimeStr[256] = {0};
    int iYear = 0, iMonth = 0, iDay = 0, iHour = 0, iMin = 0, iSec = 0;

    DebugPrint(DEBUG_UI_OPTION_PRINT, "recordPlayWidget stopTimeSetPushButton pressed!\n");
    strcpy(acTimeStr, timeStr.toLatin1().data());
    if (strlen(acTimeStr) != 0)
    {
        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] timeStr:%s!\n", __FUNCTION__, acTimeStr);
        sscanf(acTimeStr, "%4d-%02d-%02d %02d:%02d:%02d", &iYear, &iMonth, &iDay, &iHour, &iMin, &iSec);
        DebugPrint(DEBUG_UI_NOMAL_PRINT, "[%s] %d-%d-%d %d:%d:%d!\n", __FUNCTION__, iYear, iMonth, iDay, iHour, iMin, iSec);
    }
    timeSetWidget->setGeometry(290, 105, timeSetWidget->width(), timeSetWidget->height());
    g_intenaiDateEditNo = 2;
    timeSetWidget->setTimeLabelText(iYear, iMonth, iDay, iHour, iMin, iSec);
    timeSetWidget->show();


}

void inteAnalyWidget::registOutButtonClick()
{
    int update_page = 5;

    this->hide();
    emit registOutSignal(update_page);    //触发注销信号，带上当前设备类型

}
void inteAnalyWidget::alarmPushButoonClickSlot()
{
    emit alarmPushButoonClickSignal();
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);

    g_iDNum = 0;
}
void inteAnalyWidget::alarmHappenSlot()
{
    if (NULL == m_alarmHappenTimer)
    {
        m_alarmHappenTimer = new QTimer(this);
        connect(m_alarmHappenTimer,SIGNAL(timeout()), this,SLOT(alarmHappenCtrlSlot()));
        m_alarmHappenTimer->start(500);
    }
}

void inteAnalyWidget::alarmHappenCtrlSlot()
{
    if (this->isHidden() != 1)
    {
        if (0 == g_iDNum%2)
        {
            ui->alarmPushButton->setChecked(true);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alerton.bmp);background-color: rgb(255, 255, 255);}");

        }
        else
        {
            ui->alarmPushButton->setChecked(false);
            ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");

        }
        g_iDNum++;
    }
}

void inteAnalyWidget::alarmClearSlot()
{
    if (m_alarmHappenTimer != NULL)
    {
        delete m_alarmHappenTimer;
        m_alarmHappenTimer = NULL;
    }
    ui->alarmPushButton->setChecked(false);
    ui->alarmPushButton->setStyleSheet("QPushButton{border-image: url(:/monres/alertoff.bmp);background-color: rgb(255, 255, 255);}");


    g_iDNum = 0;
}
