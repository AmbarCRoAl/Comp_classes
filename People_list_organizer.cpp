/* This code takes a txt document with names and last names,
   organize them in alphabetical order, and allows you to edit 
   that list (add new names, change the current data).

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstddef>
#include <vector>
#include <cctype>
#include <fstream>
//#include <boost/algorithm/string.hpp> //for trimming
using namespace std;

namespace pointers
{
using std::string;
typedef int *intPtr;
typedef double *doubleptr;
typedef char *charptr;
typedef string *stringptr;
} // namespace pointers

using namespace pointers;

const string archivoSalida = "salida.txt";
const string archivoIn = "entrada.txt";

struct Datos
{
	int cantNombres;
	stringptr nombres;
	string apellidos;
	Datos *enlace;
};
typedef Datos* DatosPtr;

class NombrePersona
{
public:
	NombrePersona();
	~NombrePersona();
	bool ListaVacia();
	void EntradaArchivo();
	void InsertarCabeza(istream &in);
	void AnadirTeclado();
	void InsertarPosicion(DatosPtr persona, int pos); //Asume que persona ya tiene los datos, no puede ser pos 1
	bool NombreExistente (DatosPtr deseado);
	void Eliminacion();// Antes de buscar para eliminar deberias verificar que esta en la lista
	DatosPtr PosicionEnLista(int pos); // Devuelve una posicion arriba d la deseada

	friend istream& operator >>(istream& in, DatosPtr& persona); //Se puede usar AdquirirNombres
	friend ostream& operator <<(ostream& out, DatosPtr persona); 

	DatosPtr cabeza;
	int cantPersonas;
};

int LineCount(ifstream &file);
string FormaEstandar(NombrePersona lista); 
string FormaRegular(NombrePersona lista); 
void CleanString(string& dirty);

//******************************************************************

bool BusquedaNombre(NombrePersona lista, string nombreBuscado);
bool BusquedaApellidos(NombrePersona lista, string letra);
void Cumple(NombrePersona listas, string nombreBuscado, string letra);
void Menu(int &respuesta);
void Ejecucion(int respuesta, NombrePersona& lista);

//*****************************************************************
template <class T>
void PantArchivo(T mensaje)
{
    cout << mensaje; //In case of custom Data Type overload >> //
    ofstream salida;
    salida.open(archivoSalida.c_str(), ios_base::app);
    salida << mensaje;
}
template <class TipoNumerico>
TipoNumerico SoloNumero(string mensaje, string mensajeError, TipoNumerico maximo, TipoNumerico minimo)
{
    string respuesta;
    TipoNumerico numero;
    do
    {
        cout << mensaje;
        getline(cin, respuesta, '\n');

        istringstream convierte(respuesta);

        bool FalloConversion = !(convierte >> numero);
        if ((FalloConversion && respuesta != "0") || numero > maximo || numero < minimo)
        {
            cout << mensajeError << endl;
            numero = maximo + 1;
        }
    } while (numero > maximo);
    return numero;
}


int LineCount(ifstream &file)
{
	int counter = 0;
	string temp;
	while (file.good())
	{
		getline(file, temp, '\n');
		counter++;
	}
	return counter;
}
string FormaEstandar(DatosPtr nodo)
{

	string temp = nodo->apellidos, inicial;
    temp.append(",");
    temp.append(" ");
    temp.append(nodo->nombres[0]);
	for (int i = 1; i < nodo->cantNombres; i++)
	{
        inicial.assign(nodo->nombres[i], 0, 1);
		temp.append(" ");
		temp.append(inicial);
		temp.append(".");
	}
	return temp;
}
string FormaRegular(DatosPtr nodo)
{
    string temp =  nodo->nombres[0];
	for (int i = 1; i < nodo->cantNombres; i++)
	{
		temp.append(" ");
		temp.append(nodo->nombres[i]);
	}    
    temp.append(",");
    temp.append(" ");	
    temp.append(nodo->apellidos);
	return temp;
}
void CleanString(string& dirty)
{

	if(dirty.size()<=0)
		return;
		
	int spaceQty = 0;
	unsigned int i=0;
	while(isspace(dirty[i]) && i<dirty.size())
	{	
		spaceQty++;
		 i++;
	}
	
	if(spaceQty == (int)dirty.size())
	{
		dirty.clear();
		return;
	}
	
	string clean = dirty.substr(spaceQty, dirty.size());
	
	spaceQty = 0;
	i = clean.size()-1;

	while(isspace(clean[i]) && i>0)
	{
		spaceQty++;
		cout<<clean[i];
		i--;
	}
     
	 dirty = clean.substr(0, clean.size()-spaceQty);
}

istream& operator >>(istream& in, DatosPtr& persona) {
    string temporal, apellido, nombre;
    int cantidad = 1;
    getline(in, temporal, '\n');
    CleanString(temporal);
    int coma = temporal.find(",");
    int largo = temporal.size();
    apellido.assign(temporal, coma+1, largo-coma);
    CleanString(apellido);
    persona->apellidos = apellido;
    nombre.assign(temporal, 0, coma);
  	CleanString(nombre);
    size_t found1 = nombre.find_first_of(" ");
    size_t found2 = nombre.find_first_of(" ", found1+1);
    while (found1 != string::npos) {
        if (found2 != found1+1)
            cantidad++;
        found1 = found2;
        found2 = nombre.find_first_of(" ", found1+1);
    }
    persona->nombres = new string[cantidad];
    persona->cantNombres = cantidad;
    for(int i=0; i<cantidad; i++){
        persona->nombres[i].assign(nombre, 0, nombre.find(" "));
        nombre.erase(0, nombre.find(" "));
        	CleanString(nombre);
    }
	return in;
}
ostream& operator <<(ostream& out, DatosPtr persona) {
		out << "\n\nEntrada: ";
		out<< FormaRegular(persona);
		out<< "\nSalida: ";
		out<< FormaEstandar(persona);
	return out;
}


NombrePersona::NombrePersona()
{
	cabeza = NULL;
	cantPersonas = 0;
}
NombrePersona::~NombrePersona()
{
	DatosPtr nodo = cabeza, next;
	while (nodo != NULL) {
		next = nodo->enlace;
		delete nodo;
		nodo = next;
	}
}
bool NombrePersona::ListaVacia()
{
	if (cabeza == NULL)
	{
		cout << "Lista vacia.\n";
		return true;
	}
	else
		return false;
}
void NombrePersona::InsertarCabeza(istream&in)
{
	DatosPtr temporal;
	temporal = new Datos;
    in >> temporal;
    if (NombreExistente(temporal)) {
		cout<< "Este nombre ya pertenece a la lista.";
		return;
	}
	else {
		temporal->enlace = cabeza;
		cabeza = temporal;
    	cantPersonas++;
		return;
	}
}
void NombrePersona::EntradaArchivo()
{
	ifstream in;
	in.open(archivoIn.c_str());
	int indice = LineCount(in);
	in.close();

	in.open(archivoIn.c_str());
	for (int i = 0; i < indice-1; i++)
	{
		InsertarCabeza(in);
	}
	in.close();
}
void NombrePersona::InsertarPosicion(DatosPtr persona, int pos) {
	persona = new Datos;
    cin >> persona;
    if (NombreExistente(persona)) {
		cout<< "Este nombre ya pertenece a la lista.";
		return;
	}
	else {
		DatosPtr posicion = PosicionEnLista(pos);
		persona->enlace = posicion->enlace;
		posicion->enlace = persona;
		cantPersonas++;
	}
}
bool NombrePersona::NombreExistente (DatosPtr deseado) {
	DatosPtr nodo = cabeza;
	bool name;
	for (int i=0; i<cantPersonas; i++)
	{
        name = true;	

        if (nodo->cantNombres != deseado->cantNombres)	
            name = false;
        else {
            for (int j=0; j < nodo->cantNombres; j++) {
			    if (nodo->nombres[j] != deseado->nombres[j])
				    name = false;
        }
        
		if (nodo->apellidos != deseado->apellidos)
			name = false;
		}

		if (name)
			return true;
		else 
			nodo = nodo->enlace;
	}
	return false;
}
DatosPtr NombrePersona::PosicionEnLista(int pos) {//devuelve anterior
	pos--;
	DatosPtr nodo = cabeza;
	int i = 1;
	if (ListaVacia())
	{
		cout<< "No hay posiciones disponibles para busqueda.\n";
		return NULL;
	}
	else {
		if (pos <= cantPersonas) {
			while (i < pos) {
				nodo = nodo-> enlace;
				i++;
			}
			return nodo;
		}
		else {
			cout<< "Posicion fuera de rango.\n";
			return NULL;
		}
	}
}
void NombrePersona::AnadirTeclado() {
	int pos;
	cout<< "Actualmente hay "<<cantPersonas<< " personas almacenadas en la lisa.\n";
	cout<< "Favor introducir la posicion en la que desea aniadir el nombre: ";
	cin>> pos;
	DatosPtr persona;
	persona = new Datos;
	cout<< "Introduzca los nombres separados con espacios, luego\n";
	cout<< "una coma y los apellidos tambien separados con espacios.\n";
	cout<< "Presione enter al terminar de entrar los datos\n"; 
    cin >> persona;
		if (pos == 1)
			InsertarCabeza(cin);
		else
			InsertarPosicion(persona, pos);
	return;
}
void NombrePersona::Eliminacion(){
    if (ListaVacia()) {
        cout<< "No se puede eliminar nombres.\n";
        return;
    }
    else {
        string deseado;
        cout<< "Introduzca el nombre para eliminar de la lista: ";
        cin>> deseado;
        DatosPtr nodo, anterior = cabeza;
        while (anterior->nombres[0] == deseado) {
            nodo = anterior->enlace;
            delete anterior;
            cabeza = nodo;
            anterior = cabeza;
        }
        while (anterior != NULL) {
            nodo = anterior->enlace;
            if (nodo->nombres[0] == deseado){
                anterior->enlace = nodo->enlace;
                delete nodo;
            }
            anterior = anterior->enlace;
    }
    }
}

//*********************************************************************

bool BusquedaNombre(DatosPtr item, string nombreBuscado)
{
	return item->nombres[0] == nombreBuscado ? true : false;
}
bool BusquedaApellidos(DatosPtr item, string letra)
{
    string inicial;
    inicial.assign(item->apellidos, 0, 1);
	return inicial == letra ? true : false;
}
/*void Cumple(NombrePersona listas, string nombreBuscado, string letra)
{ 
	int j = 0;
	for (DatosPtr lista = listas.cabeza; lista != NULL; lista = lista->enlace)
	{
		if (BusquedaNombre(lista, nombreBuscado) && BusquedaApellidos(lista, letra))
		{
			PantArchivo("\n\nEntrada:");
			PantArchivo(FormaRegular(lista));
			PantArchivo("\nSalida:");
			PantArchivo(FormaEstandar(lista));
			j++;
		}
	}
	if (j == 0)
		PantArchivo("No hay nombre que Cumpla Con Ambas Condiciones.\n");
}*/
void Menu(int &respuesta)
{
	string menu = "Favor de escoger una de las siguientes opciones:\n";
	menu.append("\t1 = Escribir todos los nombres en forma estandar\n");
	menu.append("\t2 = Escribir las personas con apellido que inicia en S y cuyo primer nombre sea Arturo\n");
	menu.append("\t3 = Introducir nuevo nombre por teclado\n");
	menu.append("\t4 = Eliminacion de personas con nombre especifico\n");
	menu.append("\t5 = Salir\n");
	menu.append("Respuesta: ");
	respuesta = SoloNumero(menu, "Respuesta Invalida Trate De Nuevo\n",5,1);
	return;
}
/*void Ejecucion(int respuesta, NombrePersona& lista)
{
	switch (respuesta)
	{
	case 1:
	{
	    DatosPtr nodo;
	    nodo = new Datos;
	    nodo = persona.cabeza;
        for (int i=0; i < persona.cantPersonas; i++) {
	    PantArchivo(lista);
	    lista = lista->enlace
        }
		break;
	}

	case 2:
	{
		Cumple(lista, "Arturo", "S");
		break;
	}

	case 3:
	{
		lista.AnadirTeclado();
		break;
	}

	case 4:
	{
        lista.Eliminacion();
		break;
	}

	case 5:
	{
		cout << "Gracias por utilizar el programa, hasta pronto!\n";
		break;
	}
	}
	return;
}*/

