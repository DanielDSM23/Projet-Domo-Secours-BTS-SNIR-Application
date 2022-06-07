#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    connect(this, SIGNAL(clicked()), ui->pushButton ,SIGNAL(clicked())); //creation d'un slot lorsque l'on ferme la fenêtre 
                                                                         //il appelle donc la methode on_pushButton_clicked()
}

about::~about()
{
    delete ui; //suppression de l'objet ui
}



void about::on_pushButton_clicked()
{
    this->~about(); //appel du destructeur
}

