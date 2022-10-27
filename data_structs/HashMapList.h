#ifndef U05_HASH_HASHMAP_HASHMAPLIST_H_
#define U05_HASH_HASHMAP_HASHMAPLIST_H_

#include "HashEntry.h"
#include "Lista.h"
#include <ctime>

// table hash con manejo de colisiones usando listas enlazadas
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
//    void putOcurrence(K key, int valor);
};

template<class K>
HashMapList<K>::HashMapList(unsigned int size) {
    this->size = size;
    table = new Lista<HashEntry<K> *> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    hashFuncP = hashFunc;
}

template<class K>
HashMapList<K>::HashMapList(unsigned int k, unsigned int (*fp)(K)) {
    size = k;
    table = new Lista<HashEntry<K> *> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    hashFuncP = fp;
}

template<class K>
HashMapList<K>::~HashMapList() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            delete table[i];
        }
    }
}


template<class K>
bool HashMapList<K>::put(K key, int valor) {
    unsigned int pos = hashFuncP(key) % size;
    if (table[pos] == NULL) {
        table[pos] = new Lista<HashEntry<K> *>;
        posiciones++;
    }
    return table[pos]->insertarHashEntry2(new HashEntry<K>(key, valor));

}

template<class K>
void HashMapList<K>::putOcurrence(K key, int valor) {
  
  unsigned int pos = hashFuncP(key) % size;

  if (table[pos] == NULL) {
    table[pos] = new Lista<HashEntry<K> *>;
    posiciones++;
    }
  
  maxocurrencia=table[pos]->insertarHashEntry(new HashEntry<K>(key, valor),maxocurrencia);
   
}

template<class K>
void HashMapList<K>::remove(K key) {
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        throw 404;
    }

    int dato; // = get(key);

    table[pos]->remove(getHashEntry(key));

    if (table[pos]->esVacia()) {
        delete table[pos];
        table[pos] = NULL;
    }
}

template<class K>
bool HashMapList<K>::esVacio() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            return false;
        }
    }
    return true;
}

template<class K>
unsigned int HashMapList<K>::hashFunc(K palabra) {

    float key = 0;

    for (int i = 0; i < palabra.length(); i++) {
        key += (float(palabra[i]) / 13 * float(palabra[i]) / 13) / 11 + key / 131;
    }

    key = key * 3019 * 3023;

    return (unsigned int) key;
}

template<class K>
void HashMapList<K>::print() {

    std::cout << "i"
              << " "
              << "Clave"
              << "\t\t"
              << "Valor" << std::endl;
    std::cout << "--------------------" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << " ";
        if (table[i] != NULL) {
            try {
                std::cout << table[i]->getDato(0)->getKey() << "\t\t";
                std::cout << table[i]->getDato(0)->getValue();
            }
            catch (int err) {

            }
        }
        std::cout << std::endl;
    }
}

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

/*template<class K>
void HashMapList<K>::put(K key, int valor) {
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        table[pos] = new Lista<HashEntry<K>*>;
        posiciones++;
    }
    for (int i = 0; i < table[pos]->getTamanio(); ++i) {

        if (table[pos]->getDato(i)->getKey() == key) {
            throw 404;
        }
    }
    table[pos]->insertarUltimo( new HashEntry<K>(key, valor));
}*/

template<class K>
void HashMapList<K>::get(K key) { // Método que devuelve la lista según la key que recibe
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