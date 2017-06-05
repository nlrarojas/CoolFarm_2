#ifndef HILOAVL_H
#define HILOAVL_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"

using namespace std;

class HiloAvl : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(void);

public:
    HiloAvl();
    MatrizArboles * matrizArboles;
    Matriz * matrizJuego;
    bool estado;
    bool crecio;
    NodoInfoArbol * nodoArbol;
};

#endif // HILOAVL_H
