#ifndef SUPPRIMERTECH_H
#define SUPPRIMERTECH_H

#include <QDialog>
#include <QCloseEvent>
#include "Src/connexion/connexionbdd.h"
#include <QMessageBox>

namespace Ui {
class supprimerTech;
}

class supprimerTech : public QDialog
{
    Q_OBJECT

public:
    explicit supprimerTech(QWidget *parent = 0);
    ~supprimerTech();

private:
    Ui::supprimerTech *ui;
    connexionBDD * bddIHM;
    QMessageBox * msg;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
private slots:
    void on_annuler_clicked();
    void on_sup_clicked();
};

#endif // SUPPRIMERTECH_H
