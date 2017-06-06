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
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->atrapadoGranjero = true;
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->tiempoTrancurrido = 0;
                    this->sleep(1);
                    matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] = -1;
                }
                if(matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] == 9){
                    matrizJuego->estado[granjeroJugador->posX][granjeroJugador->posY] = -1;
                    matrizPlagas->matrizPlagas[granjeroJugador->posX][granjeroJugador->posY]->atrapadoGranjero = true;
                }
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if(matrizJuego->estado[i][j] == 8){
                            if(!matrizPlagas->matrizPlagas[i][j]->atrapadoGranjero)
                                matrizPlagas->matrizPlagas[i][j]->tiempoTrancurrido++;
                        }
                    }
                }
            }
            this->sleep(1);
        }
    }
}
