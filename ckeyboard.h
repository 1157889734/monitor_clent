#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLabel>
#include "define.h"
#include<QDebug>
#include<QDesktopWidget>
#include<QPushButton>
#include<QSignalMapper>
#include<QVector>
#include<QButtonGroup>
#include<QTextCursor>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>

#define BSPACE 0x2
#define TAB 0X3
#define CAPS 0x4
#define ENTER 0x5
#define SHIFT 0x6
#define SHIFT2 0x7

namespace Ui {
class CKeyboard;
}

class CKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit CKeyboard(QWidget *parent = nullptr,int type = 0);
    ~CKeyboard();
    void ResizeControl(int width,int height);
    void ResizeControl_600P(int width,int height);
    void CreatKeyBoard();
    void SetControlStyleSheet();
    void SetControlStyleSheet_600P();
    bool IsSpecialButton(char but);

private:
    Ui::CKeyboard *ui;
    QVector<char>CapKey;
    QVector<char>ComKey;
    QList<QPushButton *> allButtons;
    QButtonGroup *m_buGroup;
    QPushButton*  keyBoardButton[54];
    int keyButtonCount;

    bool    bCapsOn;
    int     ShiftIndex;

private slots:
    void buttonNumslot(int);

signals:
    void KeyboardPressKeySignal(char);


};

#endif // KEYBOARD_H
