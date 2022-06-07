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
    ui->label->setPixmap(pix); //met une image sur le label
    msg = new QMessageBox; //instanciation dynamique de QMessageBox
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("xxxx"); //definition de l'hostname de la base de données
    db.setUserName("dmsc"); //definition du User
    db.setPassword("xxxx"); //definition du MDP de la BDD
    db.setDatabaseName("dmsc_bdd"); //definition du nom de la BDD
    if(!db.open()) //si la base de donnée n'est pas ouverte
    {
        this->show(); //ouverture de la fenêtre 
        msg->critical(this, tr("BDD"),tr("Echec ouverture bdd ! \nVeuillez contacter un administrateur\n")); //affichage du message d'erreur
        this->close(); //fermeture de la fenêtre
        exit(0); //fermeture du programme
    }
    //slots qui permettent d'executer la methode on_connexion_clicked() lors de l'appuie de la touche entrer
    connect(ui->passwordText, SIGNAL(returnPressed()),ui->connexion,SIGNAL(clicked()));
    connect(ui->loginText, SIGNAL(returnPressed()),ui->connexion,SIGNAL(clicked()));
}


void connexionBDD::on_connexion_clicked()
{
    if(db.isOpen()){ //si la BDD est ouverte
        QSqlQuery query;
        QString login = ui->loginText->text(), //recuperation du texte qui est sur le QLineEdit loginText
                password = ui->passwordText->text(), //recuperation du texte qui est sur le QLineEdit passwordText
                nom;
        ui->connexion->setEnabled(false); //rend le bouton connexion indisponible
        ui->connexion->setText("Connexion..."); //met le texte "Connexion..." sur le bouton connexion
        //execution de la requête SQL pour savoir si l'utilisateur et le MDP existent
        query.exec("SELECT Admin_System.nom FROM Admin_System WHERE Admin_System.password = MD5('"+password+"') AND Admin_System.login = '"+login+"';");
        if(query.size() == 1){
            mainWindow = new watchEditor; //instanciation de la classe watchEditor
            mainWindow->show(); //ouverture de la fenêtre 
            this->close(); //fermeture de la fenêtre de connexion
            while (query.next()){
                nom = query.value(0).toString(); //recuperation de la valeur nom
                mainWindow->setNom(nom); //met le nom sur mainWindows
            }
            mainWindow->adminAccess(login); //verifie si l'admin est le User
            this->~connexionBDD();
        }
        else{
            msg->warning(this, tr("formulaire incorrect"), tr("login ou mot de passe incorrect !")); //informe l'utilisateur que le login ou le mot de
                                                                                                    //passe sont incorrects
            ui->connexion->setText("Connexion");
            ui->connexion->setEnabled(true);
        }
    }
}



connexionBDD::~connexionBDD()
{
    delete msg; //suppression de l'objet msg
    delete ui; //suppression de l'objet ui
}

QSqlDatabase connexionBDD::getDb(){//getteur de l'objet db;
    return db; 
}


void connexionBDD::closeProg(){
    exit(0);
}

