#include "alarmwidget.h"
#include "ui_alarmwidget.h"
#include "state.h"
#include "log.h"
#include <QDateTime>


#define MAX_ITEM_NUM  50   //报警列表最多的记录行数
#define MAX_NVR_NUM  4
#define MAX_CAMERA_NUM 4

typedef struct _T_NVRALARM_INFO
{
    int iCarriageNO;      //NVR服务器车厢号
    int iDiskErrFlag;  //0-无报警，1-硬盘丢失报警，2-硬盘错误报警
} T_NVRALARM_INFO, *PT_NVRALARM_INFO;

typedef struct _T_CAMERAALARM_INFO
{
    int iCarriageNO;  //NVR服务器车厢号
    int iDevPos;      //位置号
    int iVideoErrFlag;  //0-无报警，1-视频遮挡报警，2-视频丢失报警
} T_CAMERAALARM_INFO, *PT_CAMERAALARM_INFO;

static T_NVRALARM_INFO g_NvrAlarmInfo[MAX_NVR_NUM];
static T_CAMERAALARM_INFO g_CameraAlarmInfo[MAX_NVR_NUM*MAX_CAMERA_NUM];


alarmWidget::alarmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarmWidget)
{
    int i = 0, j = 0, iCameraNum = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->closePushButton->setFocusPolicy(Qt::NoFocus);
    ui->closeRPushButton->setFocusPolicy(Qt::NoFocus);

    ui->tableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setAlternatingRowColors(true);                        //设置隔一行变一颜色，即：一灰一白
    ui->tableWidget->horizontalHeader()->resizeSection(0,95); //设置表头第一列的宽度为95
    ui->tableWidget->horizontalHeader()->resizeSection(1,145); //设置表头第二列的宽度为145

    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClick()));
    connect(ui->closeRPushButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClick()));
    connect(ui->clearPushButton, SIGNAL(clicked(bool)), this, SLOT(clearAllSlot()));

    memset(&g_NvrAlarmInfo[0], 0, MAX_NVR_NUM*sizeof(T_NVRALARM_INFO));
    memset(&g_CameraAlarmInfo[0], 0, MAX_NVR_NUM*MAX_CAMERA_NUM*sizeof(T_CAMERAALARM_INFO));

    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    for (i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        g_NvrAlarmInfo[i].iCarriageNO = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;

        for (j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            g_CameraAlarmInfo[iCameraNum].iCarriageNO = tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            g_CameraAlarmInfo[iCameraNum].iDevPos = 1+j;
            iCameraNum++;
        }
    }

}

