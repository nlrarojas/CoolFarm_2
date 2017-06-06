#ifndef GENERADORPLAGAS_H
#define GENERADORPLAGAS_H

#include <QThread>
#include <QMutex>
#include <random>
#include "estructurasTablero.h"
#include "arbolescomprados.h"
#include "hiloplagas.h"
#include "hilocuervos.h"
#include "hiloovejas.h"
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
    GeneradorPlagas(ListaPlagas *, Matriz *, MatrizPlagas *, MatrizArboles *);

    ListaPlagas * listaPlagas;
    Matriz * matrizJuego;    
    MatrizPlagas * matrizPlagasTablero;

    HiloPlagas * hiloPlagas;
    HiloCuervos * hiloCuervos;
    HiloOvejas * hiloOvejas;

    int estado;
    int tiempoCreacionPlagas;    
    void cambiarEstado(int);
    void colocarEnCeldasAdyacentes(int pPosX, int pPosY, int tipoPlaga, Plaga * pTipoPlaga);
    bool validarPosicion(int posX, int posY);
    bool validarPlagasAdyacentes(int pPosX, int pPosY);
};

#endif // GENERADORPLAGAS_H
