#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

Dialog::Dialog(QDateTime dateTime, QString str):
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(dateTime);
    ui->label_2->setText(QString::fromLocal8Bit(str.toLatin1().data()));
}
