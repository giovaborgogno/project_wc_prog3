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

    string ARCHIVO = "../db_texto/toseti.txt";
    WordCounter wce(ARCHIVO);
    int npalabras = 2;
    try {

        wce.ocurrencias(wce.loadInHash());
    }
    catch (int err) { cerr << "error..." << err; }

    return 0;
}