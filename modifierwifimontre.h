#ifndef MODIFIERWIFIMONTRE_H
#define MODIFIERWIFIMONTRE_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QCloseEvent>
namespace Ui {
class modifierWifiMontre;
}

class modifierWifiMontre : public QDialog
{
    Q_OBJECT

public:
    explicit modifierWifiMontre(QWidget *parent = 0);
    ~modifierWifiMontre();
    void setCom(QString);
private slots:
    void on_annuler_clicked();

    void on_modifier_clicked();

private:
    Ui::modifierWifiMontre *ui;
    QSerialPort * watch;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
};

#endif // MODIFIERWIFIMONTRE_H
