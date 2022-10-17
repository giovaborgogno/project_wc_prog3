//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_NODOARBOL_H
#define PROJECT_WC_PROG3_NODOARBOL_H

#include <iostream>

using namespace std;
template <class T> class NodoArbol {
private:
    T data;
    int ocurrencia;
    NodoArbol *left, *right;

public:
    NodoArbol() {
        left = nullptr;
        right = nullptr;
    }

    NodoArbol(T d) {
        this->data = d;
        this->ocurrencia = 1;
        left = nullptr;
        right = nullptr;
    }
    NodoArbol(T d, int o) {
        this->data = d;
        this->ocurrencia = o;
        left = nullptr;
        right = nullptr;
    }

    T getData() const { return data;}

    int getOcurrencia() const { return ocurrencia;}

    void setData(T d) { this->data = d;}

    void aumentarOcurrencia(){ocurrencia++;}

    NodoArbol *getRight() const { return right;}

    NodoArbol *getLeft() const { return left;}

    void setRight(NodoArbol *r) {
        this->right = r;
    }

    void setLeft(NodoArbol *l) {
        this->left = l;
    }

    void print(bool esDerecho, std::string identacion) {
        if (right != nullptr) {
            right->print(true, identacion + (esDerecho ? "     " : "|    "));
        }
        cout << identacion;
        if (esDerecho) {
            cout << " /";
        } else {
            cout << " \\";
        }
        cout << "-- ";
        cout << data << endl;
        if (left != NULL) {
            left->print(false, identacion + (esDerecho ? "|    " : "     "));
        }
    }
};


#endif //PROJECT_WC_PROG3_NODOARBOL_H
