#include <iostream> 
#include <string>
#include <fstream>
#include <iomanip>
#include <assert.h> 
#include <vector>

using namespace std;

//-termino principal ordenado alfabeticamente
//  -seguido de numero indefinido de pag y subtrminos tambien org 
//   en orden alfabeticos, los subterm tienen cant indef de paginas 
//   donde aparecen
//  -las paginas del term princip no estan attachhed a los subterm
//  -los subterm se imprimen con tab

//************************************************************
//                     CLASES PARA INDICE 
//************************************************************
template <class Type>
struct nodeType
{
	Type principal;
	nodeType<Type>* next;
	nodeType<Type>* back;
    vector<int> paginas;
};

class Terminos {
public:  

	bool isEmptyList() const {
        return (first == NULL);
    }
	void destroy() {
        nodeType<string> *temp; //pointer to delete the node
        while (first != NULL)
        {
        temp = first;
        first = first->next;
        delete temp;
        }
        last = NULL;
        count = 0;
    }
	void printOne(nodeType<string>* printItem) const { 
        cout<< "     "<< printItem->principal<< " ";
        int count = 0;
        int pagMax = printItem->paginas.size();
        for (int i=0; i<pagMax; i++) {
            if (count == 10) {
                cout<<endl<< "     ";
                for (int j=0; j<=pagMax; j++) 
                    cout<< " "; //El espacio para que quede alineado
            }
            if(printItem->paginas[i] == -1) { //Dos terminos seguidos
                i++;
                cout<< printItem->paginas[i];
                i++;
                cout<< "-"<< printItem->paginas[i];
                count++;
            }
            else
                cout<< printItem->paginas[i];
            if(i<pagMax)
                cout<< ", ";
            count++;
        }
        cout<<endl;
        return;
    }
	int length() const {
        return count;
    }
	string front() const {
        assert(first != NULL);
        return first->principal;
    }
	string back() const {
        assert(last != NULL);
        return last->principal;
    }
  bool search(const string& searchItem) {
        bool found = false;
        nodeType<string> *current; //pointer to traverse the list
        current = first;
        while (current != NULL && !found)
            if (Palabra1Mayor(current->principal, searchItem))
                found = true;
            else
                current = current->next;
        if (found)
            found = (PalabrasIguales(current->principal, searchItem)); //test for equality
        return found;
    }
	void deleteNode(const string& deleteItem) {
      nodeType<string> *current; //pointer to traverse the list
      nodeType<string> *trailCurrent; //pointer just before current
      bool found;
      if (first == NULL)
      cout << "Cannot delete from an empty list." << endl;
      else if (first->principal == deleteItem) //node to be deleted is
      //the first node
      {
        current = first;
        first = first->next;
        if (first != NULL)
        first->back = NULL;
        else
        last = NULL;
        count--;
        delete current;
      }
      else
      {
          found = false;
          current = first;
          while (current != NULL && !found) //search the list
              if (current->principal >= deleteItem)
                  found = true;
              else
                  current = current->next;
          if (current == NULL)
              cout << "The item to be deleted is not in "
              << "the list." << endl;
          else if (current->principal == deleteItem) //check for equality
          {
              trailCurrent = current->back;
              trailCurrent->next = current->next;
              if (current->next != NULL)
                  current->next->back = trailCurrent;
              if (current == last)
                  last = trailCurrent;
              count--;
              delete current;
          }
          else
              cout << "The item to be deleted is not in list." <<endl;
      }//end else
  }
  bool Palabra1Mayor (string palabra1, string palabra2) {
        char letra1 = palabra1[0];
        char letra2 = palabra2[0];
        if (letra1 > letra2)
            return true;
        else if (letra1 < letra2)
            return false;

        int largoMenor = palabra1.size();
        if (palabra2.size() < largoMenor)
            largoMenor =  palabra2.size();
        int i = 1;
        while (letra1 == letra2 && i<largoMenor) {
            letra1 = palabra1[i];
            letra2 = palabra2[i];
            if (letra1 > letra2)
                return true;
            else if (letra1 < letra2)
                return false;
            i++;
        }
        cout << "\nAmbas palabras son iguales\n";
        return true;
    }
  bool PalabrasIguales (string palabra1, string palabra2) {
        int largoMenor = palabra1.size();
        if (palabra2.size() != largoMenor)
            return false;
        bool diferentes = false;
        char letra1, letra2;
        for (int i=0; i<largoMenor; i++) {
            letra1 = palabra1[i];
            letra2 = palabra2[i];
            if (letra2 != letra1) 
                diferentes = true;
        }
        return !diferentes;
    }
  vector<int> InsertPag() {
        int respuesta, cantidad;
        vector<int> lista;
        do {
            cout<< "Son varias paginas consecutivas? (si=1//no=0)\n";
            cin>> respuesta;
            if (!respuesta) {
                cout<< "Ingrese la pagina:\n";
                cin>> cantidad;
                lista.push_back(cantidad);
            }
            else {
                lista.push_back(-1); //Especifica que los terminos siguientes
                                              //son continuos
                cout<< "Ingrese la primera y ultima de las paginas continuas:\n";
                cin>> cantidad;
                lista.push_back(cantidad);
                cin>> cantidad;
                lista.push_back(cantidad);
            }
            cout<< "Faltan paginas para el termino? (si=1//no=0)\n";
            cin>> respuesta;
        } while (respuesta);
        return lista; 
    }
  void insert(const string& insertItem) {
        nodeType<string> *current; //pointer to traverse the list
        nodeType<string> *trailCurrent; //pointer just before current
        nodeType<string> *newNode; //pointer to create a node
        bool found;
        newNode = new nodeType<string>; //create the node
        newNode->principal = insertItem; //store the new item in the node
        newNode->next = NULL;
        newNode->back = NULL;
        cout<< "Para "<<insertItem<< ", ingrese las paginas.\n";
        newNode->paginas = InsertPag();
        if (first == NULL) //if list is empty, newNode is the only node
        {
            first = newNode;
            last = newNode;
            count++;
        }
        else
        {
            found = false;
            current = first;
            while (current != NULL && !found) //search the list
                if (Palabra1Mayor(current->principal, insertItem))
                    found = true;
                else
                {
                    trailCurrent = current;
                    current = current->next;
                }
            if (current == first) //insert newNode before first
            {
                first->back = newNode;
                newNode->next = first;
                first = newNode;
                count++;
            }
            else {
                //insert newNode between trailCurrent and current
                if (current != NULL)
                {
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    newNode->next = current;
                    current->back = newNode;
                }
                else
                {
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    last = newNode;
                }
                count++;
            }//end else
        }//end else
    }
    void InsertarSubTermin() {
        string palabra;
        cout<< "Inserte el subtermino:\n";
        cin>> palabra;
        insert(palabra);
        return;
    }
  Terminos() {
      first = NULL;
      last = NULL;
      count = 0;
    }
 	~Terminos() {
        nodeType<string> *temp; //pointer to delete the node
        while (first != NULL)
        {
            temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    }
  void print() {
        cout<< TerminoPrincipal<< " ";
        int count = 0;
        int pagMax = paginasTermino.size();
        for (int i=0; i<pagMax; i++) {
            if (count == 10) {
                cout<<endl;
            }
            if(paginasTermino[i] == -1) {
                i++;
                cout<< paginasTermino[i];
                i++;
                cout<< "-"<< paginasTermino[i];
                count++;
            }
            else
                cout<< paginasTermino[i];
            if(i<pagMax)
                cout<< ", ";
            count++;
        }
        cout<< endl;
        nodeType<string>* current = first;
        while (current!=NULL) {
            printOne(current);
            current = current->next;
        }
    }

    //Partes 
    int count;
    nodeType<string>* first;
    nodeType<string>* last;
    string TerminoPrincipal;
    vector<int> paginasTermino;
    // first y last son los subterminos para este termino
};

class Indice:public Terminos {
public:

