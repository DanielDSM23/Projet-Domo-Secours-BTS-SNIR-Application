#ifndef MODIFIERNTPMONTRE_H
#define MODIFIERNTPMONTRE_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QCloseEvent>

namespace Ui {
class modifierNtpMontre;
}

class modifierNtpMontre : public QDialog
{
    Q_OBJECT

public:
    explicit modifierNtpMontre(QWidget *parent = 0);
    ~modifierNtpMontre();
    void setCom(QString);
private slots:
    void on_Annuler_clicked();

    void on_modifier_clicked();

private:
    Ui::modifierNtpMontre *ui;
    QSerialPort * watch;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
};

#endif // MODIFIERNTPMONTRE_H
