#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include "useredit.h"
#include "useradd.h"

namespace Ui {
class userManage;
}

class userManage : public QWidget
{
    Q_OBJECT

public:
    explicit userManage(QWidget *parent = nullptr);
    ~userManage();

public slots:
    void closeButtonClick();
    void delUser();
    void addUser();
    void editUser();
    void CloseUsrEdit();
    void CloseUsrAdd();
signals:
    void SendUsrEditMsg(QString usrName);
    void SendEscape();


private:
    Ui::userManage *ui;
    userEdit *usrEditPage;
    userAdd *usrAddPage;
};

#endif // USERMANAGE_H
