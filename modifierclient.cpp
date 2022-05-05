#include "modifierclient.h"
#include "ui_modifierclient.h"

modifierClient::modifierClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modifierClient)
{
    ui->setupUi(this);
}

modifierClient::~modifierClient()
{
    delete ui;
}
