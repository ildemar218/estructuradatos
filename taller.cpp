#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct nodo {
    char destinatario[50];
    int codigo_seguimiento;
    char prioridad[10];
    char destino[15];
    nodo* siguiente;
};

struct nodo *lista_envios = NULL, *aux, *aux2;

int registrar() {
    aux = (struct nodo*)malloc(sizeof(struct nodo));

    cout << "Ingrese el nombre del destinatario: ";
    cin >> aux->destinatario;
    cout << "Ingrese el codigo de seguimiento: ";
    cin >> aux->codigo_seguimiento;
    cout << "Ingrese la prioridad (Alta, Media, Baja): ";
    cin >> aux->prioridad;
    cout << "Ingrese el destino (Nacional, Internacional): ";
    cin >> aux->destino;

    aux->siguiente = lista_envios;
    lista_envios = aux;
    return 0;
}


int main() {
    int opc;
    do {
        cout << "1. Registrar envio" << endl
            << "2. Mostrar envios" << endl
            << "3. Ordenar envios" << endl
            << "4. Salir" << endl;
        cin >> opc;
        switch(opc) {
            case 1: registrar(); break;
            //case 2: mostrar(); break;
            //case 3: ordenar(); break;
        }
    } while(opc != 4);
    return 0;
}
