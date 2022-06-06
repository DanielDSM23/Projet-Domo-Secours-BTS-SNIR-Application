#include "ajoutertechnicien.h"
#include "ui_ajoutertechnicien.h"
#include <QSqlQuery>
ajouterTechnicien::ajouterTechnicien(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterTechnicien)
{
    ui->setupUi(this);
    bddIHM = new connexionBDD;
    msg = new QMessageBox;
    connect(this, SIGNAL(clicked()), this ,SLOT(on_buttonBox_rejected()));
}

ajouterTechnicien::~ajouterTechnicien()
{
    delete bddIHM;
    delete msg;
    delete ui;
}



void ajouterTechnicien::on_buttonBox_rejected()
{
    this->~ajouterTechnicien();
}

void ajouterTechnicien::on_buttonBox_accepted()
{
    QString nom = ui->nomTech->text(),
            login = ui->loginTech->text(),
            password = ui->passTech->text();
    if(!login.isEmpty() && !nom.isEmpty() && !password.isEmpty()){
        if(bddIHM->getDb().isOpen()){
            QSqlQuery query;
            query.exec("INSERT INTO `Admin_System` (`nom`, `login`, `password`) VALUES ('"+nom+"', '"+login+"', MD5('"+password+"'));");
            msg->information(this, tr("Technicien.ne ajouté.e"), tr("Technicien.ne ajouté.e avec succès"));

        }
    }
    else{
        msg->critical(this, tr("Erreur formulaire"), tr("Veuillez remplir le formulaire !"));
        this->show();
    }
}


std::string ajouterTechnicien::gen_random(const int len) {
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

void ajouterTechnicien::on_generer_clicked()
{
    ui->passTech->setText(QString::fromStdString(gen_random(10)).toUtf8());
}
