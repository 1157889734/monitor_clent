#include "presetpasswdconfirm.h"
#include "ui_presetpasswdconfirm.h"
#include <QMessageBox>

presetPasswdConfirm::presetPasswdConfirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::presetPasswdConfirm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    ui->passwordLineEdit->installEventFilter(this);
    ui->closePushButton->setFocusPolicy(Qt::NoFocus);
    ui->confirmPushButton->setFocusPolicy(Qt::NoFocus);
    ui->canclePushButton->setFocusPolicy(Qt::NoFocus);
    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));
    connect(ui->confirmPushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));
    connect(ui->canclePushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));
}

presetPasswdConfirm::~presetPasswdConfirm()
{
    delete ui;
}

void presetPasswdConfirm::pushButtonClickSlot()
{

    QObject *Object = sender();
    if ((Object == ui->closePushButton) || (Object == ui->canclePushButton))
    {
        emit sendCloseSignal();
    }
    if (Object == ui->confirmPushButton)
    {
        if (0 == QString::compare(ui->passwordLineEdit->text(), "12345"))
        {
            emit sendOkSignal();
        }
        else
        {
            QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("密码错误!"));     //新建消息提示框，提示错误信息
            box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("确 定"));     //将按钮显示改成"确 定"
            box.exec();
        }
    }

}
