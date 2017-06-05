#ifndef ESTRUCTURASTABLERO_H
#define ESTRUCTURASTABLERO_H

#include <iostream>
#include <QString>
#include <QDebug>

using namespace std;

struct plaga{
    int probabilidad;
    int tasaFrutos;
    int tiempoConsumeFrutos;
    int tasaPlagas;
    int tiempo;
    QString tipoPlaga;
    plaga * siguiente;

    plaga(int probabilidad, int tasaFrutos, int pTiempoConsumeFrutos, int pTasaPlagas, int pTiempo, QString tipoPlaga){
        this->probabilidad = probabilidad;
        this->tasaFrutos = tasaFrutos;
        this->tiempoConsumeFrutos = pTiempoConsumeFrutos;
        this->tasaPlagas = pTasaPlagas;
        this->tiempo = pTiempo;
        this->tipoPlaga = tipoPlaga;
        this->siguiente = NULL;
    }
};

struct Granjero{
    int tiempoDesplazamiento;
    int posX;
    int posY;

    Granjero(int tiempoDesplazamiento, int posX, int posY){
        this->tiempoDesplazamiento = tiempoDesplazamiento;
        this->posX = posX;
        this->posY = posY;
    }
    void moverIzquierda(){
        if ((this->posX)-1 >= 0)
            this->posX--;
    }

    void moverDerecha(){
        if ((this->posX)+1 < 8)
            this->posX++;
    }

    void moverAbajo(){
        if ((this->posY)+1 < 8)
            this->posY++;
    }

    void moverArriba(){
        if ((this->posY)-1 >= 0)
            this->posY--;
    }
};

struct Espantapajaros{
    double costo;
    int cantidadPorTerreno;

    Espantapajaros(double pCosto, int pCantidadPorTerreo){
        this->costo = pCosto;
        this->cantidadPorTerreno = pCantidadPorTerreo;
    }
};

struct Mercado{
    int tiempoAbre;
    int tiempoAbierto;
    int rangoInferior;
    int rangoSuperior;

    Mercado(int pTiempoAbierto, int pTiempoQueAbre, int pRangoInferior, int pRangoSuperior){
        this->tiempoAbre = pTiempoAbierto;
        this->tiempoAbierto = pTiempoQueAbre;
        this->rangoInferior = pRangoInferior;
        this->rangoSuperior = pRangoSuperior;
    }
};

struct ListaPlagas{
    plaga * primerNodo;

    ListaPlagas(){
        primerNodo = NULL;
    }

    void insertar(plaga * pPlaga){
        if(primerNodo == NULL){
            primerNodo = pPlaga;
        }else{
            pPlaga->siguiente = primerNodo;
            primerNodo = pPlaga;
        }
    }

    plaga * buscarPlaga(QString nombrePlaga){
        if(primerNodo == NULL){
            return NULL;
        }else{
            plaga * temporal = primerNodo;

            while (temporal != NULL){
                if(temporal->tipoPlaga == nombrePlaga){
                    return temporal;
                }
                temporal = temporal->siguiente;
            }
            return NULL;
        }
    }
    bool isEmpty(){
        return primerNodo == NULL;
    }
};

struct NodoInfoArbol{
    QString tipoArbol;
    int precio;
    int tiempoCrecimiento;
    int cantidadFrutos;
    int tiempoCosecha;
    int rangoInferior;
    int rangoSuperior;
    NodoInfoArbol * siguiente;

    NodoInfoArbol(QString pTipoArbol, int pPrecio,int pTiempoCrecimiento, int pCantidadFrutos, int pTiempoCosecha, int pRangoInferior, int pRangoSuperior){
        this->tipoArbol = pTipoArbol;
        this->precio = pPrecio;
        this->tiempoCrecimiento = pTiempoCrecimiento;
        this->cantidadFrutos = pCantidadFrutos;
        this->tiempoCosecha = pTiempoCosecha;
        this->rangoInferior = pRangoInferior;
        this->rangoSuperior = pRangoSuperior;
        this->siguiente = NULL;
    }
};

struct ListaNodosArboles{
    NodoInfoArbol * primerNodo;

    ListaNodosArboles(){
        primerNodo = NULL;
    }

    void insertar(NodoInfoArbol * nuevoNodo){
        if(primerNodo == NULL){
            primerNodo = nuevoNodo;
        }else{
            nuevoNodo->siguiente = primerNodo;
            primerNodo = nuevoNodo;
        }
    }

    NodoInfoArbol * buscarTipoArbol(QString pTipoArbol){
        if(primerNodo == NULL){
            return NULL;
        }else{
            NodoInfoArbol * temporal = primerNodo;

            while (temporal != NULL){
                if(temporal->tipoArbol == pTipoArbol){
                    return temporal;
                }
                temporal = temporal->siguiente;
            }
            return NULL;
        }
    }
};

struct Matriz{
    int matrizJuego[8][8];
    int estado[8][8];
    Matriz(){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                matrizJuego[i][j] = 0;
                estado[i][j] = -1;
           }
        }
    }
};
#endif // ESTRUCTURASTABLERO_H
