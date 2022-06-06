#include "modifierclient.h"
#include "ui_modifierclient.h"
#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QTableWidgetItem>
modifierClient::modifierClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifierClient)
{
    ui->setupUi(this);
    connect(this, SIGNAL(clicked()), ui->annuler ,SIGNAL(clicked()));
    bddIHM = new connexionBDD;
    msg = new QMessageBox;
    //info client
    tableModel = new QSqlTableModel();
    tableModel->setTable("info_client");
    tableModel->select();
    ui->infoClient->setModel(tableModel);
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Prenom"));
    tableModel->setHeaderData(3, Qt::Horizontal, tr("Email"));
    tableModel->setHeaderData(4, Qt::Horizontal, tr("Adresse"));
    ui->infoClient->setColumnHidden(0,true);
    ui->infoClient->setColumnHidden(5,true);
    //ui->infoClient->setColumnHidden(0,true);
    ui->infoClient->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->infoClient->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    ui->infoClient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //infomed
    tableModel2 = new QSqlTableModel();
    tableModel2->setTable("med_client");
    tableModel2->select();
    ui->infoMed->setModel(tableModel2);
    tableModel2->setHeaderData(1, Qt::Horizontal, tr("Sexe"));
    tableModel2->setHeaderData(2, Qt::Horizontal, tr("Date de Naissance"));
    tableModel2->setHeaderData(3, Qt::Horizontal, tr("Taille (en cm)"));
    tableModel2->setHeaderData(4, Qt::Horizontal, tr("Poids"));
    tableModel2->setHeaderData(5, Qt::Horizontal, tr("Num Secu"));
    tableModel2->setHeaderData(6, Qt::Horizontal, tr("Num Medecin"));
    tableModel2->setHeaderData(7, Qt::Horizontal, tr("Num ECU"));
    tableModel2->setHeaderData(8, Qt::Horizontal, tr("Infos Medicales"));
    ui->infoMed->setColumnHidden(0,true);
    ui->infoMed->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->infoMed->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    ui->infoMed->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

modifierClient::~modifierClient()
{
    delete ui;
}

void modifierClient::on_annuler_clicked()
{
    this->~modifierClient();
}

void modifierClient::on_modifier_clicked()
{
    if(bddIHM->getDb().isOpen()){
        QString clientId = ui->clientId->text();
        QSqlQuery query;
        bool isNum = false;
        clientId.toInt(&isNum);
        if(isNum){
            query.exec("SELECT * FROM info_client WHERE info_client.client_id='"+clientId+"';");
            if(query.size() == 1){
                for (int col=0; col<tableModel->columnCount(); col++){
                    // return a list of all matching results
                    QModelIndexList results = ui->infoClient->model()->match(
                        ui->infoClient->model()->index(0, col),
                        Qt::DisplayRole,
                        clientId,
                        -1,
                        Qt::MatchContains
                    );
                    // for each result, print the line number
                    for (QModelIndex idx : results)
                       rowNumberClient = idx.row();
                }
                for (int col=0; col<tableModel2->columnCount(); col++){
                    // return a list of all matching results
                    QModelIndexList results = ui->infoMed->model()->match(
                        ui->infoMed->model()->index(0, col),
                        Qt::DisplayRole,
                        clientId,
                        -1,
                        Qt::MatchContains
                    );
                    // for each result, print the line number
                    for (QModelIndex idx : results)
                        rowNumberMed = idx.row();
                }
                ui->infoClient->selectRow(rowNumberClient++);

                ui->infoMed->selectRow(rowNumberMed++);
            }
            else{
                msg->critical(this, tr("ID Introuvable"), tr("ID introuvable!\nVeuillez verifier!"));
            }
        }
    }
}
