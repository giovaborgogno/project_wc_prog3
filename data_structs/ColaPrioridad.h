//
// Created by giovaborgogno on 08/09/2022.
//

#ifndef INC_2021A2_U04_COLAS_GIOVABORGOGNO_COLAPRIORIDAD_H
#define INC_2021A2_U04_COLAS_GIOVABORGOGNO_COLAPRIORIDAD_H
#include "NodoPrioridad.h"


/**
 * Clase que implementa una Cola generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T>
class ColaPrioridad
{
private:
    NodoPrioridad<T> *tope, *fondo;

public:
    ColaPrioridad();
    ~ColaPrioridad();
    void encolar(T dato);
    void encolarPrioridad(T dato, int prioridad);
    void encolarPrioridadString(T dato, string prioridad);
    T desencolar();
    bool esVacia();
    T peek();
};

/**
 * Constructor de la clase Cola
 * @tparam T
 */
template <class T>
ColaPrioridad<T>::ColaPrioridad()
{
    tope = nullptr;
    fondo = nullptr;
}

/**
 * Destructor de la clase Cola, se encarga de liberar la memoria de todos los
 * nodos utilizados en la Cola
 * @tparam T
 */
template <class T>
ColaPrioridad<T>::~ColaPrioridad()
{
    while (!esVacia())
    {
        desencolar();
    }

    delete tope;
    delete fondo;
}

/**
 * Inserta un dato en la Cola
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T>
void ColaPrioridad<T>::encolar(T dato)
{
    NodoPrioridad<T> *nuevo = new NodoPrioridad<T>(dato,SIN_PRIORIDAD);

    if (esVacia())tope = nuevo;
    else fondo->setSiguiente(nuevo);

    fondo = nuevo;
}

/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T>
T ColaPrioridad<T>::desencolar()
{
    if (esVacia())throw 400;

    T dato = tope->getDato();
    NodoPrioridad<T> *aBorrar = tope;
    tope = tope->getSiguiente();

    if (tope == nullptr)fondo = nullptr;

    delete aBorrar;
    return dato;
}

/**
 * Responde si la Cola se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T>
bool ColaPrioridad<T>::esVacia()
{
    return fondo == nullptr;
}

/**
 * Obtener el dato de la Cola sin eliminar el nodo
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T>
T ColaPrioridad<T>::peek()
{
    if (esVacia())throw 400;

    return tope->getDato();
}

/**
 * Inserta un dato en la Cola con prioridad 
 * @tparam T dato a insertar
 * @param int prioridad
 */
template <class T>
void ColaPrioridad<T>::encolarPrioridad(T dato, int prioridad)
{

    NodoPrioridad<T> *nuevo = new NodoPrioridad<T>(dato,prioridad);

    if(esVacia()){
        nuevo->setSiguiente(nullptr);
        tope = nuevo;
        fondo = nuevo;
        return;
    }
    if (tope->getPrioridad() < prioridad){
        nuevo->setSiguiente(tope);
        tope = nuevo;
        return;
    }
    if(tope->getSiguiente()== nullptr){

        tope->setSiguiente(nuevo);
        fondo = nuevo;
        return;
    }
    NodoPrioridad<T> *aux = tope;
    while (aux->getSiguiente()!= nullptr && aux->getSiguiente()->getPrioridad() >= prioridad){
        aux = aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

#endif //INC_2021A2_U04_COLAS_GIOVABORGOGNO_COLAPRIORIDAD_H
