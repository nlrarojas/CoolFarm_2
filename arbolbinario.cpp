#include "arbolBinario.h"

// PRINCIPAL DE INSERTA,
//INSERTA UN NUMERO ENTERO

void Arbol::insertar(int dato) {
    raiz = insertar(dato, raiz);
}

//  INSERTA RECURSIVAMENTE

NodoABB * Arbol::insertar(int valor, NodoABB* nodo) {
    // cuando el nodo es nulo, raiz o hijos de hojas
    //quiere decir que allí debe
    // ubicar el valor, en un nuevo nodo

    if (nodo == NULL) {
        return new NodoABB(valor);
    }
    //si el valor es mayor,
    //llama recursivamente a insertar en el hijo
    //derecho
    else if (nodo->precio < valor) {
        nodo->hijoderecho = insertar(valor, nodo->hijoderecho);
    }// en caso contrario, va al lado izquierdo
    else if (nodo->precio >= valor) {
        nodo->hijoizquierdo = insertar(valor, nodo->hijoizquierdo);
    }
    return nodo;
}

void Arbol::inOrden(NodoABB* nodo) {
    if (nodo != NULL) {
        inOrden(nodo->hijoizquierdo);
        cout << nodo->precio << "  ";
        inOrden(nodo->hijoderecho);
    }
}

void Arbol::preOrden(NodoABB* nodo) {
    if (nodo != NULL) {
        cout << nodo->precio << "  ";
        preOrden(nodo->hijoizquierdo);
        preOrden(nodo->hijoderecho);
    }
}

void Arbol::posOrden(NodoABB* nodo) {
    if (nodo != NULL) {
        posOrden(nodo->hijoizquierdo);
        posOrden(nodo->hijoderecho);
        cout << nodo->precio << "  ";

    }
}

int Arbol::cantidadFrutos(){
    return contadorNodos(raiz);
}

int Arbol::contadorNodos(NodoABB* nodo) {
    if (nodo == NULL)
        return 0;
    else
        return 1 + contadorNodos(nodo->hijoderecho) + contadorNodos(nodo->hijoizquierdo);
}


// BUSCA UN VALOR EN EL ARBOL ORDENADO

NodoABB* Arbol::buscar(int valor, NodoABB* nodo) {
    // cuando el nodo es nulo, quiere decir que allí debe
    // ubicar el valor, en un nuevo nodo
    if (nodo == NULL) {
        return NULL;
    } else if (nodo->precio == valor) {
        return nodo;
    }// si el valor es mayor, llama recursivamente a insertar en el hijo
    // derecho
    else if (nodo->precio < valor) {
        return buscar(valor, nodo->hijoderecho);
    }// en caso contrario, va al lado izquierdo
    else //(nodo.dato >= valor)
    {
        return buscar(valor, nodo->hijoizquierdo);
    }
}

NodoABB * Arbol::buscarNodo(int indice) {
    return buscarNodo(indice, raiz);
}

NodoABB * Arbol::buscarNodo(int indice, NodoABB* nodo) {
    // cuando el nodo es nulo, quiere decir que allí debe
    // ubicar el valor, en un nuevo nodo
    if (nodo == NULL) {
        return NULL;
    } else if (nodo->precio == indice) {
        return nodo;
    }// si el valor es mayor, llama recursivamente a insertar en el hijo
    // derecho
    else if (nodo->precio < indice) {
        return buscarNodo(indice, nodo->hijoderecho);
    }// en caso contrario, va al lado izquierdo
    else //(nodo.dato >= valor)
    {
        return buscarNodo(indice, nodo->hijoizquierdo);
    }
}


// cantidad de elementos de un arbol binario

int Arbol::obtenerNumeroElementos(NodoABB* nodo) {
    int num_elems = 0;

    if (nodo != NULL) {
        num_elems += obtenerNumeroElementos(nodo->hijoizquierdo);
        num_elems++; // contabilizar el nodo visitado
        num_elems += obtenerNumeroElementos(nodo->hijoderecho);
    }
    return num_elems;
}


// obtiene la altura
//Altura. La altura de un árbol se define como el
//nivel del nodo de mayor nivel. Como cada nodo de un árbol
//puede considerarse a su vez como la raíz de un árbol, también
//podemos hablar de altura de ramas; el máximo número de nodos
//que hay que recorrer para llegar de la raíz a una de las hojas.

