//
// Created by giovaborgogno on 17/10/2022.
//

#include "WordCounter.h"
#include <fstream>
#include <sstream>

/**
 * Retorna un string sin signos de puntuacion y numeros,
 *  convierte el string a minuscula
 * @param string
 * @return string nuevaPalabra
 */
string WordCounter::soloPalabra(string palabra) {
  string nuevaPalabra;
  for (int i = 0; i < palabra.length(); ++i) {
    // if (!ispunct(palabra[i]))
    if (!ispunct(palabra[i]) && !isdigit(palabra[i]))
      nuevaPalabra += tolower(palabra[i]);
  }
  if (nuevaPalabra.length() == 0)
    throw 11;
  return nuevaPalabra;
}

/**
 * Lee un archivo de texto y carga las palabras en un HashMapList
 * Cuenta palabras, palabras diferentes, lineas y letras
 * @return HashMapList<string> *hash
 */
HashMapList<string> *WordCounter::load() {
  ifstream fich(ARCHIVO);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 584999;
  //    int tamanio = 200003;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra, linea;

  // Recorre cada linea del archivo contando las lineas, letras, palabras,
  // palabras diferentes Carga las palabras en un HashMapList
  while (getline(fich, linea)) {
    countLineas++;
    stringstream stream(linea);
    while (stream >> palabra) {
      try {
        palabra = soloPalabra(palabra);
        countLetras += palabra.length();
        countPalabras++;
        hash->put(palabra, 1);
        countPalabrasDif++;
      } catch (int err) {
      };
    }
  }
  cout << "Hubo " << countPalabrasDif - hash->posiciones << " colisiones\n";

  return hash;
}

/**
 * Lee un archivo de texto y carga las palabras en un HashMapList
 * @return HashMapList<string> *hash
 */
HashMapList<string> *WordCounter::loadHashList() {

  ifstream fich(ARCHIVO);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 584999;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra;

  // Recorre el archivo cargando cada palabra en un HashMapList
  while (fich >> palabra) {
    try {
      hash->put(soloPalabra(palabra), 1);
    } catch (int err) {
    };
  }

  return hash;
}

/**
 * Lee un archivo de texto y retorna un HashMapList
 * Carga las palabras en un hash contando las ocurrencias de las palabras
 * @return HashMapList<string> *hash
 */
HashMapList<string> *WordCounter::loadHashList_occurrence() {
  //   unsigned t3, t4;
  ifstream fich(ARCHIVO);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 10061;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra;
  //   t3 = clock();
  while (fich >> palabra) {
    try {
      hash->putOcurrence(soloPalabra(palabra),
                         1); // el metodo putOcurrence carga el hash mientras
                             // cuenta las ocurrencias de las palabras
    } catch (int err) {
    };
  }
  //   t4 = clock();
  //   double time = (double(t4 - t3) / CLOCKS_PER_SEC);
  //   cout << "Load in hash: " << time << "\n";
  return hash;
}

/**
 * Lee un archivo de texto y retorna un HashMapTree
 * Carga el hash ordenado alfabeticamente
 * @return HashMapTree<string> *hash
 */
HashMapTree<string> *WordCounter::loadHashTree() {
  ifstream fich(ARCHIVO);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio =
      27; // una posicion del hash para cada letra, y una para los signos
  HashMapTree<string> *hash = new HashMapTree<string>(tamanio);
  string palabra, linea;
  while (fich >> palabra) {
    try {
      palabra = soloPalabra(palabra);
      hash->put(palabra, 1);
    } catch (int err) {
    };
  }
  return hash;
}

/**
 * Carga un hash con las palabras del archivo
 * Muestra la cantidad de letras, lineas, palabras y palabras diferentes
 */
void WordCounter::basicas() {
  load();
  cout << countLineas << " lineas\n";
  cout << countLetras << " letras\n";
  cout << countPalabras << " palabras\n";
  cout << countPalabrasDif << " palabras diferentes\n";
}

/**
 * Muestra las palabras en orden alfabetico
 * @param HashMapTree<string> *hash
 * @param int nPalabras :cantidad de palabras que desea mostrar (por defecto
 * nPalabras = 0)
 */
