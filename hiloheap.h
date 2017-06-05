#ifndef HILOHEAP_H
#define HILOHEAP_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"

using namespace std;

class HiloHeap : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(void);

public:
    HiloHeap();
    MatrizArboles * matrizArboles;
    Matriz * matrizJuego;
    bool estado;
    bool crecio;
    NodoInfoArbol * nodoArbol;
};

#endif // HILOHEAP_H
