#ifndef U04_COLAS_COLA_COLA_H_
#define U04_COLAS_COLA_COLA_H_
#include "Nodo.h"
#include <iostream>
/**
 * Clase que implementa una Cola generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Cola {
private:
    Nodo<T> *primero, *ultimo;
public:
  Cola();
  ~Cola();
  void encolar(T dato);
  T desencolar();
  bool esVacia();
  void encolarPrioridad(int prioridad);
};

/**
 * Constructor de la clase Cola
 * @tparam T
 */
template <class T> Cola<T>::Cola() {
    primero = nullptr;
    ultimo = nullptr;
}

/**
 * Destructor de la clase Cola, se encarga de liberar la memoria de todos los
 * nodos utilizados en la Cola
 * @tparam T
 */
template <class T> Cola<T>::~Cola() {}

/**
 * Inserta un dato en la Cola
 * @tparam T
 * @param dato  dato a insertar
 */
template <class T> void Cola<T>::encolar(T dato) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato);

    if(esVacia()) {
        primero = nuevo;
        ultimo = nuevo;
        return;
    }
        nuevo->setSiguiente(ultimo);
        ultimo = nuevo;
}

/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template <class T> T Cola<T>::desencolar() {
    Nodo<T> *auxNodo = ultimo;
    T dato;

    if(esVacia()) throw 404;
    if(primero == ultimo){
        dato = primero->getDato();
        auxNodo = primero;
        delete auxNodo;
        primero = nullptr;
        ultimo = nullptr;
        return dato;
    }
    while(auxNodo->getSiguiente() != primero){
        auxNodo = auxNodo->getSiguiente();
    }
    dato = primero->getDato();
    delete primero;
    primero = auxNodo;
    return dato;
}

/**
 * Responde si la Cola se encuentra Vacía
 * @tparam T
 * @return
 */
template <class T> bool Cola<T>::esVacia() {
    return primero == nullptr && ultimo == nullptr;
}


#endif // U04_COLAS_COLA_COLA_H_
