#include "heap.h"
#include <QtCore>
#include <QDebug>
//#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

Heap::Heap(NodoInfoArbol * pNodoInfoArbol)
{
    this->arbol = NULL;
    this->largo = 0;
    this->nodoInfoArbol = pNodoInfoArbol;
    this->vendidos = 0;
    this->perdidos = 0;
}

void Heap::insertar(int dato)
{
    this->largo++;
    if (this->largo == 0){
        this->arbol = (int*)realloc(this->arbol, this->largo * sizeof(int));
    }
    else{
        int * punteroRevisar = (int*) realloc(this->arbol, this->largo * sizeof(int));
        if (punteroRevisar != NULL)
            this->arbol = punteroRevisar;
    }
    this->arbol[this->largo-1] = dato;
    if (this->largo !=1){
        int tmp = largo;
        while (tmp !=1){
            if (tmp%2 == 0){
                if (dato < this->arbol[(tmp-1)/2])
                    break;
                this->arbol[tmp-1] = this->arbol[(tmp-1)/2];
                this->arbol[(tmp-1)/2] = dato;
                tmp = tmp/2;
            }
            else{
                if (dato < this->arbol[(tmp-2)/2])
                    break;
                this->arbol[tmp-1] = this->arbol[(tmp-2)/2];
                this->arbol[(tmp-2)/2] = dato;
                tmp = (tmp-1)/2;
            }
        }
    }
}


void Heap::imprimir(){
    for(int i = 0;i < this->largo;i++){
        qDebug() << this->arbol[i];
    }
}

int Heap::eliminar(){
    int tmp = this->largo;
    this->arbol[0] = this->arbol[tmp-1];
    this->arbol[tmp-1] = -1;
    largo--;
    int i = 1;
    int dato;
    while ( i*2 <= largo){
        if (i*2+1 <= largo){
            if (this->arbol[i-1]<this->arbol[i*2-1] || this->arbol[i-1]<this->arbol[i*2]){
                int mayor = maximo(this->arbol[i*2-1], this->arbol[i*2]);
                if (mayor == 1){
                    dato = this->arbol[i-1];
                    this->arbol[i-1] = this->arbol[i*2-1];
                    this->arbol[i*2-1] = dato;
                    i = i*2;
                }
                else{
                    int dato = this->arbol[i-1];
                    this->arbol[i-1] = this->arbol[i*2];
                    this->arbol[i*2] = dato;
                    i = i*2+1;
                }
            }
            else
                i = i*2+1;
        }
        else if (i*2 <= largo){
            if (this->arbol[i-1] < this->arbol[i*2-1]){
                int dato = this->arbol[i-1];
                this->arbol[i-1] = this->arbol[i*2-1];
                this->arbol[i*2-1] = dato;
                i = i*2;
            }
            else
                i = i*2+1;
        }
        else
            i = i*2+1;
    }
    return dato;
}



int Heap::maximo (int a, int b)
{
    if (a>b)
        return 1;
    return 2;
}

int Heap::cantidadFrutos(){
    return this->largo;
}

int Heap::montoTotal(void){
    int suma = 0;
    for (int i = 0; i < largo; i++) {
        suma += arbol[i];
    }

    return suma;
}
