#ifndef SECTOR_H
#define SECTOR_H

#include <string>
#include <iostream>

using namespace std;

class Sector {
private:
    int id;
    char nombre[50];

public:
    Sector(int id = 0, string n = "") : id(id) {
        setNombre(n);
    }

    int getId() const {
        return id;
    }
    string getNombre() const {
        return nombre;
    }


    void setId(int _id) {
        id = _id;
    }

    void setNombre(const string& n) {
        size_t len = n.copy(nombre, sizeof(nombre) - 1);
        nombre[len] = '\0';
    }

    void mostrar() const {
        cout << "ID: " << id << " | Sector: " << nombre << endl;
    }
};

#endif
