#ifndef MODIFIERCLIENT_H
#define MODIFIERCLIENT_H

#include <QMainWindow>

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
};

#endif // MODIFIERCLIENT_H