    bool isEmptyList() const {
          return (first == NULL);
      }
    void destroy() {
          nodeType<Terminos> *temp; //pointer to delete the node
          while (first != NULL)
          {
          temp = first;
          first = first->next;
          delete temp;
          }
          last = NULL;
          count = 0;
      }
    void print() const { 
        nodeType<Terminos>* pointer = first;
        while(pointer != NULL) {
          pointer->principal.print();
          pointer = pointer->next;
        }
    }
	  int length() const {
        return count;
    }
	  string front() const {
        assert(first != NULL);
        return first->principal.TerminoPrincipal;
    }
	  string back() const {
        assert(last != NULL);
        return last->principal.TerminoPrincipal;
    }
    bool search(const string& searchItem) {
        bool found = false;
        nodeType<Terminos> *current; //pointer to traverse the list
        current = first;
        while (current != NULL && !found)
            if (Palabra1Mayor(current->principal.TerminoPrincipal, searchItem))
                found = true;
            else
                current = current->next;
        if (found)
            found = (PalabrasIguales(current->principal.TerminoPrincipal, searchItem)); //test for equality
        return found;
    }
    void InsertarTermino() {
      string palabra;
      cout<< "Porfavor ingrese un termino principal: \n";
      cin>> palabra;
      insert(palabra);
    }
	  void deleteNode(const string deleteItem) {
      nodeType<Terminos> *current; //pointer to traverse the list
      nodeType<Terminos> *trailCurrent; //pointer just before current
      bool found;
      if (first == NULL)
      cout << "Cannot delete from an empty list." << endl;
      else if (PalabrasIguales(first->principal.TerminoPrincipal, deleteItem)) //node to be deleted is
      //the first node
      {
          current = first;
          first = first->next;
          if (first != NULL)
          first->back = NULL;
          else
          last = NULL;
          count--;
          delete current;
      }
      else
      {
          found = false;
          current = first;
          while (current != NULL && !found) //search the list
              if (Palabra1Mayor(current->principal.TerminoPrincipal, deleteItem))
                  found = true;
              else
                  current = current->next;
          if (current == NULL)
              cout << "The item to be deleted is not in "
              << "the list." << endl;
          else if (PalabrasIguales(current->principal.TerminoPrincipal, deleteItem)) //check for equality
          {
              trailCurrent = current->back;
              trailCurrent->next = current->next;
              if (current->next != NULL)
                  current->next->back = trailCurrent;
              if (current == last)
                  last = trailCurrent;
              count--;
              delete current;
          }
          else
              cout << "The item to be deleted is not in list." <<endl;
      }//end else
    }
    bool Palabra1Mayor (string palabra1, string palabra2) {
        char letra1 = palabra1[0];
        char letra2 = palabra2[0];
        if (letra1 > letra2)
            return true;
        else if (letra1 < letra2)
            return false;

        int largoMenor = palabra1.size();
        if (palabra2.size() < largoMenor)
            largoMenor =  palabra2.size();
        int i = 1;
        while (letra1 == letra2 && i<largoMenor) {
            letra1 = palabra1[i];
            letra2 = palabra2[i];
            if (letra1 > letra2)
                return true;
            else if (letra1 < letra2)
                return false;
            i++;
        }
        cout << "\nAmbas palabras son iguales\n";
        return true;
    }
    bool PalabrasIguales (string palabra1, string palabra2) {
        int largoMenor = palabra1.size();
        if (palabra2.size() != largoMenor)
            return false;
        bool diferentes = false;
        char letra1, letra2;
        for (int i=0; i<largoMenor; i++) {
            letra1 = palabra1[i];
            letra2 = palabra2[i];
            if (letra2 != letra1) 
                diferentes = true;
        }
        return !diferentes;
    }
    Indice() {
      first = NULL;
      last = NULL;
      count = 0;
      int respuesta;
      string palabra;
      do {
        cout<< "Ingrese un termino principal: \n";
        cin>> palabra;
        insert(palabra);
        cout<< "Desea aniadir otro termino principal? (si=1//no=0)\n";
        cin>> respuesta;
      } while(respuesta);
    }
    ~Indice() {
        nodeType<Terminos> *temp; //pointer to delete the node
        while (first != NULL)
        {
            temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    }
protected:
    int count;
    nodeType<Terminos>* first; //pointer to the first node
    nodeType<Terminos>* last;
    void insert(const string& insertItem) {
        nodeType<Terminos> *current; //pointer to traverse the list
        nodeType<Terminos> *trailCurrent; //pointer just before current
        nodeType<Terminos> *newNode; //pointer to create a node
        bool found;
        int respuesta;
        newNode = new nodeType<Terminos>; //create the node
        newNode->principal.TerminoPrincipal = insertItem; //store the new item in the node
        cout<< "Para "<<insertItem<< ", ingrese las paginas.\n";
        newNode->principal.paginasTermino = newNode->principal.InsertPag();
        cout<< "Desea aniadir subterminos? (si=1//no=0)\n";
        cin>> respuesta;
        while(respuesta) {
          newNode->principal.InsertarSubTermin();
          cout<< "Desea aniadir otro subtermino? (si=1//no=0)\n";
          cin>> respuesta;
        }
        newNode->next = NULL;
        newNode->back = NULL;
        if (first == NULL) //if list is empty, newNode is the only node
        {
            first = newNode;
            last = newNode;
            count++;
        }
        else
        {
            found = false;
            current = first;
            while (current != NULL && !found) //search the list
                if (Palabra1Mayor(current->principal.TerminoPrincipal, insertItem))
                    found = true;
                else
                {
                    trailCurrent = current;
                    current = current->next;
                }
            if (current == first) //insert newNode before first
            {
                first->back = newNode;
                newNode->next = first;
                first = newNode;
                count++;
            }
            else {
                //insert newNode between trailCurrent and current
                if (current != NULL)
                {
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    newNode->next = current;
                    current->back = newNode;
                }
                else
                {
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    last = newNode;
                }
                count++;
            }//end else
        }//end else
    }
};




//************************************************************
//                           MAIN
//************************************************************

int main() {
    Indice prueba;
    prueba.InsertarTermino();
    prueba.print();
    return 0;
}