int Arbol::obtenerAltura(NodoABB* nodo) {

    // resultado
    int altura = 0;

    // referencias hi e hd
    NodoABB* ref_h_izq;
    NodoABB* ref_h_der;

    // resultado de alturas de hi e hd
    int altura_r_izq = 0;
    int altura_r_der = 0;

    //
    if (nodo != NULL) {
        // incia en 1 para contar la raiz
        altura = 1;

        // inicialiaza las referencias
        ref_h_izq = nodo->hijoizquierdo;
        ref_h_der = nodo->hijoderecho;

        // si ninguno de los hijos es nulo
        if ((ref_h_izq != NULL) && (ref_h_der != NULL)) {
            // obtiene las alturas de cada arbol izq y der
            altura_r_izq = obtenerAltura(ref_h_izq);
            altura_r_der = obtenerAltura(ref_h_der);

            // suma la altura mayor, para determinar el mayor nivel
            if (altura_r_izq >= altura_r_der) {
                altura += altura_r_izq;
            } else {
                altura += altura_r_der;
            }
            // hizq no es nulo, suma altura de hijo izquierdo
        } else if ((ref_h_izq != NULL) && (ref_h_der == NULL)) {
            altura += obtenerAltura(ref_h_izq);
        }// hder no es nulo, suma altura de hijo derecho
        else if ((ref_h_izq == NULL) && (ref_h_der != NULL)) {
            altura += obtenerAltura(ref_h_der);
        }// cuando ambos son nulos, resta el uno con el que empezó
        else if ((ref_h_izq == NULL) && (ref_h_der == NULL)) {
            altura -= 1;
        }
    }
    // retorna el resultado
    return altura;
}

int maximo(int a, int b) {
    if (a > b)
        return a;
    else return b;
}

int Arbol::altura(NodoABB* nodo) {
    if (nodo == NULL)
        return -1;
    else
        return 1 + maximo(altura(nodo->hijoizquierdo), altura(nodo->hijoderecho));
}

int Arbol::cantNodos2(NodoABB* nodo) {
    if (nodo == NULL)
        return 0;
    else
        return 1 + cantNodos2(nodo->hijoizquierdo) + cantNodos2(nodo->hijoderecho);
}

int Arbol::cantHojas(NodoABB* raiz) {
    if (raiz == NULL)
        return 0;
    else if (raiz->hijoderecho == NULL && raiz->hijoizquierdo == NULL)
        return 1;
    else
        return cantHojas(raiz->hijoderecho) + cantHojas(raiz->hijoizquierdo);
}

// borrar

NodoABB* Arbol::mayor(NodoABB* arbol) {
    if (arbol == NULL)
        return NULL;
    else if (arbol->hijoderecho == NULL)
        return arbol;
    else
        return mayor(arbol->hijoderecho);
}

NodoABB* Arbol::borrarElemento(int ele) {
    raiz = borrarElemento(ele, raiz);
    return raiz;
}

NodoABB* Arbol::borrarElemento(int ele, NodoABB* arbol) {
    if (arbol == NULL) {
        return NULL;
    } else if (ele < arbol->precio)
        arbol->hijoizquierdo = borrarElemento(ele, arbol->hijoizquierdo);
    else if (ele > arbol->precio)
        arbol->hijoderecho = borrarElemento(ele, arbol->hijoderecho);
    else if (arbol->hijoizquierdo == NULL && arbol->hijoderecho == NULL)
        arbol = NULL;
    else if (arbol->hijoizquierdo == NULL)
        arbol = arbol->hijoderecho;
    else if (arbol->hijoderecho == NULL)
        arbol = arbol->hijoizquierdo;
    else {
        NodoABB* max = mayor(arbol->hijoizquierdo); // mayor de los menores
        arbol->hijoizquierdo = borrarElemento(max->precio, arbol->hijoizquierdo);
        arbol->precio = max->precio;
    }
    return arbol;
}

int Arbol::montoTotal(void){
    return montoTotalAuxiliar(raiz);
}

int Arbol::montoTotalAuxiliar(NodoABB * nodo){
    if(nodo == NULL){
        return 0;
    }else{
        return nodo->precio + montoTotalAuxiliar(nodo->hijoizquierdo) + montoTotalAuxiliar(nodo->hijoderecho);
    }
}


