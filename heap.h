#ifndef HEAP_H
#define HEAP_H

#include <QtCore>
#include "estructurasTablero.h"

struct Heap
{
    int *arbol, largo;
    NodoInfoArbol * nodoInfoArbol;
    int vendidos;
    int perdidos;

    Heap(NodoInfoArbol *);

    void insertar(int dato);
    void imprimir();
    void eliminar();
    int maximo(int, int);
    int cantidadFrutos(void);
    int montoTotal(void);
};

#endif // HEAP_H
