#include "controladorgranjero.h"

ControladorGranjero::ControladorGranjero(Granjero * pGranjero, Matriz * pMatrizJuego, MatrizPlagas * pMatrizPlagas)
{
    this->granjeroJugador = pGranjero;
    this->matrizJuego = pMatrizJuego;
    this->matrizPlagas = pMatrizPlagas;
    this->estado = true;
}

void ControladorGranjero::run(){
    while(true){
        while(this->estado){
            if(!this->estado){
                break;
            }else{
                if(matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] == 7){
                    matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] = -1;
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->atrapadoGranjero = true;
                }
                if(matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] == 8){
                    matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] = -1;
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->atrapadoGranjero = true;
                }
                if(matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] == 9){
                    matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] = -1;
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->atrapadoGranjero = true;
                }
            }
            this->sleep(0.5);
        }
    }
}
