//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_WORDCOUNTER_H
#define PROJECT_WC_PROG3_WORDCOUNTER_H

#include "../data_structs/ArbolAlpha.h"
#include "../data_structs/ArbolOccurrence.h"
#include "../data_structs/HashMap.h"

/*
 *
 */
class WordCounter {
private:
    string ARCHIVO;
    int countPalabras, countPalabrasDif, countLineas, countLetras;

    ArbolAlpha<string> llenarArbol();

public:
    WordCounter(string ARCHIVO){
        this->ARCHIVO = ARCHIVO;
        countPalabras = 0;
        countPalabrasDif = 0;
        countLineas = 0;
        countLetras = 0;

    }
    WordCounter() {};

    void basicas();

    void palabras(int nPalabras = 0);

    void ocurrencias(int nPalabras = 0);

    void mostrar(string palabras);

    void excluir(string palabras);

    void excluirf(string ARCHIVO);

};

#endif //PROJECT_WC_PROG3_WORDCOUNTER_H
