#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <iostream>
using namespace std;

template <class T>
struct elemento {
    T numero;
    elemento<T> *enlace;
};

template <class T>
class Conjuntos {
    public:
    	Conjuntos();
    	~Conjuntos();

        elemento<T> *cabeza;
        int cantElementos;

        void Agregar(T valor);
        void Eliminar(T valor);
        bool Pertenece(T valor);
        bool EstaVacia();
        int Cardinal();
        void Escribir();
};
#endif



