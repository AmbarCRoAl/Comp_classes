/* 
  This code create a list of characters, integers or float numbers
  and allows you to interact with that list.
  It goes with conjunto.cpp and conjunto.h
*/

#include <iostream>
#include "conjunto.cpp"
#include "conjunto.h"
#include<string>
#include<sstream>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
template <class TipoNumerico>
TipoNumerico SoloNumero(string mensaje, string mensajeError, TipoNumerico maximo, TipoNumerico minimo)
{
    string s;
    TipoNumerico numero;
    do
    {
        cout << mensaje;
        getline(cin, s, '\n');

        istringstream convierte(s);

        bool FalloConversion = !(convierte >> numero);
        if ((FalloConversion && s != "0") || numero > maximo || numero < minimo)
        {
            cout << mensajeError << endl;
            numero = maximo + 1;
        }
    } while (numero > maximo);
    return numero;
}

template <class T>
T PedirValor() {
	T elemento;
	cout<< "Favor de ingresar un valor: ";
	cin>> elemento;
	return elemento;
}

template <class T>
void Menu2(T valor, int& respuesta)
{
	Conjuntos<T> conjunto;
	string menu = "Seleccione una opcion para el menu:\n";
	menu.append("\t1. Agregar un nuevo elemento al conjunto\n");
	menu.append("\t2. Eliminar un elemento del conjunto\n");
	menu.append("\t3. Mostrar la cantidad de elementos existentes\n");
	menu.append("\t4. Coroborar la existencia de un elemento\n");
	menu.append("\t5. Escribir todos los elementos\n");
	menu.append("\t6. Volver al menu de seleccion de tipo\n");
	menu.append("\t0. Salir\n");
	int respuesta2;
	do{
	  respuesta2 = SoloNumero<int>(menu,"invalida",0,6);
		switch(respuesta2)
    	{
			case 1:
			{
				T valor = PedirValor<T>();
				conjunto.Agregar(valor);
				break;
			}
		
			case 2:
			{
				T valor = PedirValor<T>();
				conjunto.Eliminar(valor); 
				break;
			}
		
			case 3:
			{
				if (!conjunto.EstaVacia()) {
					PantArchivo<string>("La cantidad de elementos en la lista: ");
					PantArchivo<int>(conjunto.Cardinal());
					PantArchivo<string>("\n");
				}
				break;
		    }
		
		    case 4:
			{
				T valor = PedirValor<T>();
				conjunto.Pertenece(valor);
				break;
			}
		
			case 5:
			{
				conjunto.Escribir();
				break;
			}
		
			case 0:
			{
				cout<< "Gracias por utilizar el programa!\n";
				respuesta = 0;
				break;
			}
	}
  
  }while(respuesta2!=0);
}

void Ejecucion(int& respuesta)
{
	switch(respuesta){
	
	case 1:
	{
		Menu2<int>(1, respuesta);
		break;
	}
	case 2:
	{
		Menu2<char>('a', respuesta);
		break;
	}
	case 3:
	{
		Menu2<float>(1.0, respuesta);
		break;
	}
	case 0:
	{
		cout<< "Gracias por utilizar el programa!\n";
		break;
	}
  }
	return;
}

void Menu1(int& respuesta) {
	string menu = "Seleccione el tipo de elemento a trabajar:\n";
	menu.append("\t1. Entero\n\t2. Caracter\n\t3. Real\n\t0. Salir\n");
  respuesta = SoloNumero<int>(menu,"invalida",0,3);
	Ejecucion(respuesta);
	return;
}

int main() {
	int respuesta;
	do
	{
		Menu1(respuesta);
	} while(respuesta != 0);	
	return 0;
}

