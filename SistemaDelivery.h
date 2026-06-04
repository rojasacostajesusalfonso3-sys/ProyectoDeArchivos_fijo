#ifndef SISTEMADELIVERY_H
#define SISTEMADELIVERY_H

#include <vector>
#include <fstream>
#include <ctime>
#include <iostream>
#include "Cliente.h"
#include "Repartidor.h"
#include "Sector.h"

using namespace std;

class SistemaDelivery {
private:
    vector<Cliente> clientes;
    vector<Repartidor> repartidores;
    vector<Sector> sectores;
    bool jornadaIniciada;

    const string FILE_CLIENTES = "clientes.dat";
    const string FILE_REPARTIDORES = "repartidores.dat";
    const string FILE_SECTORES = "sectores.dat";

    void cargarDatos() {
        ifstream fCli(FILE_CLIENTES, ios::binary);
        if (fCli) {
            Cliente c;
            while (fCli.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
                clientes.push_back(c);
            }
            fCli.close();
        }

        ifstream fRep(FILE_REPARTIDORES, ios::binary);
        if (fRep) {
            Repartidor r;
            while (fRep.read(reinterpret_cast<char*>(&r), sizeof(Repartidor))) {
                repartidores.push_back(r);
            }
            fRep.close();
        }

        ifstream fSec(FILE_SECTORES, ios::binary);
        if (fSec) {
            Sector s;
            while (fSec.read(reinterpret_cast<char*>(&s), sizeof(Sector))) {
                sectores.push_back(s);
            }
            fSec.close();
        }
    }

    void guardarDatos() {
        ofstream fCli(FILE_CLIENTES, ios::binary);
        for (int i = 0; i < clientes.size(); i++) {
            fCli.write(reinterpret_cast<const char*>(&clientes[i]), sizeof(Cliente));
        }

        ofstream fRep(FILE_REPARTIDORES, ios::binary);
        for (int i = 0; i < repartidores.size(); i++) {
            fRep.write(reinterpret_cast<const char*>(&repartidores[i]), sizeof(Repartidor));
        }

        ofstream fSec(FILE_SECTORES, ios::binary);
        for (int i = 0; i < sectores.size(); i++) {
            fSec.write(reinterpret_cast<const char*>(&sectores[i]), sizeof(Sector));
        }
    }

public:
    SistemaDelivery() {
        jornadaIniciada = false;
        cargarDatos();
        srand(time(0));
    }

    ~SistemaDelivery() {
        guardarDatos();
    }

    // Gestion Clientes
    void agregarCliente(const Cliente& c) {
        clientes.push_back(c);
    }

    void listarClientes() {
        for (int i = 0; i < clientes.size(); i++) {
            clientes[i].mostrar();
        }
    }

    void modificarCliente(string cedula, string nuevoNombre, string nuevoTelefono) {
        for (int i = 0; i < clientes.size(); i++) {
            if (string(clientes[i].getCedula()) == cedula) {
                if (!nuevoNombre.empty()) clientes[i].setNombre(nuevoNombre);
                if (!nuevoTelefono.empty()) clientes[i].setTelefono(nuevoTelefono);
                cout << "Cliente modificado.\n";
                return;
            }
        }
        cout << "Cliente no encontrado.\n";
    }

    void eliminarCliente(string cedula) {
        for (int i = 0; i < clientes.size(); i++) {
            if (string(clientes[i].getCedula()) == cedula) {
                clientes.erase(clientes.begin() + i);
                cout << "Cliente eliminado.\n";
                return;
            }
        }
        cout << "Cliente no encontrado.\n";
    }

    //gestion de Repartidores
    void agregarRepartidor(const Repartidor& r) {
        repartidores.push_back(r);
    }

    void listarRepartidores() {
        for (int i = 0; i < repartidores.size(); i++) {
            repartidores[i].mostrar();
        }
    }

