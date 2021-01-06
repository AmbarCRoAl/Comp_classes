#include <iostream> 
#include <string>
#include <fstream>
#include <iomanip>
#include <assert.h> 

//rlink= derecha= SI & llink= izquierda= NO
//info del tree es el key de las listas
//tree para guardar el orden de las respuestas
//dos doublinklist para guardar palabras y preguntas
using namespace std;


//************************************************************
//                    TEMPLATE PARA LISTA DOBLE  
//************************************************************

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* next;
	nodeType<Type>* back;
    int key;
};
template <class Type>
class doublyLinkedList
{
public:
	bool isEmptyList() const {
        return (first == NULL);
    }
	void destroy() {
        nodeType<Type> *temp; //pointer to delete the node
        while (first != NULL)
        {
        temp = first;
        first = first->next;
        delete temp;
        }
        last = NULL;
        count = 0;
    }
	void printOne(int printItem) const { 
        nodeType<Type> *current; 
        current = search(printItem); 
        cout<< current->info;
        return;
    }
	int length() const {
        return count;
    }
	Type front() const {
        assert(first != NULL);
        return first->info;
    }
	Type back() const {
        assert(last != NULL);
        return last->info;
    }
  void saveTo_File() {
        ofstream Out_file;
        Out_file.open("Data.txt",std::ios_base::app);
        nodeType<Type> *temp = first; 
        while (temp != NULL)
        {
            Out_file << temp->info<< endl;
            temp = temp->next;
        }
        Out_file<< "*****"<<endl;
        Out_file.close();
    }
	nodeType<Type>* search(const int searchItem) const {
        bool found = false;
        nodeType<Type> *current; //pointer to traverse the list
        current = first;
        while (current != NULL && !found)
            if (current->key == searchItem)
                found = true;
            else
                current = current->next;
        return current;
    }
	void insert(const Type& insertItem) {
        nodeType<Type> *newNode; //pointer to create a node
        newNode = new nodeType<Type>; //create the node
        newNode->info = insertItem; //store the new item in the node
        newNode->next = NULL;
        newNode->back = NULL;
        newNode->key = count; //Empieza en 0
        if (first == NULL) //if list is empty, newNode is the only node
        {
            first = newNode;
            last = newNode;
            count++;
        }
        else //insert at the end
        {
            last->next = newNode;
            newNode->back = last;
            last = newNode;
            count++;
        }
    }
	void deleteNode(const int deleteItem) {
        nodeType<Type> *current; //pointer to traverse the list
        nodeType<Type> *trailCurrent; //pointer just before current
        bool found;
        if (first == NULL)
            cout << "Cannot delete from an empty list." << endl;
        else if (first->key == deleteItem) 
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
            while (current != NULL && !found) 
                if (current->key == deleteItem)
                    found = true;
                else
                    current = current->next;
            if (found) 
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
                cout << "The item to be deleted is not in list."<< endl;
        }
    }
	doublyLinkedList() {
		first = NULL;
		last = NULL;
		count = 0;
	}
	~doublyLinkedList() {
        nodeType<Type> *temp; //pointer to delete the node
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
	nodeType<Type>* first; //pointer to the first node
	nodeType<Type>* last; //pointer to the last node
};


//************************************************************
//                    TEMPLATE PARA TREE
//************************************************************

template <class elemType>
struct binaryTreeNode
{
    elemType info;
    binaryTreeNode<elemType> *llink;
    binaryTreeNode<elemType> *rlink;
};

template <class elemType>
class binaryTreeType {
public:
    bool isEmpty() const {
        return (root == NULL);
    }
    int treeHeight() const {
        binaryTreeNode<elemType> *p = root; 
        if (p == NULL)
            return 0;
        else
            return 1 + max(height(p->llink), height(p->rlink));
    }
    int max(int x, int y) const {
        if (x >= y)
            return x;
        else
            return y;
    }
    void destroyTree() {
        destroy(root);
    }  
    void destroy(binaryTreeNode<elemType>* &p) {
        if (p != NULL)
        {
            destroy(p->llink);
            destroy(p->rlink);
            delete p;
            p = NULL;
        }
    }
    void insert(const elemType& insertItem, binaryTreeNode<elemType>* &p, int lORr) {
        binaryTreeNode<elemType> *newNode; //pointer to create the node
        newNode = new binaryTreeNode<elemType>;
        assert(newNode != NULL);
        newNode->info = insertItem;
        newNode->llink = NULL;
        newNode->rlink = NULL;
        if (p == NULL) { //si esta vacio
            root = newNode;
            nodeAmount++;
            p = newNode;
            return;
        }
        else if (lORr == 0) {
            p->llink = newNode;
            nodeAmount++;
            return;
        }
        else if (lORr == 1){
            //Esta pregunta tiene dos respuestas
            binaryTreeNode<elemType> *OldNode; //pointer to create the node
            OldNode = new binaryTreeNode<elemType>;
            assert(OldNode != NULL);
            OldNode->info = p->info;
            OldNode->llink = p->llink;
            OldNode->rlink = p->rlink;
            p->rlink = newNode; //Como tiene rlink, solo pregunta
            newNode->llink = OldNode;
            nodeAmount++;
            return;
        }
    }
    binaryTreeType() {
        root = NULL;
        nodeAmount = 0;
    }
    ~binaryTreeType(){
        destroyTree();
    }
    
