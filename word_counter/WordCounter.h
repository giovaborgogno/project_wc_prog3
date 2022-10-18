//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_WORDCOUNTER_H
#define PROJECT_WC_PROG3_WORDCOUNTER_H

#include "../data_structs/ArbolAlpha.h"
#include "../data_structs/Cola.h"
#include "../data_structs/HashMap.h"

/*
 *
 */
class WordCounter {
private:
    string ARCHIVO;
    int countPalabras, countPalabrasDif, countLineas, countLetras;
public:
    WordCounter(string ARCHIVO){
        this->ARCHIVO = ARCHIVO;
        countPalabras = 0;
        countPalabrasDif = 0;
        countLineas = 0;
        countLetras = 0;
    }

    ArbolAlpha<string> *loadDataInTree();
    void basicas();
    void palabras(ArbolAlpha<string> *arbol ,int nPalabras = 0);
    void ocurrencias(ArbolAlpha<string> *arbol, int nPalabras = 0);
    void mostrar(string palabras);
    ArbolAlpha<string> *excluir(string palabras);
    ArbolAlpha<string> *excluirf(string ARCHIVO_EXCLUIR);
};

#endif //PROJECT_WC_PROG3_WORDCOUNTER_H
