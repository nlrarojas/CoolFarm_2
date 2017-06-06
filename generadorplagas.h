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
    Plaga * selecionarTipoPlaga(void);

public:
    GeneradorPlagas(ListaPlagas * pListaPlagas, Matriz * pMatrizJuego, MatrizPlagas * pMatrizPlagas);
    ListaPlagas * listaPlagas;
    Matriz * matrizJuego;
    HiloPlagas * hiloPlagas;
    MatrizPlagas * matrizPlagasTablero;

    int estado;
    int tiempoCreacionPlagas;    
    void cambiarEstado(int);
    void colocarEnCeldasAdyacentes(int pPosX, int pPosY, int tipoPlaga, Plaga * pTipoPlaga);
    bool validarPosicion(int posX, int posY);
    bool validarPlagasAdyacentes(int pPosX, int pPosY);
};

#endif // GENERADORPLAGAS_H
