#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class mypushbutton : public QPushButton
{
     Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent();

signals:
    void clicked_left();
    void clicked_right();
    void clicked_release();

public slots:

private:
    int click_left_flag;

};

#endif // MYPUSHBUTTON_H