//*******************************************************************

int main()
{
	int respuesta;
	ofstream(archivoSalida.c_str());
	NombrePersona lista;
	lista.EntradaArchivo();
	lista.ListaVacia();

	do
	{
		cout << "\n==========================================================================\n";
		Menu(respuesta);
		cout << "\n\t\t========================================\n";
	    switch (respuesta) {
	    case 1:
	    {
	        DatosPtr nodo;
	        nodo = lista.cabeza;
            for (int i=0; i < lista.cantPersonas; i++) {
	            PantArchivo(nodo);
	            nodo = nodo->enlace;
            }
		break;
	    }
	    case 2:
	    {
		    //Cumple(lista, "Arturo", "S");
		    int j = 0;
	        for (DatosPtr nodo = lista.cabeza; nodo != NULL; nodo = nodo->enlace)
        	{
	        	if (BusquedaNombre(nodo, "Arturo") && BusquedaApellidos(nodo, "S"))
	           	{
	        		PantArchivo("\n\nEntrada:");
	        		PantArchivo(FormaRegular(nodo));
		        	PantArchivo("\nSalida:");
			        PantArchivo(FormaEstandar(nodo));
			        j++;
	        	}
        	}
	        if (j == 0)
	        	PantArchivo("No hay nombre que Cumpla Con Ambas Condiciones.\n");
		    break;
	    }
	    case 3:
	    {
    		lista.AnadirTeclado();
		    break;
	    }
	    case 4:
        {
            lista.Eliminacion();
		    break;
	    }
	    case 5: 
	    {
    		cout << "Gracias por utilizar el programa, hasta pronto!\n";
	    	break;
	    }
	    }
	} while (respuesta != 5);
	return 0;
}