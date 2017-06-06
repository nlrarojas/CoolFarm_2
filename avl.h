#ifndef AVL_H
#define AVL_H
#include <QtCore>
#include "estructurasTablero.h"

struct NodoAVL{
    int dato;
    NodoAVL* hijoizquierdo;
    NodoAVL* hijoderecho;
    int balance;

    NodoAVL(int d){
        dato = d;
        hijoizquierdo = hijoderecho = NULL;
        balance = 0;
    }
};

struct Avl
{
    NodoAVL *raiz;
    NodoInfoArbol * nodoInfoArbol;
    int vendidos;
    int perdidos;

    Avl(NodoInfoArbol *);

    void insertar(int);
    NodoAVL* insertar(int, NodoAVL*);
    void sacarBalance(NodoAVL*);
    int maximo(int , int);
    int altura(NodoAVL*);
    void imprimir(NodoAVL*);
    void imprimirNivel(NodoAVL *, int , int);
    void balancear(NodoAVL*, NodoAVL*);
    NodoAVL* balancear(NodoAVL*, int, int);

    int cantidadFrutos(void);
    int contadorNodos(NodoAVL *);
    int montoTotal(void);
    int montoTotalAuxiliar(NodoAVL *);

    NodoAVL * mayor(NodoAVL * arbol);
    NodoAVL * borrarElemento(int);
    NodoAVL * borrarElemento(int, NodoAVL *);
};

#endif // AVL_H
