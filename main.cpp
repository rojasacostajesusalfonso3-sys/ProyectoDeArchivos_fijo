//integrantess
//Jesus Alfonso Rojas Acosta 31386557
//Tomas Antonio Useche Cordero 30982189



#include <iostream>
#include <string>
#include "SistemaDelivery.h"

using namespace std;

void subMenuClientes(SistemaDelivery& sistema) {
    int opcion;
    do {
        cout << "\n --- GESTION DE CLIENTES ---\n";
        cout << "1. Registrar Cliente\n";
        cout << "2. Modificar Cliente\n";
        cout << "3. Eliminar Cliente\n";
        cout << "0. Volver al Menu de Gestion\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string c, n, t;
            cout << "Cedula: "; cin >> c; cin.ignore();
            cout << "Nombre: "; getline(cin, n);
            cout << "Telefono: "; cin >> t; cin.ignore();
            sistema.agregarCliente(Cliente(c, n, t));
        } else if (opcion == 2) {
            string c, n, t;
            cout << "Cedula del cliente a modificar: "; cin >> c; cin.ignore();
            cout << "Nuevo Nombre (Vacio para mantener): "; getline(cin, n);
            cout << "Nuevo Telefono (Vacio para mantener): "; cin >> t; cin.ignore();
            sistema.modificarCliente(c, n, t);
        } else if (opcion == 3) {
            string c;
            cout << "Cedula del cliente a eliminar: "; cin >> c; cin.ignore();
            sistema.eliminarCliente(c);
        }
    } while (opcion != 0);
}

void subMenuRepartidores(SistemaDelivery& sistema) {
    int opcion;
    do {
        cout << "\n --- GESTION DE REPARTIDORES ---\n";
        cout << "1. Registrar Repartidor\n";
        cout << "2. Modificar Repartidor\n";
        cout << "3. Eliminar Repartidor\n";
        cout << "0. Volver al Menu de Gestion\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string c, n, v, m, p;
            cout << "Cedula: "; cin >> c; cin.ignore();
            cout << "Nombre: "; getline(cin, n);
            cout << "Vehiculo (Moto/Carro): "; cin >> v; cin.ignore();
            cout << "Modelo: "; getline(cin, m);
            cout << "Placa: "; cin >> p; cin.ignore();
            sistema.agregarRepartidor(Repartidor(c, n, v, m, p));
        } else if (opcion == 2) {
            string p, n, v, m;
            cout << "Placa del repartidor a modificar: "; cin >> p; cin.ignore();
            cout << "Nuevo Nombre (Vacio para mantener): "; getline(cin, n);
            cout << "Nuevo Vehiculo (Vacio para mantener): "; cin >> v; cin.ignore();
            cout << "Nuevo Modelo (Vacio para mantener): "; getline(cin, m);
            sistema.modificarRepartidor(p, n, v, m);
        } else if (opcion == 3) {
            string p;
            cout << "Placa del repartidor a eliminar: "; cin >> p; cin.ignore();
            sistema.eliminarRepartidor(p);
        }
    } while (opcion != 0);
}

void subMenuSectores(SistemaDelivery& sistema) {
    int opcion;
    do {
        cout << "\n --- GESTION DE SECTORES ---\n";
        cout << "1. Registrar Sector\n";
        cout << "2. Modificar Sector\n";
        cout << "3. Eliminar Sector\n";
        cout << "0. Volver al Menu de Gestion\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            int id; string n;
            cout << "ID Sector: "; cin >> id; cin.ignore();
            cout << "Nombre Sector: "; getline(cin, n);
            sistema.agregarSector(Sector(id, n));
        } else if (opcion == 2) {
            int id; string n;
            cout << "ID del sector a modificar: "; cin >> id; cin.ignore();
            cout << "Nuevo Nombre del Sector: "; getline(cin, n);
            sistema.modificarSector(id, n);
        } else if (opcion == 3) {
            int id;
            cout << "ID del sector a eliminar: "; cin >> id; cin.ignore();
            sistema.eliminarSector(id);
        }
    } while (opcion != 0);
}

void menuGestion(SistemaDelivery& sistema) {
    int opcion;
    do {
        cout << "\n --- MENU GENERAL DE GESTION ---\n";
        cout << "1. Gestionar Clientes\n";
        cout << "2. Gestionar Repartidores\n";
        cout << "3. Gestionar Sectores\n";
        cout << "4. Listar Todo el Sistema\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: subMenuClientes(sistema); break;
            case 2: subMenuRepartidores(sistema); break;
            case 3: subMenuSectores(sistema); break;
            case 4:
                cout << "\n--- Clientes ---\n"; sistema.listarClientes();
                cout << "\n--- Repartidores ---\n"; sistema.listarRepartidores();
                cout << "\n--- Sectores ---\n"; sistema.listarSectores();
                break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
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
        cout << "4. Solicitar Envio (Ruta Optima)\n";
        cout << "0. Finalizar Jornada (Generar Reporte y Salir)\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string placa; int idS;
            cout << "Placa del repartidor: "; cin >> placa;
            cout << "ID del nuevo sector: "; cin >> idS; cin.ignore();
            sistema.actualizarUbicacionRepartidor(placa, idS);
        } else if (opcion == 2) {
            string ced; int idO, idD;
            cout << "Cedula del cliente: "; cin >> ced;
            cout << "ID Sector Origen: "; cin >> idO;
            cout << "ID Sector Destino: "; cin >> idD; cin.ignore();
            sistema.solicitarEnvio(ced, idO, idD);
        } else if (opcion == 3) {
            string placa;
            cout << "Placa del repartidor que finaliza: "; cin >> placa; cin.ignore();
            sistema.finalizarEntrega(placa);
        } else if (opcion == 4) {
            sistema.solicitarEnvioRutaOptima();
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
        cin.ignore();

        switch (opcion) {
            case 1: menuGestion(sistema); break;
            case 2: menuServicio(sistema); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}