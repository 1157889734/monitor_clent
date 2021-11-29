#ifndef USEREDIT_H
#define USEREDIT_H

#include <QWidget>

namespace Ui {
class userEdit;
}

class userEdit : public QWidget
{
    Q_OBJECT

public:
    explicit userEdit(QWidget *parent = nullptr);
    ~userEdit();
    bool eventFilter(QObject *target, QEvent *event);


public slots:
    void recvOpenMsg(QString userName);
    void closeWidgetSlot();
    void confirmSlot();
    void cancleSlot();

signals:
    void sendCloseMsg();

private:
    Ui::userEdit *ui;
};

#endif // USEREDIT_H
