//
// Created by giovaborgogno on 17/10/2022.
//

#ifndef PROJECT_WC_PROG3_WORDCOUNTER_H
#define PROJECT_WC_PROG3_WORDCOUNTER_H

#include "../data_structs/ArbolAlpha.h"
#include "../data_structs/Cola.h"
#include "../data_structs/ColaPrioridad.h"
#include "../data_structs/HashMapList.h"
#include "../data_structs/HashMapTree.h"
#include "../data_structs/Pila.h"

/*
 *
 */
class WordCounter {
private:
  string ARCHIVO;
  string soloPalabra(string palabra);
  int countPalabras, countPalabrasDif, countLineas, countLetras;

public:
  WordCounter(string ARCHIVO) {
    this->ARCHIVO = ARCHIVO;
    countPalabras = 0;
    countPalabrasDif = 0;
    countLineas = 0;
    countLetras = 0;
  }

  HashMapList<string> *load();
  HashMapList<string> *loadHashList();
  HashMapTree<string> *loadHashTree();
  HashMapList<string> *loadHashList_occurrence();

  void basicas();
  void palabras(HashMapTree<string> *hash, int nPalabras = 0);
  void ocurrencias(HashMapList<string> *hash, int nPalabras=0);
  void mostrar(string palabras);

  HashMapTree<string> *palabrasExcluir(string palabras);
  HashMapTree<string> *palabrasExcluirf(string ARCHIVO_EXCLUIR);
  HashMapList<string> *ocurrenciasExcluir(string palabras);
  HashMapList<string> *ocurrenciasExcluirf(string ARCHIVO_EXCLUIR);
};

#endif // PROJECT_WC_PROG3_WORDCOUNTER_H
