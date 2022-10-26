#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_

#include "Nodo.h"

/**
 * Clase que implementa una Lista Enlazada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Lista {
private:
  Nodo<T> *inicio;
  int tamanio = 0;

public:
  Lista();
  Lista(const Lista<T> &li);
  ~Lista();
  bool esVacia();
  int getTamanio();
  void insertar(int pos, T dato);
  void insertarPrimero(T dato);
  void insertarUltimo(T dato);
  int insertarHashEntry(HashEntry<string> *HashEntry, int maxocurrencia);
  void insertarHashEntry2(HashEntry<string> *HashEntry);
  void remover(int pos);
  T getDato(int pos);
  void reemplazar(int pos, T dato);
  void vaciar();
  Nodo<T> *getinicio() {
    if (esVacia())
      throw 404;
    return inicio;
  };
  void setinicio(Nodo<T> *inicio) { this->inicio = inicio; }

  void remove(HashEntry<string> *hashEntry);
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T> Lista<T>::Lista() {
  inicio = nullptr;
  tamanio = 0;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T> Lista<T>::Lista(const Lista<T> &li) { tamanio = 0; }

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Lista<T>::~Lista() {}

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T> bool Lista<T>::esVacia() { return inicio == NULL; }

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
/*template <class T> int Lista<T>::getTamanio() {
    int size = 0;
    Nodo<T> *auxNodo= inicio;

    while(auxNodo->getSiguiente() != NULL){
        size++;
        auxNodo = auxNodo->getSiguiente();
    }

    return size+1;
}*/

template <class T> int Lista<T>::getTamanio() { return tamanio; }

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T> void Lista<T>::insertar(int pos, T dato) {
  int posActual = 0;
  Nodo<T> *auxNodo = inicio, *nuevo;
  nuevo = new Nodo<T>;
  nuevo->setDato(dato);

  if (pos == 0) {
    nuevo->setSiguiente(inicio);
    inicio = nuevo;
    tamanio++;
    return;
  }

  while (auxNodo != NULL && posActual < pos - 1) {
    auxNodo = auxNodo->getSiguiente();
    posActual++;
  }

  if (auxNodo == NULL)
    throw 404;

  nuevo->setSiguiente(auxNodo->getSiguiente());
  auxNodo->setSiguiente(nuevo);
  tamanio++;
}

/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarPrimero(T dato) {
  Nodo<T> *nuevo;
  nuevo = new Nodo<T>(dato);

  nuevo->setSiguiente(inicio);
  inicio = nuevo;
  tamanio++;
}
/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarUltimo(T dato) {
  Nodo<T> *auxNodo = inicio, *nuevo = new Nodo<T>(dato);

  if (esVacia()) {
    insertarPrimero(dato);
    return;
  }

  while (auxNodo->getSiguiente() != nullptr) {
    auxNodo = auxNodo->getSiguiente();
  }

  auxNodo->setSiguiente(nuevo);
  nuevo->setSiguiente(nullptr);
  tamanio++;
}

