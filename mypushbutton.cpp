#include "mypushbutton.h"

mypushbutton::mypushbutton(QWidget *parent) :
    QPushButton(parent)
{
    click_left_flag = 0;
}

void mypushbutton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        click_left_flag = 1;
        emit clicked_left();
    }
    else if (event->button() == Qt::RightButton)
    {
        click_left_flag = 0;
        emit clicked_right();
    }
}

void mypushbutton::mouseReleaseEvent()    //只处理左键释放
{
    if (1 == click_left_flag)
    {
        click_left_flag = 0;
        emit clicked_release();
    }
}

