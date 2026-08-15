#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
#include <iostream>
#include "Repartidor.h"

using namespace std;


struct Solicitud {
    string cedulaCliente;
    int idOrigen;
    int idDestino;


    Solicitud(string ced = "", int orig = 0, int dest = 0)
        : cedulaCliente(ced), idOrigen(orig), idDestino(dest) {}
};


struct NodoCola {
    Solicitud info;
    NodoCola* sig;

    NodoCola(Solicitud s) : info(s), sig(nullptr) {}
};


class ColaClientes {
private:
    NodoCola* frente;
    NodoCola* final;

public:
    ColaClientes() : frente(nullptr), final(nullptr) {}

    bool estaVacia() const {
        return frente == nullptr;
    }


    void encolar(Solicitud s) {
        NodoCola* nuevo = new NodoCola(s);
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->sig = nuevo;
            final = nuevo;
        }
    }

    bool desencolar(Solicitud& s) {
        if (estaVacia()) return false;
        NodoCola* aux = frente;
        s = aux->info;
        frente = frente->sig;
        if (frente == nullptr) final = nullptr;
        delete aux;
        return true;
    }


    bool obtenerFrente(Solicitud& s) const {
        if (estaVacia()) return false;
        s = frente->info;
        return true;
    }
};
struct NodoListaRep {
    Repartidor info;
    NodoListaRep* sig;

    NodoListaRep(Repartidor r) : info(r), sig(nullptr) {}
};


class ListaRepartidores {
private:
    NodoListaRep* cabeza;

public:
    ListaRepartidores() : cabeza(nullptr) {}

    bool estaVacia() const { return cabeza == nullptr; }


    void insertarOrdenado(Repartidor r) {
        NodoListaRep* nuevo = new NodoListaRep(r);


        if (cabeza == nullptr || r.getTiempoEnMinutos() < cabeza->info.getTiempoEnMinutos()) {
            nuevo->sig = cabeza;
            cabeza = nuevo;
            return;
        }


        NodoListaRep* actual = cabeza;
        while (actual->sig != nullptr && actual->sig->info.getTiempoEnMinutos() <= r.getTiempoEnMinutos()) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }

    // Recorrer y mostrar los repartidores de la lista
    void mostrar() const {
        NodoListaRep* aux = cabeza;
        int i = 1;
        while (aux != nullptr) {
            cout << i << ". ";
            aux->info.mostrar();
            aux = aux->sig;
            i++;
        }
    }

    bool obtenerPorIndice(int indice, Repartidor& r) {
        NodoListaRep* aux = cabeza;
        int i = 1;
        while (aux != nullptr) {
            if (i == indice) {
                r = aux->info;
                return true;
            }
            aux = aux->sig;
            i++;
        }
        return false;
    }
};

#endif