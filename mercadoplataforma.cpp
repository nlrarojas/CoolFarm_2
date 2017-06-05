#include "mercadoplataforma.h"

MercadoPlataforma::MercadoPlataforma()
{
    estado = false;
}

void MercadoPlataforma::run(){
    while(true){
        if(this->mercado != NULL){
            while(this->estado){
                mutex.lock();
                if(!this->estado){
                    break;
                }
                if(this->mercado->tiempoAbierto != 0){
                    this->sleep(this->mercado->tiempoAbierto);//Esta por segundo, agregarle *60
                    this->estado = false;
                }
                mutex.unlock();
            }
            mutex.lock();
            if(this->mercado->tiempoAbre != 0){
                this->sleep(this->mercado->tiempoAbre);//Está por segundos, agregarle *60
                this->estado = true;
            }
            mutex.unlock();
        }
    }
}
