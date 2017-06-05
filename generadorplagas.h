#ifndef GENERADORPLAGAS_H
#define GENERADORPLAGAS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "estructurasTablero.h"
#include "arbolescomprados.h"
#include "hiloplagas.h"
#include <QDebug>

using namespace std;

class GeneradorPlagas : public QThread
{
private:
    QMutex mutex;
    void run(void);
    int aleatorio(int limiteInferior, int limeteSuperior);
    plaga * selecionarTipoPlaga(void);

public:
    GeneradorPlagas(ListaPlagas * pListaPlagas, Matriz * pMatrizJuego);
    ListaPlagas * listaPlagas;
    Matriz * matrizJuego;
    HiloPlagas * hiloPlagas;
    plaga * matrizPlagasTablero;
    int estado;
    int tipoPlagaACrear;
    int tiempoCreacionPlagas;    
    void cambiarEstado(int);
};

#endif // GENERADORPLAGAS_H
