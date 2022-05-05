#ifndef SUPPRIMERCLIENT_H
#define SUPPRIMERCLIENT_H

#include <QMainWindow>
#include <QCloseEvent>
#include "connexionbdd.h"
#include <QMessageBox>
namespace Ui {
class supprimerClient;
}

class supprimerClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit supprimerClient(QWidget *parent = 0);
    ~supprimerClient();

private slots:
    void on_annuler_clicked();

    void on_sup_clicked();

private:
    Ui::supprimerClient *ui;
    connexionBDD * bddIHM;
    QMessageBox * msg;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
};

#endif // SUPPRIMERCLIENT_H
