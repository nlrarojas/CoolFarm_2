#include "mainwindow.h"
//#include "windowiniciajuego.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //windownuevapartida w;
    MainWindow w;
    w.show();

    return a.exec();
}
