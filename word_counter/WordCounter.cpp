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

    string palabra, linea;
    ArbolAlpha<string> *arbol = new ArbolAlpha<string>();

    while (getline(fich, linea)) {
        countLineas++;
        stringstream stream(linea);
        while (stream >> palabra) {
            countLetras += palabra.length();
            try {
                countPalabras++;
                arbol->put(palabra);
                countPalabrasDif++;
            }
            catch (int err) {
            };
        }
    }
    return arbol;
}

void WordCounter::basicas() {
    loadDataInTree();
    cout << countLineas << " lineas\n";
    cout << countLetras << " letras\n";
    cout << countPalabras << " palabras\n";
    cout << countPalabrasDif << " palabras diferentes\n";
}

void WordCounter::palabras(ArbolAlpha<string> *arbol, int nPalabras) {
    //ArbolAlpha<string> *arbol = loadDataInTree();
    arbol->inorder(nPalabras);
}

void WordCounter::ocurrencias(ArbolAlpha<string> *arbol, int nPalabras) {
    //ArbolAlpha<string> *arbol = loadDataInTree();
    arbol->setArbolOccurrence();
    arbol->inorderOccurrence(nPalabras);
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