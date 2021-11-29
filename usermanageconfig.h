#ifndef USERMANAGECONFIG_H
#define USERMANAGECONFIG_H

#include <QWidget>

namespace Ui {
class usermanageconfig;
}

class usermanageconfig : public QWidget
{
    Q_OBJECT

public:
    explicit usermanageconfig(QWidget *parent = nullptr);
    ~usermanageconfig();

private:
    Ui::usermanageconfig *ui;
};

#endif // USERMANAGECONFIG_H
