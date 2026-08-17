#ifndef SISTEMADELIVERY_H
#define SISTEMADELIVERY_H

#include <vector>
#include <fstream>
#include <ctime>
#include <iostream>
#include <map>
#include "Estructuras.h"
#include "Cliente.h"
#include "Repartidor.h"
#include "Sector.h"
#include "Grafo.h"
#include <sstream>

using namespace std;

class SistemaDelivery {
private:
    vector<Cliente> clientes;
    vector<Repartidor> repartidores;
    vector<Sector> sectores;
    bool jornadaIniciada;
    Grafo* grafoSectores;


    map<int, ColaClientes> colasEsperaPorSector;

    const string FILE_CLIENTES = "clientes.dat";
    const string FILE_REPARTIDORES = "repartidores.dat";
    const string FILE_SECTORES = "sectores.dat";
    const string FILE_GRAFO = "Grafo.txt";

public:
    SistemaDelivery() {
        jornadaIniciada = false;
        grafoSectores = nullptr;
        cargarDatos();
    }

    ~SistemaDelivery() {
        guardarDatos();
        delete grafoSectores;
    }

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
            int maxId = -1;
            Sector s;
            while (fSec.read(reinterpret_cast<char*>(&s), sizeof(Sector))) {
                sectores.push_back(s);
                if (s.getId() > maxId) {
                    maxId = s.getId();
                }
            }
            fSec.close();

