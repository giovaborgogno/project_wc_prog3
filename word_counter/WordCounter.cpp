//
// Created by giovaborgogno on 17/10/2022.
//

#include "WordCounter.h"
#include <fstream>
#include <sstream>

// soloPalabra() elimina del string los signos de puntuacion y numeros y convierte a minuscula
string WordCounter::soloPalabra(string palabra) {
    string nuevaPalabra;
    for (int i = 0; i < palabra.length(); ++i) {
        if (!ispunct(palabra[i]) && !isdigit(palabra[i])) nuevaPalabra += tolower(palabra[i]);
    }
    if (nuevaPalabra.length() == 0)throw 11;
    return nuevaPalabra;
}
// load() se usa en wce.basicas();
HashMapList<string> *WordCounter::load() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    int tamanio = 584999;
//    int tamanio = 200003;
    HashMapList<string> *hash = new HashMapList<string>(tamanio);
    string palabra, linea;
    while (getline(fich, linea)) {
        countLineas++;
        stringstream stream(linea);
        while (stream >> palabra) {
            try {
                palabra = soloPalabra(palabra);
                countLetras += palabra.length();
                countPalabras++;
                hash->put(palabra, 1);
                countPalabrasDif++;
            }
            catch (int err) {
            };
        }
    }
    cout << "Hubo " << countPalabrasDif - hash->posiciones << " colisiones\n";

    return hash;
}
// loadInHash() se usa en mostrar();
HashMapList<string> *WordCounter::loadHashList() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    int tamanio = 584999;
    HashMapList<string> *hash = new HashMapList<string>(tamanio);
    string palabra;
    while (fich >> palabra) {
        try {
            hash->put(soloPalabra(palabra), 1);
        }
        catch (int err) {
        };
    }

    return hash;
}
//loadHashTree() se usa en palabras();
HashMapTree<string> *WordCounter::loadHashTree() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    int tamanio = 27;
    HashMapTree<string> *hash = new HashMapTree<string>(tamanio);
    string palabra, linea;
        while (fich >> palabra) {
            try {
                palabra = soloPalabra(palabra);
                hash->put(palabra, 1);
            }
            catch (int err) {

            };
        }
    return hash;
}

void WordCounter::basicas() {
    load();
    cout << countLineas << " lineas\n";
    cout << countLetras << " letras\n";
    cout << countPalabras << " palabras\n";
    cout << countPalabrasDif << " palabras diferentes\n";
}

void WordCounter::palabras(HashMapTree<string> *hash, int nPalabras) {
   // HashMapTree<string> *hash = loadHashTree();
    ColaPrioridad<HashEntry<string> *> colaPrioridad;
    int count = 0;
    for (int i = 0; i < hash->size; ++i) {
        if(hash->table[i] != NULL) {
            try {
                hash->table[i]->inorder(nPalabras, count);
            }
            catch (int err) {

            }
        }
    }
}

void WordCounter::mostrar(string palabras) {
    HashMapList<string> *hash = loadHashList();
    stringstream stream(palabras);
    Cola<string> cola;
    ColaPrioridad<HashEntry<string> *> colaPrioridad;
    string palabra;
    while (stream >> palabra) {
        try { cola.encolar(soloPalabra(palabra)); }
        catch (int err) {

        }
    }
    while (!cola.esVacia()) {
        try {
            string dato = cola.desencolar();
            colaPrioridad.encolarPrioridad(hash->getHashEntry(dato), hash->getHashEntry(dato)->getValue());

        } catch (int err) {
        }
    }
    while (!colaPrioridad.esVacia()) {
        HashEntry<string> *dato = colaPrioridad.desencolar();
        cout << dato->getKey() << " " << dato->getValue() << "\n";
    }

}

HashMapTree<string> *WordCounter::palabrasExcluir(string palabras) {
    HashMapTree<string> *hash = loadHashTree();
    stringstream stream(palabras);
    Cola<string> cola;
    string palabra;
    while (stream >> palabra) {
        cola.encolar(soloPalabra(palabra));
    }
    while (!cola.esVacia()) {
        try {
            hash->remove(cola.desencolar());
        } catch (int err) {
        }
    }
    return hash;
}

