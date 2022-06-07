#include "Src/connexion/connexionbdd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexionBDD w; //instanciation de la classe connexionBDD
    w.show(); //methode show

    return a.exec();
}
