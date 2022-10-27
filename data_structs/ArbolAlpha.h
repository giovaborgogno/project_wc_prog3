//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_ARBOLALPHA_H
#define PROJECT_WC_PROG3_ARBOLALPHA_H

#include "NodoArbol.h"
#include "HashEntry.h"

/**
 * Clase que implementa una Arbol Binario
 * @tparam T cualquier tipo de dato
 */
template<class T>
class ArbolAlpha {
private:
    T inOrderSuccessor(NodoArbol<T> *r);
    NodoArbol<T> *remove(HashEntry<string>* data, NodoArbol<HashEntry<string>*> *r);
    T search(HashEntry<string> *data, NodoArbol<HashEntry<string> *> *r);
    NodoArbol<T> *put(HashEntry<string> *data, NodoArbol<HashEntry<string> *> *r);
    void inorder(NodoArbol<HashEntry<string>*> *r);
    void inorder(int nPalabras, NodoArbol<HashEntry<string>*> *r, int &count);

protected:
    NodoArbol<T> *root;

public:
    ArbolAlpha();
    ~ArbolAlpha();
    bool esVacio();
    void print();
    void remove(T dato);
    T search(T dato);
    void inorder(int nPalabras, int &count);
    void put(HashEntry<string> *dato);

};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 */
template<class T>
ArbolAlpha<T>::ArbolAlpha() {
    root = nullptr;
}

/**
 * Destructor del Arbol
 */
template<class T>
ArbolAlpha<T>::~ArbolAlpha() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param dato Valor a buscar
 * @return el valor buscado
 */
template<class T>
T ArbolAlpha<T>::search(T dato) { return search(dato, root); }
template<class T>
T ArbolAlpha<T>::search(HashEntry<string> *data, NodoArbol<HashEntry<string>*> *r) {
    if (r == nullptr)throw 703;
    if (r->getData()->getKey() == data->getKey())return r->getData();
    if (r->getData()->getKey() > data->getKey())return search(data, r->getLeft());
    else return search(data, r->getRight());
}

/**
 * Agrega un dato al árbol
 * @param dato Dato para agregar al arbol
 */
template<class T>
void ArbolAlpha<T>::put(HashEntry<string>* dato) { root = put(dato, root); }
template<class T>
NodoArbol<T> *ArbolAlpha<T>::put(HashEntry<string>* data, NodoArbol<HashEntry<string>*> *r) {
    if (r == nullptr) return new NodoArbol<T>(data);
    if (r->getData()->getKey() == data->getKey()) {
        r->aumentarOcurrencia();
        throw 704;
    }
    if (r->getData()->getKey() > data->getKey()) r->setLeft(put(data, r->getLeft()));
    else r->setRight(put(data, r->getRight()));
    return r;
}

/**
 * Informa si un árbol esta vacío
 * @return bool si esta vacio: True
 */
template<class T>
bool ArbolAlpha<T>::esVacio() { return root == nullptr; }

/**
 * Remueve un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param dato Valor a remover
 */
template<class T>
void ArbolAlpha<T>::remove(T dato) { root = remove(dato, root); }
template<class T> NodoArbol<T> *ArbolAlpha<T>::remove(HashEntry<string>* data, NodoArbol<HashEntry<string>*> *r) {
    if (r == nullptr)throw 705;
    if (data->getKey() < r->getData()->getKey()) r->setLeft(remove(data, r->getLeft()));
    else if (data->getKey() > r->getData()->getKey())r->setRight(remove(data, r->getRight()));
    else {
        if (r->getLeft() == nullptr) return r->getRight();
        else if (r->getRight() == nullptr) return r->getLeft();

        r->setData(inOrderSuccessor(r->getRight()));
        r->setRight(remove(r->getData(), r->getRight()));
    }
    return r;
}
template<class T>
T ArbolAlpha<T>::inOrderSuccessor(NodoArbol<T> *r) {
    T minimum = r->getData();
    while (r->getLeft() != nullptr) {
        minimum = r->getLeft()->getData();
        r = r->getLeft();
    }
    return minimum;
}

/**
 * Imprime los datos del arbol en orden
 */
template<class T>
void ArbolAlpha<T>::inorder(int nPalabras, int &count) {
    if (nPalabras == 0) {
        inorder(root);
        return;
    }
    inorder(nPalabras, root, count);
}
template<class T>
void ArbolAlpha<T>::inorder(NodoArbol<HashEntry<string>*> *r) {
    if (r == nullptr) return;
    try {
    inorder(r->getLeft());
        cout << r->getData()->getKey() << "\n";
        inorder(r->getRight());
    }
    catch(int err){}
}
template<class T>
void ArbolAlpha<T>::inorder(int nPalabras, NodoArbol<HashEntry<string>*> *r, int &count) {
    if (r == nullptr) return;
    if (count == nPalabras) return;
    inorder(nPalabras, r->getLeft(), count);
    if (nPalabras > count) {
        cout << r->getData()->getKey() << "\n";
        count++;
        inorder(nPalabras, r->getRight(), count);
    }
}

#endif //PROJECT_WC_PROG3_ARBOLALPHA_H