void WordCounter::palabras(HashMapTree<string> *hash, int nPalabras) {
  int countPalabras = 0; // cuenta las palabras que se imprimen
                         // Se recorre el hash de arboles
  for (int i = 0; i < hash->size; ++i) {
    if (hash->table[i] != NULL) {
      try {
        hash->table[i]->inorder(nPalabras,
                                countPalabras); // se imprime inOrder cada arbol
      } catch (int err) {
      }
    }
  }
}

/**
 * Busca las palabras pasadas como parametro y
 * las muestra ordenadas por ocurrencias
 * @param string palabras
 */
void WordCounter::mostrar(string palabras) {
  HashMapList<string> *hash = loadHashList(); // carga un HashMapList con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra) {
    try {
      cola.encolar(soloPalabra(palabra));
    } catch (int err) {
    }
  }

  // Busca las palabras en el hash y las almacena en una colaPrioridad, la prioridad es la ocurrencia de la palabra
  ColaPrioridad<HashEntry<string> *> colaPrioridad;
  while (!cola.esVacia()) {
    try {
      palabra = cola.desencolar();
      colaPrioridad.encolarPrioridad(hash->getHashEntry(palabra),
                                     hash->getHashEntry(palabra)->getValue());

    } catch (int err) {
      cerr << "error..." << err << endl;
    }
  }

  // Imprime las palabras(key) y ocurrencias(value)
  while (!colaPrioridad.esVacia()) {
    HashEntry<string> *auxHashEntry = colaPrioridad.desencolar();
    cout << auxHashEntry->getKey() << " " << auxHashEntry->getValue() << "\n";
  }
}

/**
 * Devuelve un *HashMapTree sin las palabras pasadas como parametros
 * @param string palabras
 * @return HashMapTree<string>* 
 */
HashMapTree<string> *WordCounter::palabrasExcluir(string palabras) {
  HashMapTree<string> *hash = loadHashTree(); // carga un HashMapTree con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra) {
    cola.encolar(soloPalabra(palabra));
  }

  // elimina del hash las palabras
  while (!cola.esVacia()) {
    try {
      hash->remove(cola.desencolar());
    } catch (int err) {
    }
  }
  return hash;
}

/**
 * Devuelve un *HashMapTree sin las palabras pasadas en un archivo
 * @param string ARCHIVO_EXCLUIR archivo que contiene las palabras a excluir
 * @return HashMapTree<string>*
 */
HashMapTree<string> *WordCounter::palabrasExcluirf(string ARCHIVO_EXCLUIR) {
  HashMapTree<string> *hash = loadHashTree(); // carga un HashMapTree con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  Cola<string> cola;
  ifstream fich(ARCHIVO_EXCLUIR);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  string palabra;
  while (fich >> palabra) {
    try {
      cola.encolar(palabra);
    } catch (int err) {
    };
  }

  // elimina del hash las palabras
  while (!cola.esVacia()) {
    try {
      hash->remove(cola.desencolar());
    } catch (int err) {
    }
  }
  return hash;
}

/**
 * Muestra las palabras por orden de ocurrencias
 * @param HashMapList<string> *hash
 * @param int nPalabras :cantidad de palabras que desea mostrar (por defecto
 * nPalabras = 0)
 */
