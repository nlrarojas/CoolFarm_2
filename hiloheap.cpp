#include "hiloheap.h"

HiloHeap::HiloHeap()
{
    estado = false;
    crecio = true;
}

void HiloHeap::run(){
    while(true){
        while(estado){
            mutex.lock();

            if(!estado){
                break;
            }
            if(crecio){
                //Heap es un 10 en la matriz del juego
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matrizJuego->matrizJuego[i][j] == 10){
                            if(nodoArbol->cantidadFrutos > matrizArboles->Terreno[i][j]->heap->cantidadFrutos()){
                                matrizArboles->Terreno[i][j]->heap->insertar(aleatorio());
                            }
                        }
                    }
                }
                this->sleep(nodoArbol->tiempoCosecha);
            }else{
                this->sleep(nodoArbol->tiempoCrecimiento);
                crecio = true;
            }
            mutex.unlock();
        }
    }
}

int HiloHeap::aleatorio(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(nodoArbol->rangoInferior, nodoArbol->rangoSuperior);
    int random = dis(gen);
    return random;
}