    binaryTreeNode<elemType> *root;
    int nodeAmount;
};

//************************************************************
//                     FUNCIONES ADICIONALES
//************************************************************

int convertirRespuesta(string entrada) {
    int respuestaNum;
    if (entrada == "si"||entrada == "Si")
        respuestaNum = 1;
    else if (entrada == "SI"||entrada == "S")
        respuestaNum = 1;
    else if (entrada =="s"||entrada =="1")
        respuestaNum = 1;
    else 
        respuestaNum = 0;
    return respuestaNum;
}

string Instrucciones() {
    string mensaje = "\tINSTRUCCIONES: Usted debera pensar en un pais y responder a las \n\t"
    "preguntas con si(1) o no(0) para asi yo tratar de adivinar en que\n\t"
    "pais esta pensando. \n\t"
    "En caso de que no lo conozca, me lo aprendo para usarlo en una \n\t"
    "proxima ocasion!\n";
    return mensaje;
}

string TextoAniadir () {
    string texto = "Ups! Parece que no conozco ese pais!\n"
                    "Pofavor, introduzca el nombre del pais (Recuerda la mayuscula!),\n"
                    "y luego una pregunta que lo distinga (Recuerda el simbol *?*)\n";
    return texto;
}


//************************************************************
//                          MAIN
//************************************************************


int main() {

binaryTreeType<int> arbolDe_Paises;
binaryTreeNode<int>* current = arbolDe_Paises.root;
doublyLinkedList<string> listaDe_Palabras;
doublyLinkedList<string> listaDe_Preguntas;
int rORl = 0;

int elementKey = listaDe_Palabras.length();
listaDe_Palabras.insert("Puerto Rico");
listaDe_Preguntas.insert("Vivimos en ese pais?");
arbolDe_Paises.insert(elementKey, current, rORl);

elementKey = listaDe_Palabras.length();
listaDe_Palabras.insert("Estados Unidos");
listaDe_Preguntas.insert("Somos territorio de esa nacion?");
arbolDe_Paises.insert(elementKey, current, rORl);


string entrada;
cout<< "Hola! Binvenido al juego de adivinanzas!\n"
        "Deseas ver las instrucciones? Si(1)||No(0)\n";
cin>> entrada;
int respuesta = convertirRespuesta(entrada);
if (respuesta) {
    cout<< Instrucciones();
}
cout<< "\tComencemos!\n\n";

int continuar;
int repetir;
binaryTreeNode<int>* previous;
do {
    current = arbolDe_Paises.root;
    continuar = 1;
    do {
        rORl = 0;
        listaDe_Preguntas.printOne(current->info);
        cout<< "\nSi(1)||No(0)\n";
        cin>> entrada;
        respuesta = convertirRespuesta(entrada);
        if (!respuesta) {
            previous = current;
            current = current->llink;
        }
        else if (respuesta && current->rlink == NULL) {
            cout<< "Es el pais: ";
            listaDe_Palabras.printOne(current->info);
            cout<< "\nSi(1)||No(0)\n";
            cin>> entrada;
            respuesta = convertirRespuesta(entrada);
            if (respuesta) {
                cout<< "Que divertido!\nQuieres jugar de nuevo? Si(1)||No(0)\n";
                cin>> entrada;
                repetir = convertirRespuesta(entrada);
                continuar = 0;
                
            }
            else {
                previous = current;
                current = NULL;
                rORl = 1;
            }
        }
        else if (respuesta && current->rlink != NULL){
            previous = current;
            current = current->rlink;
        }
        if (current == NULL) {
            cout<< TextoAniadir();
            elementKey = listaDe_Palabras.length();
            cin.get();
	    	    getline(cin, entrada, '\n');
            listaDe_Palabras.insert(entrada);
	    	    getline(cin, entrada, '\n');
            listaDe_Preguntas.insert(entrada);
            arbolDe_Paises.insert(elementKey,previous,rORl);
            cout<< "\nQue divertido!\nQuieres jugar de nuevo? Si(1)||No(0)\n";
            cin>> entrada;
            repetir = convertirRespuesta(entrada);
            continuar = 0;
            
        }
    }while (continuar);
    cout<< "\n*******************************************************\n"
            "*******************************************************\n\n";
} while (repetir);
ofstream Out_file;
Out_file.open("Data.txt");
Out_file.close();
listaDe_Palabras.saveTo_File();
listaDe_Preguntas.saveTo_File();
cout<< "\nAdios!\n";
return 0;
}

