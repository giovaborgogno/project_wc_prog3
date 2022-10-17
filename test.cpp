//
// Created by giovaborgogno on 17/10/2022.nn
//
#include "data_structs/ArbolAlpha.h"
#include <iostream>

using namespace std;

int main(){

    ArbolAlpha<string> a;
    a.put("borgogno");
    a.put("alvarez");
    a.put("perez");
    a.put("marcelo");
    a.put("juan");
    a.put("felipe");
    a.put("abuelo");

    a.inorder();
    return 0;
}