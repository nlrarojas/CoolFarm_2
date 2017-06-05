#ifndef HILOROJINEGRO_H
#define HILOROJINEGRO_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"

using namespace std;

class HiloRojiNegro : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(void);

public:
    HiloRojiNegro();
    MatrizArboles * matrizArboles;
    Matriz * matrizJuego;
    bool estado;
    bool crecio;
    NodoInfoArbol * nodoArbol;
};

#endif // HILOROJINEGRO_H
