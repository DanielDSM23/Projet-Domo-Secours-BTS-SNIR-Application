#ifndef MODIFIERCLIENTIDMONTRE_H
#define MODIFIERCLIENTIDMONTRE_H

#include <QDialog>
#include <QCloseEvent>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class modifierClientIdMontre;
}

class modifierClientIdMontre : public QDialog
{
    Q_OBJECT

public:
    explicit modifierClientIdMontre(QWidget *parent = 0);
    ~modifierClientIdMontre();
    void setCom(QString);
private:
    Ui::modifierClientIdMontre *ui;
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

#endif // MODIFIERCLIENTIDMONTRE_H
