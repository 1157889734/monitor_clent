#include "presetpasswdconfirm.h"
#include "ui_presetpasswdconfirm.h"
#include <QMessageBox>
static int g_ibShowKeyboard = 0;

presetPasswdConfirm::presetPasswdConfirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::presetPasswdConfirm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    ui->passwordLineEdit->installEventFilter(this);


    mCkeybord = new CKeyboard(this,0);
    mCkeybord->setGeometry(50,500,924,200);
    mCkeybord->hide();


    ui->passwordLineEdit->installEventFilter(this);
    ui->closePushButton->setFocusPolicy(Qt::NoFocus);
    ui->confirmPushButton->setFocusPolicy(Qt::NoFocus);
    ui->canclePushButton->setFocusPolicy(Qt::NoFocus);
    connect(ui->closePushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));
    connect(ui->confirmPushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));
    connect(ui->canclePushButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClickSlot()));


    connect(this,SIGNAL(show_hide_Signal(int)),this,SLOT(show_hide_Funtion(int)));
    connect(mCkeybord,SIGNAL(KeyboardPressKeySignal(char)),this,SLOT(KeyboardPressKeySlots(char)));

}

presetPasswdConfirm::~presetPasswdConfirm()
{
    delete mCkeybord;
    mCkeybord =NULL;

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
            static QMessageBox box(QMessageBox::Warning,QString::fromUtf8("错误"),QString::fromUtf8("密码错误!"));     //新建消息提示框，提示错误信息
            box.setWindowFlags(Qt::FramelessWindowHint);
            box.setStandardButtons (QMessageBox::Ok);   //设置提示框只有一个标准按钮
            box.setButtonText (QMessageBox::Ok,QString::fromUtf8("OK"));     //将按钮显示改成"确 定"
            box.exec();

        }
    }

}


void presetPasswdConfirm::ShowKeyboardSlots(int nShow)
{
    if(0 == nShow)
    {
        emit show_hide_Signal(nShow);
        g_ibShowKeyboard =0;
    }
    else
    {
        if(g_ibShowKeyboard ==0)
        {
            emit show_hide_Signal(nShow);
            g_ibShowKeyboard =1;

        }
    }
}

bool presetPasswdConfirm::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        if(obj == ui->passwordLineEdit && ui->passwordLineEdit->isEnabled())         //判断是不是我创建的label触发了事件
        {
            ShowKeyboardSlots(1);
        }

    }
    else if(e->type() == QEvent::FocusOut)
    {
        if(obj == ui->passwordLineEdit)
        {
            ShowKeyboardSlots(0);
        }

    }
    return QWidget::eventFilter(obj, e);


}

void presetPasswdConfirm::show_hide_Funtion(int value)
{
    if(0 == value)
    {
        mCkeybord->hide();

    }
    else
    {
        mCkeybord->show();

    }
}

void presetPasswdConfirm::KeyboardPressKeySlots(char key)
{
    if(key==BSPACE)
     {
         if(ui->passwordLineEdit->hasFocus())//输入框1焦点
         {
             if(!ui->passwordLineEdit->selectedText().isEmpty())
             {
                  ui->passwordLineEdit->del();
             }
             else
             {
                 ui->passwordLineEdit->backspace();
             }
         }
    }
    else if(key == ENTER)
    {
        ShowKeyboardSlots(0);
    }
    else
    {
        if(ui->passwordLineEdit->hasFocus())//输入框1焦点
        {
            ui->passwordLineEdit->insert(QString( key));
        }
    }
}

