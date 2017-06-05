#ifndef CONTROLADORHILOS_H
#define CONTROLADORHILOS_H

#include <QThread>
#include <QMutex>
#include "arbolescomprados.h"
#include "estructurasTablero.h"
#include "hiloabb.h"
#include "hiloavl.h"
#include "hiloheap.h"
#include "hilorojinegro.h"

class ControladorHilos : public QThread {
private:
    int estado;
    void run();
    QMutex mutex;

public:
    ControladorHilos(MatrizArboles * matrizArboles, Matriz * matrizJuego,
                     NodoInfoArbol * pNodoInfoAbb,  NodoInfoArbol * pNodoInfoAvl,
                     NodoInfoArbol * pNodoInfoHeap, NodoInfoArbol * pNodoInfoRojinegro);
    void cambiarEstado(int);
    MatrizArboles * matrizArboles;
    Matriz * matrizJuego;
    HiloABB * hiloAbb;
    HiloAvl * hiloAvl;
    HiloHeap * hiloHeap;
    HiloRojiNegro * hiloRojinegro;
};

#endif // CONTROLADORHILOS_H