/**
 * Inserta un HashEntry y verifica ocurrencia de la palabra
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
int Lista<T>::insertarHashEntry(HashEntry<string> *HashEntry,
                                int maxocurrencia) {
  Nodo<T> *auxNodo = inicio, *nuevo = new Nodo<T>(HashEntry);

  if (esVacia()) {
    insertarPrimero(HashEntry);
    return maxocurrencia;
  }

  while (auxNodo->getDato()->getKey() != HashEntry->getKey() &&
         auxNodo->getSiguiente() != nullptr) {
    auxNodo = auxNodo->getSiguiente();
  }
  if (auxNodo->getDato()->getKey() == HashEntry->getKey()) {
    auxNodo->getDato()->incrementValue();
    if (auxNodo->getDato()->getValue() > maxocurrencia)
      maxocurrencia = auxNodo->getDato()->getValue();
    return maxocurrencia;
  }
    auxNodo->setSiguiente(nuevo);
    nuevo->setSiguiente(nullptr);
    tamanio++;
    return maxocurrencia;
}

template <class T>
void Lista<T>::insertarHashEntry2(HashEntry<string> *HashEntry) {
  Nodo<T> *auxNodo = inicio, *nuevo = new Nodo<T>(HashEntry);

  if (esVacia()) {
    insertarPrimero(HashEntry);
    return;
  }

  while (auxNodo->getDato()->getKey() != HashEntry->getKey() &&
         auxNodo->getSiguiente() != nullptr) {
    auxNodo = auxNodo->getSiguiente();
  }
  if (auxNodo->getDato()->getKey() == HashEntry->getKey()) {
    HashEntry->incrementValue();
    throw 405;
  }
    auxNodo->setSiguiente(nuevo);
    nuevo->setSiguiente(nullptr);
    tamanio++;
    return;
}

/**
 * Elimina el nodo en la posicion 'pos' de la lista enlasada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T> void Lista<T>::remover(int pos) {
  int posActual1 = 0, posActual2 = 0;
  Nodo<T> *auxNodo1 = inicio, *auxNodo2 = inicio;

  if (pos == 0) {
    inicio = inicio->getSiguiente();
    auxNodo1->setSiguiente(NULL);
    delete auxNodo1;
    tamanio--;
    return;
  }

  // Nodo anterior al que se desea eliminar
  while (auxNodo1 != NULL && posActual1 < pos - 1) {
    auxNodo1 = auxNodo1->getSiguiente();
    posActual1++;
  }
  if (auxNodo1 == NULL)
    throw 406;

  // Nodo que se desea eliminar
  auxNodo2 = auxNodo1->getSiguiente();

  auxNodo1->setSiguiente(auxNodo2->getSiguiente());
  auxNodo2->setSiguiente(NULL);
  tamanio--;
  delete auxNodo2;
}

template <class T> void Lista<T>::remove(HashEntry<string> *hashEntry) {
  Nodo<T> *auxNodo1 = inicio, *auxNodo2 = inicio;

  if (inicio->getDato()->getKey() == hashEntry->getKey()) {
    inicio = inicio->getSiguiente();
    auxNodo1->setSiguiente(NULL);
    delete auxNodo1;
    tamanio--;
    return;
  }

  // Nodo anterior al que se desea eliminar
  while (auxNodo1 != NULL &&
         auxNodo1->getDato()->getKey() != hashEntry->getKey()) {
    auxNodo1 = auxNodo1->getSiguiente();
  }
  if (auxNodo1 == NULL)
    throw 406;

  // Nodo que se desea eliminar
  auxNodo2 = auxNodo1->getSiguiente();

  auxNodo1->setSiguiente(auxNodo2->getSiguiente());
  auxNodo2->setSiguiente(NULL);
  tamanio--;
  delete auxNodo2;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T> T Lista<T>::getDato(int pos) {
  int posActual = 0;
  Nodo<T> *auxNodo = inicio;

  if (esVacia())
    throw 413;

  while (auxNodo != NULL && posActual < pos) {
    auxNodo = auxNodo->getSiguiente();
    posActual++;
  }

  if (auxNodo == NULL)
    throw 409;

  return auxNodo->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T> void Lista<T>::reemplazar(int pos, T dato) {
  int posActual = 0;
  Nodo<T> *auxNodo = inicio;

  if (esVacia())
    throw 412;

  while (auxNodo != NULL && posActual < pos) {
    auxNodo = auxNodo->getSiguiente();
    posActual++;
  }

  if (auxNodo == NULL)
    throw 410;

  auxNodo->setDato(dato);
}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T> void Lista<T>::vaciar() {
  Nodo<T> *auxNodo;

  if (esVacia())
    throw 411;

  auxNodo = inicio;
  inicio = NULL;
  delete auxNodo;
}

#endif // U02_LISTAS_LISTA_LISTA_H_