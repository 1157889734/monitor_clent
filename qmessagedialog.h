#ifndef QMESSAGEDIALOG_H
#define QMESSAGEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QFont>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>

class MsgBox : public QWidget
{
    Q_OBJECT

public:
    MsgBox(QWidget *parent = 0);
    ~MsgBox();
    int getStatus();

public:
    QPushButton *ok_button;
    QPushButton *close_button;
    QPushButton *cancel_button;
    QLabel *ask_label;
    QLabel *title_label;
    QString ok_text;
    QString cancel_text;
    int gStatusFlag;

public:
    void setInfo(QString title_info, QString info, bool is_ok_hidden);

signals:
    void emitstatus(int state);

protected:
    QPoint move_point;
    bool mouse_press;

public slots:
    void okOperate();
    void cancelOperate();
    void closeOperate();
};


#endif // QMESSAGEDIALOG_H
