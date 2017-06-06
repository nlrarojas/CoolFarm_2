#ifndef HILOPLAGAS_H
#define HILOPLAGAS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"
#include <QDebug>

using namespace std;

class HiloPlagas : public QThread
{
private:
    QMutex mutex;
    void run(void);

public:
    HiloPlagas(Matriz * pMatrizJuego, Plaga * pPlagas, MatrizPlagas * pMatrizPlagas, MatrizArboles * pMatrizArboles);
    Matriz * matriz;
    Plaga * plagas;
    Granjero * granjero;
    MatrizPlagas * matrizPlagas;
    MatrizArboles * matrizArboles;
    bool estado;
    int aleatorio(void);
};

#endif // HILOPLAGAS_H
