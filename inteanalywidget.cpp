#include "inteanalywidget.h"
#include "ui_inteanalywidget.h"
#include <QLineEdit>
#define PVMSPAGETYPE  2    //此页面类型，2表示受电弓监控页面

static int g_iDNum = 0;

inteAnalyWidget::inteAnalyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inteAnalyWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);


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


    ui->StartdateEdit->setCalendarPopup(true);
    ui->EnddateEdit->setCalendarPopup(true);

    ui->EnddateEdit->setDateTime(QDateTime::currentDateTime());
//    ui->EndtimeEdit->setDateTime(QDateTime::currentDateTime());

    ui->StartdateEdit->setDateTime(QDateTime::currentDateTime());
//    ui->StarttimeEdit->setDateTime(QDateTime::currentDateTime());

    ui->StartdateEdit->dumpObjectTree();
    QLineEdit* lEdit = ui->StartdateEdit->findChild<QLineEdit*>();
    if(lEdit)
        lEdit->setReadOnly(true);


    ui->StartdateEdit->setLocale(QLocale::Chinese);

    ui->EnddateEdit->dumpObjectTree();
    QLineEdit* lEdit2 = ui->EnddateEdit->findChild<QLineEdit*>();
    if(lEdit2)
        lEdit2->setReadOnly(true);
    ui->EnddateEdit->setLocale(QLocale::Chinese);



    int value = QTime::currentTime().hour();
    ui->EndcomboBox->setCurrentIndex(value);
    ui->StartcomboBox->setCurrentIndex(0);

    m_alarmHappenTimer = NULL;



}

inteAnalyWidget::~inteAnalyWidget()
{
    delete ui;
}

void inteAnalyWidget::pageShowCtrl()  //每次切换到当前页面，则更新查询起始和结束时间控件显示
{
    QDateTime time = QDateTime::currentDateTime();

    ui->StartdateEdit->setDate(time.date());
    ui->EnddateEdit->setDate(time.date());
    int value = QTime::currentTime().hour();
     ui->EndcomboBox->setCurrentIndex(value);
//    ui->EndtimeEdit->setTime(time.time());

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