void WordCounter::ocurrencias(HashMapList<string> *hashocurrencia, int nPalabras) {
  //   unsigned t5, t6;
  //   t5 = clock();
  int count = hashocurrencia->maxocurrencia;
  Pila<HashEntry<string> *> arrayordenado[count];
  for (int i = 0; i < hashocurrencia->size; i++) {
    try {
      if (hashocurrencia->table[i] != NULL) {
        Nodo<HashEntry<string> *> *HashEntryaux =
            hashocurrencia->table[i]->getinicio();
        while (HashEntryaux != nullptr) {
          arrayordenado[HashEntryaux->getDato()->getValue()].push(
              HashEntryaux->getDato());
          HashEntryaux = HashEntryaux->getSiguiente();
        }
      } else
        throw 409;
    } catch (int err) {
    }
  }
  //   t6 = clock();

  if (nPalabras == 0) {
    while (count >= 0) {
      try {
        while (!arrayordenado[count].esVacia()) {
          HashEntry<string> *HashEntryaux = arrayordenado[count].pop();
          cout << HashEntryaux->getKey() << ' ' << HashEntryaux->getValue()
               << '\n';
        }
      } catch (int err) {
        cout << "Error" << endl;
      }
      count--;
    }
  } else {
    for (int i = 0; i < nPalabras; i) {
      try {
        while (!arrayordenado[count].esVacia() && i < nPalabras) {
          HashEntry<string> *HashEntryaux = arrayordenado[count].pop();
          cout << HashEntryaux->getKey() << ' ' << HashEntryaux->getValue()
               << '\n';
          i++;
        }
      } catch (int err) {
        cout << "Error" << endl;
      }
      count--;
    }
  }
  //   double time = (double(t6 - t5) / CLOCKS_PER_SEC);
  //   cout << "OCURRENCIAAAAA: " << time << "\n";
}

HashMapList<string> *WordCounter::ocurrenciasExcluir(string palabras) {
  HashMapList<string> *hash = loadHashList_occurrence();
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra) {
    cola.encolar(soloPalabra(palabra));
  }
  while (!cola.esVacia()) {
    try {
      hash->remove(cola.desencolar());
    } catch (int err) {
    }
  }
  return hash;
}

