#ifndef USERADD_H
#define USERADD_H

#include <QWidget>

namespace Ui {
class userAdd;
}

class userAdd : public QWidget
{
    Q_OBJECT

public:
    explicit userAdd(QWidget *parent = nullptr);
    ~userAdd();
    bool eventFilter(QObject *target, QEvent *event);


public slots:
    void closeWidgetSlot();
    void confirmSlot();
    void cancleSlot();

signals:
    void sendCloseMsg();


private:
    Ui::userAdd *ui;
};

#endif // USERADD_H
