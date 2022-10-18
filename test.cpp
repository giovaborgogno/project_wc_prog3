//
// Created by giovaborgogno on 17/10/2022. mi rama
//
#include "data_structs/ArbolAlpha.h"
#include <iostream>
#include "word_counter/WordCounter.h"
#include <ctime>

using namespace std;

int main() {

    unsigned t0, t1;

    t0 = clock();

    string ARCHIVO = "../db_texto/textoprueba.txt";
    string ARCHIVO_EXCLUIR = "../db_texto/excluir.txt";
    WordCounter wce(ARCHIVO);
    wce.basicas();
    cout << "\n";
    wce.palabras(wce.loadDataInTree(), 5);
    cout << "\n";
    wce.ocurrencias(wce.loadDataInTree(), 5);
    cout << "\n";
    ArbolAlpha<string> *excluidos = wce.excluirf(ARCHIVO_EXCLUIR);
    wce.palabras(excluidos, 5);
    cout << "\n";
    wce.ocurrencias(excluidos, 5);
    cout << "\n";
    excluidos = wce.excluir("Las de");
    wce.palabras(excluidos, 5);
    cout << "\n";
    wce.ocurrencias(excluidos, 5);
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;


    return 0;
}