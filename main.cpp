#include <iostream>
#include <string>
#include "SistemaDelivery.h"

using namespace std;

void menuGestion(SistemaDelivery& sistema) {
    int opcion;
    do {
        cout << "\n SUBMENU DE GESTION \n";
        cout << "1. Registrar Cliente\n";
        cout << "2. Registrar Repartidor\n";
        cout << "3. Registrar Sector\n";
        cout << "4. Listar Todo\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string c, n, t;
            cout << "Cedula: "; cin >> c;
            cout << "Nombre: "; cin.ignore(); getline(cin, n);
            cout << "Telefono: "; cin >> t;
            sistema.agregarCliente(Cliente(c, n, t));
        } else if (opcion == 2) {
            string c, n, v, m, p;
            cout << "Cedula: "; cin >> c;
            cout << "Nombre: "; cin.ignore(); getline(cin, n);
            cout << "Vehiculo (Moto/Carro): "; cin >> v;
            cout << "Modelo: "; cin.ignore(); getline(cin, m);
            cout << "Placa: "; cin >> p;
            sistema.agregarRepartidor(Repartidor(c, n, v, m, p));
        } else if (opcion == 3) {
            int id; string n;
            cout << "ID Sector: "; cin >> id;
            cout << "Nombre Sector: "; cin.ignore(); getline(cin, n);
            sistema.agregarSector(Sector(id, n));
        } else if (opcion == 4) {
            cout << "\nClientes \n"; sistema.listarClientes();
            cout << "\n Repartidores \n"; sistema.listarRepartidores();
            cout << "\n Sectores \n"; sistema.listarSectores();
        }
    } while (opcion != 0);
}

void menuServicio(SistemaDelivery& sistema) {
    sistema.iniciarJornada();
    int opcion;
    do {
        cout << "\nSUBMENU DE SERVICIO DIARIO \n";
        cout << "1. Actualizar Ubicacion Repartidor\n";
        cout << "2. Solicitar Envio\n";
        cout << "3. Finalizar Entrega\n";
        cout << "0. Finalizar Jornada (Generar Reporte y Salir)\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string placa; int idS;
            cout << "Placa del repartidor: "; cin >> placa;
            cout << "ID del nuevo sector: "; cin >> idS;
            sistema.actualizarUbicacionRepartidor(placa, idS);

        } else if (opcion == 2) {
            string ced; int idO, idD;
            cout << "Cedula del cliente: "; cin >> ced;
            cout << "ID Sector Origen: "; cin >> idO;
            cout << "ID Sector Destino: "; cin >> idD;
            sistema.solicitarEnvio(ced, idO, idD);

        } else if (opcion == 3) {
            string placa;
            cout << "Placa del repartidor que finaliza: "; cin >> placa;
            sistema.finalizarEntrega(placa);
        }

    } while (opcion != 0);
    sistema.finalizarJornada();
}

int main() {
    SistemaDelivery sistema;
    int opcion;

    do {
        cout << "\n SPEED DELIVERY - SAN CRISTOBAL \n";
        cout << "1. Gestion \n";
        cout << "2. Servicio Diario \n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuGestion(sistema); break;
            case 2: menuServicio(sistema); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
