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
string WordCounter::soloPalabra(string palabra)
{
  string nuevaPalabra;
  for (int i = 0; i < palabra.length(); ++i)
  {
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
HashMapList<string> *WordCounter::load()
{
  ifstream fich(ARCHIVO);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 584999;
  //  int tamanio = 10061;
  //    int tamanio = 200003;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra, linea;

  // Recorre cada linea del archivo contando las lineas, letras, palabras,
  // palabras diferentes Carga las palabras en un HashMapList
  while (getline(fich, linea))
  {
    countLineas++;
    stringstream stream(linea);
    while (stream >> palabra)
    {
      try
      {
        palabra = soloPalabra(palabra);
        countLetras += palabra.length();
        countPalabras++;
        if (hash->put(palabra, 1))
          countPalabrasDif++;
      }
      catch (int err)
      {
      };
    }
  }

  return hash;
}

/**
 * Lee un archivo de texto y carga las palabras en un HashMapList con sus ocurrencias
 * @return HashMapList<string> *hash
 */
HashMapList<string> *WordCounter::loadHashList()
{

  ifstream fich(ARCHIVO);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 584999;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra;

  // Recorre el archivo cargando cada palabra en un HashMapList
  while (fich >> palabra)
  {
    try
    {
      hash->putOcurrence(soloPalabra(palabra), 1);
    }
    catch (int err)
    {
    };
  }

  return hash;
}

/**
 * Lee un archivo de texto y retorna un HashMapList
 * Carga las palabras en un hash contando las ocurrencias de las palabras
 * @return HashMapList<string> *hash
 */
HashMapList<string> *WordCounter::loadHashList_occurrence()
{
  ifstream fich(ARCHIVO);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio = 10061;
  // int tamanio = 584999;
  HashMapList<string> *hash = new HashMapList<string>(tamanio);
  string palabra;
  while (fich >> palabra)
  {
    try
    {
      hash->putOcurrence(soloPalabra(palabra), 1); // el metodo putOcurrence carga el hash mientras
                                                   // cuenta las ocurrencias de las palabras
    }
    catch (int err)
    {
    };
  }
  return hash;
}

/**
 * Lee un archivo de texto y retorna un HashMapTree
 * Carga el hash ordenado alfabeticamente
 * @return HashMapTree<string> *hash
 */
HashMapTree<string> *WordCounter::loadHashTree()
{
  ifstream fich(ARCHIVO);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  int tamanio =
      27; // una posicion del hash para cada letra, y una para los signos
  HashMapTree<string> *hash = new HashMapTree<string>(tamanio);
  string palabra, linea;
  while (fich >> palabra)
  {
    try
    {
      palabra = soloPalabra(palabra);
      hash->put(palabra, 1);
    }
    catch (int err)
    {
    };
  }
  return hash;
}

/**
 * Carga un hash con las palabras del archivo
 * Muestra la cantidad de letras, lineas, palabras y palabras diferentes
 */
void WordCounter::basicas()
{
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
void WordCounter::palabras(HashMapTree<string> *hash, int nPalabras)
{
  int countPalabras = 0; // cuenta las palabras que se imprimen

  // Se recorre el hash de arboles
  for (int i = 0; i < hash->size; ++i)

        hash->table[i]->inorder(nPalabras, countPalabras); // se imprime inOrder cada arbol

}

/**
 * Busca las palabras pasadas como parametro y
 * las muestra ordenadas por ocurrencias
 * @param string palabras
 */
void WordCounter::mostrar(string palabras)
{
  HashMapList<string> *hash = loadHashList(); // carga un HashMapList con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra)
  {
    try
    {
      cola.encolar(soloPalabra(palabra));
    }
    catch (int err)
    {
    }
  }

  // Busca las palabras en el hash y las almacena en una colaPrioridad, la prioridad es la ocurrencia de la palabra
  ColaPrioridad<HashEntry<string> *> colaPrioridad;
  while (!cola.esVacia())
  {
    try
    {
      palabra = cola.desencolar();
      colaPrioridad.encolarPrioridad(hash->getHashEntry(palabra), hash->getHashEntry(palabra)->getValue());
    }
    catch (int err)
    {
      cerr << "error..." << err << endl;
    }
  }

  // Imprime las palabras(key) y ocurrencias(value)
  while (!colaPrioridad.esVacia())
  {
    HashEntry<string> *auxHashEntry = colaPrioridad.desencolar();
    cout << auxHashEntry->getKey() << " " << auxHashEntry->getValue() << "\n";
  }
}

/**
 * Devuelve un *HashMapTree sin las palabras pasadas como parametros
 * @param string palabras
 * @return HashMapTree<string>*
 */
HashMapTree<string> *WordCounter::palabrasExcluir(string palabras)
{
  HashMapTree<string> *hash = loadHashTree(); // carga un HashMapTree con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra)
  {
    cola.encolar(soloPalabra(palabra));
  }

  // elimina del hash las palabras
  while (!cola.esVacia())
  {
    try
    {
      hash->remove(cola.desencolar());
    }
    catch (int err)
    {
    }
  }
  return hash;
}

/**
 * Devuelve un *HashMapTree sin las palabras pasadas en un archivo
 * @param string ARCHIVO_EXCLUIR archivo que contiene las palabras a excluir
 * @return HashMapTree<string>*
 */
HashMapTree<string> *WordCounter::palabrasExcluirf(string ARCHIVO_EXCLUIR)
{
  HashMapTree<string> *hash = loadHashTree(); // carga un HashMapTree con las palabras del archivo

  // Las palabras del archivo pasado como parametro son almacenadas en una cola
  Cola<string> cola;
  ifstream fich(ARCHIVO_EXCLUIR);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  string palabra;
  while (fich >> palabra)
  {
    try
    {
      cola.encolar(palabra);
    }
    catch (int err)
    {
    };
  }

  // elimina del hash las palabras
  while (!cola.esVacia())
  {
    try
    {
      hash->remove(cola.desencolar());
    }
    catch (int err)
    {
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
void WordCounter::ocurrencias(HashMapList<string> *hash, int nPalabras) {
// Se cargan las palabras en un array, en la posicion que le corresponde segun su ocurrencia
  // Ej: todas las palabras con 8 ocurrencias se cargan en arrayPilas[7]
  int tamanioArray = hash->maxocurrencia; // El tamanio del array es la maxima ocurrencia de las palabras cargadas
  Pila<HashEntry<string> *> arrayPilas[tamanioArray];
  for (int i = 0; i < hash->size; i++) {
    try {
      if (hash->table[i] != NULL) {
        Nodo<HashEntry<string> *> *HashEntryaux =
            hash->table[i]->getinicio();
        while (HashEntryaux != nullptr) {
          arrayPilas[HashEntryaux->getDato()->getValue()-1].push(
              HashEntryaux->getDato());
          HashEntryaux = HashEntryaux->getSiguiente();
        }
      } else
        throw 409;
    } catch (int err) {
    }
  }
    // Para imprimir todas las palabras se recorre todo el array desde la ultima posicion hasta la primera
    if (nPalabras == 0) {
      while (tamanioArray-1 >= 0) {
        try {
          // en cada posicion del array si la pila no es vacia se hace pop hasta vaciar la pila
          while (!arrayPilas[tamanioArray-1].esVacia()) {
            HashEntry<string> *HashEntryaux = arrayPilas[tamanioArray-1].pop();
            cout << HashEntryaux->getKey() << ' ' << HashEntryaux->getValue()
                 << '\n';
          }
        } catch (int err) {
          cout << "Error" << endl;
        }
        tamanioArray--;
      }
    }

    // Para imprimir nPalabras tambien se recorre el array desde la ultima posicion hasta la primera haciendo pop para vaciar cada pila, pero si llega a nPalabras finaliza el recorrido 
    else {
      for (int i = 0; i < nPalabras; i) {
        try {
          while (!arrayPilas[tamanioArray-1].esVacia() && i < nPalabras) {
            HashEntry<string> *HashEntryaux = arrayPilas[tamanioArray-1].pop();
            cout << HashEntryaux->getKey() << ' ' << HashEntryaux->getValue()
                 << '\n';
            i++;
          }
        } catch (int err) {
          cout << "Error" << endl;
        }
        tamanioArray--;
      }
    }

}

/**
 * Devuelve un *HashMapList sin las palabras pasadas como parametros
 * @param string palabras
 * @return HashMapList<string>*
 */
HashMapList<string> *WordCounter::ocurrenciasExcluir(string palabras)
{
  HashMapList<string> *hash = loadHashList_occurrence(); // carga un HashMapList con las palabras del archivo

  // Las palabras pasadas como parametros son almacenadas en una cola
  stringstream stream(palabras);
  Cola<string> cola;
  string palabra;
  while (stream >> palabra)
  {
    cola.encolar(soloPalabra(palabra));
  }
  // elimina del hash las palabras
  while (!cola.esVacia())
  {
    try
    {
      hash->remove(cola.desencolar());
    }
    catch (int err)
    {
    }
  }
  return hash;
}

/**
 * Devuelve un *HashMapList sin las palabras pasadas en un archivo
 * @param string ARCHIVO_EXCLUIR archivo que contiene las palabras a excluir
 * @return HashMapList<string>*
 */
HashMapList<string> *WordCounter::ocurrenciasExcluirf(string ARCHIVO_EXCLUIR)
{
  HashMapList<string> *hash = loadHashList_occurrence(); // carga un HashMapList con las palabras del archivo

  // Las palabras del archivo pasado como parametro son almacenadas en una cola
  Cola<string> cola;
  ifstream fich(ARCHIVO_EXCLUIR);
  if (!fich.is_open())
  {
    cout << "Error al abrir el archivo";
    exit(EXIT_FAILURE);
  }
  string palabra;
  while (fich >> palabra)
  {
    try
    {
      cola.encolar(palabra);
    }
    catch (int err)
    {
    };
  }

  // elimina del hash las palabras
  while (!cola.esVacia())
  {
    try
    {
      hash->remove(cola.desencolar());
    }
    catch (int err)
    {
    }
  }
  return hash;
}
