#ifndef CONTROLADORGRANJERO_H
#define CONTROLADORGRANJERO_H

#include <QThread>
#include <QMutex>
#include <random>
#include "estructurasTablero.h"

using namespace std;

class ControladorGranjero : public QThread
{
private:
    QMutex mutex;
    void run(void);

public:
    ControladorGranjero(Granjero *, Matriz *, MatrizPlagas *);
    Granjero * granjeroJugador;
    Matriz * matrizJuego;
    MatrizPlagas * matrizPlagas;
    bool estado;
};

#endif // CONTROLADORGRANJERO_H