HashMapTree<string> *WordCounter::palabrasExcluirf(string ARCHIVO_EXCLUIR) {
    HashMapTree<string> *hash = loadHashTree();
    Cola<string> cola;
    ifstream fich(ARCHIVO_EXCLUIR);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    while (fich >> palabra) {
        try {
            cola.encolar(palabra);
        }
        catch (int err) {
        };
    }
    while (!cola.esVacia()) {
        try {
            hash->remove(cola.desencolar());
        } catch (int err) {
        }
    }
    return hash;
}

/*ArbolAlpha<string> *WordCounter::loadDataInTree() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    ArbolAlpha<string> *arbol = new ArbolAlpha<string>();

    while (fich >> palabra) {
        try {
            arbol->put(soloPalabra(palabra));
        }
        catch (int err) {
        }
    }
    return arbol;
}*/
/*ArbolAlpha<string> *WordCounter::excluir(string palabras) {
    ArbolAlpha<string> *arbol = loadDataInTree();
    stringstream stream(palabras);
    Cola<string> cola;
    string palabra;
    while (stream >> palabra) {
        cola.encolar(palabra);
    }
    while (!cola.esVacia()) {
        try {
            arbol->remove(cola.desencolar());

        } catch (int err) {

        }
    }
    return arbol;
}*/
/*

ArbolAlpha<string> *WordCounter::excluirf(std::string ARCHIVO_EXCLUIR) {
    ArbolAlpha<string> *arbol = loadDataInTree();
    Cola<string> cola;
    ifstream fich(ARCHIVO_EXCLUIR);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    while (fich >> palabra) {
        try {
            cola.encolar(palabra);
        }
        catch (int err) {
        };
    }

    while (!cola.esVacia()) {
        try {
            arbol->remove(cola.desencolar());

        } catch (int err) {

        }
    }
    return arbol;
}
*/
/*
 * void WordCounter::palabras(ArbolAlpha<string> *arbol, int nPalabras) {
    //ArbolAlpha<string> *arbol = loadDataInTree();
    arbol->inorder(nPalabras);
}
*/
/*
void WordCounter::palabrasNuevo(int nPalabras) {
    HashMapList<string> *hash = loadInHash();
    ColaPrioridad<HashEntry<string> *> colaPrioridad;
    int count = 0;
    for (int i = 0; i < hash->size; ++i) {
        try {
            if (!hash->table[i])throw 404;
            Nodo<HashEntry<string> *> *temp = hash->table[i]->getinicio();
            if (hash->table[i]->esVacia())throw 404;
            else {
                while (temp != nullptr) {
                    {
                        colaPrioridad.encolarPrioridadString(temp->getDato(), temp->getDato()->getKey());
                        count++;
//                        colaPrioridad.encolarPrioridadString(temp->getDato(),temp->getDato()->getKey());
                        if (temp->getSiguiente() == nullptr) break;
                        temp = temp->getSiguiente();

                    }
                }
            }
        }
        catch (int err) {
        }
    }
    if (nPalabras == 0) {
        for (int i = 0; i < count; ++i) {
            HashEntry<string> *hashEntry = colaPrioridad.desencolar();
            cout << hashEntry->getKey() << " " << hashEntry->getValue() << "\n";
        }
        return;
    }

    for (int i = 0; i < nPalabras; ++i) {
        HashEntry<string> *hashEntry = colaPrioridad.desencolar();
        cout << hashEntry->getKey() << " " << hashEntry->getValue() << "\n";
    }

}
*/
/*
void WordCounter::ocurrencias(HashMapList<string> *hash, int nPalabras) {
    ArbolOccurrence-viejo<string> *arbol = new ArbolOccurrence-viejo<string>();
    for (int i = 0; i < hash->size; ++i) {
        try {

            if (!hash->table[i])throw 404;
            Nodo<HashEntry<string> *> *temp = hash->table[i]->getinicio();
            if (hash->table[i]->esVacia())throw 404;
            else {
                while (temp != nullptr) {
                    {
                        arbol->put(temp->getDato()->getKey(), temp->getDato()->getValue());
                        if (temp->getSiguiente() == nullptr) break;
                        temp = temp->getSiguiente();

                    }
                }
            }
        }
        catch (int err) {
        }
    }

    arbol->inorder(nPalabras);
}
*/




