#include "generadorplagas.h"

GeneradorPlagas::GeneradorPlagas(ListaPlagas * pListaPlagas, Matriz * pMatrizJuego, MatrizPlagas * pMatrizPlagas)
{
    this->estado = 4;
    this->hiloPlagas = new HiloPlagas(pMatrizJuego, pListaPlagas->buscarPlaga("Plagas"), pMatrizPlagas);
    this->listaPlagas = pListaPlagas;
    this->matrizJuego = pMatrizJuego;
    this->tiempoCreacionPlagas = 3;
    this->matrizPlagasTablero = pMatrizPlagas;
}

void GeneradorPlagas::run(){
    while(true){
        mutex.lock();
        if(estado == 1){
            this->hiloPlagas->estado = true;
            this->hiloPlagas->start();

            this->estado = 0;
        }else if(estado == 2){
            this->hiloPlagas->estado = false;
            this->estado = 4;
        }else if(estado == 3){
            this->hiloPlagas->estado = true;
            this->estado = 0;
        }else if(this->estado == 0){
            Plaga * tipoPlaga = selecionarTipoPlaga();
            if(tipoPlaga != NULL){
                int posX = 0;
                int posY = 0;
                for (int i = 0; i < tipoPlaga->tasaPlagas; i++) {
                    posX = aleatorio(0, 7);
                    posY = aleatorio(0, 7);
                    if(tipoPlaga->tipoPlaga == "Ovejas"){
                        colocarEnCeldasAdyacentes(posX, posY, 9, tipoPlaga);
                    }else if(tipoPlaga->tipoPlaga == "Cuervos"){
                        colocarEnCeldasAdyacentes(posX, posY, 7, tipoPlaga);
                    }else if(tipoPlaga->tipoPlaga == "Plagas"){
                        colocarEnCeldasAdyacentes(posX, posY, 8, tipoPlaga);
                    }
                    this->sleep(tipoPlaga->tiempo);
                }
            }else{
                this->sleep(tiempoCreacionPlagas);
            }
        }
        mutex.unlock();
    }
}

int GeneradorPlagas::aleatorio(int limiteInferior, int limeteSuperior){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(limiteInferior, limeteSuperior);
    int random = dis(gen);
    return random;
}

void GeneradorPlagas::cambiarEstado(int estadoNuevo){
    this->estado = estadoNuevo;
}

Plaga * GeneradorPlagas::selecionarTipoPlaga(){
    int numAleatorio = aleatorio(1, 3);
    Plaga * tipoPlaga = listaPlagas->primerNodo;
    int probabilidad = 0;
    int rangoProbabilidades[3];
    int i = 0;

    while (tipoPlaga != NULL){
        probabilidad += tipoPlaga->probabilidad;
        rangoProbabilidades[i++] = probabilidad;
        tipoPlaga = tipoPlaga->siguiente;
    }

    if(numAleatorio == 1){
        tipoPlaga = listaPlagas->buscarPlaga("Ovejas");
    }else if(numAleatorio == 2){
        tipoPlaga = listaPlagas->buscarPlaga("Cuervos");
    }else if(numAleatorio == 3){
        tipoPlaga = listaPlagas->buscarPlaga("Plagas");
    }

    int probabilidadAparezcaPlaga = aleatorio(0, probabilidad);
    if(probabilidadAparezcaPlaga < rangoProbabilidades[numAleatorio]){
        return tipoPlaga;
    }else{
        return NULL;
    }
}

void GeneradorPlagas::colocarEnCeldasAdyacentes(int pPosX, int pPosY, int tipoPlaga, Plaga * pPlaga){
    Plaga * nuevaPlaga = new Plaga(pPlaga->probabilidad, pPlaga->tasaFrutos, pPlaga->tiempoConsumeFrutos, pPlaga->tasaPlagas, pPlaga->tiempo, pPlaga->tipoPlaga);
    if(validarPosicion(pPosX, pPosY)){
        if(validarPlagasAdyacentes(pPosX, pPosY)){
            matrizJuego->estado[pPosX][pPosY] = tipoPlaga;
            matrizPlagasTablero->matrizPlagas[pPosX][pPosY] = nuevaPlaga;
        }
    }else {
        if(pPosX - 1 >= 0 && pPosY - 1 >= 0){
            if (validarPosicion(pPosX - 1, pPosY - 1)){
                if(validarPlagasAdyacentes(pPosX - 1, pPosY - 1)){
                    matrizJuego->estado[pPosX - 1][pPosY - 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX - 1][pPosY - 1] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX - 1 >= 0 && pPosY >= 0){
            if (validarPosicion(pPosX - 1, pPosY)){
                if(validarPlagasAdyacentes(pPosX - 1, pPosY)){
                    matrizJuego->estado[pPosX - 1][pPosY] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX - 1][pPosY] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX - 1 >= 0 && pPosY + 1 < 8){
            if (validarPosicion(pPosX - 1, pPosY + 1)){
                if(validarPlagasAdyacentes(pPosX - 1, pPosY + 1)){
                    matrizJuego->estado[pPosX - 1][pPosY + 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX - 1][pPosY + 1] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX >= 0 && pPosY - 1 >= 0){
            if (validarPosicion(pPosX, pPosY - 1)){
                if(validarPlagasAdyacentes(pPosX, pPosY - 1)){
                    matrizJuego->estado[pPosX][pPosY - 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX][pPosY - 1] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX >= 0 && pPosY + 1 < 8){
            if (validarPosicion(pPosX, pPosY + 1)){
                if(validarPlagasAdyacentes(pPosX, pPosY + 1)){
                    matrizJuego->estado[pPosX][pPosY + 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX][pPosY + 1] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX + 1 < 8 && pPosY - 1 >= 0){
            if (validarPosicion(pPosX + 1, pPosY - 1)){
                if(validarPlagasAdyacentes(pPosX + 1, pPosY - 1)){
                    matrizJuego->estado[pPosX + 1][pPosY - 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX + 1][pPosY - 1] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX + 1 < 8 && pPosY >= 0){
            if (validarPosicion(pPosX + 1, pPosY)){
                if(validarPlagasAdyacentes(pPosX + 1, pPosY)){
                    matrizJuego->estado[pPosX + 1][pPosY] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX + 1][pPosY] = nuevaPlaga;
                    return;
                }
            }
        }
        if(pPosX + 1 < 8 && pPosY + 1 < 8){
            if (validarPosicion(pPosX + 1, pPosY + 1)){
                if(validarPlagasAdyacentes(pPosX + 1, pPosY + 1)){
                    matrizJuego->estado[pPosX + 1][pPosY + 1] = tipoPlaga;
                    matrizPlagasTablero->matrizPlagas[pPosX + 1][pPosY + 1] = nuevaPlaga;
                    return;
                }
            }
        }
    }
}

bool GeneradorPlagas::validarPosicion(int posX, int posY){
    if(matrizJuego->estado[posX][posY] == -1) //&& matrizJuego->estado[posX][posY] != 1 && matrizJuego->estado[posX][posY] != 2
        if(matrizJuego->matrizJuego[posX][posY] == 10 || matrizJuego->matrizJuego[posX][posY] == 5 ||
                matrizJuego->matrizJuego[posX][posY] == 3 || matrizJuego->matrizJuego[posX][posY] == 4){
            return true;
        }
    return false;
}

bool GeneradorPlagas::validarPlagasAdyacentes(int pPosX, int pPosY){
    return matrizJuego->estado[pPosX][pPosY] != 7 && matrizJuego->estado[pPosX][pPosY] != 8 &&
            matrizJuego->estado[pPosX][pPosY] != 9;
}
