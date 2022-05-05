#include "ui_watcheditor.h"
#include "watcheditor.h"
#include <QDebug>
watchEditor::watchEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::watchEditor)
{
    ui->setupUi(this);
    QPixmap pix("./logo-domo.png");
    ui->label_3->setPixmap(pix);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->menuGestion_montre->setEnabled(false);
    timer = new QTimer();
    timerUsb = new QTimer();
    timer->setInterval(minute(1));
    timerUsb->setInterval(1000);
    connect(this, SIGNAL(clicked()), this ,SLOT(exitProg()));
    connect(timer, SIGNAL(timeout()), this, SLOT(deconnexion()));
    connect(timerUsb, SIGNAL(timeout()), this, SLOT(verifyUsb()));
    timer->start();
    timerUsb->start();
    serialInfoList = QSerialPortInfo::availablePorts();
        if (serialInfoList.size() < 0)
        {
            portCom = nullptr;
        }
        else
        {
            for (int i=0; i<serialInfoList.size(); i++)
            {
                serialInfo = serialInfoList.at(i);
                if(serialInfo.manufacturer() == "wch.cn" && serialInfo.description() == "USB-SERIAL CH340"
                        && serialInfo.vendorIdentifier() == 6790 && serialInfo.productIdentifier() == 29987){
                    portCom = serialInfo.portName();
                    isWatchConnected = true;
                    atAddr = i;
                    ui->label->setText("<font color=\"#15B7B9\">Montre OK!</font>");
                    ui->label->setAlignment(Qt::AlignCenter);
                    ui->menuGestion_montre->setEnabled(true);
                }
            }
        }
}

watchEditor::~watchEditor()
{
    delete timer;
    delete ui;
}


void watchEditor::setNom(QString nom){
    nom = "Technicien : "+nom;
    ui->label_2->setText(nom);
    this->setWindowTitle("Technicien Domo-Secours - "+nom);
}

void watchEditor::on_actionAjouter_client_triggered()
{
    addclient = new ajouterClient;
    addclient->show();
    timer->setInterval(minute(10));
}




void watchEditor::on_actionSupprimer_client_triggered()
{
    delClient = new supprimerClient;
    delClient->show();
    timer->setInterval(minute(10));
}

void watchEditor::deconnexion(){
    ihmbdd = new connexionBDD;
    ihmbdd->show();
    this->~watchEditor();
}

void watchEditor::on_deco_clicked()
{
    ihmbdd = new connexionBDD;
    ihmbdd->show();
    this->~watchEditor();
}


void watchEditor::adminAccess(QString id){
    if(id.toLower() == "admin"){
        ui->menuGestion_technicien->menuAction()->setVisible(true);
    }
    else{
        ui->menuGestion_technicien->menuAction()->setVisible(false);
    }
}

void watchEditor::on_actionAjouter_technicien_triggered()
{
    addTech = new ajouterTechnicien;
    addTech->show();
    timer->setInterval(minute(10));
}


void watchEditor::exitProg(){
    exit(0);
}

void watchEditor::on_actionModifier_Client_triggered()
{
    modifyClient = new modifierClient;
    modifyClient->setWindowModality(Qt::WindowModal);
    modifyClient->show();
    timer->setInterval(minute(10));
}

void watchEditor::on_actionA_propos_triggered()
{
    aPropos = new about;
    aPropos->setModal(true);
    aPropos->show();
    timer->setInterval(minute(10));
}


void watchEditor::on_actionSupprimer_technicien_triggered()
{
    delTech = new supprimerTech;
    delTech->setModal(true);
    delTech->show();
    timer->setInterval(minute(10));
}


int watchEditor::minute(int min){
    return min*60*1000;
}

void watchEditor::on_actionRemplacer_MDP_triggered()
{
    modifyPassTech = new modifierMdpTech;
    modifyPassTech->setModal(true);
    modifyPassTech->show();
    timer->setInterval(minute(10));
}

void watchEditor::verifyUsb(){
    if(serialInfo.isValid() == false){
        portCom = nullptr;
        isWatchConnected = false;
        ui->label->setText("<font color=\"#D96E2E\">Montre non OK!</font>");
        ui->label->setAlignment(Qt::AlignCenter);
        ui->menuGestion_montre->setEnabled(false);
        atAddr = -1;
    }
    if(isWatchConnected == false && atAddr == -1){
        serialInfoList = QSerialPortInfo::availablePorts();
            if (serialInfoList.size() < 0)
            {
                portCom = nullptr;
            }
            else
            {
                for (int i=0; i<serialInfoList.size(); i++)
                {
                    serialInfo = serialInfoList.at(i);
                    if(serialInfo.manufacturer() == "wch.cn" && serialInfo.description() == "USB-SERIAL CH340"
                            && serialInfo.vendorIdentifier() == 6790 && serialInfo.productIdentifier() == 29987){
                        portCom = serialInfo.portName();
                        isWatchConnected = true;
                        atAddr = i;
                        ui->label->setText("<font color=\"#15B7B9\">Montre OK!</font>");
                        ui->label->setAlignment(Qt::AlignCenter);
                        ui->menuGestion_montre->setEnabled(true);
                    }
                }
            }
    }
}

void watchEditor::on_actionModifier_wifi_montre_triggered()
{
    wifiWatch = new modifierWifiMontre;
    wifiWatch->setCom(portCom);
    wifiWatch->setModal(true);
    wifiWatch->show();
    timer->setInterval(minute(10));
}




void watchEditor::on_actionModifier_NTP_montre_triggered()
{
    ntpWatch = new modifierNtpMontre;
    ntpWatch->setCom(portCom);
    ntpWatch->setModal(true);
    ntpWatch->show();
    timer->setInterval(minute(10));
}
