//
// Created by giovaborgogno on 17/10/2022. mi rama
//
#include "data_structs/ArbolAlpha.h"
#include "data_structs/HashMapList.h"
#include <iostream>
#include "word_counter/WordCounter.h"
#include <ctime>
#include "sstream"
#include "fstream"

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    unsigned t0, t1;

    t0 = clock();
        // Code to execute

    string ARCHIVO = "db_texto/toseti.txt";
    WordCounter wce(ARCHIVO);
    int npalabras = 2;
    try {

        wce.ocurrencias(wce.loadInHash());
    }
    catch (int err) { cerr << "error..." << err; }
    t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    return 0;
}