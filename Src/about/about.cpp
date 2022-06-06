#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    connect(this, SIGNAL(clicked()), ui->pushButton ,SIGNAL(clicked()));
}

about::~about()
{
    delete ui;
}



void about::on_pushButton_clicked()
{
    this->~about();
}

