//
// Created by giovaborgogno on 17/10/2022. mi rama
//
#include "data_structs/ArbolAlpha.h"
#include "data_structs/HashMapList.h"
#include <iostream>
#include "word_counter/WordCounter.h"
#include <ctime>
#include "sstream"

using namespace std;

int main() {

//    Lista<HashEntry<string>*> lista;
//    lista.insertarUltimo(new HashEntry<string>("juan", 1));
//    lista.getDato(0)->incrementValue();
//    cout << lista.getDato(0)->getValue();
/*
    HashMapList<string> hash(10);
    try{ hash.putOcurrence("juan", 1); }
    catch (int cerr) {}
    try{ hash.putOcurrence("juan", 1); }
    catch (int cerr) {}
    try{ hash.putOcurrence("juan", 1); }
    catch (int cerr) {}

    try {
        hash.print();
    }
    catch (int err) {
        
    }*/



    unsigned t0, t1;

    t0 = clock();
    string ARCHIVO = "../db_texto/mucho_texto.txt";
    //string ARCHIVO_EXCLUIR = "../db_texto/excluir.txt";
    WordCounter wce(ARCHIVO);
    wce.basicas();
//    cout << "\n";
//    wce.palabras(wce.excluirf(ARCHIVO_EXCLUIR), 3);
//    cout << "\n";
//    wce.palabras(wce.excluir("que de"), 3);
//    cout << "\n";
//    wce.ocurrencias(wce.loadInHash(),3);
//    cout << "\n";
//    wce.mostrar("que de");
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;


    return 0;
}