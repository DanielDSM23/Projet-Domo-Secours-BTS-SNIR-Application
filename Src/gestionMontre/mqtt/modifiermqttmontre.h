#ifndef MODIFIERMQTTMONTRE_H
#define MODIFIERMQTTMONTRE_H

#include <QDialog>
#include <QCloseEvent>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class modifierMqttMontre;
}

class modifierMqttMontre : public QDialog
{
    Q_OBJECT

public:
    explicit modifierMqttMontre(QWidget *parent = 0);
    ~modifierMqttMontre();
    void setCom(QString);
private:
    Ui::modifierMqttMontre *ui;
    QSerialPort * watch;
protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
private slots:
    void on_modifier_clicked();
    void on_annuler_clicked();
};

#endif // MODIFIERMQTTMONTRE_H
