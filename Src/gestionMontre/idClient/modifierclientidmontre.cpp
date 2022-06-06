#include "modifierclientidmontre.h"
#include "ui_modifierclientidmontre.h"

modifierClientIdMontre::modifierClientIdMontre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierClientIdMontre)
{
    ui->setupUi(this);
    watch = new QSerialPort;
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
}

modifierClientIdMontre::~modifierClientIdMontre()
{
    delete watch;
    delete ui;
}

void modifierClientIdMontre::on_modifier_clicked()
{
    QString command = "set client\n",
            ID = (ui->id->text())+"\n";
    watch->write(command.toLocal8Bit());
    watch->write(ID.toLocal8Bit());
}

void modifierClientIdMontre::setCom(QString comPort){
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

void modifierClientIdMontre::on_annuler_clicked()
{
    this->~modifierClientIdMontre();
}
