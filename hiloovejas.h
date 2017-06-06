#ifndef HILOOVEJAS_H
#define HILOOVEJAS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"

using namespace std;

class HiloOvejas : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(int limiteInferior, int limeteSuperior);

public:
    HiloOvejas();
    MatrizArboles * matrizArboles;
    Matriz * matrizJuego;
    bool estado;
    int tiempo;
    Plaga * oveja;
};

#endif // HILOOVEJAS_H
