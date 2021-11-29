#ifndef TIMESET_H
#define TIMESET_H

#include <QWidget>

namespace Ui {
class timeSet;
}

class timeSet : public QWidget
{
    Q_OBJECT

public:
    explicit timeSet(QWidget *parent = 0);
    ~timeSet();
	void setTimeLabelText(int year, int month, int day, int hour, int min, int sec);

public slots:
    void cancleButtonClick();
    void okButtonClick();
    void stButtonClick();   

signals:
    void timeSetSendMsg(QString year, QString month, QString day, QString hour, QString min, QString sec);
    void cancleMsg();

private:
    Ui::timeSet *ui;
};

#endif // TIMESET_H
