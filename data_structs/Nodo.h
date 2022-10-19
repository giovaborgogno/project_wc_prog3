//
// Created by giovaborgogno on 18/10/2022.
//

#ifndef PROJECT_WC_PROG3_NODO_H
#define PROJECT_WC_PROG3_NODO_H
#include <iostream>

using namespace std;

template<class T>class Nodo{
private:
    T dato;
    Nodo<T> *siguiente;

public:

    Nodo(){};

    Nodo(T dato){
        this->dato = dato;
    }
    ~Nodo(){

    }
    void setDato(T dato){
        this->dato = dato;
    };
    T getDato(){
        return dato;
    };
    void setSiguiente(Nodo<T> *siguiente){
        this->siguiente = siguiente;
    };
    Nodo<T>* getSiguiente(){
        return siguiente;
    };
};
#endif //PROJECT_WC_PROG3_NODO_H
