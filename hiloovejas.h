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
    HiloOvejas(Matriz * pMatrizJuego, Plaga * pOveja, MatrizPlagas * pMatrizPlgas, MatrizArboles * pMatrizArboles);
    Matriz * matrizJuego;
    Plaga * oveja;
    Granjero * granjero;
    MatrizPlagas * matrizPlagas;
    MatrizArboles * matrizArboles;
    bool estado;
};

#endif // HILOOVEJAS_H
