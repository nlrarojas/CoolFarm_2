#ifndef MERCADOPLATAFORMA_H
#define MERCADOPLATAFORMA_H

#include "estructurasTablero.h"
//#pragma once
#include <QThread>
#include <QMutex>
#include <random>

using namespace std;

class MercadoPlataforma : public QThread{

private:
    QMutex mutex;
    void run(void);

public:
    MercadoPlataforma();
    Mercado * mercado;
    bool estado;
};

#endif // MERCADOPLATAFORMA_H
