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
    void inorder(NodoArbol<T> *r);
    void inorder(int nPalabras, NodoArbol<T> *r, int &count);

public:
    NodoArbol<T> *root;
    ArbolOccurrence();
    void put(T data, int ocurrencia);
    void inorder(int nPalabras);
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

/**
 * Recorre un árbol en orden
 */
template<class T>
void ArbolOccurrence<T>::inorder(int nPalabras) {
    if (nPalabras == 0) {
        inorder(root);
        return;
    }
    int a = 0;
    inorder(nPalabras, root, a);
}

template<class T>
void ArbolOccurrence<T>::inorder(NodoArbol<T> *r) {
    if (r == nullptr) return;
    inorder(r->getLeft());
//    cout << r->getData() << " " << r->getOcurrencia() << " ,";
    cout << r->getData() << " " << r->getOcurrencia() << "\n";
    inorder(r->getRight());
}

template<class T>
void ArbolOccurrence<T>::inorder(int nPalabras, NodoArbol<T> *r, int &count) {
    if (r == nullptr) return;
    if (count == nPalabras) return;
    inorder(nPalabras, r->getLeft(), count);
    if (nPalabras > count) {
        cout << r->getData() << " " << r->getOcurrencia() << "\n";
        count++;
        inorder(nPalabras, r->getRight(), count);
    }
}


#endif //PROJECT_WC_PROG3_ARBOLOCCURRENCE_H
