//
// Created by giovaborgogno on 08/09/2022.
//

#ifndef INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODOPRIORIDAD_H
#define INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODOPRIORIDAD_H
template <class T>
class NodoPrioridad
{
private:
    T dato;
    NodoPrioridad<T> *siguiente;
    int prioridad;
    string prioridadString;

public:

    NodoPrioridad(){};

    NodoPrioridad(T dato, int prioridad) {
        this->dato=dato;
        this->prioridad=prioridad;
        setSiguiente(nullptr);
    }

    NodoPrioridad(T dato, string prioridad) {
        this->dato=dato;
        this->prioridadString=prioridad;
        setSiguiente(nullptr);
    }

    T getDato()
    {
        return dato;
    }

    void setDato(T d)
    {
        dato = d;
    }

    NodoPrioridad<T> *getSiguiente()
    {
        return siguiente;
    }

    void setSiguiente(NodoPrioridad<T> *s)
    {
        this->siguiente = s;
    }

    int getPrioridad()
    {
        return prioridad;
    }
    string getPrioridadString()
    {
        return prioridadString;
    }

    void setPrioridad(int p)
    {
        prioridad = p;
    }
};
#endif //INC_2021A2_U04_COLAS_GIOVABORGOGNO_NODOPRIORIDAD_H
