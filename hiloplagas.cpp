#include "hiloplagas.h"

HiloPlagas::HiloPlagas(Matriz * pMatrizJuego, Plaga * pPlagas, MatrizPlagas * pMatrizPlagas)
{
    this->matrizJuego = pMatrizJuego;
    this->plagas = pPlagas;
    this->matrizPlagas = pMatrizPlagas;
    this->estado = false;
}

void HiloPlagas::run(){
    while(true){
        while(this->estado){
            if(!this->estado){
                break;
            }else{
                for (int i = 0; i < 8; i++) {
                    for (int i = 0; i < 8; i++) {

                    }
                }
            }
        }
    }
}
