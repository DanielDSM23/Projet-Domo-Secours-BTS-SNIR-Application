#include "Src/connexion/connexionbdd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexionBDD w;
    w.show();

    return a.exec();
}