alarmWidget::~alarmWidget()
{
    delete ui;
}
void alarmWidget::triggerAlarmCleanSignal()
{
    emit alarmClearSignal();

}
void alarmWidget::closeButtonClick()
{
    emit SendEscape();
    return;
}
void alarmWidget::clearAllSlot()
{
    int iRow = 0, i = 0;
    iRow = ui->tableWidget->rowCount();//获取录像文件列表总行数
    for (i = 0; i < iRow; i++)
    {
        ui->tableWidget->removeRow(i);
    }
    ui->tableWidget->setRowCount(0);

    /*清除所有记录时，将所有的报警标志恢复为0，方便后续重新有报警时能再显示。同时通知报警按钮停止闪烁*/
    for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
    {
        g_CameraAlarmInfo[i].iVideoErrFlag = 0;
    }

    for (i = 0; i < MAX_NVR_NUM; i++)
    {
        g_NvrAlarmInfo[i].iDiskErrFlag = 0;
    }
    emit alarmClearSignal();

}
void alarmWidget::reflushAlarmPageSlot(int iAlarmType, int iCarriageNO, int iDevPos)
{
    int iRow = 0, i = 0;
    char acTimestr[128] = {0};
    QString string = "";
    QString videoAlarmStr = "", hdiskAlarmStr = "";
    T_LOG_INFO tLogInfo;

    videoAlarmStr = QString::number(iCarriageNO);
    videoAlarmStr += tr("车厢服务器");
    videoAlarmStr += QString::number(iDevPos);
    videoAlarmStr += tr("号相机");

    hdiskAlarmStr = QString::number(iCarriageNO);
    hdiskAlarmStr += tr("车厢服务器硬盘");

    QDateTime time = QDateTime::currentDateTime();
    snprintf(acTimestr, sizeof(acTimestr), "%4d-%02d-%02d %02d:%02d:%02d", time.date().year(), time.date().month(), time.date().day(), time.time().hour(), time.time().minute(), time.time().second());
    string = QString(QLatin1String(acTimestr)) ;

    if ((ALARM_VIDEO_CLEAR == iAlarmType) || (ALARM_HDISK_CLEAR == iAlarmType))   //视频报警恢复
    {
        if (ALARM_VIDEO_CLEAR == iAlarmType)
        {
            for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
            {
                if ((iCarriageNO == g_CameraAlarmInfo[i].iCarriageNO) && (iDevPos == g_CameraAlarmInfo[i].iDevPos) && ((1 == g_CameraAlarmInfo[i].iVideoErrFlag) || (2 == g_CameraAlarmInfo[i].iVideoErrFlag)))
                {
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    if (1 == g_CameraAlarmInfo[i].iVideoErrFlag)
                    {
                        videoAlarmStr += tr("视频遮挡报警清除");
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d video shade alarm restore!", 100+iCarriageNO, 200+iDevPos-1);
                    }
                    else
                    {
                        videoAlarmStr += tr("视频丢失报警清除");
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d video lost alarm restore!", 100+iCarriageNO, 200+iDevPos-1);
                    }
                    LOG_WriteLog(&tLogInfo);
                    g_CameraAlarmInfo[i].iVideoErrFlag = 0;

                    iRow = ui->tableWidget->rowCount();//获取列表总行数
                    /*当列表总行数达到50，把后30条往前替换，删除后20条*/
                    if (MAX_ITEM_NUM == iRow)
                    {
                        for (i = 0; i < iRow-20; i++)
                        {
                            if (ui->tableWidget->item(i, 1) != NULL && ui->tableWidget->item(20+i, 1) != NULL)
                            {
                                ui->tableWidget->item(i, 1)->setText(ui->tableWidget->item(20+i, 1)->text());
                            }
                            if (ui->tableWidget->item(i, 2) != NULL && ui->tableWidget->item(20+i, 2) != NULL)
                            {
                                ui->tableWidget->item(i, 2)->setText(ui->tableWidget->item(20+i, 2)->text());
                            }
                        }

                        for (i = iRow-20; i < iRow; i++)
                        {
                            ui->tableWidget->removeRow(i);
                        }
                        ui->tableWidget->setRowCount(iRow-20);
                    }

                    iRow = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(iRow);//添加新的一行
                    ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(QString::number(iRow+1)));
                    ui->tableWidget->item(iRow, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(string));
                    ui->tableWidget->item(iRow, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(videoAlarmStr));
                    ui->tableWidget->item(iRow, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    break;
                }
            }
        }
        else
        {
            for (i = 0; i < MAX_NVR_NUM; i++)
            {
                if ((iCarriageNO == g_NvrAlarmInfo[i].iCarriageNO) && ((1 == g_NvrAlarmInfo[i].iDiskErrFlag) || (2 == g_NvrAlarmInfo[i].iDiskErrFlag)))
                {
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    if (1 == g_NvrAlarmInfo[i].iDiskErrFlag)
                    {
                        hdiskAlarmStr += tr("丢失报警清除");
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %d hdisk lost alarm restore!", 100+iCarriageNO);
                    }
                    else
                    {
                        hdiskAlarmStr += tr("错误报警清除");
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %d hdisk error alarm restore!", 100+iCarriageNO);
                    }
                    LOG_WriteLog(&tLogInfo);
                    g_NvrAlarmInfo[i].iDiskErrFlag = 0;

                    iRow = ui->tableWidget->rowCount();//获取列表总行数
                    /*当列表总行数达到50，把后30条往前替换，删除后20条*/
                    if (MAX_ITEM_NUM == iRow)
                    {
                        for (i = 0; i < iRow-20; i++)
                        {
                            if (ui->tableWidget->item(i, 1) != NULL && ui->tableWidget->item(20+i, 1) != NULL)
                            {
                                ui->tableWidget->item(i, 1)->setText(ui->tableWidget->item(20+i, 1)->text());
                            }
                            if (ui->tableWidget->item(i, 2) != NULL && ui->tableWidget->item(20+i, 2) != NULL)
                            {
                                ui->tableWidget->item(i, 2)->setText(ui->tableWidget->item(20+i, 2)->text());
                            }
                        }

                        for (i = iRow-20; i < iRow; i++)
                        {
                            ui->tableWidget->removeRow(i);
                        }
                        ui->tableWidget->setRowCount(iRow-20);
                    }

                    iRow = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(iRow);//添加新的一行
                    ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(QString::number(iRow+1)));
                    ui->tableWidget->item(iRow, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(string));
                    ui->tableWidget->item(iRow, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(hdiskAlarmStr));
                    ui->tableWidget->item(iRow, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    break;
                }
            }
        }

        /*只有当所有报警全部清除了才触发报警清除信号，让报警按钮停止闪烁*/
        for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
        {
            if ((1 == g_CameraAlarmInfo[i].iVideoErrFlag) || (2 == g_CameraAlarmInfo[i].iVideoErrFlag))
            {
                return;
            }
        }

        for (i = 0; i < MAX_NVR_NUM; i++)
        {
            if ((1 == g_NvrAlarmInfo[i].iDiskErrFlag) || (2 == g_NvrAlarmInfo[i].iDiskErrFlag))
            {
                return;
            }
        }
        emit alarmClearSignal();

    }
    else if ((ALARM_VIDEO_SHADE == iAlarmType) || (ALARM_VIDEO_LOST == iAlarmType))   //视频报警
    {
        for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
        {
            if ((iCarriageNO == g_CameraAlarmInfo[i].iCarriageNO) && (iDevPos == g_CameraAlarmInfo[i].iDevPos))
            {
                if (0 == g_CameraAlarmInfo[i].iVideoErrFlag)
                {
                    if (ALARM_VIDEO_SHADE == iAlarmType)
                    {
                        g_CameraAlarmInfo[i].iVideoErrFlag = 1;
                        videoAlarmStr += tr("视频遮挡报警");
                    }
                    else if (ALARM_VIDEO_LOST == iAlarmType)
                    {
                        g_CameraAlarmInfo[i].iVideoErrFlag = 2;
                        videoAlarmStr += tr("视频丢失报警");
                    }

                    emit alarmHappenSignal();

                    iRow = ui->tableWidget->rowCount();//获取列表总行数
                    /*当列表总行数达到50，把后30条往前替换，删除后20条*/
                    if (MAX_ITEM_NUM == iRow)
                    {
                        for (i = 0; i < iRow-20; i++)
                        {
                            if (ui->tableWidget->item(i, 1) != NULL && ui->tableWidget->item(20+i, 1) != NULL)
                            {
                                ui->tableWidget->item(i, 1)->setText(ui->tableWidget->item(20+i, 1)->text());
                            }
                            if (ui->tableWidget->item(i, 2) != NULL && ui->tableWidget->item(20+i, 2) != NULL)
                            {
                                ui->tableWidget->item(i, 2)->setText(ui->tableWidget->item(20+i, 2)->text());
                            }
                        }

                        for (i = iRow-20; i < iRow; i++)
                        {
                            ui->tableWidget->removeRow(i);
                        }
                        ui->tableWidget->setRowCount(iRow-20);
                    }

                    iRow = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(iRow);//添加新的一行
                    ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(QString::number(iRow+1)));
                    ui->tableWidget->item(iRow, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(string));
                    ui->tableWidget->item(iRow, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(videoAlarmStr));
                    ui->tableWidget->item(iRow, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    if (ALARM_VIDEO_SHADE == iAlarmType)
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d video shade alarm happen!", 100+iCarriageNO, 200+iDevPos-1);
                    }
                    else if (ALARM_VIDEO_LOST == iAlarmType)
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "camera %d.%d video lost alarm happen!", 100+iCarriageNO, 200+iDevPos-1);
                    }
                    LOG_WriteLog(&tLogInfo);
                }
                break;
            }
        }
    }

    else if ((ALARM_HDISK_LOST == iAlarmType) || (ALARM_HDISK_ERR == iAlarmType))   //硬盘报警
    {
        for (i = 0; i < MAX_NVR_NUM; i++)
        {
            if (iCarriageNO == g_NvrAlarmInfo[i].iCarriageNO)
            {
                if (0 == g_NvrAlarmInfo[i].iDiskErrFlag)
                {
                    if (ALARM_HDISK_LOST == iAlarmType)
                    {
                        g_NvrAlarmInfo[i].iDiskErrFlag = 1;
                        hdiskAlarmStr += tr("丢失报警");
                    }
                    else if (ALARM_HDISK_ERR == iAlarmType)
                    {
                        g_NvrAlarmInfo[i].iDiskErrFlag = 2;
                        hdiskAlarmStr += tr("异常报警");
                    }

                    emit alarmHappenSignal();

                    iRow = ui->tableWidget->rowCount();//获取列表总行数
                    /*当列表总行数达到50，把后30条往前替换，删除后20条*/
                    if (MAX_ITEM_NUM == iRow)
                    {
                        for (i = 0; i < iRow-20; i++)
                        {
                            if (ui->tableWidget->item(i, 1) != NULL && ui->tableWidget->item(20+i, 1) != NULL)
                            {
                                ui->tableWidget->item(i, 1)->setText(ui->tableWidget->item(20+i, 1)->text());
                            }
                            if (ui->tableWidget->item(i, 2) != NULL && ui->tableWidget->item(20+i, 2) != NULL)
                            {
                                ui->tableWidget->item(i, 2)->setText(ui->tableWidget->item(20+i, 2)->text());
                            }
                        }

                        for (i = iRow-20; i < iRow; i++)
                        {
                            ui->tableWidget->removeRow(i);
                        }
                        ui->tableWidget->setRowCount(iRow-20);
                    }

                    iRow = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(iRow);//添加新的一行
                    ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(QString::number(iRow+1)));
                    ui->tableWidget->item(iRow, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(string));
                    ui->tableWidget->item(iRow, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(hdiskAlarmStr));
                    ui->tableWidget->item(iRow, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    if (ALARM_HDISK_LOST == iAlarmType)
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %d hdisk lost alarm happen!", 100+iCarriageNO);
                    }
                    else if (ALARM_HDISK_ERR == iAlarmType)
                    {
                        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %d hdisk error alarm happen!", 100+iCarriageNO);
                    }
                    LOG_WriteLog(&tLogInfo);
                }
                break;
            }
        }
    }
    else if (ALARM_SERVER_OFFLINE == iAlarmType)    /*服务器离线，清除所有服务器相关和其相机相关的报警*/
    {
        for (i = 0; i < MAX_NVR_NUM; i++)
        {
            if (g_NvrAlarmInfo[i].iCarriageNO == iCarriageNO)
            {
                g_NvrAlarmInfo[i].iDiskErrFlag = 0;
            }
        }

        for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
        {
            if (g_CameraAlarmInfo[i].iCarriageNO == iCarriageNO)
            {
                g_CameraAlarmInfo[i].iVideoErrFlag = 0;
            }
        }

        /*只有当所有报警全部清除了才触发报警清除信号，让报警按钮停止闪烁*/
        for (i = 0; i < MAX_NVR_NUM*MAX_CAMERA_NUM; i++)
        {
            if ((1 == g_CameraAlarmInfo[i].iVideoErrFlag) || (2 == g_CameraAlarmInfo[i].iVideoErrFlag))
            {
                return;
            }
        }

        for (i = 0; i < MAX_NVR_NUM; i++)
        {
            if ((1 == g_NvrAlarmInfo[i].iDiskErrFlag) || (2 == g_NvrAlarmInfo[i].iDiskErrFlag))
            {
                return;
            }
        }
        emit alarmClearSignal();
    }
}
