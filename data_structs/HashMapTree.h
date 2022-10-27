#ifndef U05_HASH_HASHMAP_HASHMAPTREE_H_
#define U05_HASH_HASHMAP_HASHMAPTREE_H_

#include "HashEntry.h"
#include "ArbolAlpha.h"


// table hash con manejo de colisiones usando arboles binarios
template<class K>
class HashMapTree{
private:

    static unsigned int hashFunc(K key);
    unsigned int (*hashFuncP)(K key);

public:

    ArbolAlpha<HashEntry<K>*> **table;
    unsigned int size;
    int posiciones = 0;
    explicit HashMapTree(unsigned int size);
    HashMapTree(unsigned int k, unsigned int (*hashFuncP)(K key));
    ~HashMapTree();
    HashEntry<K> *getHashEntry(K key);
    void put(K key, int valor);
    void remove(K key);
    bool esVacio();

//    void print();
//    void get(K key);
};

template<class K>
HashMapTree<K>::HashMapTree(unsigned int size) {
    this->size = size;
    table = new ArbolAlpha<HashEntry<K>*> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = new ArbolAlpha<HashEntry<K>*>;
    }
    hashFuncP = hashFunc;
}

template<class K>
HashMapTree<K>::HashMapTree(unsigned int k, unsigned int (*fp)(K)) {
    size = k;
    table = new ArbolAlpha<HashEntry<K>*> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = new ArbolAlpha<HashEntry<K>*>;
    }
    hashFuncP = fp;
}

template<class K>
HashMapTree<K>::~HashMapTree() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            delete table[i];
        }
    }
}

template<class K>
void HashMapTree<K>::put(K key, int valor) {
    unsigned int pos = hashFuncP(key) % size;

    try{table[pos]->put(new HashEntry<K>(key, valor));}
    catch (int err) {
    }


}

template<class K>
void HashMapTree<K>::remove(K key) {
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        throw 601;
    }
    table[pos]->remove(getHashEntry(key));

    if (table[pos]->esVacio()) {
        delete table[pos];
        table[pos] = NULL;
    }
}

template<class K>
bool HashMapTree<K>::esVacio() {
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            return false;
        }
    }
    return true;
}

template<class K>
unsigned int HashMapTree<K>::hashFunc(K palabra) {

    int key = int(palabra[0]);
    key -= 97;

    return (unsigned int) key;
}

template<class K>
HashEntry<K> *HashMapTree<K>::getHashEntry(K key) {
    unsigned int pos = hashFuncP(key) % size;
    if (table[pos] == NULL) {
        throw 602;
    }
    HashEntry<K> *aux = new HashEntry<K>(key, 1);
    return table[pos]->search(aux);
}

/*template<class K>
void HashMapTree<K>::get(K key) { // Método que devuelve la lista según la key que recibe
    unsigned int pos = hashFuncP(key) % size;

    if (table[pos] == NULL) {
        throw 404;
    }

    NodoArbol<HashEntry<K>*> *aux = table[pos]->getinicio();

    while (aux != NULL) {
        cout << aux->getDato()->getKey() << " " << aux->getDato()->getValue() << endl;
        aux = aux->getSiguiente();
    }
}*/

/*template<class K>
void HashMapTree<K>::print() {

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
}*/



#endif // U05_HASH_HASHMAP_HASHMAPTREE_H_