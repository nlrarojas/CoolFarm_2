#include "hilorojinegro.h"

HiloRojiNegro::HiloRojiNegro()
{
    estado = false;
    crecio = true;
}

void HiloRojiNegro::run(){
    while(true){
        while(estado){
            mutex.lock();

            if(!estado){
                break;
            }
            if(crecio){
                //RojiNegro es un 5 en la matriz del juego
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matrizJuego->matrizJuego[i][j] == 5){
                            if(nodoArbol->cantidadFrutos > matrizArboles->Terreno[i][j]->rojinegro->cantidadFrutos()){
                                matrizArboles->Terreno[i][j]->rojinegro->insertar(aleatorio());
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

int HiloRojiNegro::aleatorio(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(nodoArbol->rangoInferior, nodoArbol->rangoSuperior);
    int random = dis(gen);
    return random;
}
