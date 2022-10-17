//
// Created by giovaborgogno on 17/10/2022. mi rama
//
#include "data_structs/ArbolAlpha.h"
#include <iostream>
#include "word_counter/WordCounter.h"

using namespace std;

int main() {
    string ARCHIVO = "../db_texto/textoprueba.txt";
    WordCounter wce(ARCHIVO);
    wce.basicas();
    cout << "\n";
    wce.palabras(3);
    cout << "\n";
    wce.ocurrencias(3);


    return 0;
}