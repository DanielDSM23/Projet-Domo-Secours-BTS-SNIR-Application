#ifndef AJOUTERCLIENT_H
#define AJOUTERCLIENT_H

#include <QMainWindow>
#include "watcheditor.h"
#include "connexionbdd.h"
#include <QCloseEvent>
#include "pleasewait.h"

class connexionBDD;

namespace Ui {
class ajouterClient;
}

class ajouterClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajouterClient(QWidget *parent = 0);
    ~ajouterClient();
    //QWidget getUi();
private slots:
    void on_ajouter_clicked();
    void on_annuler_clicked();
    std::string gen_random(int n);
private:
    connexionBDD * bddIHM;
    Ui::ajouterClient *ui;
    QMessageBox * msg;
    pleaseWait * wait;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
};

#endif // AJOUTERCLIENT_H
