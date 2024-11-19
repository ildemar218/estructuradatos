#include <iostream>
using namespace std;

struct Vehiculo {
    string tipo; 
    int movimientos;
    Vehiculo *sig;
};

struct Vehiculo *top_carros = NULL, *top_motos = NULL, *aux = NULL;
int ingresos_totales = 0;


int registrar() {
    aux = (struct Vehiculo *)malloc(sizeof(struct Vehiculo));
    int tipo;
    cout << "Seleccione el tipo de vehiculo:\n1. Carro\n2. Moto\n";
    cin >> tipo;

    if (tipo == 1) {
        aux->tipo = "carro";
    } else if (tipo == 2) {
        aux->tipo = "moto";
    } else {
        cout << "Opcion invalida.\n";
        free(aux);
        return 0;
    }

    aux->movimientos = 0;

    if (aux->tipo == "carro") {
        aux->sig = top_carros;
        top_carros = aux;
    } else {
        aux->sig = top_motos;
        top_motos = aux;
    }

    cout << aux->tipo << " registrado.\n";
    aux = NULL;
    return 0;
}


int retirar() {
    int tipo;
    cout << "Seleccione el tipo de vehiculo a retirar:\n1. Carro\n2. Moto\n";
    cin >> tipo;

    Vehiculo *top = (tipo == 1) ? top_carros : top_motos;

    if (!top) {
        cout << ((tipo == 1) ? "No hay carros" : "No hay motos") << " para retirar.\n";
        return 0;
    }

    aux = top;
    if (tipo == 1) {
        top_carros = top_carros->sig;
    } else {
        top_motos = top_motos->sig;
    }

    int tarifa = (aux->tipo == "carro" ? 2000 : 1000) + (aux->movimientos * 100);
    ingresos_totales += tarifa;

    cout << aux->tipo << " retirado. Tarifa: $" << tarifa << ".\n";
    free(aux);
    aux = NULL;
    return 0;
}


int mover() {
    int tipo;
    cout << "Seleccione el tipo de vehiculo a mover:\n1. Carro\n2. Moto\n";
    cin >> tipo;

    Vehiculo *top = (tipo == 1) ? top_carros : top_motos;

    if (!top) {
        cout << ((tipo == 1) ? "No hay carros" : "No hay motos") << " para mover.\n";
        return 0;
    }

    top->movimientos++;
    cout << top->tipo << " movido. Movimientos actuales: " << top->movimientos << ".\n";
    return 0;
}

int mostrar_ingresos() {
    cout << "Ingresos totales generados: $" << ingresos_totales << ".\n";
    return 0;
}


int main() {
    int opc;
    do {
        cout << "1. Registrar vehiculo" << endl
            << "2. Retirar vehiculo" << endl
            << "3. Mover vehiculo" << endl
            << "4. Mostrar ingresos" << endl
            << "5. Salir" << endl;
        cin >> opc;

        switch (opc) {
            case 1: registrar(); break;
            case 2: retirar(); break;
            case 3: mover(); break;
            case 4: mostrar_ingresos(); break;
        }
    } while (opc != 5);

    return 0;
}
