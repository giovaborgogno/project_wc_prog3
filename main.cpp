//
// Created by giovaborgogno on 17/10/2022.
//

#include <iostream>
#include <ctime>
#include "sstream"
#include <stdio.h>
#include <string.h>
#include "data_structs/ArbolAlpha.h"
#include "data_structs/HashMapList.h"
#include "word_counter/WordCounter.h"

using namespace std;

int main(int argc, char *argv[]) {
    unsigned t0, t1;
    t0 = clock();

   cout.sync_with_stdio(false);


     /*
      * Uso Normal
      * */
    if (argc == 2) {
        cout << "uso normal\n\n";
        string ARCHIVO = argv[1];
        WordCounter wce(ARCHIVO);
        wce.basicas();
    }
    /*fin uso normal*/

    /*
     * -palabras, -palabras [n],
     * -palabras -excluir "palabras a excluir", -palabras -excluir "a excluir" [n],
     * -palabras -excluirf ignorar.txt, -palabras -excluirf ignorar.txt [n]
     * */
    if (argc == 3 && strcmp(argv[1], "-palabras") == 0 && !argv[3]) {
        cout << "-palabras\n\n";
        string ARCHIVO = argv[2];
        WordCounter wce(ARCHIVO);
        wce.palabras(wce.loadHashTree());
    }
    else if (argc == 4 && strcmp(argv[1], "-palabras") == 0 && !argv[4]) {
        cout << "-palabras [n]\n\n";
        string ARCHIVO = argv[3];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[2]);
        wce.palabras(wce.loadHashTree(), npalabras);
    }
    else if (argc == 5 && strcmp(argv[1], "-palabras") == 0 && strcmp(argv[2], "-excluir") == 0) {
        cout << "-palabras -excluir\n\n";
        string ARCHIVO = argv[4];
        WordCounter wce(ARCHIVO);
        wce.palabras(wce.palabrasExcluir(argv[3]));
    }
    else if (argc == 6 && strcmp(argv[1], "-palabras") == 0 && strcmp(argv[2], "-excluir") == 0) {
        cout << "-palabras -excluir\n\n";
        string ARCHIVO = argv[5];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[4]);
        wce.palabras(wce.palabrasExcluir(argv[3]), npalabras);
    }
    else if (argc == 5 && strcmp(argv[1], "-palabras") == 0 && strcmp(argv[2], "-excluirf") == 0) {
        cout << "-palabras -excluirf\n\n";
        string ARCHIVO = argv[4];
        string ARCHIVO_EXCLUIR = argv[3];
        WordCounter wce(ARCHIVO);
        wce.palabras(wce.palabrasExcluirf(ARCHIVO_EXCLUIR));
    }
    else if (argc == 6 && strcmp(argv[1], "-palabras") == 0 && strcmp(argv[2], "-excluirf") == 0) {
        cout << "-palabras -excluirf [n]\n\n";
        string ARCHIVO = argv[5];
        string ARCHIVO_EXCLUIR = argv[3];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[4]);
        wce.palabras(wce.palabrasExcluirf(ARCHIVO_EXCLUIR), npalabras);
    }
    /* fin -palabras */

    /*
     * -ocurrencias, -ocurrencias [n],
     * -ocurrencias -excluir "ocurrencias a excluir", -ocurrencias -excluir "a excluir" [n],
     * -ocurrencias -excluirf ignorar.txt, -ocurrencias -excluirf ignorar.txt [n]
     * */
    if (argc == 3 && strcmp(argv[1], "-ocurrencias") == 0 && !argv[3]) {
        cout << "-ocurrencias\n\n";
        string ARCHIVO = argv[2];
        WordCounter wce(ARCHIVO);
        wce.ocurrencias(wce.loadInHash());
    }
    else if (argc == 4 && strcmp(argv[1], "-ocurrencias") == 0 && !argv[4]) {
        cout << "-ocurrencias [n]\n\n";
        string ARCHIVO = argv[3];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[2]);
        try{
        wce.ocurrencias(wce.loadInHash(), npalabras);
        }
        catch(int err){cerr << "error..." << err;}
    }
    else if (argc == 5 && strcmp(argv[1], "-ocurrencias") == 0 && strcmp(argv[2], "-excluir") == 0) {
        cout << "-ocurrencias -excluir\n\n";
        string ARCHIVO = argv[4];
        WordCounter wce(ARCHIVO);
        wce.ocurrencias(wce.ocurrenciasExcluir(argv[3]));
    }
    else if (argc == 6 && strcmp(argv[1], "-ocurrencias") == 0 && strcmp(argv[2], "-excluir") == 0) {
        cout << "-ocurrencias -excluir\n\n";
        string ARCHIVO = argv[5];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[4]);
        wce.ocurrencias(wce.ocurrenciasExcluir(argv[3]), npalabras);
    }
    else if (argc == 5 && strcmp(argv[1], "-ocurrencias") == 0 && strcmp(argv[2], "-excluirf") == 0) {
        cout << "-ocurrencias -excluirf\n\n";
        string ARCHIVO = argv[4];
        string ARCHIVO_EXCLUIR = argv[3];
        WordCounter wce(ARCHIVO);
        wce.ocurrencias(wce.ocurrenciasExcluirf(ARCHIVO_EXCLUIR));
    }
    else if (argc == 6 && strcmp(argv[1], "-ocurrencias") == 0 && strcmp(argv[2], "-excluirf") == 0) {
        cout << "-ocurrencias -excluirf\n\n";
        string ARCHIVO = argv[5];
        string ARCHIVO_EXCLUIR = argv[3];
        WordCounter wce(ARCHIVO);
        int npalabras = stoi(argv[4]);
        wce.ocurrencias(wce.ocurrenciasExcluirf(ARCHIVO_EXCLUIR), npalabras);
    }
    /* fin ocurrencias */

    /*
     * -mostrar "palabras a mostrar"
     * */
    else if (argc == 4 && strcmp(argv[1], "-mostrar") == 0 && argv[2]) {
        cout << "-mostrar [palabras]\n\n";
        string ARCHIVO = argv[3];
        WordCounter wce(ARCHIVO);
        wce.mostrar(argv[2]);
    }
    /* fin -mostrar */

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";
    return 0;


}