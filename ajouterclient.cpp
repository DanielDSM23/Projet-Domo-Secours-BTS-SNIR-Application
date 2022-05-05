#include "ajouterclient.h"
#include "ui_ajouterclient.h"
#include <QDebug>
#include <QCloseEvent>

#include <shlobj.h>
#include <shlwapi.h>
#include <bits/stdc++.h>

#include<time.h>
ajouterClient::ajouterClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ajouterClient)
{
    ui->setupUi(this);
    bddIHM = new connexionBDD;
    wait = new pleaseWait;
    msg = new QMessageBox;
    QPixmap pix("./logo-domo3.png");
    ui->label_2->setPixmap(pix);
    ui->nom->selectAll();
    ui->progressBar->setVisible(false);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(100);
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
}

ajouterClient::~ajouterClient()
{
    delete ui;
    delete bddIHM;
    delete msg;
    delete wait;
    //delete smtpClient;

}

void ajouterClient::on_ajouter_clicked()
{
    ui->ajouter->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar->setFormat("Recuperation infos...");
    bool canBeSended[2] = {false, false};
    QString nomClient = ui->nom->text(),
            prenomClient = ui->prenom->text(),
            mailClient = ui->mail->text(),
            adresseClient = ui->textEdit->toPlainText(),
            dateNaissanceClient = ui->dateNaissance->text(),
            numeroEcuClient = ui->numeroECU->text(),
            poidsClient = "'"+ui->poids->text()+"'",
            tailleClient = "'"+ui->taille->text()+"'",
            numeroSecuClient = "'"+ui->numeroMedecin_2->text()+"'",
            numeroSecoursClient = "'"+ui->numeroSecours->text()+"'",
            numeroMedecinClient = "'"+ui->numeroMedecin->text()+"'",
            pathologiesClient = "'"+ui->textEdit_2->toPlainText()+"'",
            sexe,
            clientID,
            message,
            password = QString::fromStdString(gen_random(10)),
            msgInfo;
            //encodedPassword = QCryptographicHash::hash( password,QCryptographicHash::Md5).toHex();
    if(ui->femme->isChecked()){
        sexe = 'F';

    }
    if(ui->homme->isChecked()){
        sexe = 'M';
    }
    QStringList date = dateNaissanceClient.split("/");
    dateNaissanceClient = date[2]+"-"+date[1]+"-"+date[0];
    //formulaire non remplie
    if(nomClient.isEmpty() ||
            prenomClient.isEmpty() ||
            mailClient.isEmpty() ||
            adresseClient.isEmpty() ||
            numeroEcuClient.isEmpty()||sexe == nullptr){
        msg->warning(this, tr("Formulaire"),tr("Veuillez remplir le formulaire !"));
    }
    else{
        canBeSended[0] = true;
    }
    if(!(ui->mail->text().contains("@")) && !(ui->mail->text().contains("."))){
        msg->warning(this, tr("Formulaire"),tr("Verifier adresse e-mail !"));
    }
    else{
        canBeSended[1] = true;
    }
    if(bddIHM->getDb().isOpen() && (canBeSended[0] & canBeSended[1])){
        ui->progressBar->setFormat("Importation du contact sur BDD...");
        QSqlQuery query;
        query.exec("INSERT INTO `info_client` (`client_id`, `nom`, `prenom`, `email`, `adresse`, `password`) "
                   "VALUES (NULL, '"+nomClient+"', '"+prenomClient+"', '"+mailClient+"', '"+adresseClient+"', MD5('"+password+"') );");//gen_random(10).toUtf8() //QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex();
        query.exec("SELECT `client_id` FROM `info_client` WHERE info_client.email='"+mailClient+"';");
        while (query.next()){
           clientID = query.value(0).toString();
        }
        if(poidsClient.isEmpty()){poidsClient = "NULL";}
        if(tailleClient.isEmpty()){tailleClient = "NULL";}
        if(numeroSecoursClient.isEmpty()){numeroSecoursClient = "NULL";}
        if(numeroSecuClient.isEmpty()){numeroSecuClient = "NULL";}
        if(numeroMedecinClient.isEmpty()){numeroMedecinClient = "NULL";}
        if(pathologiesClient.isEmpty()){pathologiesClient = "NULL";}
        query.exec("INSERT INTO `med_client` (`info_client_client_id`, `sexe`, `dateNaissance`, `taille`, `poids`, `numSecu`, `numMedecin`, `numECU`, `infoMedPAT`)"
                   "VALUES ('"+clientID+"', '"+sexe+"', '"+dateNaissanceClient+"', "+tailleClient+", "+poidsClient+", "+numeroSecuClient+", "+numeroMedecinClient+", '"+numeroEcuClient+"', "+pathologiesClient+");");
        if(sexe == "F"){
            msgInfo = "la cliente a été ajoutée avec succès";
            message = "Bienvenue Madame "+nomClient+" "+prenomClient+",\n\nVous venez de vous inscrire sur Domo-Secours, nous vous remercions.\n\nVoici votre mot de passe temporaire : "+password+"\n\nCordialement,\n\nL'Equipe Domo-Secours.";

        }
        if(sexe == "M"){
            message = "Bienvenue Monsieur "+nomClient+" "+prenomClient+",\n\nVous venez de vous inscrire sur Domo-Secours, nous vous remercions.\n\nVoici votre mot de passe temporaire : "+password+"\nVotre identifiant client est le suivant : "+clientID+"\n\nCordialement,\n\nL'Equipe Domo-Secours.";
            msgInfo = "le client a été ajouté avec succès";
        }
        ui->progressBar->setFormat("Generation E-mail...");
        QFile file("message.txt");
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&file);
        out << message;
        file.close();
        //system("mailsend1.20b.exe  -f domosecours@alwaysdata.net -t "+ui->mail->text().toUtf8()+" -smtp smtp-domosecours.alwaysdata.net -sub \"Bienvenue sur Domo-Secours\" -ssl -port 465 -auth -user domosecours@alwaysdata.net -pass hellotheworld -cs \"utf-8\" -mime-type \"text/plain\" -msg-body \"message.txt\" -attach \"logo-domo2.png\"");
        QString argumentsStr = "-f domosecours@alwaysdata.net -t "+mailClient+" -smtp smtp-domosecours.alwaysdata.net -sub \"Bienvenue sur Domo-Secours\" -ssl -port 465 -auth -user domosecours@alwaysdata.net -pass hellotheworld -cs \"utf-8\" -mime-type \"text/plain\" -msg-body \"message.txt\"";
        QByteArray argumentsStrqb = argumentsStr.toLocal8Bit();
        const char * arguments = argumentsStrqb.data();
        char program[]="mailsend1.20b.exe";
        ui->progressBar->setFormat("Envoie E-mail...");
        ShellExecuteA(GetDesktopWindow(), "open", program, arguments, NULL, SW_HIDE);
        ui->progressBar->setVisible(false);
        msg->information(this, tr("Client.e ajouté.e"),tr(msgInfo.toUtf8()+"\nMail envoyé avec succès"));
        if (file.exists())
        {
           system("del .\\message.txt");
        }
        this->~ajouterClient();
    }
    else{
        msg->critical(this, tr("bdd"), tr("Un problème est survenue!\nVerifier votre connexion internet.\nSi le problème persiste Veuillez contacter un administrateur."));
    }
//mailsend1.20b.exe  -f domosecours@alwaysdata.net -t tmj62764@jiooq.com -smtp smtp-domosecours.alwaysdata.net -sub test -ssl -port 465 -auth -user domosecours@alwaysdata.net -pass hellotheworld -cs "utf-8" -mime-type "text/plain" -M "This is a \n test" -mime-type "image/gif" -enc-type "base64" -aname "domo-secours.png" -attach "/usr/file.gif"
    //INSERT INTO `med_client` (`info_client_client_id`, `sexe`, `dateNaissance`, `taille`, `poids`, `numSecu`, `numMedecin`, `numECU`, `infoMedPAT`)
    //VALUES ('12', 'M', '2022-02-03', '155', '50', '000011', '0000', '00000', NULL);
}

void ajouterClient::on_annuler_clicked()
{
    this->~ajouterClient();

}

std::string ajouterClient::gen_random(const int len) {
    srand(time(0));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}


