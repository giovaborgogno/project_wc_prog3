//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_ARBOLALPHA_H
#define PROJECT_WC_PROG3_ARBOLALPHA_H

#include "NodoArbol.h"

template<class T>
class ArbolAlpha {
private:
    T search(T data, NodoArbol<T> *r);

    NodoArbol<T> *put(T data, NodoArbol<T> *r);

    void inorder(NodoArbol<T> *r);

    int palabras, palabrasDif;

protected:
    NodoArbol<T> *root;

public:
    ArbolAlpha();

    void put(T dato);

    T search(T dato);

    void inorder();

    ~ArbolAlpha();

    bool esVacio();

    void print();

};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template<class T>
ArbolAlpha<T>::ArbolAlpha() {
    root = nullptr;
    palabras = 0;
    palabrasDif = 0;
}

/**
 * Destructor del Arbol
 */
template<class T>
ArbolAlpha<T>::~ArbolAlpha() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template<class T>
T ArbolAlpha<T>::search(T dato) { return search(dato, root); }

template<class T>
T ArbolAlpha<T>::search(T data, NodoArbol<T> *r) {
    if (r == nullptr)throw 404;
    if (r->getData() == data)return r->getData();
    if (r->getData() > data)return search(data, r->getLeft());
    else return search(data, r->getRight());
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template<class T>
void ArbolAlpha<T>::put(T dato) { root = put(dato, root); }

template<class T>
NodoArbol<T> *ArbolAlpha<T>::put(T data, NodoArbol<T> *r) {
    palabras++;
    if (r == nullptr) return new NodoArbol<T>(data);
    if (r->getData() == data) {
        r->aumentarOcurrencia();
        throw 200;
    }
    palabrasDif++;
    if (r->getData() > data) r->setLeft(put(data, r->getLeft()));
    else r->setRight(put(data, r->getRight()));
    return r;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template<class T>
bool ArbolAlpha<T>::esVacio() { return root == nullptr; }


/**
 * Recorre un árbol en orden
 */
template<class T>
void ArbolAlpha<T>::inorder() { inorder(root); }

template<class T>
void ArbolAlpha<T>::inorder(NodoArbol<T> *r) {
    if (r == nullptr) return;
    inorder(r->getLeft());
    cout << r->getData() << " ";
    inorder(r->getRight());


}


/**
 * Muestra un árbol por consola
 */
template<class T>
void ArbolAlpha<T>::print() {
    if (root != NULL)
        root->print(false, "");
}

#endif //PROJECT_WC_PROG3_ARBOLALPHA_H
