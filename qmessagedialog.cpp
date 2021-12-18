#include "qmessagedialog.h"
#include <QDebug>


MsgBox::MsgBox(QWidget *parent)
    : QWidget(parent)
{
    this->resize(320, 160);

    //获取主界面的宽度
    int width = this->width();
    int height = this->height();
    gStatusFlag = 0;
    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    close_button = new QPushButton(this);
    close_button->setGeometry(width-30,5, 20, 20);
    close_button->setStyleSheet("border-image: url(:/res/close.png);");

    //设置标题
    title_label = new QLabel(this);
    QFont font = title_label->font();
    font.setPixelSize(20);
//    font.setBold(true);
    title_label->setFont(font);
    title_label->setGeometry(0, 0, width-50, 30);


    //设置提示信息，让QLabel能够自动判断并换行显示：
    ask_label = new QLabel(this);
    ask_label->setGeometry(0, 40, width, 25*2);
    ask_label->setFont(font);
    ask_label->setScaledContents(true);
    ask_label->setWordWrap(true);
    ask_label->setAlignment(Qt::AlignCenter);

    cancel_button = new QPushButton(this);
    cancel_button->resize(100, 30);
    cancel_button->setFont(font);
    cancel_button->move(width - cancel_button->width() - 10, height - 35);

    ok_button = new QPushButton(this);
    ok_button->resize(100, 30);
    ok_button->setFont(font);

    ok_button->move(width - ok_button->width() - cancel_button->width() - 20, height - 35);


    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(okOperate()));
    QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(closeOperate()));
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));

}

MsgBox::~MsgBox()
{
    delete close_button;
    close_button = NULL;

    delete title_label;
    title_label = NULL;

    delete ask_label;
    ask_label = NULL;

    delete cancel_button;
    cancel_button =NULL;

    delete ok_button;
    ok_button =NULL;

}

//设置对话框信息
void MsgBox::setInfo(QString title_info, QString info,bool is_ok_hidden)
{
  title_label->setText(QString("  ") + title_info);

  //设置提示信息
  ask_label->setText(info);

  //是否隐藏确定按钮
  ok_button->setHidden(is_ok_hidden);
  if(is_ok_hidden)
  {
      cancel_button->setText(tr("OK"));
      cancel_button->move((this->width() / 2)-(cancel_button->width()/2), (this->height()-35));

  }
  else
  {
      cancel_button->move((cancel_button->width()/2), (this->height()-35));
      ok_button->move((this->width()- (ok_button->width()) -(cancel_button->width()/2) ), (this->height()-35));
      ok_button->setText(tr("OK"));
      cancel_button->setText(tr("Cancel"));

  }

  //设置默认按钮为取消按钮
  cancel_button->setFocus();
}


//确认操作
void MsgBox::okOperate()
{
    gStatusFlag = 1;
    emit emitstatus(gStatusFlag);

    close();
}
//取消操作
void MsgBox::cancelOperate()
{
    gStatusFlag = 0;
    emit emitstatus(gStatusFlag);

    close();

}

//关闭窗体操作
void MsgBox::closeOperate()
{
    gStatusFlag = 1;
    emit emitstatus(gStatusFlag);

    close();
}

int MsgBox::getStatus()
{
    return gStatusFlag;
}