    void modificarRepartidor(string placa, string nuevoNombre, string nuevoVehiculo, string nuevoModelo) {
        for (int i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                if (!nuevoNombre.empty()) repartidores[i].setNombre(nuevoNombre);
                if (!nuevoVehiculo.empty()) repartidores[i].setVehiculo(nuevoVehiculo);
                if (!nuevoModelo.empty()) repartidores[i].setModelo(nuevoModelo);
                cout << "Repartidor modificado.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void eliminarRepartidor(string placa) {
        for (int i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                repartidores.erase(repartidores.begin() + i);
                cout << "Repartidor eliminado.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    //gestion de sectores
    void agregarSector(const Sector& s) {
        sectores.push_back(s);
    }

    void listarSectores() {
        for (int i = 0; i < sectores.size(); i++) {
            sectores[i].mostrar();
        }
    }

    void modificarSector(int id, string nuevoNombre) {
        for (int i = 0; i < sectores.size(); i++) {
            if (sectores[i].getId() == id) {
                sectores[i].setNombre(nuevoNombre);
                cout << "Sector modificado.\n";
                return;
            }
        }
        cout << "Sector no encontrado.\n";
    }

    void eliminarSector(int id) {
        for (int i = 0; i < sectores.size(); i++) {
            if (sectores[i].getId() == id) {
                sectores.erase(sectores.begin() + i);
                cout << "Sector eliminado.\n";
                return;
            }
        }
        cout << "Sector no encontrado.\n";
    }

    //gestion de jornada
    void iniciarJornada() {
        if (sectores.empty() || jornadaIniciada) return;
        for (int i = 0; i < repartidores.size(); i++) {
            int indiceAleatorio = rand() % sectores.size();
            repartidores[i].setIdSectorActual(sectores[indiceAleatorio].getId());
            repartidores[i].setDisponible(true);
        }
        jornadaIniciada = true;
        cout << "Jornada iniciada. Repartidores distribuidos aleatoriamente.\n";
    }

    void actualizarUbicacionRepartidor(string placa, int nuevoSectorId) {
        for (int i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                repartidores[i].setIdSectorActual(nuevoSectorId);
                cout << "Ubicacion actualizada.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void solicitarEnvio(string cedulaCli, int idOrigen, int idDestino) {
        int posCli = -1;
        for (int i = 0; i < clientes.size(); i++) {
            if (string(clientes[i].getCedula()) == cedulaCli) {
                posCli = i;
                break;
            }
        }

        if (posCli == -1) {
            cout << "Cliente no registrado.\n";
            return;
        }


        vector<int> indicesDisponibles;
        for (int i = 0; i < repartidores.size(); i++) {
            if (repartidores[i].isDisponible() && repartidores[i].getIdSectorActual() == idOrigen) {
                indicesDisponibles.push_back(i);
            }
        }

        if (indicesDisponibles.empty()) {
            cout << "Lo sentimos, en este momento no hay repartidores disponibles en su zona. Por favor, intente mas tarde.\n";
            return;
        }

        cout << "Repartidores disponibles en el sector:\n";
        for (int i = 0; i < indicesDisponibles.size(); i++) {
            cout << i + 1 << ". ";
            repartidores[indicesDisponibles[i]].mostrar();
        }

        int seleccion;
        cout << "Seleccione un repartidor (numero): ";
        cin >> seleccion;

        if (seleccion > 0 && seleccion <= indicesDisponibles.size()) {
            int posRep = indicesDisponibles[seleccion - 1];
            repartidores[posRep].setDisponible(false);
            repartidores[posRep].setIdSectorActual(idDestino);
            repartidores[posRep].incrementarServicios();
            clientes[posCli].incrementarServicios();
            cout << "Servicio asignado a " << repartidores[posRep].getNombre() << ". En camino...\n";
        }
    }

    void finalizarEntrega(string placa) {
        for (int i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                repartidores[i].setDisponible(true);
                cout << "Entrega finalizada. Repartidor " << repartidores[i].getNombre() << " ahora esta disponible.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void finalizarJornada() {
        ofstream report("reporte_estadisticas.txt");
        report << " REPORTE DE ESTADISTICAS DEL DIA \n\n";


        auto repSorted = repartidores;
        for (int i = 0; i < repSorted.size(); i++) {
            for (int j = 0; j < repSorted.size() - 1 - i; j++) {
                if (repSorted[j].getServiciosCompletados() < repSorted[j+1].getServiciosCompletados()) {
                    Repartidor aux = repSorted[j];
                    repSorted[j] = repSorted[j+1];
                    repSorted[j+1] = aux;
                }
            }
        }

        report << "TOP REPARTIDORES:\n";
        for (int i = 0; i < repSorted.size(); i++) {
            report << repSorted[i].getNombre() << " (" << repSorted[i].getPlaca() << "): " << repSorted[i].getServiciosCompletados() << " entregas\n";
        }


        auto cliSorted = clientes;
        for (int i = 0; i < cliSorted.size(); i++) {
            for (int j = 0; j < cliSorted.size() - 1 - i; j++) {
                if (cliSorted[j].getServiciosRealizados() < cliSorted[j+1].getServiciosRealizados()) {
                    Cliente aux = cliSorted[j];
                    cliSorted[j] = cliSorted[j+1];
                    cliSorted[j+1] = aux;
                }
            }
        }

        report << "\nTOP CLIENTES:\n";
        for (int i = 0; i < cliSorted.size(); i++) {
            report << cliSorted[i].getNombre() << " (" << cliSorted[i].getCedula() << "): " << cliSorted[i].getServiciosRealizados() << " pedidos\n";
        }

        report.close();
        cout << "Jornada finalizada. Reporte generado en reporte_estadisticas.txt\n";
    }
};

#endif