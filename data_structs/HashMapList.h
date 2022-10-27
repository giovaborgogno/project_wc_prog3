#ifndef U05_HASH_HASHMAP_HASHMAPLIST_H_
#define U05_HASH_HASHMAP_HASHMAPLIST_H_

#include "HashEntry.h"
#include "Lista.h"
#include <ctime>

/**
 * Clase que implementa una Table Hash con 
 * manejo de excepciones usando Listas Enlazadas
 * @tparam T cualquier tipo de dato
 */
template<class K>
class HashMapList {
private:
    static unsigned int hashFunc(K key);

    unsigned int (*hashFuncP)(K key);

public:

    Lista<HashEntry<K>*> **table;
    unsigned int size;
    int posiciones = 0;
    int maxocurrencia = 0;

    explicit HashMapList(unsigned int size);
    HashMapList(unsigned int k, unsigned int (*hashFuncP)(K key));
    ~HashMapList();
    HashEntry<K> *getHashEntry(K key);
    bool put(K key, int valor);
    void putOcurrence(K key, int valor);
    void remove(K key);
    bool esVacio();
    void print();
    void get(K key);
};

/**
 * Constructor de la clase HashMapList
 * @param int size 
 */
template<class K>
HashMapList<K>::HashMapList(unsigned int size) {
    this->size = size;
    table = new Lista<HashEntry<K> *> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    hashFuncP = hashFunc;
}

/**
 * Constructor de la clase HashMapList
 * @param int size 
 */
template<class K>
HashMapList<K>::HashMapList(unsigned int k, unsigned int (*fp)(K)) {
    size = k;
    table = new Lista<HashEntry<K> *> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    hashFuncP = fp;
}

/**
 * Destructor de la clase HashMapList, se encarga de liberar la memoria de todos los
 * nodos utilizados en el HashMapList
 * @tparam T
 */
template<class K>
HashMapList<K>::~HashMapList() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            delete table[i];
        }
    }
}

/**
 * Inserta un dato en el table hash
 * 
 * @tparam K 
 * @param key 
 * @param valor 
 * @return bool
 */
template<class K>
bool HashMapList<K>::put(K key, int valor) {
    unsigned int pos = hashFuncP(key) % size;
    if (table[pos] == NULL) {
        table[pos] = new Lista<HashEntry<K> *>;
        posiciones++;
    }
    return table[pos]->insertarHashEntry(new HashEntry<K>(key, valor));

}

/**
 * Inserta un dato en el table hash seteando la ocurrencia del key
 * 
 * @tparam K 
 * @param key 
 * @param valor 
 */
template<class K>
void HashMapList<K>::putOcurrence(K key, int valor) {
  
  unsigned int pos = hashFuncP(key) % size;

  if (table[pos] == NULL) {
    table[pos] = new Lista<HashEntry<K> *>;
    posiciones++;
    }
  
  maxocurrencia=table[pos]->insertarHashEntry_occurrence(new HashEntry<K>(key, valor),maxocurrencia);
   
}

/**
 * Remueve del table Hash el dato que contenga el key
 * 
 * @tparam K 
 * @param key 
 */
template<class K>
void HashMapList<K>::remove(K key) {
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        throw 404;
    }

    table[pos]->remove(getHashEntry(key));

    if (table[pos]->esVacia()) {
        delete table[pos];
        table[pos] = NULL;
    }
}

/**
 * Muestra si esta vacio el table hash
 * 
 * @tparam K 
 * @return bool
 */
template<class K>
bool HashMapList<K>::esVacio() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            return false;
        }
    }
    return true;
}

/**
 * Funcion Hash 
 * 
 * @tparam K 
 * @param palabra 
 * @return unsigned int posicion donde se guardara la palabra
 */
template<class K>
unsigned int HashMapList<K>::hashFunc(K palabra) {

    float key = 0;

    for (int i = 0; i < palabra.length(); i++) {
        key += (float(palabra[i]) / 13 * float(palabra[i]) / 13) / 11 + key / 131;
    }

    key = key * 3019 * 3023;

    return (unsigned int) key;
}

/**
 * Retorna el HashEntry con el key pasado por parametro 
 * 
 * @tparam K 
 * @param key 
 * @return HashEntry<K>* 
 */
template<class K>
HashEntry<K> *HashMapList<K>::getHashEntry(K key) {
    unsigned int pos = hashFuncP(key) % size;
    if (table[pos] == NULL) {
        throw 2;
    }

    Nodo<HashEntry<K> *> *aux = table[pos]->getinicio();
    HashEntry<K> *hashEntry;

    while (aux != NULL) {
        if (aux->getDato()->getKey() == key) {
            hashEntry = aux->getDato();
            return hashEntry;
        }
        aux = aux->getSiguiente();
    }
    throw 123;
}

// Método que devuelve el nodo según la key que recibe
template<class K>
void HashMapList<K>::get(K key) { 
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        throw 404;
    }

    Nodo<HashEntry<K> *> *aux = table[pos]->getinicio();

    while (aux != NULL) {
        cout << aux->getDato()->getKey() << " " << aux->getDato()->getValue() << endl;
        aux = aux->getSiguiente();
    }
}


#endif // U05_HASH_HASHMAP_HASHMAPLIST_H_