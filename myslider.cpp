#include "myslider.h"
#include <stdio.h>
#include <QDebug>


mySlider::mySlider(QWidget *parent) :
    QSlider(parent)
{

}

mySlider::~mySlider()
{

}
void mySlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    int iDur = 0, iPos = 0;

    if (mouseEvent->button() == Qt::LeftButton)	//判断左键
    {
        iDur = maximum() - minimum();
        iPos = minimum() + iDur * ((double)mouseEvent->x() / width());

        emit presliderPressSianal(iPos);
    }
    QSlider::mousePressEvent(mouseEvent);
}

void mySlider::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    int iDur = 0, iPos = 0;

    iDur = maximum() - minimum();
    iPos = minimum() + iDur * ((double)mouseEvent->x() / width());

    emit presliderMoveSianal(iPos);
    QSlider::mouseReleaseEvent(mouseEvent);
}
