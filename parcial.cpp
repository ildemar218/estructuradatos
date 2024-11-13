#include "iostream"

using namespace std;

struct nodo {
    int edad;
    int numero_identificacion;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL, *aux, *aux2 , *padre;

int posicionar() {
    if (aux->edad < aux2->edad) {
        if (aux2->izq == NULL) {
            aux2->izq = aux;
            return 0;
        } else {
            aux2 = aux2->izq;
            posicionar();
        }
    } else {
        if (aux2->der == NULL) {
            aux2->der = aux;
            return 0;
        } else {
            aux2 = aux2->der;
            posicionar();
        }
    }
    return 0;
}

int registrar() {
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    cout << "Digite la edad del paciente: ";
    cin >> aux->edad;
    cout << "Digite la numero_identificacion del paciente: ";
    cin >> aux->numero_identificacion;
    aux->izq = aux->der = NULL;

    if (raiz == NULL) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
    return 0;
}

int recorrer(nodo *a) {  
    if(a->der!=NULL){
        recorrer(a->der);
    }
    cout << "-------paciente--------" << endl;
    cout << "numero identificacion: " << a->numero_identificacion << endl;
    cout << "edad: " << a->edad << endl;

    if(a->izq!=NULL){
        recorrer(a->izq);
    }

    return 0;
}


int mostrar() {
    if (raiz != NULL) {
        recorrer(raiz); 
    } else {
        cout << "No hay pacientes registrados." << endl;
    }
    return 0;
}

int ubicar(nodo *a, int aguja){
    if(a->numero_identificacion==aguja){
        aux2 = a;
        return 0;
    } else {
        if(a->izq!=NULL){
            ubicar(a->izq, aguja);
        } 
        
        if(a->der!=NULL){
            ubicar(a->der, aguja);
        }         
    }
    return 0;
}

int buscar(int aguja){
    aux = NULL;
    if(raiz!=NULL){
        aux = raiz;
        ubicar(aux, aguja);
    }
}

int pedirAguja(){
    aux2 = NULL;
    int dato;
    cout<<"numero de identificacion del paciente"<<endl;
    cin>>dato;
    buscar(dato);
    if(aux2){
        cout<<"paciente encontrado"<<endl;
        cout << "Numero de identificacion: " << aux2->numero_identificacion << endl;
        cout << "Edad: " << aux2->edad << endl;
    } else {
        cout<<"El paciente no se encontro"<<endl;
    }
}

int ubicarPadre(nodo *a){
    if((a->izq==aux2)||(a->der==aux2)){
        padre = a;
    }
    else {
        if(a->izq!=NULL){
            ubicarPadre(a->izq);
        } 
        
        if(a->der!=NULL){
            ubicarPadre(a->der);
        }         
    }
}

int caso_Uno(){
    if(aux != raiz){
        ubicarPadre(raiz);
    }
    if(padre != NULL) {
        if(padre->izq == aux) {
            padre->izq = NULL;
        } else if(padre->der == aux) {
            padre->der = NULL;
        }
    } else {
        raiz = NULL;
    }
    free(aux);
    return 0;
}

int caso_Dos() {
    nodo* hijo;
    if(aux->izq != NULL) {
        hijo = aux->izq;
    } else {
        hijo = aux->der;
    }

    if(aux == raiz) {
        raiz = hijo;
    } else {
        ubicarPadre(raiz);
        if(padre->izq == aux) {
            padre->izq = hijo;
        } else {
            padre->der = hijo;
        }
    }
    free(aux);
    return 0;
}

nodo* encontrarMinimo(nodo* a) {
    while(a->izq != NULL) {
        a = a->izq;
    }
    return a;
}

int eliminar_sucesor(int id_sucesor) {
    ubicar(raiz, id_sucesor);
    if(aux2 != NULL) {
        aux = aux2;
        if(aux->izq == NULL && aux->der == NULL) {
            caso_Uno();
        } else if(aux->izq == NULL || aux->der == NULL) {
            caso_Dos();
        }
    }
    return 0;
}

int caso_Tres() {
    nodo* sucesor = encontrarMinimo(aux->der);
    int edadSucesor = sucesor->edad;
    int idSucesor = sucesor->numero_identificacion;
    eliminar_sucesor(idSucesor); 
    aux->edad = edadSucesor; 
    aux->numero_identificacion = idSucesor;
    return 0;
}

int eliminar_nodo() {
    int buscarId;
    cout<<"numero de identificacion del paciente"<<endl;
    cin>>buscarId;    
    ubicar(raiz, buscarId);

    if(aux2 == NULL) {
        cout << "Paciente no encontrado." << endl;
        return 0;
    }

    aux = aux2;

    if(aux->izq == NULL && aux->der == NULL) {
        caso_Uno();
    } else if(aux->izq == NULL || aux->der == NULL) {
        caso_Dos();
    } else {
        caso_Tres();
    }
    return 0;
}

int main() {
    int opc;
    do {
        cout << "1. Registrar" << endl
            << "2. Mostrar" << endl
            << "3. buscar paciente" << endl
            << "4. eliminar paciente" << endl
            << "6. salir" << endl;
        cin >> opc;
        switch (opc) {
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: pedirAguja(); break;
            case 4: eliminar_nodo(); break;
        }
    } while (opc != 6);
    return 0;
}
