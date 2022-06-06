#include "modifierwifimontre.h"
#include "ui_modifierwifimontre.h"

modifierWifiMontre::modifierWifiMontre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierWifiMontre)
{
    ui->setupUi(this);
    watch = new QSerialPort;
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
}

modifierWifiMontre::~modifierWifiMontre()
{
    watch->close();
    delete watch;
    delete ui;
}

void modifierWifiMontre::setCom(QString comPort){
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
void modifierWifiMontre::on_annuler_clicked()
{
    this->~modifierWifiMontre();
}

void modifierWifiMontre::on_modifier_clicked()
{
    QString command = "set wifi\n",
            ssid = (ui->ssid->text())+"\n",
            passwd = (ui->password->text())+"\n",
            passwdTech = "domo-secours2022\n";
    watch->write(command.toLocal8Bit());
    watch->write(passwdTech.toLocal8Bit());
    watch->write(ssid.toLocal8Bit());
    watch->write(passwd.toLocal8Bit());
}
