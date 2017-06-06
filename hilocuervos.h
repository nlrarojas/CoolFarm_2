#ifndef HILOCUERVOS_H
#define HILOCUERVOS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"
#include <QDebug>

using namespace std;

class HiloCuervos : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(int limiteInferior, int limeteSuperior);

public:
    HiloCuervos(Matriz * pMatrizJuego, Plaga * pCuervo, MatrizPlagas * pMatrizPlgas, MatrizArboles * pMatrizArboles);
    Matriz * matrizJuego;
    Plaga * cuervo;
    Granjero * granjero;
    MatrizPlagas * matrizPlagas;
    MatrizArboles * matrizArboles;
    bool estado;
};

#endif // HILOCUERVOS_H
