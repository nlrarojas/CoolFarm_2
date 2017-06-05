#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <cstdlib>
#include <iostream>
#include "estructurasTablero.h"
#pragma once;

using namespace std;

struct NodoABB {
    int precio;
    NodoABB* hijoizquierdo;
    NodoABB* hijoderecho;

    NodoABB(int pPrecio) {
        this->precio = pPrecio;
        hijoizquierdo = hijoderecho = NULL;
    }
};

struct Arbol {
    NodoABB * raiz;
    NodoInfoArbol * nodoInfoArbol;
    int vendidos;
    int perdidos;

    Arbol(NodoInfoArbol * pNodoInfoArbol) {
        this->nodoInfoArbol = pNodoInfoArbol;
        raiz = NULL;
        this->vendidos = 0;
        this->perdidos = 0;
    }

    void insertar(int);
    NodoABB * insertar(int, NodoABB *);

    NodoABB * buscarNodo(int indice);
    NodoABB * buscarNodo(int indice, NodoABB *);

    void inOrden(NodoABB *);
    void preOrden(NodoABB *);
    void posOrden(NodoABB *);
    NodoABB * buscar(int, NodoABB *);

    int obtenerNumeroElementos(NodoABB *);
    int peso(NodoABB *);
    int obtenerAltura(NodoABB *);
    NodoABB * mayor(NodoABB * arbol);
    NodoABB * borrarElemento(int);
    NodoABB * borrarElemento(int, NodoABB*);
    void anchura(NodoABB *);
    int altura(NodoABB *);
    int cantHojas(NodoABB *);
    int cantNodos2(NodoABB *);
    void nodos_nivel(NodoABB *, int, int);
    int contadorNodos(NodoABB *);

    int cantidadFrutos(void);
    int montoTotal(void);
    int montoTotalAuxiliar(NodoABB *);
};

#endif // ARBOLBINARIO_H
