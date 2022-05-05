#include "connexionbdd.h"
#include "ui_connexionbdd.h"
#include <QCryptographicHash>
connexionBDD::connexionBDD(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connexionBDD)
{
    ui->setupUi(this);
    ui->passwordText->setEchoMode(QLineEdit::Password);
    QPixmap pix("./logo-domo2.png");
    ui->label->setPixmap(pix);
    msg = new QMessageBox;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("host.com");
    db.setUserName("username");
    db.setPassword("password");
    db.setDatabaseName("domosecours_btssn");
    if(!db.open())
    {
        this->show();
        msg->critical(this, tr("BDD"),tr("Echec ouverture bdd ! \nVeuillez contacter un administrateur\n"));
        this->close();
        exit(0);
    }
    connect(ui->passwordText, SIGNAL(returnPressed()),ui->connexion,SIGNAL(clicked()));
    connect(ui->loginText, SIGNAL(returnPressed()),ui->connexion,SIGNAL(clicked()));
    //connect(this, SIGNAL(clicked()), this ,SLOT(closeProg()));
}


void connexionBDD::on_connexion_clicked()
{
    if(db.isOpen()){
        QSqlQuery query;
        QString login = ui->loginText->text(),
                password = ui->passwordText->text(),
                //encodedPassword = QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex(),
                nom;
        ui->connexion->setEnabled(false);
        ui->connexion->setText("Connexion...");
        query.exec("SELECT Admin_System.nom FROM Admin_System WHERE Admin_System.password = MD5('"+password+"') AND Admin_System.login = '"+login+"';");
        if(query.size() == 1){
            mainWindow = new watchEditor;
            mainWindow->show();
            this->close();
            while (query.next()){
                nom = query.value(0).toString();
                mainWindow->setNom(nom);
            }
            mainWindow->adminAccess(login);
            this->~connexionBDD();
        }
        else{
            msg->warning(this, tr("formulaire incorrect"), tr("login ou mot de passe incorrect !"));
            ui->connexion->setText("Connexion");
            ui->connexion->setEnabled(true);
        }
    }
}



connexionBDD::~connexionBDD()
{
    delete msg;
    delete ui;
}

QSqlDatabase connexionBDD::getDb(){
    return db;
}


void connexionBDD::closeProg(){
    exit(0);
}

