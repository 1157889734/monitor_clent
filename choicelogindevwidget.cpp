#include "choicelogindevwidget.h"
#include "ui_choicelogindevwidget.h"
#include "loginwidget.h"
#include "state.h"

choiceLoginDevWidget::choiceLoginDevWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choiceLoginDevWidget)
{
    ui->setupUi(this);
    char acVersion[32] = {0};

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/monres/background.bmp")));
    QIcon icon;
    this->setPalette(palette);
    this->setGeometry(0,0,1024,768);
    this->showFullScreen();


    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->cvmsPushButton->setFocusPolicy(Qt::NoFocus); // 得到焦点时，不显示虚线框
    ui->pvmsPushButton->setFocusPolicy(Qt::NoFocus);


    connect(ui->cvmsPushButton, SIGNAL(clicked()), this, SLOT(choiceCvmsSlot()));
    connect(ui->pvmsPushButton, SIGNAL(clicked()), this, SLOT(choicePvmsSlot()));

    STATE_GetSysVersion(acVersion, sizeof(acVersion));
    if (strlen(acVersion) != 0)
    {
//        DebugPrint(DEBUG_UI_NOMAL_PRINT, "ui app version:%s!\n",acVersion);
        ui->versionLabel->setText(QString(QLatin1String(acVersion)));
    }

}

choiceLoginDevWidget::~choiceLoginDevWidget()
{
    delete ui;
}
void choiceLoginDevWidget::showPageSlot()
{
    this->show();
}

void choiceLoginDevWidget::choiceCvmsSlot()
{

    this->hide();
    emit confirmDevTypeSignal();
}

void choiceLoginDevWidget::choicePvmsSlot()
{
//    this->hide();
//    emit confirmDevTypeSignal(E_PVMSTYPE);
}
