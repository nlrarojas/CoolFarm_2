#include "avl.h"
#include <QtCore>
#include <QDebug>
//#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

Avl::Avl(NodoInfoArbol * pNodoInfoArbol)
{
    this->raiz = NULL;
    this->nodoInfoArbol = pNodoInfoArbol;
    this->vendidos = 0;
    this->perdidos = 0;
}


void Avl::insertar(int dato){
    raiz = insertar(dato, raiz);
    balancear(raiz, raiz);
}


NodoAVL* Avl::insertar(int valor, NodoAVL* nodo){
    if (nodo == NULL)
        return new NodoAVL(valor);
    else if (nodo->dato < valor){
        nodo->hijoderecho = insertar(valor, nodo->hijoderecho);
    }
    else if (nodo->dato >= valor){
        nodo->hijoizquierdo = insertar(valor, nodo->hijoizquierdo);
    }
    return nodo;
}


int Avl::maximo (int a, int b)
{
    if (a>b)
        return a;
    return b;
}

int Avl::altura (NodoAVL* nodo)
{
    if (nodo == NULL)
        return -1;
    return 1 + maximo(altura(nodo->hijoizquierdo),altura(nodo->hijoderecho));
}

void Avl::imprimir(NodoAVL* nodo){
    int nivel = altura(nodo)+2;
    for (int i=1; i< nivel; i++)
    {
        for (int j=i; j< nivel-1; j++)
            cout <<" ";
        imprimirNivel(nodo,i,1);
        cout << endl;
    }
}

void Avl::imprimirNivel(NodoAVL* nodo, int nivel, int cont){
    if (nodo != NULL){
        if (nivel == cont)
            cout << nodo->dato << " ";
        cont++;
        imprimirNivel(nodo->hijoizquierdo, nivel, cont);
        imprimirNivel(nodo->hijoderecho, nivel, cont);
    }
}


void Avl::balancear(NodoAVL* padre, NodoAVL* nodo){
    if (nodo!= NULL){
        sacarBalance(nodo);
        if (nodo->balance < -1){
            sacarBalance(nodo->hijoizquierdo);
            if (-2 < nodo->hijoizquierdo->balance && nodo->hijoizquierdo->balance < 2){
                if (nodo ==raiz)
                    raiz = balancear(nodo, nodo->balance, nodo->hijoizquierdo->balance);
                else if (nodo->hijoizquierdo->balance == 1)
                    padre->hijoderecho = balancear(nodo, nodo->balance, nodo->hijoizquierdo->balance);
                else
                    padre->hijoizquierdo = balancear(nodo, nodo->balance, nodo->hijoizquierdo->balance);
            }
            balancear(nodo, nodo->hijoizquierdo);
        }
        else if (nodo->balance >1){
            sacarBalance(nodo->hijoderecho);
            if (-2 < nodo->hijoderecho->balance && nodo->hijoderecho->balance < 2){
                if (nodo == raiz)
                    raiz = balancear(nodo, nodo->balance, nodo->hijoderecho->balance);
                else if (nodo->hijoderecho->balance == 1)
                    padre->hijoderecho = balancear(nodo, nodo->balance, nodo->hijoderecho->balance);
                else
                    padre->hijoizquierdo = balancear(nodo, nodo->balance, nodo->hijoderecho->balance);
            }
            balancear(nodo, nodo->hijoderecho);
        }
        balancear(nodo, nodo->hijoizquierdo);
        balancear(nodo, nodo->hijoderecho);
    }
}

NodoAVL* Avl::balancear(NodoAVL* nodo, int factor1, int factor2){
    if (factor1 == -2){
        if (factor2 == 1){//Rotacion Doble
            int valor = nodo->dato;
            nodo->dato = nodo->hijoizquierdo->hijoderecho->dato;
            nodo->hijoderecho = new NodoAVL(valor);
            nodo->hijoizquierdo->hijoderecho = NULL;
            return nodo;
        }
        else{//Rotacion Simple
            if (nodo->hijoizquierdo->hijoderecho == NULL){
                int valor = nodo->dato;
                nodo = nodo->hijoizquierdo;
                nodo->hijoderecho = new NodoAVL(valor);
                return nodo;
            }
            NodoAVL *tmp = nodo->hijoizquierdo;
            nodo->hijoizquierdo = nodo->hijoizquierdo->hijoderecho;
            tmp->hijoderecho = nodo;
            return tmp;
        }
    }
    else{
        if (factor2 == -1){//Rotacion Doble
            int valor = nodo->dato;
            nodo->dato = nodo->hijoderecho->hijoizquierdo->dato;
            nodo->hijoizquierdo = new NodoAVL(valor);
            nodo->hijoderecho->hijoizquierdo = NULL;
            return nodo;
        }
        else{//Rotacion Simple
            if (nodo->hijoderecho->hijoizquierdo == NULL){
                int valor = nodo->dato;
                nodo = nodo->hijoderecho;
                nodo->hijoizquierdo = new NodoAVL(valor);
                return nodo;
            }
            NodoAVL *tmp = nodo->hijoderecho;
            nodo->hijoderecho = nodo->hijoderecho->hijoizquierdo;
            tmp->hijoizquierdo = nodo;
            return tmp;
        }
    }
}

void Avl::sacarBalance(NodoAVL* nodo){
    if (nodo != NULL)
        nodo->balance = (altura(nodo->hijoderecho)-altura(nodo->hijoizquierdo));
}

int Avl::cantidadFrutos(){
    return contadorNodos(raiz);
}

int Avl::contadorNodos(NodoAVL* nodo) {
    if (nodo == NULL)
        return 0;
    else
        return 1 + contadorNodos(nodo->hijoderecho) + contadorNodos(nodo->hijoizquierdo);
}

int Avl::montoTotal(void){
    //return cantidadFrutos() * this->nodoInfoArbol->precio;
    return cantidadFrutos() * montoTotalAuxiliar(raiz);
}

int Avl::montoTotalAuxiliar(NodoAVL * nodo){
    if(nodo == NULL){
        return 0;
    }else{
        return nodo->dato + montoTotalAuxiliar(nodo->hijoizquierdo) + montoTotalAuxiliar(nodo->hijoderecho);
    }
}
