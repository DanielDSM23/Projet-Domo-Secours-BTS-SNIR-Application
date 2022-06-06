#include "supprimertech.h"
#include "ui_supprimertech.h"

supprimerTech::supprimerTech(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimerTech)
{
    ui->setupUi(this);
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
    //connect(ui->loginTech, SIGNAL(returnPressed()),ui->sup,SIGNAL(clicked()));
    bddIHM = new connexionBDD;
    msg = new QMessageBox;
}

supprimerTech::~supprimerTech()
{
    delete msg;
    delete bddIHM;
    delete ui;
}

void supprimerTech::on_annuler_clicked()
{
    this->~supprimerTech();
}



void supprimerTech::on_sup_clicked()
{
    if(bddIHM->getDb().isOpen()){
        QString loginTech = ui->loginTech->text();
        QString nomTechnicien;
        QSqlQuery query;
        query.exec("SELECT `nom` FROM `Admin_System` WHERE `login` = '"+loginTech+"'");
        if(query.size() == 1){
            while (query.next()){
                nomTechnicien = query.value(0).toString();
            }
            int ret = msg->warning(this, tr("Information"), tr("Voulez-vous vraiment supprimer "+loginTech.toUtf8()+" ?\nCETTE ACTION EST IRREVERSIBLE"),QMessageBox::Yes | QMessageBox::No);
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
                query.exec("DELETE FROM `Admin_System` WHERE `login` = '"+loginTech+"'");
                msg->information(this, tr("Information"), tr(loginTech.toUtf8()+" a été supprimé avec succès !"));
                this->~supprimerTech();
            }
          }
            else{
                msg->critical(this, tr("Technicien introuvable"), tr("Technicien inexistant !"));
            }


    }
}
