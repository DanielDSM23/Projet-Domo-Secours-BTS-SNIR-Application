#ifndef MODIFIERMDPTECH_H
#define MODIFIERMDPTECH_H

#include <QDialog>
#include <QCloseEvent>
#include "Src/connexion/connexionbdd.h"
#include <QMessageBox>

namespace Ui {
class modifierMdpTech;
}

class modifierMdpTech : public QDialog
{
    Q_OBJECT

public:
    explicit modifierMdpTech(QWidget *parent = 0);
    ~modifierMdpTech();
    std::string gen_random(const int len);

private:
    Ui::modifierMdpTech *ui;
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
    void on_annuler_clicked();
    void on_generer_clicked();
    void on_modifier_clicked();
};

#endif // MODIFIERMDPTECH_H
