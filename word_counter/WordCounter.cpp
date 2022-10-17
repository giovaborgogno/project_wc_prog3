//
// Created by giovaborgogno on 17/10/2022.
//

#include "WordCounter.h"
#include <fstream>


ArbolAlpha<string> WordCounter::llenarArbol() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }

    string palabra;
    ArbolAlpha<string> arbol;

    int countErrors=0;
    while (fich >> palabra) {
        countLetras += palabra.length();
        try {
            countPalabras++;
            arbol.put(palabra);
            countPalabrasDif++;
        }
        catch (int err){
        };
    }
    return arbol;
}

void WordCounter::basicas(){
    ArbolAlpha<string> arbol = llenarArbol();
    cout << countLineas << " lineas\n";
    cout << countLetras << " letras\n";
    cout << countPalabras << " palabras\n";
    cout << countPalabrasDif << " palabras diferentes\n";
}

void WordCounter::palabras(int nPalabras){
    ArbolAlpha<string> arbol = llenarArbol();
    arbol.inorder(nPalabras);
}

void WordCounter::ocurrencias(int nPalabras){
    ArbolAlpha<string> arbol = llenarArbol();
    arbol.setArbolOccurrence();
    arbol.inorderOccurrence(nPalabras);
}