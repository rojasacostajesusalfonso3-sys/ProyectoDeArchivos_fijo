#ifndef SISTEMADELIVERY_H
#define SISTEMADELIVERY_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "Cliente.h"
#include "Repartidor.h"
#include "Sector.h"

using namespace std;

class SistemaDelivery {
private:
    vector<Cliente> clientes;
    vector<Repartidor> repartidores;
    vector<Sector> sectores;

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
        for (const auto& c : clientes) fCli.write(reinterpret_cast<const char*>(&c), sizeof(Cliente));

        ofstream fRep(FILE_REPARTIDORES, ios::binary);
        for (const auto& r : repartidores) fRep.write(reinterpret_cast<const char*>(&r), sizeof(Repartidor));

        ofstream fSec(FILE_SECTORES, ios::binary);
        for (const auto& s : sectores) fSec.write(reinterpret_cast<const char*>(&s), sizeof(Sector));
    }

public:
    SistemaDelivery() {
        cargarDatos();
        srand(time(0));
    }

    ~SistemaDelivery() {
        guardarDatos();
    }

    //Registro de los clinetes
    void agregarCliente(const Cliente& c) {
        clientes.push_back(c);
    }

    void listarClientes() {
        for (const auto& c : clientes) c.mostrar();
    }


    // Registro de los repartidores
    void agregarRepartidor(const Repartidor& r) {
        repartidores.push_back(r);
    }

    void listarRepartidores() {
        for (const auto& r : repartidores) r.mostrar();
    }

    // Registro de los sectoes
    void agregarSector(const Sector& s) { sectores.push_back(s); }
    void listarSectores() {
        for (const auto& s : sectores) s.mostrar();
    }

    // opciones de servicio diario
    void iniciarJornada() {
        if (sectores.empty()) return;
        for (auto& r : repartidores) {
            r.setIdSectorActual(sectores[rand() % sectores.size()].getId());
            r.setDisponible(true);
        }
        cout << "Jornada iniciada. Repartidores distribuidos aleatoriamente.\n";
    }

    void actualizarUbicacionRepartidor(string placa, int nuevoSectorId) {
        for (auto& r : repartidores) {
            if (r.getPlaca() == placa) {
                r.setIdSectorActual(nuevoSectorId);
                cout << "Ubicacion actualizada.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void solicitarEnvio(string cedulaCli, int idOrigen, int idDestino) {
        auto itCli = find_if(clientes.begin(), clientes.end(), [&](const Cliente& c) {
            return c.getCedula() == cedulaCli;
        });

        if (itCli == clientes.end()) {
            cout << "Cliente no registrado.\n";
            return;
        }

        vector<Repartidor*> disponiblesEnSector;
        for (auto& r : repartidores) {
            if (r.isDisponible() && r.getIdSectorActual() == idOrigen) {
                disponiblesEnSector.push_back(&r);
            }
        }

        if (disponiblesEnSector.empty()) {
            cout << "Lo sentimos, en este momento no hay repartidores disponibles en su zona. Por favor, intente mas tarde.\n";
            return;
        }

        cout << "Repartidores disponibles en el sector:\n";
        for (size_t i = 0; i < disponiblesEnSector.size(); ++i) {
            cout << i + 1 << ". ";
            disponiblesEnSector[i]->mostrar();
        }


        int seleccion;

        cout << "Seleccione un repartidor (numero): ";
        cin >> seleccion;

        if (seleccion > 0 && seleccion <= (int)disponiblesEnSector.size()) {
            Repartidor* elegido = disponiblesEnSector[seleccion - 1];
            elegido->setDisponible(false);

            elegido->setIdSectorActual(idDestino);

            elegido->incrementarServicios();

            itCli->incrementarServicios();

            cout << "Servicio asignado a " << elegido->getNombre() << ". En camino a destino...\n";
        }
    }

    void finalizarEntrega(string placa) {
        for (auto& r : repartidores) {
            if (r.getPlaca() == placa) {
                r.setDisponible(true);
                cout << "Entrega finalizada. Repartidor " << r.getNombre() << " ahora esta disponible.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void finalizarJornada() {
        ofstream report("reporte_estadisticas.txt");
        report << " REPORTE DE ESTADISTICAS DEL DIA \n\n";

        report << "TOP REPARTIDORES:\n";
        auto repSorted = repartidores;
        sort(repSorted.begin(), repSorted.end(), [](const Repartidor& a, const Repartidor& b) {
            return a.getServiciosCompletados() > b.getServiciosCompletados();
        });
        for (const auto& r : repSorted) {
            report << r.getNombre() << " (" << r.getPlaca() << "): " << r.getServiciosCompletados() << " entregas\n";
        }

        report << "\nTOP CLIENTES:\n";

        auto cliSorted = clientes;
        sort(cliSorted.begin(), cliSorted.end(), [](const Cliente& a, const Cliente& b) {
            return a.getServiciosRealizados() > b.getServiciosRealizados();
        });
        for (const auto& c : cliSorted) {
            report << c.getNombre() << " (" << c.getCedula() << "): " << c.getServiciosRealizados() << " pedidos\n";
        }


        report.close();
        cout << "Jornada finalizada. Reporte generado en reporte_estadisticas.txt\n";
    }
};

#endif
