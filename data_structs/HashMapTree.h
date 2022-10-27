#ifndef U05_HASH_HASHMAP_HASHMAPTREE_H_
#define U05_HASH_HASHMAP_HASHMAPTREE_H_

#include "HashEntry.h"
#include "ArbolAlpha.h"


/**
 * Clase que implementa una Table Hash con 
 * manejo de excepciones usando Arboles Binarios
 * @tparam T cualquier tipo de dato
 */
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

};

/**
 * Constructor de la clase HashMapTree
 * @param int size 
 */
template<class K>
HashMapTree<K>::HashMapTree(unsigned int size) {
    this->size = size;
    table = new ArbolAlpha<HashEntry<K>*> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = new ArbolAlpha<HashEntry<K>*>;
    }
    hashFuncP = hashFunc;
}

/**
 * Constructor de la clase HashMapTree
 * @param int size 
 */
template<class K>
HashMapTree<K>::HashMapTree(unsigned int k, unsigned int (*fp)(K)) {
    size = k;
    table = new ArbolAlpha<HashEntry<K>*> *[size];
    for (int i = 0; i < size; i++) {
        table[i] = new ArbolAlpha<HashEntry<K>*>;
    }
    hashFuncP = fp;
}

/**
 * Destructor de la clase HashMapTree, se encarga de liberar la memoria de todos los
 * nodos utilizados en el HashMapTree
 * @tparam T
 */
template<class K>
HashMapTree<K>::~HashMapTree() {
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
 */
template<class K>
void HashMapTree<K>::put(K key, int valor) {
    unsigned int pos = hashFuncP(key) % size;

    try{table[pos]->put(new HashEntry<K>(key, valor));}
    catch (int err) {
    }
}

/**
 * Remueve del table Hash el dato que contenga el key
 * 
 * @tparam K 
 * @param key 
 */
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

/**
 * Muestra si esta vacio el table hash
 * 
 * @tparam K 
 * @return bool
 */
template<class K>
bool HashMapTree<K>::esVacio() {
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
unsigned int HashMapTree<K>::hashFunc(K palabra) {

    int key = int(palabra[0]);
    key -= 97;

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
HashEntry<K> *HashMapTree<K>::getHashEntry(K key) {
    unsigned int pos = hashFuncP(key) % size;
    if (table[pos] == NULL) {
        throw 602;
    }
    HashEntry<K> *aux = new HashEntry<K>(key, 1);
    return table[pos]->search(aux);
}

#endif // U05_HASH_HASHMAP_HASHMAPTREE_H_