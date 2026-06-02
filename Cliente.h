#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class Cliente {
private:
    char cedula[15];
    char nombre[50];
    char telefono[20];
    int serviciosRealizados;

public:
    Cliente(string ced = "", string nom = "", string tel = "") {
        setCedula(ced);
        setNombre(nom);
        setTelefono(tel);
        serviciosRealizados = 0;
    }

    const char * getCedula() const {
        return cedula;
    }

    const char * getNombre() const {
        return nombre;
    }
    const char * getTelefono() const {
        return telefono;
    }

    int getServiciosRealizados() const {
        return serviciosRealizados;
    }

    void setCedula(const string& val) {
        strncpy(cedula, val.c_str(), sizeof(cedula)-1); cedula[sizeof(cedula)-1] = '\0';
    }

    void setNombre(const string& val) {
        strncpy(nombre, val.c_str(), sizeof(nombre)-1); nombre[sizeof(nombre)-1] = '\0';
    }

    void setTelefono(const string& val) {
        strncpy(telefono, val.c_str(), sizeof(telefono)-1); telefono[sizeof(telefono)-1] = '\0';
    }

    void incrementarServicios() {
        serviciosRealizados++;
    }

    void mostrar() const {
        cout << "Cedula: " << cedula << " | Nombre: " << nombre << " | Tel: " << telefono << " | Pedidos: " << serviciosRealizados << endl;
    }
};

#endif
