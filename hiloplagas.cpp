#include "hiloplagas.h"

HiloPlagas::HiloPlagas(Matriz * pMatrizJuego, Plaga * pPlagas, MatrizPlagas * pMatrizPlagas, MatrizArboles * pMatrizArboles)
{
    this->matriz = pMatrizJuego;
    this->plagas = pPlagas;
    this->matrizPlagas = pMatrizPlagas;
    this->matrizArboles = pMatrizArboles;
    this->estado = false;
}

void HiloPlagas::run(){
    while(true){
        mutex.lock();
        while(this->estado){
            if(!this->estado){
                break;
            }else{
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matriz->estado[i][j] == 8){
                            if(matrizPlagas->matrizPlagas[i][j]->tiempoTrancurrido == 5){
                                matriz->matrizJuego[i][j] = 11;
                                matriz->estado[i][j] = -1;
                                matrizPlagas->matrizPlagas[i][j] = 0;
                                matrizArboles->Terreno[i][j]->borrado = true;

                                //debe eliminar el arbol por completo
                                //debe de eliminar la plaga
                            }else{
                                if(matrizPlagas->matrizPlagas[i][j]->atrapadoGranjero){
                                    int tiempoConsumido = matrizPlagas->matrizPlagas[i][j]->tiempoTrancurrido / 60;
                                    if(matrizArboles->Terreno[i][j]->tipoArbol == "ABB"){
                                        int cantidadConsumir = matrizArboles->Terreno[i][j]->abb->cantidadFrutos() * tiempoConsumido;
                                        for (int k = 0; k < cantidadConsumir; k++) {
                                            if(matrizArboles->Terreno[i][j]->abb->cantidadFrutos() > 0){
                                                matrizArboles->Terreno[i][j]->abb->borrarElemento(matrizArboles->Terreno[i][j]->abb->raiz->precio);
                                            }
                                        }
                                    }
                                    if(matrizArboles->Terreno[i][j]->tipoArbol == "AVL"){
                                        int cantidadConsumir = matrizArboles->Terreno[i][j]->abb->cantidadFrutos() * tiempoConsumido;
                                        for (int k = 0; k < cantidadConsumir; k++) {
                                            if(matrizArboles->Terreno[i][j]->avl->cantidadFrutos() > 0)
                                                matrizArboles->Terreno[i][j]->avl->borrarElemento(matrizArboles->Terreno[i][j]->avl->raiz->dato);
                                        }
                                    }
                                    if(matrizArboles->Terreno[i][j]->tipoArbol == "HEAP"){
                                        int cantidadConsumir = matrizArboles->Terreno[i][j]->abb->cantidadFrutos() * tiempoConsumido;
                                        for (int k = 0; k < cantidadConsumir; k++) {
                                            if(matrizArboles->Terreno[i][j]->heap->cantidadFrutos() > 0)
                                                matrizArboles->Terreno[i][j]->heap->eliminar();
                                        }
                                    }
                                    if(matrizArboles->Terreno[i][j]->tipoArbol == "ROJINEGRO"){
                                        int cantidadConsumir = matrizArboles->Terreno[i][j]->abb->cantidadFrutos() * tiempoConsumido;
                                        for (int k = 0; k < cantidadConsumir; k++) {
                                            if(matrizArboles->Terreno[i][j]->rojinegro->cantidadFrutos() > 0)
                                                matrizArboles->Terreno[i][j]->rojinegro->borrarElemento(matrizArboles->Terreno[i][j]->rojinegro->raiz->precio);
                                        }
                                    }
                                    //debe de eliminar del arbol la cantidad
                                    //debe de eliminar la plaga por que ya llegó el granjero
                                }
                            }
                        }
                    }
                }
            }
            this->sleep(1);
        }
        mutex.unlock();
    }
}

