#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <climits> // Necesario para INT_MAX
#include <vector>  // Para los arrays de Dijkstra
#include <stack>   // Para reconstruir la ruta

class Grafo {
private:
    int** matrizAdyacencia;
    int numSectores;

public:
    // Constructor
    Grafo(int nSectores);

    // Destructor
    ~Grafo();

    void agregarArista(int origen, int destino, int peso);
    void encontrarRutaMinima(int origen, int destino);

};

#endif //GRAFO_H