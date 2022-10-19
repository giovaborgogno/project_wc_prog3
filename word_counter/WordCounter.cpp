//
// Created by giovaborgogno on 17/10/2022.
//

#include "WordCounter.h"
#include <fstream>
#include <sstream>

ArbolAlpha<string> *WordCounter::loadDataInTree() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    ArbolAlpha<string> *arbol = new ArbolAlpha<string>();

    while (fich >> palabra) {
        try {
            arbol->put(palabra);
        }
        catch (int err) {
        }
    }
    return arbol;
}

HashMapList<string> *WordCounter::load() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    int tamanio = 584999;
    HashMapList<string> *hash = new HashMapList<string>(tamanio);
    string palabra, linea;
    while (getline(fich, linea)) {
        countLineas++;
        stringstream stream(linea);
        while (stream >> palabra) {
            countLetras += palabra.length();
            try {
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

void WordCounter::basicas() {
    load();
    cout << countLineas << " lineas\n";
    cout << countLetras << " letras\n";
    cout << countPalabras << " palabras\n";
    cout << countPalabrasDif << " palabras diferentes\n";
}

void WordCounter::palabras(ArbolAlpha<string> *arbol, int nPalabras) {
    //ArbolAlpha<string> *arbol = loadDataInTree();
    arbol->inorder(nPalabras);
}

void WordCounter::ocurrencias(HashMapList<string> *hash, int nPalabras) {
    ArbolOccurrence<string> *arbol = new ArbolOccurrence<string>();
    for (int i = 0; i < hash->size; ++i) {
        try {

            if(!hash->table[i])throw 404;
            Nodo<HashEntry<string>> *temp = hash->table[i]->getinicio();
            if (hash->table[i]->esVacia())throw 404;
            else {
                while (temp != nullptr) {
                    {
                        arbol->put(temp->getDato().getKey(), temp->getDato().getValue());
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

ArbolAlpha<string> *WordCounter::excluir(string palabras) {
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
}

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

HashMapList<string> *WordCounter::loadInHash() {
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
            hash->putOcurrence(palabra, 1);
        }
        catch (int err) {
        };
    }

    return hash;
}

void WordCounter::mostrar(string palabras) {
    HashMapList<string> *hash = loadInHash();
    stringstream stream(palabras);
    Cola<string> cola;
    string palabra;
    while (stream >> palabra) {
        cola.encolar(palabra);
    }
    while (!cola.esVacia()) {
        try {
            hash->get(cola.desencolar());

        } catch (int err) {

        }
    }

}
