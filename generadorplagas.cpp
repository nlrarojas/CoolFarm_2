#include "generadorplagas.h"

GeneradorPlagas::GeneradorPlagas(ListaPlagas * pListaPlagas, Matriz * pMatrizJuego)
{
    this->estado = 4;
    this->tipoPlagaACrear = 0;
    this->hiloPlagas = new HiloPlagas();
    this->hiloPlagas->matrizJuego = pMatrizJuego;
    this->hiloPlagas->plagas = pListaPlagas->buscarPlaga("Plagas");
    this->listaPlagas = pListaPlagas;
    this->matrizJuego = pMatrizJuego;
    this->tiempoCreacionPlagas = 3;
    qDebug() << "Generador de plagas listo";
}

void GeneradorPlagas::run(){
    while(true){
        mutex.lock();
        if(estado == 1){
            qDebug() << "Inicio hilo plagas";
            this->hiloPlagas->estado = true;
            this->hiloPlagas->start();

            this->estado = 0;
        }else if(estado == 2){
            qDebug() << "Pausando hilo plagas";
            this->hiloPlagas->estado = false;
            this->estado = 4;
        }else if(estado == 3){
            qDebug() << "Reanudando hilo plagas";
            this->hiloPlagas->estado = true;
            this->estado = 0;
        }else if(this->estado == 0){
            qDebug() << "Hilo plagas";
            plaga * tipoPlaga = selecionarTipoPlaga();
            if(tipoPlaga != NULL){
                qDebug() << "Plaga seleccionada " + tipoPlaga->tipoPlaga;
                int posX = 0;
                int posY = 0;
                for (int i = 0; i < tipoPlaga->tasaPlagas; i++) {
                    posX = aleatorio(0, 7);
                    posY = aleatorio(0, 7);
                    qDebug() << "Dentro del for";
                    if(tipoPlaga->tipoPlaga == "Ovejas"){
                        qDebug() << "Oveja";
                        if(matrizJuego->estado[posX][posY] != 0 || matrizJuego->estado[posX][posY] != 1 ||matrizJuego->estado[posX][posY] != 2){
                            if(matrizJuego->matrizJuego[posX][posY] == 10 || matrizJuego->matrizJuego[posX][posY] == 5 ||
                                    matrizJuego->matrizJuego[posX][posY] == 3 || matrizJuego->matrizJuego[posX][posY] == 4){
                                qDebug() << "Oveja Insertada";
                                matrizJuego->estado[posX][posY] = 9;
                            }
                        }
                    }else if(tipoPlaga->tipoPlaga == "Cuervos"){
                        qDebug() << "Cuervo";
                        if(matrizJuego->estado[posX][posY] != 0 || matrizJuego->estado[posX][posY] != 1 ||matrizJuego->estado[posX][posY] != 2){
                            if(matrizJuego->matrizJuego[posX][posY] == 10 || matrizJuego->matrizJuego[posX][posY] == 5 ||
                                    matrizJuego->matrizJuego[posX][posY] == 3 || matrizJuego->matrizJuego[posX][posY] == 4){
                                qDebug() << "Cuervo insertado";
                                matrizJuego->estado[posX][posY] = 7;
                            }
                        }
                    }else if(tipoPlaga->tipoPlaga == "Plagas"){
                        qDebug() << "Plagas";
                        if(matrizJuego->estado[posX][posY] != 0 || matrizJuego->estado[posX][posY] != 1 ||matrizJuego->estado[posX][posY] != 2){
                            if(matrizJuego->matrizJuego[posX][posY] == 10 || matrizJuego->matrizJuego[posX][posY] == 5 ||
                                    matrizJuego->matrizJuego[posX][posY] == 3 || matrizJuego->matrizJuego[posX][posY] == 4){
                                qDebug() << "Plagas insertado";
                                matrizJuego->estado[posX][posY] = 8;
                            }
                        }
                    }
                    qDebug() << "Durmiendo: " + QString::number(tipoPlaga->tiempo);
                    this->sleep(tipoPlaga->tiempo);
                }
            }else{
                qDebug() << "Plaga no encontrada";
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

plaga * GeneradorPlagas::selecionarTipoPlaga(){
    int numAleatorio = aleatorio(1, 3);
    qDebug() << QString::number(numAleatorio);
    plaga * tipoPlaga = listaPlagas->primerNodo;
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
        qDebug() << "Si cayó";
        return tipoPlaga;
    }else{
        qDebug() << "No cayó";
        return NULL;
    }
}
