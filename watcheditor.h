#ifndef WATCHEDITOR_H
#define WATCHEDITOR_H

#include <QMainWindow>
#include "connexionbdd.h"
#include "ajouterclient.h"
#include "supprimerclient.h"
#include <QTimer>
#include "ajoutertechnicien.h"
#include "modifierclient.h"
#include "about.h"
#include "supprimertech.h"
#include "modifiermdptech.h"
#include <QtSerialPort/QSerialPortInfo>
#include "modifierwifimontre.h"
#include "modifierntpmontre.h"
class ajouterClient;

class supprimerClient;

class ajouterTechnicien;

class supprimerTech;

class modifierMdpTech;

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

protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();

};

#endif // WATCHEDITOR_H
