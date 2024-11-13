#include "iostream"
using namespace std;

struct nodo {
    int edad;
    int numero_identificacion;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz = NULL, *aux, *aux2, *padre;

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
    cout << "Digite la numero identificacion del paciente: ";
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

int pedir_aguja() {
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

int caso_uno() {
    if (aux2 != raiz) {
        if (padre->izq == aux2) padre->izq = NULL;
        else padre->der = NULL;
    } else {
        raiz = NULL;
    }
    free(aux2);
    return 0;
}

int caso_dos() {
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

nodo* encontrar_minimo(nodo* a) {
    while (a->izq != NULL) {
        a = a->izq;
    }
    return a;
}

int caso_tres() {
    nodo* sucesor = encontrar_minimo(aux2->der);
    int edad_sucesor = sucesor->edad;
    int id_sucesor = sucesor->numero_identificacion;

    nodo *padre_sucesor = aux2;
    nodo *nodo_actual = aux2->der;

    while (nodo_actual->izq != NULL) {
        padre_sucesor = nodo_actual;
        nodo_actual = nodo_actual->izq;
    }

    if (padre_sucesor->izq == nodo_actual) {
        padre_sucesor->izq = nodo_actual->der;
    } else {
        padre_sucesor->der = nodo_actual->der;
    }
    free(nodo_actual);

    aux2->edad = edad_sucesor;
    aux2->numero_identificacion = id_sucesor;
    return 0;
}

int eliminar_nodo() {
    int buscar_id;
    cout << "Numero de identificacion del paciente: ";
    cin >> buscar_id;

    if (!buscar(buscar_id)) {
        cout << "Paciente no encontrado." << endl;
        return 0;
    }

    if (aux2->izq == NULL && aux2->der == NULL) {
        caso_uno();
    } else if (aux2->izq == NULL || aux2->der == NULL) {
        caso_dos();
    } else {
        caso_tres();
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
            << "5. Salir" << endl;
        cin >> opc;
        switch (opc) {
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: pedir_aguja(); break;
            case 4: eliminar_nodo(); break;
        }
    } while (opc != 5);
    return 0;
}
