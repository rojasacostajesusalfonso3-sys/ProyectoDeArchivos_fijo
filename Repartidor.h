#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <string>
#include <iostream>
#include <cstring>

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

public:
    Repartidor(string ced = "", string nom = "", string veh = "", string mod = "", string pla = "") {
        setCedula(ced);
        setNombre(nom);
        setVehiculo(veh);
        setModelo(mod);
        setPlaca(pla);
        idSectorActual = -1;
        disponible = true;
        serviciosCompletados = 0;
    }

    const char * getCedula() const {
        return cedula;
    }

    const char * getNombre() const {
        return nombre;
    }

    const char * getVehiculo() const {
        return vehiculo;
    }

    const char * getModelo() const {
        return modelo;
    }

    const char * getPlaca() const {
        return placa;
    }

    int getIdSectorActual() const {
        return idSectorActual;
    }

    bool isDisponible() const {
        return disponible;
    }

    int getServiciosCompletados() const {
        return serviciosCompletados;
    }


    void setCedula(const string& val) {
        strncpy(cedula, val.c_str(), sizeof(cedula)-1); cedula[sizeof(cedula)-1] = '\0';
    }

    void setNombre(const string& val) {
        strncpy(nombre, val.c_str(), sizeof(nombre)-1); nombre[sizeof(nombre)-1] = '\0';
    }

    void setVehiculo(const string& val) {
        strncpy(vehiculo, val.c_str(), sizeof(vehiculo)-1); vehiculo[sizeof(vehiculo)-1] = '\0';
    }

    void setModelo(const string& val) {
        strncpy(modelo, val.c_str(), sizeof(modelo)-1); modelo[sizeof(modelo)-1] = '\0';
    }

    void setPlaca(const string& val) {
        strncpy(placa, val.c_str(), sizeof(placa)-1); placa[sizeof(placa)-1] = '\0';
    }


    void setIdSectorActual(int id) {
        idSectorActual = id;
    }

    void setDisponible(bool d) {
        disponible = d;
    }

    void incrementarServicios() {
        serviciosCompletados++;
    }


    void mostrar() const {
        cout << "Placa: " << placa << " | Repartidor: " << nombre << " | Vehiculo: " << vehiculo << " (" << modelo << ") | Sector Actual: " << idSectorActual << " | " << (disponible ? "Disponible" : "Ocupado") << endl;
    }
};

#endif
