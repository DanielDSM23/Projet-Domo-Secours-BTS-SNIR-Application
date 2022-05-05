#ifndef CONNEXIONBDD_H
#define CONNEXIONBDD_H
#include <QtSql>
#include <QSqlDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include "watcheditor.h"
#include <QCloseEvent>


class watchEditor;



namespace Ui {
class connexionBDD;
}

class connexionBDD : public QMainWindow
{
    Q_OBJECT

public:
    explicit connexionBDD(QWidget *parent = 0);
    ~connexionBDD();
    QSqlDatabase getDb();
private slots:
    void on_connexion_clicked();
    void closeProg();
private:
    QSqlDatabase db;
    QSqlQuery * query;
    watchEditor * mainWindow;
    Ui::connexionBDD *ui;
    QMessageBox * msg;
    /*
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();*/
};

#endif // CONNEXIONBDD_H
