#ifndef PRESETPASSWDCONFIRM_H
#define PRESETPASSWDCONFIRM_H

#include <QWidget>

namespace Ui {
class presetPasswdConfirm;
}

class presetPasswdConfirm : public QWidget
{
    Q_OBJECT

public:
    explicit presetPasswdConfirm(QWidget *parent = nullptr);
    ~presetPasswdConfirm();


public slots:
    void pushButtonClickSlot();

signals:
    void sendCloseSignal();
    void sendOkSignal();

private:
    Ui::presetPasswdConfirm *ui;
};

#endif // PRESETPASSWDCONFIRM_H