            if (!sectores.empty()) {
                // El tamaño de la matriz debe ser maxId + 1 para poder usar los IDs como índices.
                // Ej: si el ID más alto es 9, necesitamos una matriz de 10x10 (índices 0 a 9).
                grafoSectores = new Grafo(maxId + 1);
                // Una vez creado el grafo, leemos las conexiones desde el archivo.
                cargarConexionesGrafo(FILE_GRAFO);
            }
        }
    }

    void cargarConexionesGrafo(const string& nombreArchivo) {
        if (!grafoSectores) { // Seguridad: no hacer nada si el grafo no existe
            return;
        }

        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "ADVERTENCIA: No se pudo abrir el archivo de grafo '" << nombreArchivo << "'. No se cargaran las distancias." << endl;
            return;
        }

        string linea;

        while (getline(archivo, linea)) {
            // Añadimos una comprobación para ignorar líneas vacías.
            // Esto es muy común si el archivo de texto tiene una línea en blanco al final.
            if (linea.empty()) {
                continue;
            }
            stringstream ss(linea);
            string origen_str, destino_str, peso_str;
            int origen, destino, peso;
            getline(ss, origen_str, ',');
            getline(ss, destino_str, ',');
            getline(ss, peso_str);
            origen = stoi(origen_str);
            destino = stoi(destino_str);
            peso = stoi(peso_str);
            grafoSectores->agregarArista(origen, destino, peso);


        }
        cout << "Conexiones del grafo cargadas." << endl;
    }

    void guardarDatos() {

        ofstream fCli(FILE_CLIENTES, ios::binary | ios::trunc);
        if (fCli) {
            for (const auto& c : clientes) {
                fCli.write(reinterpret_cast<const char*>(&c), sizeof(Cliente));
            }
            fCli.close();
        }

        ofstream fRep(FILE_REPARTIDORES, ios::binary | ios::trunc);
        if (fRep) {
            for (const auto& r : repartidores) {
                fRep.write(reinterpret_cast<const char*>(&r), sizeof(Repartidor));
            }
            fRep.close();
        }


        ofstream fSec(FILE_SECTORES, ios::binary | ios::trunc);
        if (fSec) {
            for (const auto& s : sectores) {
                fSec.write(reinterpret_cast<const char*>(&s), sizeof(Sector));
            }
            fSec.close();
        }
    }


    void iniciarJornada() {
        if (jornadaIniciada) {
            cout << "La jornada ya esta iniciada.\n";
            return;
        }
        jornadaIniciada = true;
        cout << "¡Jornada de delivery iniciada exitosamente!\n";
    }

    void finalizarJornada() {
        if (!jornadaIniciada) {
            cout << "La jornada no ha sido iniciada.\n";
            return;
        }
        jornadaIniciada = false;
        cout << "Jornada de delivery finalizada.\n";
    }

    void agregarCliente(const Cliente& c) {
        clientes.push_back(c);
        cout << "Cliente registrado exitosamente.\n";
    }

    void listarClientes() const {
        cout << "\n--- LISTA DE CLIENTES ---\n";
        if (clientes.empty()) {
            cout << "No hay clientes registrados.\n";
            return;
        }
        for (const auto& c : clientes) {
            c.mostrar();
        }
    }

    void modificarCliente(string cedula, string nuevoNombre, string nuevoTelf) {
        for (auto& c : clientes) {
            if (string(c.getCedula()) == cedula) {
                c.setNombre(nuevoNombre);
                c.setTelefono(nuevoTelf);
                cout << "Cliente modificado exitosamente.\n";
                return;
            }
        }
        cout << "Cliente no encontrado.\n";
    }

    void eliminarCliente(string cedula) {
        for (auto it = clientes.begin(); it != clientes.end(); ++it) {
            if (string(it->getCedula()) == cedula) {
                clientes.erase(it);
                cout << "Cliente eliminado exitosamente.\n";
                return;
            }
        }
        cout << "Cliente no encontrado.\n";
    }


    void agregarRepartidor(const Repartidor& r) {
        repartidores.push_back(r);
        cout << "Repartidor registrado exitosamente.\n";
    }

    void listarRepartidores() const {
        cout << "\n--- LISTA DE REPARTIDORES ---\n";
        if (repartidores.empty()) {
            cout << "No hay repartidores registrados.\n";
            return;
        }
        for (const auto& r : repartidores) {
            r.mostrar();
        }
    }

    void modificarRepartidor(string placa, string nuevoNombre, string nuevoVehiculo, string nuevoModelo) {
        for (auto& r : repartidores) {
            if (string(r.getPlaca()) == placa) {
                r.setNombre(nuevoNombre);
                r.setVehiculo(nuevoVehiculo);
                r.setModelo(nuevoModelo);
                cout << "Repartidor modificado exitosamente.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void eliminarRepartidor(string placa) {
        for (auto it = repartidores.begin(); it != repartidores.end(); ++it) {
            if (string(it->getPlaca()) == placa) {
                repartidores.erase(it);
                cout << "Repartidor eliminado exitosamente.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }




    void agregarSector(const Sector& s) {
        sectores.push_back(s);
        cout << "Sector registrado exitosamente.\n";
    }

    void listarSectores() const {
        cout << "\n--- LISTA DE SECTORES ---\n";
        if (sectores.empty()) {
            cout << "No hay sectores registrados.\n";
            return;
        }
        for (const auto& s : sectores) {
            s.mostrar();
        }
    }

    void modificarSector(int id, const string& nuevoNombre) {
        for (auto& s : sectores) {
            if (s.getId() == id) {
                s.setNombre(nuevoNombre);
                cout << "Sector modificado exitosamente.\n";
                return;
            }
        }
        cout << "Sector no encontrado.\n";
    }

    void eliminarSector(int id) {
        for (auto it = sectores.begin(); it != sectores.end(); ++it) {
            if (it->getId() == id) {
                sectores.erase(it);
                cout << "Sector eliminado exitosamente.\n";
                return;
            }
        }
        cout << "Sector no encontrado.\n";
    }



    void solicitarEnvio(string cedulaCli, int idOrigen, int idDestino) {
        int posCli = -1;
        for (size_t i = 0; i < clientes.size(); i++) {
            if (string(clientes[i].getCedula()) == cedulaCli) {
                posCli = i;
                break;
            }
        }

        if (posCli == -1) {
            cout << "Cliente no registrado.\n";
            return;
        }


        ListaRepartidores disponiblesOrdenados;
        int cantidadDisponibles = 0;

        for (size_t i = 0; i < repartidores.size(); i++) {
            if (repartidores[i].isDisponible() && repartidores[i].getIdSectorActual() == idOrigen) {
                disponiblesOrdenados.insertarOrdenado(repartidores[i]);
                cantidadDisponibles++;
            }
        }


        if (cantidadDisponibles == 0) {
            Solicitud sol(cedulaCli, idOrigen, idDestino);
            colasEsperaPorSector[idOrigen].encolar(sol);

            cout << "\n[!] No hay repartidores disponibles en este sector en este momento.\n";
            cout << "Los datos del cliente (" << cedulaCli << ") han sido ingresados a la COLA DE ESPERA del Sector " << idOrigen << ".\n";
            return;
        }


        cout << "\nRepartidores disponibles en el sector (ordenados por hora de llegada):\n";
        disponiblesOrdenados.mostrar();

        int seleccion;
        cout << "Seleccione un repartidor (numero): ";
        cin >> seleccion;

        Repartidor repSeleccionado;
        if (disponiblesOrdenados.obtenerPorIndice(seleccion, repSeleccionado)) {
            for (auto& r : repartidores) {
                if (string(r.getPlaca()) == string(repSeleccionado.getPlaca())) {
                    r.setDisponible(false);
                    r.setIdSectorActual(idDestino);
                    r.incrementarServicios();
                    break;
                }
            }
            clientes[posCli].incrementarServicios();
            cout << "Servicio asignado a " << repSeleccionado.getNombre() << ". En camino...\n";
        } else {
            cout << "Seleccion invalida.\n";
        }
    }


    void actualizarUbicacionRepartidor(string placa, int nuevoSectorId) {
        int posRep = -1;
        for (size_t i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                posRep = i;
                break;
            }
        }

        if (posRep == -1) {
            cout << "Repartidor no encontrado.\n";
            return;
        }

        int h, m;
        cout << "Ingrese la hora de llegada al nuevo sector (HH MM, ej: 14 30): ";
        cin >> h >> m;

        repartidores[posRep].setIdSectorActual(nuevoSectorId);
        repartidores[posRep].setDisponible(true);
        repartidores[posRep].setHoraLlegada(h, m);

        cout << "\nUbicacion actualizada. El repartidor " << repartidores[posRep].getNombre()
             << " se movio al sector " << nuevoSectorId << " a las "
             << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m << ".\n";


        Solicitud sol;
        if (colasEsperaPorSector[nuevoSectorId].obtenerFrente(sol)) {
            cout << "\n--------------------------------------------------\n";
            cout << "[!] ATENCION: Hay clientes en la cola de espera de este sector.\n";
            cout << "Cliente CI: " << sol.cedulaCliente << " | Destino solicitante: Sector " << sol.idDestino << endl;

            char resp;
            cout << "¿El cliente todavia necesita el delivery? (s/n): ";
            cin >> resp;

            if (resp == 's' || resp == 'S') {
                colasEsperaPorSector[nuevoSectorId].desencolar(sol);

                repartidores[posRep].setDisponible(false);
                repartidores[posRep].setIdSectorActual(sol.idDestino);
                repartidores[posRep].incrementarServicios();

                for (auto& c : clientes) {
                    if (string(c.getCedula()) == sol.cedulaCliente) {
                        c.incrementarServicios();
                        break;
                    }
                }
                cout << "¡Servicio asignado exitosamente desde la cola de espera!\n";
                cout << "El repartidor va en camino al sector " << sol.idDestino << ".\n";
                cout << "--------------------------------------------------\n";
            } else {
                colasEsperaPorSector[nuevoSectorId].desencolar(sol);
                cout << "Solicitud descartada de la cola de espera.\n";
                cout << "--------------------------------------------------\n";
            }
        }
    }

    void finalizarEntrega(string placa) {
        for (size_t i = 0; i < repartidores.size(); i++) {
            if (string(repartidores[i].getPlaca()) == placa) {
                repartidores[i].setDisponible(true);
                cout << "Entrega finalizada. Repartidor " << repartidores[i].getNombre() << " ahora esta disponible.\n";
                return;
            }
        }
        cout << "Repartidor no encontrado.\n";
    }

    void solicitarEnvioRutaOptima() {
        cout << "\n--- SOLICITAR ENVIO CON RUTA OPTIMA ---\n";

        // 1. Encontrar y mostrar repartidores disponibles
        vector<Repartidor> disponibles;
        for (const auto& r : repartidores) {
            if (r.isDisponible()) {
                disponibles.push_back(r);
            }
        }

        if (disponibles.empty()) {
            cout << "No hay repartidores disponibles en este momento.\n";
            return;
        }

        cout << "Repartidores disponibles:\n";
        for (const auto& r : disponibles) {
            r.mostrar();
        }

        // 2. Pedir al usuario que elija por placa
        string placaSeleccionada;
        cout << "\nIngrese la placa del repartidor que desea seleccionar: ";
        cin >> placaSeleccionada;
        cin.ignore(); // Limpiar el buffer

        // 3. Encontrar el repartidor y obtener el origen
        int origen = -1;
        Repartidor* repartidorSeleccionado = nullptr; // Usamos un puntero para poder modificar el repartidor original

        if ((repartidorSeleccionado = buscarRepartidorPorPlaca(placaSeleccionada)) == nullptr) {
            cout << "Placa no valida o repartidor no disponible. Operacion cancelada.\n";
            return;
        }

        // 4. Pedir el destino
        int destino;
        origen = repartidorSeleccionado->getIdSectorActual();
        cout << "Sector actual del repartidor (" << repartidorSeleccionado->getNombre() << "): " << origen << endl;
        cout << "Ingrese el ID del sector de destino: ";
        cin >> destino;
        cin.ignore();

        // 5. Validar, calcular la ruta y actualizar estado
        if (grafoSectores) {
            grafoSectores->encontrarRutaMinima(origen, destino);

            repartidorSeleccionado->setDisponible(false);
            repartidorSeleccionado->incrementarServicios();
            repartidorSeleccionado->setIdSectorActual(destino);
            cout << "\nServicio asignado a " << repartidorSeleccionado->getNombre() << ". La ruta optima ha sido calculada.\n";
        } else {
            cout << "Error: El grafo de sectores no ha sido inicializado.\n";
        }
    }
private: // Funcion ayudante
    Repartidor* buscarRepartidorPorPlaca(const string& placa) {
        for (auto& r : repartidores) {
            if (string(r.getPlaca()) == placa && r.isDisponible()) {
                return &r; // Devuelve un puntero al repartidor encontrado
            }
        }
        return nullptr; // No se encontró
    }

};

#endif