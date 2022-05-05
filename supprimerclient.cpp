#include "supprimerclient.h"
#include "ui_supprimerclient.h"

supprimerClient::supprimerClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::supprimerClient)
{
    ui->setupUi(this);
    ui->idClient->selectAll();
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
    connect(ui->idClient, SIGNAL(returnPressed()),ui->sup,SIGNAL(clicked()));
    bddIHM = new connexionBDD;
    msg = new QMessageBox;
}

supprimerClient::~supprimerClient()
{
    delete msg;
    delete bddIHM;
    delete ui;
}

void supprimerClient::on_annuler_clicked()
{
    this->~supprimerClient();
}

void supprimerClient::on_sup_clicked()
{
    if(bddIHM->getDb().isOpen()){
        QString clientId = ui->idClient->text();
        bool isNum = false;
        clientId.toInt(&isNum);
        QString nomClient;
        QString prenomClient;
        QSqlQuery query;
        QString test;
        if(isNum){
            query.exec("SELECT info_client.nom FROM info_client WHERE info_client.client_id = "+clientId+";");
            if(query.size() == 1){
                while (query.next()){
                    nomClient = query.value(0).toString();
                }
                query.exec("SELECT info_client.prenom FROM info_client WHERE info_client.client_id = "+clientId+";");
                while (query.next()){
                    prenomClient = query.value(0).toString();
                }
                query.exec("SELECT * FROM info_client;");
                int ret = msg->warning(this, tr("Information"), tr("Voulez-vous vraiment supprimer "+nomClient.toUtf8()+" "+prenomClient.toUtf8()+" ?\nCETTE ACTION EST IRREVERSIBLE"),QMessageBox::Yes | QMessageBox::No);
                bool deleteUser;
                switch (ret) {
                   case QMessageBox::Yes:
                       deleteUser=true;
                       break;
                   case QMessageBox::No:
                       deleteUser=false;
                       break;
                   default:
                       deleteUser=false;
                       break;
                 }
                if(deleteUser == true){
                    query.exec("DELETE FROM med_client WHERE med_client.info_client_client_id = "+clientId);
                    query.exec("DELETE FROM info_client WHERE info_client.client_id = "+clientId);
                    msg->information(this, tr("Information"), tr(nomClient.toUtf8()+" "+prenomClient.toUtf8()+" a été supprimé avec succès !"));
                    this->~supprimerClient();
                }
              }
                else{
                    msg->critical(this, tr("Mauvais ID client"), tr("ID Client renseigné non trouvé\nVeuillez verifier l'ID du client !"));
                }
        }
        else{
            msg->critical(this, tr("Mauvaise valeur"), tr("Veuillez mettre un entier !"));
        }

    }
}
