#include "controladorhilos.h"

ControladorHilos::ControladorHilos(MatrizArboles * matrizArboles, Matriz * matrizJuego,
                                   NodoInfoArbol * pNodoInfoAbb,  NodoInfoArbol * pNodoInfoAvl,
                                   NodoInfoArbol * pNodoInfoHeap, NodoInfoArbol * pNodoInfoRojinegro)
{
    this->estado = 1;
    hiloAbb = new HiloABB();
    hiloAbb->matrizArboles= matrizArboles;
    hiloAbb->matrizJuego = matrizJuego;
    hiloAbb->nodoArbol = pNodoInfoAbb;

    hiloAvl = new HiloAvl();
    hiloAvl->matrizArboles = matrizArboles;
    hiloAvl->matrizJuego = matrizJuego;
    hiloAvl->nodoArbol = pNodoInfoAvl;

    hiloHeap = new HiloHeap();
    hiloHeap->matrizArboles = matrizArboles;
    hiloHeap->matrizJuego = matrizJuego;
    hiloHeap->nodoArbol = pNodoInfoHeap;

    hiloRojinegro = new HiloRojiNegro();
    hiloRojinegro->matrizArboles = matrizArboles;
    hiloRojinegro->matrizJuego = matrizJuego;
    hiloRojinegro->nodoArbol = pNodoInfoRojinegro;
}

void ControladorHilos::run(){
    while(true){
        mutex.lock();

        if(this->estado == 1){
            this->hiloAbb->estado = true;
            this->hiloAbb->start();

            this->hiloAvl->estado = true;
            this->hiloAvl->start();

            this->hiloHeap->estado = true;
            this->hiloHeap->start();

            this->hiloRojinegro->estado = true;
            this->hiloRojinegro->start();

            this->estado = 4;
        }else if(this->estado == 2){
            this->hiloAbb->estado = false;
            this->hiloAvl->estado = false;
            this->hiloHeap->estado = false;            
            this->hiloRojinegro->estado = false;
            this->estado = 4;
        }else if(this->estado == 3){
            this->hiloAbb->estado = true;
            this->hiloAvl->estado = true;
            this->hiloHeap->estado = true;
            this->hiloRojinegro->estado = true;
            this->estado = 4;
        }
        mutex.unlock();
    }
}

void ControladorHilos::cambiarEstado(int estadoNuevo){
    this->estado = estadoNuevo;
}
