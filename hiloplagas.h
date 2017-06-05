#ifndef HILOPLAGAS_H
#define HILOPLAGAS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "arbolescomprados.h"
#include "estructurasTablero.h"

using namespace std;

class HiloPlagas : public QThread
{
private:
    QMutex mutex;
    void run(void);

public:
    HiloPlagas();
    Matriz * matrizJuego;
    plaga * plagas;
    bool estado;
    int aleatorio(void);
};

#endif // HILOPLAGAS_H
