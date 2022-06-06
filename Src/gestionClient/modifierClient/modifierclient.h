#ifndef MODIFIERCLIENT_H
#define MODIFIERCLIENT_H
#include <QCloseEvent>
#include <QMainWindow>
#include "Src/connexion/connexionbdd.h"
#include <QMessageBox>
namespace Ui {
class modifierClient;
}

class modifierClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifierClient(QWidget *parent = 0);
    ~modifierClient();

private:
    Ui::modifierClient *ui;
    connexionBDD * bddIHM;
    QMessageBox * msg;
    QSqlTableModel * tableModel;
    QSqlTableModel * tableModel2;
    int rowNumberClient;
    int rowNumberMed;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
private slots:
    void on_annuler_clicked();
    void on_modifier_clicked();
};

#endif // MODIFIERCLIENT_H
