#ifndef USERGROUPMANAGE_H
#define USERGROUPMANAGE_H

#include <QWidget>
#include <QButtonGroup>
#include <QTableWidgetItem>
#include <QTableWidget>

namespace Ui {
class usergroupManage;
}

class usergroupManage : public QWidget
{
    Q_OBJECT

public:
    explicit usergroupManage(QWidget *parent = nullptr);
    ~usergroupManage();
    void update_database_function();
    QButtonGroup *g_buttonGroup;
    QString gtype_text;
    void init_datavase();


signals:
    void buttonClicked(int);
public slots:
    void on_addpushButton_clicked();
    void on_savepushButton_clicked();
    void on_deletepushButton_clicked();
    void choose_type_function(int type);
    void table_choose_fuction(QTableWidgetItem *item);

private:
    Ui::usergroupManage *ui;
};

#endif // USERGROUPMANAGE_H
