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

int mostrar() {
    if (raiz != NULL) {
        recorrer(raiz); 
    } else {
        cout << "No hay pacientes registrados." << endl;
    }
    return 0;
}

int ubicar(nodo *a, int aguja, nodo* &padre) {
    if (a == NULL) return 0;

    if (a->numero_identificacion == aguja) {
        aux2 = a; 
        return 1;
    } 
    padre = a;
    if (aguja < a->numero_identificacion) {
        return ubicar(a->izq, aguja, padre);
    } else {
        return ubicar(a->der, aguja, padre);
    }
}

int buscar(int aguja) {
    aux2 = NULL;
    padre = NULL;
    if (raiz != NULL) {
        ubicar(raiz, aguja, padre);
    }
    return aux2 != NULL;
}

int pedirAguja() {
    int dato;
    cout << "Numero de identificacion del paciente: ";
    cin >> dato;
    if (buscar(dato)) {
        cout << "Paciente encontrado" << endl;
        cout << "Numero de identificacion: " << aux2->numero_identificacion << endl;
        cout << "Edad: " << aux2->edad << endl;
    } else {
        cout << "El paciente no se encontro" << endl;
    }
    return 0;
}

int caso_Uno() {
    if (aux2 != raiz) {
        if (padre->izq == aux2) padre->izq = NULL;
        else padre->der = NULL;
    } else {
        raiz = NULL;
    }
    free(aux2);
    return 0;
}

int caso_Dos() {
    nodo* hijo = (aux2->izq != NULL) ? aux2->izq : aux2->der;

    if (aux2 == raiz) {
        raiz = hijo;
    } else {
        if (padre->izq == aux2) padre->izq = hijo;
        else padre->der = hijo;
    }
    free(aux2);
    return 0;
}

nodo* encontrarMinimo(nodo* a) {
    while (a->izq != NULL) {
        a = a->izq;
    }
    return a;
}

int caso_Tres() {
    nodo* sucesor = encontrarMinimo(aux2->der);  // Encuentra el sucesor inorden
    int edadSucesor = sucesor->edad;
    int idSucesor = sucesor->numero_identificacion;

    nodo *padreSucesor = aux2;
    nodo *nodoActual = aux2->der;

    while (nodoActual->izq != NULL) {
        padreSucesor = nodoActual;
        nodoActual = nodoActual->izq;
    }

    if (padreSucesor->izq == nodoActual) {
        padreSucesor->izq = nodoActual->der;
    } else {
        padreSucesor->der = nodoActual->der;
    }
    free(nodoActual);

    aux2->edad = edadSucesor;
    aux2->numero_identificacion = idSucesor;
    return 0;
}

int eliminar_nodo() {
    int buscarId;
    cout << "Numero de identificacion del paciente: ";
    cin >> buscarId;

    if (!buscar(buscarId)) {
        cout << "Paciente no encontrado." << endl;
        return 0;
    }

    if (aux2->izq == NULL && aux2->der == NULL) {
        caso_Uno();
    } else if (aux2->izq == NULL || aux2->der == NULL) {
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
             << "3. Buscar paciente" << endl
             << "4. Eliminar paciente" << endl
             << "6. Salir" << endl;
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