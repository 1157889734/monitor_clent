#include "timeset.h"
#include "ui_timeset.h"
#include <QDateTime>
#include <stdio.h>

int idayNum[12]={31,28,31,30,31,30,31,31,30,31,30,31};

timeSet::timeSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timeSet)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButton_1, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_2, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_3, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_4, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_5, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_6, SIGNAL(clicked_left()), this, SLOT(stButtonClick()));
    connect(ui->pushButton_7, SIGNAL(clicked_left()), this, SLOT(okButtonClick()));
    connect(ui->pushButton_8, SIGNAL(clicked_left()), this, SLOT(cancleButtonClick()));
}

timeSet::~timeSet()
{
    delete ui;
}

void timeSet::cancleButtonClick()
{
    this->hide();
	emit cancleMsg();  
}

void timeSet::okButtonClick()
{
    this->hide();
    emit timeSetSendMsg(ui->label_2->text(), ui->label_3->text(), ui->label_4->text(), ui->label_5->text(), ui->label_6->text(), ui->label_7->text());
}

void timeSet::stButtonClick()
{
    //printf("timeSet::stButtonClick (%d,%d),(%d,%d)\n",cursor().pos().x(),cursor().pos().y(),this->pos().x(),this->pos().y());
    int num = 0, mon = 0;
    QString string = "";
    QPoint pt=cursor().pos()-((QWidget *)(this->parent()))->pos()-this->pos();
    QObject* Object=sender();
    if (Object == ui->pushButton_1)
    {
        //printf("set year! %d-%d\n",pt.x(),pt.y());
        num = ui->label_2->text().toInt();
        if (((pt.x() >= ui->pushButton_1->x()) && (pt.x() < ui->pushButton_1->x() + ui->pushButton_1->width())) && ((pt.y() >= ui->pushButton_1->y() && (pt.y() < ui->pushButton_1->y() + 27))))
        {
            //printf("up!\n");
            num +=1;
        }
        else if (((pt.x() >= ui->pushButton_1->x()) && (pt.x() < ui->pushButton_1->x() + ui->pushButton_1->width())) && ((pt.y() >= 84 && (pt.y() < 111))))
        {
            //printf("down!\n");
            num -=1;
        }
        if ((num%4==0&&num%100!=0)||(num%400==0))
        {
            idayNum[1] = 29;
        }
        else
        {
            idayNum[1] = 28;
        }
        ui->label_2->setText(QString::number(num));
    }
    if (Object == ui->pushButton_2)
    {
        num = ui->label_3->text().toInt();
        if (((pt.x() >= ui->pushButton_2->x()) && (pt.x() < ui->pushButton_2->x() + ui->pushButton_2->width())) && ((pt.y() >= ui->pushButton_2->y() && (pt.y() < ui->pushButton_2->y() + 27))))
        {
            num +=1;
            if (num > 12)
            {
                num = 1;
            }
        }
        else if (((pt.x() >= ui->pushButton_2->x()) && (pt.x() < ui->pushButton_2->x() + ui->pushButton_2->width())) && ((pt.y() >= 84 && (pt.y() < 111))))
        {
            num -=1;
            if (num < 1)
            {
                num = 12;
            }
        }
        if (num < 10)
        {
            string += "0";
        }
        string += QString::number(num);
        ui->label_3->setText(string);
    }
    if (Object == ui->pushButton_3)
    {
        mon = ui->label_3->text().toInt();
        num = ui->label_4->text().toInt();
        if (((pt.x() >= ui->pushButton_3->x()) && (pt.x() < ui->pushButton_3->x() + ui->pushButton_3->width())) && ((pt.y() >= ui->pushButton_3->y() && (pt.y() < ui->pushButton_3->y() + 27))))
        {
            num +=1;
            if (num > idayNum[mon-1])
            {
                num = 1;
            }
        }
        else if (((pt.x() >= ui->pushButton_3->x()) && (pt.x() < ui->pushButton_3->x() + ui->pushButton_3->width())) && ((pt.y() >= 84 && (pt.y() < 111))))
        {
            num -=1;
            if (num < 1)
            {
                num = idayNum[mon-1];
            }
        }
        if (num < 10)
        {
            string += "0";
        }
        string += QString::number(num);
        ui->label_4->setText(string);
    }
    if (Object == ui->pushButton_4)
    {
        num = ui->label_5->text().toInt();
        if (((pt.x() >= ui->pushButton_4->x()) && (pt.x() < ui->pushButton_4->x() + ui->pushButton_4->width())) && ((pt.y() >= ui->pushButton_4->y() && (pt.y() < ui->pushButton_4->y() + 30))))
        {
            num +=1;
            if (num > 23)
            {
                num = 0;
            }
        }
        else if (((pt.x() >= ui->pushButton_4->x()) && (pt.x() < ui->pushButton_4->x() + ui->pushButton_4->width())) && ((pt.y() >= 214 && (pt.y() < 238))))
        {
            num -=1;
            if (num < 0)
            {
                num = 23;
            }
        }
        if (num < 10)
        {
            string += "0";
        }
        string += QString::number(num);
        ui->label_5->setText(string);
    }
    if (Object == ui->pushButton_5)
    {
        num = ui->label_6->text().toInt();
        if (((pt.x() >= ui->pushButton_5->x()) && (pt.x() < ui->pushButton_5->x() + ui->pushButton_5->width())) && ((pt.y() >= ui->pushButton_5->y() && (pt.y() < ui->pushButton_5->y() + 30))))
        {
            num +=1;
            if (num > 59)
            {
                num = 0;
            }
        }
        else if (((pt.x() >= ui->pushButton_5->x()) && (pt.x() < ui->pushButton_5->x() + ui->pushButton_5->width())) && ((pt.y() >= 214 && (pt.y() < 238))))
        {
            num -=1;
            if (num < 0)
            {
                num = 59;
            }
        }
        if (num < 10)
        {
            string += "0";
        }
        string += QString::number(num);
        ui->label_6->setText(string);
    }
    if (Object == ui->pushButton_6)
    {
        num = ui->label_7->text().toInt();
        if (((pt.x() >= ui->pushButton_6->x()) && (pt.x() < ui->pushButton_6->x() + ui->pushButton_6->width())) && ((pt.y() >= ui->pushButton_6->y() && (pt.y() < ui->pushButton_6->y() + 30))))
        {
            num +=1;
            if (num > 59)
            {
                num = 0;
            }
        }
        else if (((pt.x() >= ui->pushButton_6->x()) && (pt.x() < ui->pushButton_6->x() + ui->pushButton_6->width())) && ((pt.y() >= 214 && (pt.y() < 238))))
        {
            num -=1;
            if (num < 0)
            {
                num = 59;
            }
        }
        if (num < 10)
        {
            string += "0";
        }
        string += QString::number(num);
        ui->label_7->setText(string);
    }
}

void timeSet::setTimeLabelText(int year, int month, int day, int hour, int min, int sec)
{
	QString string = "";
	ui->label_2->setText(QString::number(year));
	if (month < 10)
    {
        string = "0";
    }
    else
    {
        string = "";
    }
    string += QString::number(month);
	ui->label_3->setText(string);
	if (day < 10)
    {
        string = "0";
    }
    else
    {
        string = "";
    }
    string += QString::number(day);
	ui->label_4->setText(string);
	if (hour < 10)
    {
        string = "0";
    }
    else
    {
        string = "";
    }
    string += QString::number(hour);
	ui->label_5->setText(string);
	if (min < 10)
    {
        string = "0";
    }
    else
    {
        string = "";
    }
    string += QString::number(min);
	ui->label_6->setText(string);
	if (sec < 10)
    {
        string = "0";
    }
    else
    {
        string = "";
    }
    string += QString::number(sec);
	ui->label_7->setText(string);
}
