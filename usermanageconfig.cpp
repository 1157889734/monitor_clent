#include "usermanageconfig.h"
#include "ui_usermanageconfig.h"

usermanageconfig::usermanageconfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usermanageconfig)
{
    ui->setupUi(this);
}

usermanageconfig::~usermanageconfig()
{
    delete ui;
}
