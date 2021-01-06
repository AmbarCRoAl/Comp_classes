#include<fstream>
#include<iostream>
#include "conjunto.h"
using namespace std;


#ifndef PANTARCHIVO
#define PANTARCHIO
const std::string archivoIn = "entrada.txt";
const std::string archivoOut = "salida.txt";
template <class T>
void PantArchivo(T mensaje)
{
	cout<<mensaje;
	ostream salida(archivoOut.c_str());
	salida<<mensaje;
    return;
}
#endif//PANTARCHIVO

template <class T>
Conjuntos<T>::Conjuntos() {
    cabeza = NULL;
}
template <class T>
Conjuntos<T>::~Conjuntos() {
    elemento<T> *nodo = cabeza, *siguiente;
    while (nodo != NULL) {
        siguiente = nodo->enlace;
        delete nodo;
        nodo = siguiente;
    }

}
template <class T>
void Conjuntos<T>::Agregar(T valor) {
    if (cabeza == NULL) {
        cabeza = new elemento<T>;
        cabeza->numero = valor;
        cabeza->enlace = NULL;
    }
    else {
        if (Pertenece(valor)){
            cout<< "Este elemento ya existe en el conjunto.\n";
            return;
        }
        else {
            elemento<T>* temp;
            temp = new elemento<T>;
            temp->numero = valor;
            temp->enlace = cabeza;
            cabeza = temp;
        }
    }
    return;
}
template <class T>
void Conjuntos<T>::Eliminar(T valor) {
    if (EstaVacia()) {
        cout<< "No se pueden eliminar elementos.\n";
        return;
    }
    else
    {
        if(Pertenece(valor)) {
            elemento<T> *nodo, *anterior = cabeza;
            if (anterior->numero == valor) {
                cabeza = cabeza->enlace;
                delete anterior;
                return;
            }
            else {
                nodo = anterior->enlace;
                while (nodo != NULL) {
                    if (nodo->numero == valor) {
                        anterior->enlace = nodo->enlace;
                        delete nodo;
                    }
                }
            }
        }
        else 
            cout<< "El elemento no existe en la lista.\n";
    }
    return;
}
template <class T>
bool Conjuntos<T>::Pertenece(T valor) {
    elemento<T> *nodo = cabeza;
    while(nodo != NULL){
        if (nodo->numero == valor)
            return true;
        else
            nodo = nodo->enlace;
    }
    return false;
    
}
template <class T>
bool Conjuntos<T>::EstaVacia() {
            if (cantElementos == 0){
                PantArchivo<string>("La lista esta vacia.\n");
                return true;
            }
            else
                return false;   
}
template <class T>
int Conjuntos<T>::Cardinal() {
            return cantElementos;
}
template <class T>
void Conjuntos<T>::Escribir() {
    if (cabeza != NULL) {
		elemento<T> *temporal = cabeza;    
   	    for (int i=0; i<cantElementos; i++) {
        	PantArchivo<int>(temporal->numero);
            PantArchivo<string>(" ");
        	temporal = temporal->enlace;
    	}
        PantArchivo<string>("\n");
	}
}
