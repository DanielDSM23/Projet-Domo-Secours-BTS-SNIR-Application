#include "modifiermdptech.h"
#include "ui_modifiermdptech.h"
#include <QSqlQuery>
modifierMdpTech::modifierMdpTech(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierMdpTech)
{
    ui->setupUi(this);
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
    ui->mdpAdmin->setEchoMode(QLineEdit::Password);
    bddIHM = new connexionBDD;
    msg = new QMessageBox;
}

modifierMdpTech::~modifierMdpTech()
{
    delete bddIHM;
    delete msg;
    delete ui;
}

void modifierMdpTech::on_annuler_clicked()
{
    this->~modifierMdpTech();
}


std::string modifierMdpTech::gen_random(const int len) {
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
void modifierMdpTech::on_generer_clicked()
{
     ui->nouveauMdp->setText(QString::fromStdString(gen_random(10)).toUtf8());
}

void modifierMdpTech::on_modifier_clicked()
{
    if(bddIHM->getDb().isOpen()){
        QString mdpAdmin = ui->mdpAdmin->text(),
                loginTech = ui->loginTech->text(),
                nomTechnicien,
                newMdpTech = ui->nouveauMdp->text();
        QSqlQuery query;
        query.exec("SELECT * FROM `Admin_System` WHERE Admin_System.login = 'admin' AND Admin_System.password = MD5('"+mdpAdmin+"')");
        if(query.size() != 1){
            msg->critical(this, tr("Opération impossible"), tr("Mot de passe admin incorrect"));
        }
        if(loginTech.toLower() == "admin"){
            msg->critical(this, tr("Opération impossible"), tr("Opération impossible !"));
        }
        if(query.size() == 1 && loginTech.toLower() != "admin"){
            query.exec("SELECT Admin_System.nom FROM `Admin_System` WHERE Admin_System.login = '"+loginTech+"'");
            while (query.next()){
                nomTechnicien = query.value(0).toString();
            }
            int ret = msg->warning(this, tr("Information"), tr("Voulez-vous vraiment remplacer le mot de passe de "+loginTech.toUtf8()+" ?"),QMessageBox::Yes | QMessageBox::No);
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
                query.exec("UPDATE `Admin_System` SET `password`=MD5('"+newMdpTech+"') WHERE `login` = '"+loginTech+"'");
                msg->information(this, tr("Information"), tr("Mot de passe modifié"));
                this->~modifierMdpTech();
            }
        }



    }
}