HashMapList<string> *WordCounter::ocurrenciasExcluirf(string ARCHIVO_EXCLUIR) {
  HashMapList<string> *hash = loadHashList_occurrence();
  Cola<string> cola;
  ifstream fich(ARCHIVO_EXCLUIR);
  if (!fich.is_open()) {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  string palabra;
  while (fich >> palabra) {
    try {
      cola.encolar(palabra);
    } catch (int err) {
    };
  }
  while (!cola.esVacia()) {
    try {
      hash->remove(cola.desencolar());
    } catch (int err) {
    }
  }
  return hash;
}

//   void WordCounter::ocurrencias(HashMapList<string> *hashocurrencia,int
//   nPalabras) {
//     int count = hashocurrencia->maxocurrencia;
//     Pila<HashEntry<string> *> arrayordenado[count];
//     for (int i = 0; i < hashocurrencia->size; i++) {
//       try {
//         if (hashocurrencia->table[i] != NULL) {
//           for (int j = 0; j < hashocurrencia->table[i]->getTamanio(); j++)
//           {
//             arrayordenado[hashocurrencia->table[i]->getDato(j)->getValue()].push(
//                 hashocurrencia->table[i]->getDato(j));
//           }
//         } else
//           throw 409;
//       } catch (int err) {
//       }
//     }

//     if (nPalabras == 0) {
//       while (count >= 0) {
//         try {
//           while (!arrayordenado[count].esVacia()) {
//             HashEntry<string> *aux = arrayordenado[count].pop();
//             cout << aux->getKey() << ' ' << aux->getValue() << '\n';
//           }
//         } catch (int err) {
//           cout << "Error" << endl;
//         }
//         count--;
//       }
//       return;
//     }

//     for (int i = 0; i < nPalabras; i) {
//       try {
//         while (!arrayordenado[count].esVacia() && i < nPalabras) {
//           HashEntry<string> *aux = arrayordenado[count].pop();
//           cout << aux->getKey() << ' ' << aux->getValue() << '\n';
//           i++;
//         }
//       } catch (int err) {
//         cout << "Error" << endl;
//       }
//       count--;
//     }
//   AAAA
//       if(nPalabras == 0){
//         while(count>=0){
//           try {
//             for (int j = 0; j < hashordenado[count].getTamanio(); j++) {
//               cout << hashordenado[count].getDato(j)->getKey() << ' '
//                    << hashordenado[count].getDato(j)->getValue() << endl;
//             }
//           } catch (int err) {
//             cout << "Error" << endl;
//           }
//           count--;
//         }
//         return;
//       }
//     for (int i = 0; i < nPalabras; i) {
//         try {
//             for (int j = 0; j < hashordenado[count].getTamanio(); j++) {
//                 if (i < nPalabras) {
//                     cout << hashordenado[count].getDato(j)->getKey() << ' '
//                          << hashordenado[count].getDato(j)->getValue() <<
//                          endl;
//                     i++;
//                 }
//             }
//         } catch (int err) {
//             cout << "Error" << endl;
//         }
//         count--;
//     }

/*ArbolAlpha<string> *WordCounter::loadDataInTree() {
    ifstream fich(ARCHIVO);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    ArbolAlpha<string> *arbol = new ArbolAlpha<string>();

    while (fich >> palabra) {
        try {
            arbol->put(soloPalabra(palabra));
        }
        catch (int err) {
        }
    }
    return arbol;
}*/
/*ArbolAlpha<string> *WordCounter::excluir(string palabras) {
    ArbolAlpha<string> *arbol = loadDataInTree();
    stringstream stream(palabras);
    Cola<string> cola;
    string palabra;
    while (stream >> palabra) {
        cola.encolar(palabra);
    }
    while (!cola.esVacia()) {
        try {
            arbol->remove(cola.desencolar());

        } catch (int err) {

        }
    }
    return arbol;
}*/
/*

ArbolAlpha<string> *WordCounter::excluirf(std::string ARCHIVO_EXCLUIR) {
    ArbolAlpha<string> *arbol = loadDataInTree();
    Cola<string> cola;
    ifstream fich(ARCHIVO_EXCLUIR);
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo";
        exit(EXIT_FAILURE);
    }
    string palabra;
    while (fich >> palabra) {
        try {
            cola.encolar(palabra);
        }
        catch (int err) {
        };
    }

    while (!cola.esVacia()) {
        try {
            arbol->remove(cola.desencolar());

        } catch (int err) {

        }
    }
    return arbol;
}
*/
/*
 * void WordCounter::palabras(ArbolAlpha<string> *arbol, int nPalabras) {
    //ArbolAlpha<string> *arbol = loadDataInTree();
    arbol->inorder(nPalabras);
}
*/
/*
void WordCounter::palabrasNuevo(int nPalabras) {
    HashMapList<string> *hash = loadInHash();
    ColaPrioridad<HashEntry<string> *> colaPrioridad;
    int count = 0;
    for (int i = 0; i < hash->size; ++i) {
        try {
            if (!hash->table[i])throw 404;
            Nodo<HashEntry<string> *> *temp = hash->table[i]->getinicio();
            if (hash->table[i]->esVacia())throw 404;
            else {
                while (temp != nullptr) {
                    {
                        colaPrioridad.encolarPrioridadString(temp->getDato(),
temp->getDato()->getKey()); count++;
//
colaPrioridad.encolarPrioridadString(temp->getDato(),temp->getDato()->getKey());
                        if (temp->getSiguiente() == nullptr) break;
                        temp = temp->getSiguiente();

                    }
                }
            }
        }
        catch (int err) {
        }
    }
    if (nPalabras == 0) {
        for (int i = 0; i < count; ++i) {
            HashEntry<string> *hashEntry = colaPrioridad.desencolar();
            cout << hashEntry->getKey() << " " << hashEntry->getValue() << "\n";
        }
        return;
    }

    for (int i = 0; i < nPalabras; ++i) {
        HashEntry<string> *hashEntry = colaPrioridad.desencolar();
        cout << hashEntry->getKey() << " " << hashEntry->getValue() << "\n";
    }

}
*/
/*
void WordCounter::ocurrencias(HashMapList<string> *hash, int nPalabras) {
    ArbolOccurrence-viejo<string> *arbol = new ArbolOccurrence-viejo<string>();
    for (int i = 0; i < hash->size; ++i) {
        try {

            if (!hash->table[i])throw 404;
            Nodo<HashEntry<string> *> *temp = hash->table[i]->getinicio();
            if (hash->table[i]->esVacia())throw 404;
            else {
                while (temp != nullptr) {
                    {
                        arbol->put(temp->getDato()->getKey(),
temp->getDato()->getValue()); if (temp->getSiguiente() == nullptr) break; temp =
temp->getSiguiente();

                    }
                }
            }
        }
        catch (int err) {
        }
    }

    arbol->inorder(nPalabras);
}
*/
