#include <iostream>
#include <cstdlib>
using namespace std;

struct nodo {
    int valor;
    int altura;
    int peso;
    int equilibrio;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *raiz = NULL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(struct nodo *n) {
    return (n == NULL) ? 0 : n->altura;
}

int calcular_peso(struct nodo *n) {
    if (n == NULL) return 0;
    return 1 + calcular_peso(n->izq) + calcular_peso(n->der);
}

int factor_equilibrio(struct nodo *n) {
    return (n == NULL) ? 0 : altura(n->izq) - altura(n->der);
}

struct nodo *rotacion_derecha(struct nodo *y) {
    struct nodo *x = y->izq;
    struct nodo *T = x->der;

    // Rotacion
    x->der = y;
    y->izq = T;

    // Actualizar alturas y peso
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    y->peso = calcular_peso(y);
    x->peso = calcular_peso(x);

    return x; // Nueva raiz
}

struct nodo *rotacion_izquierda(struct nodo *x) {
    struct nodo *y = x->der;
    struct nodo *T = y->izq;

    // Rotacion
    y->izq = x;
    x->der = T;

    // Actualizar alturas y peso
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    x->peso = calcular_peso(x);
    y->peso = calcular_peso(y);

    return y; // Nueva raiz
}

void insertar(struct nodo *&n) {  
    int valor;
    cout << "Valor a insertar: ";
    cin >> valor;

    if (n == NULL) {
        struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo));
        nuevo->valor = valor;
        nuevo->altura = 1;
        nuevo->peso = 1;
        nuevo->equilibrio = 0;
        nuevo->izq = nuevo->der = NULL;
        n = nuevo;
        return;
    }

    if (valor < n->valor) {
        insertar(n->izq);
    } else if (valor > n->valor) {
        insertar(n->der);
    } else {
        cout << "Valor duplicado, no se puede insertar." << endl;
        return; 
    }

    // Actualizar la altura, peso y equilibrio del nodo actual
    n->altura = 1 + max(altura(n->izq), altura(n->der));
    n->peso = calcular_peso(n);
    n->equilibrio = factor_equilibrio(n);

    // Rotaciones
    if (n->equilibrio > 1 and valor < n->izq->valor) {
        cout << "Rotacion derecha realizada." << endl;
        n = rotacion_derecha(n);
    }

    if (n->equilibrio < -1 and valor > n->der->valor) {
        cout << "Rotacion izquierda realizada." << endl;
        n = rotacion_izquierda(n);
    }

    if (n->equilibrio > 1 and valor > n->izq->valor) {
        cout << "Rotacion doble derecha realizada." << endl;
        n->izq = rotacion_izquierda(n->izq);
        n = rotacion_derecha(n);
    }

    if (n->equilibrio < -1 and valor < n->der->valor) {
        cout << "Rotacion doble izquierda realizada." << endl;
        n->der = rotacion_derecha(n->der);
        n = rotacion_izquierda(n);
    }
}

struct nodo *encontrar_minimo(struct nodo *n) {
    while (n->izq != NULL) {
        n = n->izq;
    }
    return n;
}

void eliminar(struct nodo *&n) {  
    int valor;
    cout << "Valor a eliminar: ";
    cin >> valor;

    if (n == NULL) {
        cout << "Nodo no encontrado." << endl;
        return;
    }

    // Buscar el valor a eliminar
    if (valor < n->valor) {
        eliminar(n->izq); // Llamada recursiva para el subárbol izquierdo
    } else if (valor > n->valor) {
        eliminar(n->der); // Llamada recursiva para el subárbol derecho
    } else {
        // Si el valor se encuentra en el nodo actual
        if (n->izq == NULL or n->der == NULL) {
            struct nodo *temp = (n->izq) ? n->izq : n->der; // Si tiene un hijo o está vacío

            if (temp == NULL) {
                temp = n;
                n = NULL; // El nodo se elimina
            } else {
                *n = *temp; // Copiar los datos del hijo
            }
            free(temp);
        } else {
            struct nodo *temp = encontrar_minimo(n->der); // Encontrar el mini en el subárbol derecho
            n->valor = temp->valor; // Copiar el valor del mínimo
            eliminar(n->der); // Eliminar el nodo mínimo
        }
    }

    if (n == NULL) return;

    // Actualizar las propiedades del nodo después de la eliminación
    n->altura = 1 + max(altura(n->izq), altura(n->der));
    n->peso = calcular_peso(n);
    n->equilibrio = factor_equilibrio(n);

    // Verificar si el árbol está desequilibrado y realizar rotaciones
    if (n->equilibrio > 1 and factor_equilibrio(n->izq) >= 0) {
        cout << "Rotacion derecha realizada." << endl;
        n = rotacion_derecha(n);
    }

    if (n->equilibrio > 1 and factor_equilibrio(n->izq) < 0) {
        cout << "Rotacion doble derecha realizada." << endl;
        n->izq = rotacion_izquierda(n->izq);
        n = rotacion_derecha(n);
    }

    if (n->equilibrio < -1 and factor_equilibrio(n->der) <= 0) {
        cout << "Rotacion izquierda realizada." << endl;
        n = rotacion_izquierda(n);
    }

    if (n->equilibrio < -1 and factor_equilibrio(n->der) > 0) {
        cout << "Rotacion doble izquierda realizada." << endl;
        n->der = rotacion_derecha(n->der);
        n = rotacion_izquierda(n);
    }
}

void recorrer(struct nodo *n) {
    if (n != NULL) {
        cout << "Valor: " << n->valor << ", Altura: " << n->altura << ", Peso: " << n->peso << ", Equilibrio: " << n->equilibrio << endl;
        recorrer(n->izq);
        recorrer(n->der);
    }
}

void mostrar() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio." << endl;
    } else {
        recorrer(raiz);
    }
}

int main() {
    int opcion;

    do {
        cout << "\n1. Insertar nodo" << endl;
        cout << "2. Eliminar nodo" << endl;
        cout << "3. Mostrar arbol" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertar(raiz);  
                break;

            case 2:
                eliminar(raiz); 
                break;

            case 3:
                mostrar();
                break;

            case 4:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 4);

    return 0;
}
