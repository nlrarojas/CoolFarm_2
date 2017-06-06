#ifndef ARBOLESCOMPRADOS_H
#define ARBOLESCOMPRADOS_H

#include <iostream>
#include "arbolbinario.h"
#include "avl.h"
#include "heap.h"
#include <QDebug>

using namespace std;

struct NodoArbolesTerreno{
    NodoArbolesTerreno * siguiente;
    Arbol * abb;
    Avl * avl;
    Heap * heap;
    Arbol * rojinegro;
    QString tipoArbol;
    int posX;
    int posY;
    bool borrado;

    NodoArbolesTerreno(Arbol * pAbb, Avl * pAvl, Heap * pHeap, Arbol * pRojiNegro, QString pTipoArbol){
        this->abb = pAbb;
        this->avl = pAvl;
        this->heap = pHeap;
        this->rojinegro = pRojiNegro;
        this->tipoArbol = pTipoArbol;
        this->siguiente = NULL;
        this->posX = 0;
        this->posY = 0;
        this->borrado = false;
    }
};

struct ListaNodosArbolesTerreno{
    NodoArbolesTerreno * primerNodo;

    ListaNodosArbolesTerreno(){
        primerNodo = NULL;
    }

    void insertar(NodoArbolesTerreno * nuevoNodo){
        if(primerNodo == NULL){
            primerNodo = nuevoNodo;
        }else{
            nuevoNodo->siguiente = primerNodo;
            primerNodo = nuevoNodo;
        }
    }

    int cantidadNodos(void){
        NodoArbolesTerreno * temporal = primerNodo;
        int cantidad = 0;
        while(temporal != NULL){
            cantidad++;
            temporal = temporal->siguiente;
        }
        return cantidad;
    }
};

struct NodoArbolAVL{
    Avl * arbolAVL;
    NodoArbolAVL * siguiente;

    NodoArbolAVL(Avl * nuevoArbol){
        this->arbolAVL = nuevoArbol;
        this->siguiente = NULL;
    }
};

struct ColaAVLComprados{
    NodoArbolAVL * frente, * fondo;

    ColaAVLComprados(){
        this->frente = this->fondo = NULL;
    }

    bool isEmpty(void){
        return this->frente == NULL;
    }

    void encolar(NodoArbolAVL * nuevaArbol){
        if(isEmpty()){
            frente = fondo = nuevaArbol;
        }else{
            fondo->siguiente = nuevaArbol;
            nuevaArbol->siguiente = NULL;
            fondo = fondo->siguiente;
        }
    }

    NodoArbolAVL * desEncolar(void){
        if(isEmpty()){
            return NULL;
        }else if(frente->siguiente == NULL){
            NodoArbolAVL * borrado = fondo;
            frente = fondo = NULL;
            return borrado;
        }else{
            NodoArbolAVL * temporal = frente;
            while(temporal->siguiente != fondo){
                temporal = temporal->siguiente;
            }
            NodoArbolAVL * borrado = fondo;
            fondo = temporal;
            fondo->siguiente = NULL;
            return borrado;
        }
    }
};

struct NodoArbolABB{
    Arbol * arbolABB;
    NodoArbolABB * siguiente;

    NodoArbolABB(Arbol * nuevoArbol){
        this->arbolABB = nuevoArbol;
        this->siguiente = NULL;
    }
};

struct ColaABBComprados{
    NodoArbolABB * frente, * fondo;

    ColaABBComprados(){
        this->frente = this->fondo = NULL;
    }

    bool isEmpty(void){
        return this->frente == NULL;
    }

    void encolar(NodoArbolABB * nuevaArbol){
        if(isEmpty()){
            frente = fondo = nuevaArbol;
        }else{
            fondo->siguiente = nuevaArbol;
            nuevaArbol->siguiente = NULL;
            fondo = fondo->siguiente;
        }
    }

    NodoArbolABB * desEncolar(void){
        if(isEmpty()){
            return NULL;
        }else if(frente->siguiente == NULL){
            NodoArbolABB * borrado = fondo;
            frente = fondo = NULL;
            return borrado;
        }else{
            NodoArbolABB * temporal = frente;
            while(temporal->siguiente != fondo){
                temporal = temporal->siguiente;
            }
            NodoArbolABB * borrado = fondo;
            fondo = temporal;
            fondo->siguiente = NULL;
            return borrado;
        }
    }
};

struct NodoArbolHeap{
    Heap * arbolHeap;
    NodoArbolHeap * siguiente;

    NodoArbolHeap(Heap * nuevoArbol){
        this->arbolHeap = nuevoArbol;
        this->siguiente = NULL;
    }
};

struct ColaHeapComprados{
    NodoArbolHeap * frente, * fondo;

    ColaHeapComprados(){
        this->frente = this->fondo = NULL;
    }

    bool isEmpty(void){
        return this->frente == NULL;
    }

    void encolar(NodoArbolHeap * nuevaArbol){
        if(isEmpty()){
            frente = fondo = nuevaArbol;
        }else{
            fondo->siguiente = nuevaArbol;
            nuevaArbol->siguiente = NULL;
            fondo = fondo->siguiente;
        }
    }

    NodoArbolHeap * desEncolar(void){
        if(isEmpty()){
            return NULL;
        }else if(frente->siguiente == NULL){
            NodoArbolHeap * borrado = fondo;
            frente = fondo = NULL;
            return borrado;
        }else{
            NodoArbolHeap * temporal = frente;
            while(temporal->siguiente != fondo){
                temporal = temporal->siguiente;
            }
            NodoArbolHeap * borrado = fondo;
            fondo = temporal;
            fondo->siguiente = NULL;
            return borrado;
        }
    }
};

struct MatrizArboles{
    NodoArbolesTerreno * Terreno[8][8];    
    MatrizArboles(){        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Terreno[i][j] = NULL;
            }
        }
    }
};

#endif // ARBOLESCOMPRADOS_H
