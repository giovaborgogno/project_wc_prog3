//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_ARBOLOCCURRENCE_H
#define PROJECT_WC_PROG3_ARBOLOCCURRENCE_H

#include "NodoArbol.h"

template<class T>
class ArbolOccurrence {
private:
    NodoArbol<T> *put(T data, int ocurrencia, NodoArbol<T> *r);

public:
    NodoArbol<T> *root;
    ArbolOccurrence();
    void put(T data, int ocurrencia);
    ~ArbolOccurrence();
    bool esVacio();
    void print();
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template<class T>
ArbolOccurrence<T>::ArbolOccurrence() {
    root = nullptr;
}

/**
 * Destructor del Arbol
 */
template<class T>
ArbolOccurrence<T>::~ArbolOccurrence() {}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template<class T>
void ArbolOccurrence<T>::put(T data, int ocurrencia) { root = put(data, ocurrencia, root); }

template<class T>
NodoArbol<T> *ArbolOccurrence<T>::put(T data, int ocurrencia, NodoArbol<T> *r) {
    if (r == nullptr) return new NodoArbol<T>(data, ocurrencia);
    if (r->getOcurrencia() < ocurrencia) r->setLeft(put(data, ocurrencia, r->getLeft()));
    else r->setRight(put(data, ocurrencia, r->getRight()));
    return r;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template<class T>
bool ArbolOccurrence<T>::esVacio() { return root == nullptr; }


/**
 * Muestra un árbol por consola
 */
template<class T>
void ArbolOccurrence<T>::print() {
    if (root != NULL)
        root->print(false, "");
}

#endif //PROJECT_WC_PROG3_ARBOLOCCURRENCE_H
