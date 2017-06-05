#include "hiloabb.h"

HiloABB::HiloABB()
{
    estado = false;
    crecio = true;
}

void HiloABB::run(){
    while(true){
        while(estado){
            mutex.lock();

            if(!estado){
                break;
            }
            if(crecio){
                //ABB es un 4 en la matriz del juego
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matrizJuego->matrizJuego[i][j] == 4){
                            if(nodoArbol->cantidadFrutos > matrizArboles->Terreno[i][j]->abb->cantidadFrutos()){
                                matrizArboles->Terreno[i][j]->abb->insertar(aleatorio());
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

int HiloABB::aleatorio(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(nodoArbol->rangoInferior, nodoArbol->rangoSuperior);
    int random = dis(gen);
    return random;
}
