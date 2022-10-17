//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_ARBOLALPHA_H
#define PROJECT_WC_PROG3_ARBOLALPHA_H

#include "NodoArbol.h"
#include "ArbolOccurrence.h"

template<class T>
class ArbolAlpha {
private:
    T search(T data, NodoArbol<T> *r);

    NodoArbol<T> *put(T data, NodoArbol<T> *r);

    void inorder(NodoArbol<T> *r);

    void inorder(int nPalabras, NodoArbol<T> *r, int &count);

    void setArbolOccurrence(NodoArbol<T> *r);



protected:
    NodoArbol<T> *root;
    ArbolOccurrence<T> ArbolOcurrence;

public:
    ArbolAlpha();
    void put(T dato);
    T search(T dato);
    void inorder(int nPalabras = 0);
    void setArbolOccurrence();
    void inorderOccurrence(int nPalabras = 0);
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
    if (r == nullptr) return new NodoArbol<T>(data);
    if (r->getData() == data) {
        r->aumentarOcurrencia();
        throw 200;
    }
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
void ArbolAlpha<T>::inorder(int nPalabras) {
    if (nPalabras == 0) {
        inorder(root);
        return;
    }
    int a = 0;
    inorder(nPalabras, root, a);
}

template<class T>
void ArbolAlpha<T>::inorder(NodoArbol<T> *r) {
    if (r == nullptr) return;
    inorder(r->getLeft());
//    cout << r->getData() << " " << r->getOcurrencia() << " ,";
    cout << r->getData() << " " << r->getOcurrencia() << "\n";
    inorder(r->getRight());
}

template<class T>
void ArbolAlpha<T>::inorder(int nPalabras, NodoArbol<T> *r, int &count) {
    if (r == nullptr) return;
    if (count == nPalabras) return;
    inorder(nPalabras, r->getLeft(), count);
    if (nPalabras > count) {
        cout << r->getData() << " " << r->getOcurrencia() << "\n";
        count++;
        inorder(nPalabras, r->getRight(), count);
    }
}
template<class T>
void ArbolAlpha<T>::setArbolOccurrence(){ setArbolOccurrence(root);}
template<class T>
void ArbolAlpha<T>::setArbolOccurrence(NodoArbol<T> *r) {
    if (r == nullptr) return;
    setArbolOccurrence(r->getLeft());
    try {
        
    ArbolOcurrence.put(r->getData(),r->getOcurrencia());
    } catch (int err) {
        
    }
    setArbolOccurrence(r->getRight());
}


/**
 * Muestra un árbol por consola
 */
template<class T>
void ArbolAlpha<T>::print() {
    if (root != NULL)
        root->print(false, "");
}

template<class T>
void ArbolAlpha<T>::inorderOccurrence(int nPalabras) {
    if (nPalabras == 0) {
        inorder(ArbolOcurrence.root);
        return;
    }
    int a = 0;
    inorder(nPalabras, ArbolOcurrence.root, a);
}

#endif //PROJECT_WC_PROG3_ARBOLALPHA_H
