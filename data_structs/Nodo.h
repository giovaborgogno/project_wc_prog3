//
// Created by giovaborgogno on 07/09/2022.
//

#ifndef INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODO_H
#define INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODO_H

#include <iostream>

using namespace std;

template<class T> class Nodo{
private:
    T dato;

public:
    Nodo<T> *siguiente;
    Nodo(T dato){
        this->dato = dato;
    };
    ~Nodo(){}
    void setdato(T dato){
        this->dato = dato;
    };
    T getdato(){
        return dato;
    };
    void setsiguiente(Nodo<T> *siguiente){
        this->siguiente = siguiente;
    };
    Nodo<T>* getsiguiente(){
        return siguiente;
    };
};
#endif //INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODO_H
