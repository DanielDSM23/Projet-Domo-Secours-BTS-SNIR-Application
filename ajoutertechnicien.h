#ifndef AJOUTERTECHNICIEN_H
#define AJOUTERTECHNICIEN_H

#include <QDialog>
#include <QCloseEvent>
#include "connexionbdd.h"
#include <QMessageBox>
#include <iostream>

namespace Ui {
class ajouterTechnicien;
}

class ajouterTechnicien : public QDialog
{
    Q_OBJECT

public:

    explicit ajouterTechnicien(QWidget *parent = 0);
    ~ajouterTechnicien();
    std::string gen_random(const int);
private:
    Ui::ajouterTechnicien *ui;
    connexionBDD *bddIHM;
    QMessageBox *msg;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_generer_clicked();
};

#endif // AJOUTERTECHNICIEN_H
