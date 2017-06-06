#include "hilocuervos.h"

HiloCuervos::HiloCuervos(Matriz * pMatrizJuego, Plaga * pCuervo, MatrizPlagas * pMatrizPlagas, MatrizArboles * pMatrizArboles)
{
    this->matrizJuego = pMatrizJuego;
    this->cuervo = pCuervo;
    this->matrizPlagas = pMatrizPlagas;
    this->matrizArboles = pMatrizArboles;
    this->estado = false;
}

void HiloCuervos::run(){
    while(true){
        mutex.lock();
        while(this->estado){
            if(!this->estado){
                break;
            }else{
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matrizJuego->estado[i][j] == 7){
                            for (int k = 0; k < cuervo->tasaFrutos; k++) {
                                if(matrizArboles->Terreno[i][j]->tipoArbol == "ABB"){
                                    if(matrizArboles->Terreno[i][j]->abb->cantidadFrutos() > 0){
                                        matrizArboles->Terreno[i][j]->abb->borrarElemento(matrizArboles->Terreno[i][j]->abb->raiz->precio);
                                        matrizArboles->Terreno[i][j]->abb->perdidos++;
                                    }
                                }
                                if(matrizArboles->Terreno[i][j]->tipoArbol == "AVL"){
                                    if(matrizArboles->Terreno[i][j]->avl->cantidadFrutos() > 0){
                                        matrizArboles->Terreno[i][j]->avl->borrarElemento(matrizArboles->Terreno[i][j]->avl->raiz->dato);
                                        matrizArboles->Terreno[i][j]->avl->perdidos++;
                                    }
                                }
                                if(matrizArboles->Terreno[i][j]->tipoArbol == "HEAP"){
                                    if(matrizArboles->Terreno[i][j]->heap->cantidadFrutos() > 0){
                                        matrizArboles->Terreno[i][j]->heap->eliminar();
                                        matrizArboles->Terreno[i][j]->heap->perdidos++;
                                    }
                                }
                                if(matrizArboles->Terreno[i][j]->tipoArbol == "ROJINEGRO"){
                                    if(matrizArboles->Terreno[i][j]->rojinegro->cantidadFrutos() > 0){
                                        matrizArboles->Terreno[i][j]->rojinegro->borrarElemento(matrizArboles->Terreno[i][j]->rojinegro->raiz->precio);
                                        matrizArboles->Terreno[i][j]->rojinegro->perdidos++;
                                    }
                                }
                            }
                        }
                    }
                }
                this->sleep(cuervo->tiempoConsumeFrutos);
            }
        }
        mutex.unlock();
    }
}
