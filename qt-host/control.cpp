#include "control.h"
#include "ui_control.h"
#include "serialledctr.h"
Control::Control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control)
{
    ui->setupUi(this);
}

Control::~Control()
{
    delete ui;
}

void Control::on_returnButton_clicked()
{
    SerialLedCtr *father = new SerialLedCtr();
    this->close();
    father->show();
}
