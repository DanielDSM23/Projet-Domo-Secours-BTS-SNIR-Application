#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private:
    Ui::about *ui;

protected:
    void closeEvent(QCloseEvent * event){
        emit clicked();
        event->ignore();
    }

signals:
    void clicked();
private slots:
    void on_pushButton_clicked();
};

#endif // ABOUT_H
