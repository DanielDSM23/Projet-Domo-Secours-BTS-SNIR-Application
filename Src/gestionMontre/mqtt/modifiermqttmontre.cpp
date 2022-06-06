#include "modifiermqttmontre.h"
#include "ui_modifiermqttmontre.h"

modifierMqttMontre::modifierMqttMontre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierMqttMontre)
{
    ui->setupUi(this);
    watch = new QSerialPort;
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
}

modifierMqttMontre::~modifierMqttMontre()
{
    delete watch;
    delete ui;

}

void modifierMqttMontre::setCom(QString comPort){
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
void modifierMqttMontre::on_modifier_clicked()
{
    QString command = "set mqtt\n",
            mqtt = (ui->mqtt->text())+"\n";
    watch->write(command.toLocal8Bit());
    watch->write(mqtt.toLocal8Bit());
}

void modifierMqttMontre::on_annuler_clicked()
{
    this->~modifierMqttMontre();
}
