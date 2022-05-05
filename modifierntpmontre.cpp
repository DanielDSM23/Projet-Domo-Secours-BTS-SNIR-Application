#include "modifierntpmontre.h"
#include "ui_modifierntpmontre.h"

modifierNtpMontre::modifierNtpMontre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierNtpMontre)
{
    ui->setupUi(this);
    watch = new QSerialPort;
    connect(this, SIGNAL(clicked()), ui->Annuler ,SIGNAL(clicked()));
}

modifierNtpMontre::~modifierNtpMontre()
{
    watch->close();
    delete watch;
    delete ui;
}

void modifierNtpMontre::on_Annuler_clicked()
{
    this->~modifierNtpMontre();
}


void modifierNtpMontre::setCom(QString comPort){
    if(!watch->isOpen()){
        watch->setPortName(comPort);
        watch->setBaudRate(QSerialPort::Baud115200);
        watch->setDataBits(QSerialPort::Data8);
        watch->setParity(QSerialPort::NoParity);
        watch->setStopBits(QSerialPort::OneStop);
        watch->setFlowControl(QSerialPort::NoFlowControl);
        watch->open(QIODevice::ReadWrite);
    }
}


void modifierNtpMontre::on_modifier_clicked()
{
    QString command = "set ntp\n",
            ntp = (ui->ntp->text())+"\n";
    watch->write(command.toLocal8Bit());
    watch->write(ntp.toLocal8Bit());
}
