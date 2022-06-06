#ifndef WATCHEDITOR_H
#define WATCHEDITOR_H

#include <QMainWindow>
#include "Src/connexion/connexionbdd.h"
#include "Src/gestionClient/ajouterClient/ajouterclient.h"
#include "Src/gestionClient/supprimerClient/supprimerclient.h"
#include <QTimer>
#include "Src/gestionTech/ajouterTech/ajoutertechnicien.h"
#include "Src/gestionClient/modifierClient/modifierclient.h"
#include "Src/about/about.h"
#include "Src/gestionTech/supprimerTech/supprimertech.h"
#include "Src/gestionTech/modifierMdpTech/modifiermdptech.h"
#include <QtSerialPort/QSerialPortInfo>
#include "Src/gestionMontre/wifi/modifierwifimontre.h"
#include "Src/gestionMontre/ntp/modifierntpmontre.h"
#include "Src/gestionMontre/mqtt/modifiermqttmontre.h"
#include "Src/gestionMontre/idClient/modifierclientidmontre.h"
class ajouterClient;

class supprimerClient;

class ajouterTechnicien;

class supprimerTech;

class modifierMdpTech;

class modifierClient;
namespace Ui {
class watchEditor;
}

class watchEditor : public QMainWindow
{
    Q_OBJECT

public:
    QSqlQuery * query;
    explicit watchEditor(QWidget *parent = 0);

    ~watchEditor();
     void setNom(QString);
     void adminAccess(QString);
private slots:
     void on_actionAjouter_client_triggered();

     void on_actionSupprimer_client_triggered();

     void deconnexion();

     void on_deco_clicked();

     void on_actionAjouter_technicien_triggered();

     void exitProg();

     void on_actionModifier_Client_triggered();

     void on_actionA_propos_triggered();

     void on_actionSupprimer_technicien_triggered();

     int minute(int);
     void on_actionRemplacer_MDP_triggered();

     void verifyUsb();

     void on_actionModifier_wifi_montre_triggered();

     void on_actionModifier_NTP_montre_triggered();

     void on_actionModifier_MQTT_montre_triggered();

     void on_actionModifier_ID_client_triggered();

private:
    Ui::watchEditor *ui;
    ajouterClient * addclient;
    QSqlDatabase db;
    supprimerClient * delClient;
    QTimer * timer;
    QTimer * timerUsb;
    connexionBDD * ihmbdd;
    ajouterTechnicien *addTech;
    modifierClient * modifyClient;
    about * aPropos;
    supprimerTech * delTech;
    modifierMdpTech * modifyPassTech;
    QList<QSerialPortInfo> serialInfoList;
    QSerialPortInfo serialInfo;
    QString portCom;
    bool isWatchConnected = false;
    int atAddr = -1;
    modifierWifiMontre * wifiWatch;
    modifierNtpMontre * ntpWatch;
    modifierMqttMontre * mqttWatch;
    modifierClientIdMontre * idWatch;

protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();

};

#endif // WATCHEDITOR_H
