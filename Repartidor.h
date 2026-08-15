#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <string>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

class Repartidor {
private:
    char cedula[15];
    char nombre[50];
    char vehiculo[30];
    char modelo[30];
    char placa[15];
    int idSectorActual;
    bool disponible;
    int serviciosCompletados;
    // Campos para la hora de llegada
    int horaLlegada;   // 0 a 23
    int minutoLlegada; // 0 a 59

public:
    Repartidor(string ced = "", string nom = "", string veh = "", string mod = "", string pla = "", int h = 0, int m = 0) {
        setCedula(ced);
        setNombre(nom);
        setVehiculo(veh);
        setModelo(mod);
        setPlaca(pla);
        idSectorActual = -1;
        disponible = true;
        serviciosCompletados = 0;
        horaLlegada = h;
        minutoLlegada = m;
    }

    const char * getCedula() const { return cedula; }
    const char * getNombre() const { return nombre; }
    const char * getVehiculo() const { return vehiculo; }
    const char * getModelo() const { return modelo; }
    const char * getPlaca() const { return placa; }
    int getIdSectorActual() const { return idSectorActual; }
    bool isDisponible() const { return disponible; }
    int getServiciosCompletados() const { return serviciosCompletados; }

    // Getters de hora de llegada
    int getHoraLlegada() const { return horaLlegada; }
    int getMinutoLlegada() const { return minutoLlegada; }

    // Método necesario para comparar el tiempo de llegada fácilmente
    int getTiempoEnMinutos() const {
        return (horaLlegada * 60) + minutoLlegada;
    }

    void setCedula(const string& val) { strncpy(cedula, val.c_str(), sizeof(cedula)-1); cedula[sizeof(cedula)-1] = '\0'; }
    void setNombre(const string& val) { strncpy(nombre, val.c_str(), sizeof(nombre)-1); nombre[sizeof(nombre)-1] = '\0'; }
    void setVehiculo(const string& val) { strncpy(vehiculo, val.c_str(), sizeof(vehiculo)-1); vehiculo[sizeof(vehiculo)-1] = '\0'; }
    void setModelo(const string& val) { strncpy(modelo, val.c_str(), sizeof(modelo)-1); modelo[sizeof(modelo)-1] = '\0'; }
    void setPlaca(const string& val) { strncpy(placa, val.c_str(), sizeof(placa)-1); placa[sizeof(placa)-1] = '\0'; }

    void setIdSectorActual(int id) { idSectorActual = id; }
    void setDisponible(bool d) { disponible = d; }
    void incrementarServicios() { serviciosCompletados++; }

    void setHoraLlegada(int h, int m) {
        horaLlegada = h;
        minutoLlegada = m;
    }

    void mostrar() const {
        cout << "Placa: " << placa
             << " | Repartidor: " << nombre
             << " | Vehiculo: " << vehiculo << " (" << modelo << ")"
             << " | Sector: " << idSectorActual
             << " | Hora Llegada: " << setfill('0') << setw(2) << horaLlegada << ":" << setw(2) << minutoLlegada
             << " | " << (disponible ? "Disponible" : "Ocupado") << endl;
    }
};

#endif