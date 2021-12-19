#ifndef PRESETPASSWDCONFIRM_H
#define PRESETPASSWDCONFIRM_H

#include <QWidget>
#include "ckeyboard.h"

namespace Ui {
class presetPasswdConfirm;
}

class presetPasswdConfirm : public QWidget
{
    Q_OBJECT

public:
    explicit presetPasswdConfirm(QWidget *parent = nullptr);
    ~presetPasswdConfirm();
    bool eventFilter(QObject *obj, QEvent *e);
    void ShowKeyboardSlots(int nShow);

public slots:
    void pushButtonClickSlot();
    void KeyboardPressKeySlots(char key);
    void show_hide_Funtion(int value);


signals:
    void sendCloseSignal();
    void sendOkSignal();
    void show_hide_Signal(int value);

private:
    Ui::presetPasswdConfirm *ui;
    CKeyboard *mCkeybord;

};

#endif // PRESETPASSWDCONFIRM_H
