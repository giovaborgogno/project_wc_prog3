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
    std::ios::sync_with_stdio(false);
    string palabra = "De, y, ave";
//    string palabra = "¡Qué dulce me parece la muerte, a pesar de todos sus terrores, ahora que se ha acabado toda esperanza engañosa de la vida! ¡Señor! ¡Tú que envías a quienes anuncian buenas eres el mar de la generosidad; tú que guías a los portadores de consuelo! ¡A ti imploro, abiertas todas las heridas de un alma atormentada! ¡Líbrame de mis sufrimientos y de los peligros! ¡Perdona mi torpeza! ¡Olvida mis errores y mis faltas! Cuando Alí-Nur terminó su lamentación, se le acercó Kutait, le explicó lo que pasaba y le ayudó a quitarse la ropa limpia que le había dado ocultamente y le vistió de harapos, llevándole en seguida a la presencia del visir, que lo aguardaba pateando de rabia. Y apenas le vió Alí-Nur, acabó de convencerse del odio que le tenía aquel enemigo de su padre. Pero le dijo: \"Heme aquí ¡oh visir! ¿Crees que te será siempre favorable el destino para fiar en él de ese modo? ¿Ignoras las palabras del poeta?: ¡Al tener que sentenciar lo aprovechan para extralimitarse";
    string ARCHIVO = "../db_texto/nuevo.txt";
    string ARCHIVO_EXCLUIR = "../db_texto/excluir.txt";
    WordCounter wce(ARCHIVO);

    unsigned t0, t1;
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);

    t0 = clock();
    cout << "Uso normal:\n";
    wce.basicas();
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    cout << "\n-palabras:\n";
    wce.palabras(wce.loadHashTree());
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    cout << "\n-palabras excluir \"abajo ababil\" 10:\n";
    wce.palabras(wce.palabrasExcluir("abajo ababil"),10);
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    cout << "\n-palabras excluir file.txt 10:\n";
    wce.palabras(wce.palabrasExcluirf(ARCHIVO_EXCLUIR),10);
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

//    t0 = clock();
//    cout << "\nOcurrencias:\n";
//    wce.ocurrencias(wce.loadInHash());
//    t1 = clock();
//    time = (double(t1 - t0) / CLOCKS_PER_SEC);
//    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    cout << "\n-mostrar \"De, y, ave\":\n";
    wce.mostrar(palabra);
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    /* agregar codigo*/
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    t0 = clock();
    /* agregar codigo*/
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << "\n";

    return 0;
}