#ifndef USERGROUPMANAGE_H
#define USERGROUPMANAGE_H

#include <QWidget>
#include <QButtonGroup>
#include <QTableWidgetItem>
#include <QTableWidget>
#include "ckeyboard.h"

namespace Ui {
class usergroupManage;
}

class usergroupManage : public QWidget
{
    Q_OBJECT

public:
    explicit usergroupManage(QWidget *parent = nullptr);
    ~usergroupManage();
    bool eventFilter(QObject *obj, QEvent *e);
    void update_database_function();
    QButtonGroup *g_buttonGroup;
    QString gtype_text;
    void init_datavase();
    void ShowKeyboardSlots(int nShow);


signals:
    void buttonClicked(int);
    void show_hide_Signal(int value);

public slots:
    void on_addpushButton_clicked();
    void on_savepushButton_clicked();
    void on_deletepushButton_clicked();
    void choose_type_function(int type);
    void table_choose_fuction(QTableWidgetItem *item);
    void KeyboardPressKeySlots(char key);
    void show_hide_Funtion(int value);


private:
    Ui::usergroupManage *ui;
    CKeyboard *mCkeybord;

};

#endif // USERGROUPMANAGE_H
