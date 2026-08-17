#include "Grafo.h"

// Constructor: Crea y prepara la matriz dinámica.
Grafo::Grafo(int nSectores) {
    this->numSectores = nSectores;

    // 1. Reservar memoria para el array de filas (un array de punteros a entero).
    matrizAdyacencia = new int*[numSectores];

    // 2. Para cada fila, reservar memoria para sus columnas.
    for (int i = 0; i < numSectores; ++i) {
        matrizAdyacencia[i] = new int[numSectores];
    }

    // 3. Inicializar la matriz con los valores por defecto.
    for (int i = 0; i < numSectores; ++i) {
        for (int j = 0; j < numSectores; ++j) {
            if (i == j) {
                matrizAdyacencia[i][j] = 0; // La distancia de un nodo a sí mismo es 0.
            } else {
                matrizAdyacencia[i][j] = INT_MAX; // Usamos INT_MAX para representar "infinito".
            }
        }
    }
    std::cout << "Grafo y matriz de adyacencia creados e inicializados." << std::endl;
}

// Destructor: Libera toda la memoria reservada para la matriz.
Grafo::~Grafo() {
    std::cout << "Liberando memoria de la matriz de adyacencia" << std::endl;

    // 1. Liberar la memoria de cada array de columnas.
    for (int i = 0; i < numSectores; ++i) {
        delete[] matrizAdyacencia[i];
    }

    // 2. Liberar la memoria del array de filas.
    delete[] matrizAdyacencia;

    std::cout << "Memoria liberada correctamente." << std::endl;
}

// Método para agregar una arista (conexión) al grafo
void Grafo::agregarArista(int origen, int destino, int peso) {
    // Asegurarse de que los IDs estén dentro de los límites de la matriz
    if (origen >= 0 && origen < numSectores && destino >= 0 && destino < numSectores) {
        matrizAdyacencia[origen][destino] = peso;
        matrizAdyacencia[destino][origen] = peso; // Es un grafo no dirigido
    }
}

void Grafo::encontrarRutaMinima(int origen, int destino) {

    // Vector para almacenar la distancia mínima desde el origen a cada nodo.
    std::vector<int> distancias(numSectores, INT_MAX);
    // Vector para marcar los nodos cuya distancia mínima ya es definitiva.
    std::vector<bool> visitados(numSectores, false);
    // Vector para reconstruir la ruta. previo[i] almacena el nodo anterior a i en la ruta.
    std::vector<int> previo(numSectores, -1);

    // La distancia del origen a sí mismo es siempre 0.
    distancias[origen] = 0;

    // --- ALGORITMO DE DIJKSTRA ---
    // Repetimos el proceso para todos los nodos.
    for (int i = 0; i < numSectores - 1; ++i) {

        // --- PASO A: Encontrar el nodo no visitado con la distancia mínima ---
        int distanciaMinima = INT_MAX;
        int sectorActual = -1;

        for (int j = 0; j < numSectores; ++j) {
            if (!visitados[j] && distancias[j] < distanciaMinima) {
                distanciaMinima = distancias[j];
                sectorActual = j;
            }
        }


        // Si no se encuentra un sector alcanzable, podemos parar.
        if (sectorActual == -1) break;

        // --- PASO B: Marcar el nodo actual como visitado ---
        // Ya no volveremos a procesar este nodo, su distancia es definitiva.
        visitados[sectorActual] = true;

        // --- PASO C: Actualizar las distancias de los vecinos ---
        // "Relajamos" las aristas: vemos si podemos acortar el camino a los vecinos a través del nodo actual.
        for (int vecino = 0; vecino < numSectores; ++vecino) {

            // Condiciones:
            // 1. El vecino no ha sido visitado aún.
            // 2. Existe una conexión directa entre el sector actual y el vecino.
            // 3. El nuevo camino (origen -> sectorActual -> vecino) es más corto que el que teníamos registrado para el vecino.
            if (!visitados[vecino] && matrizAdyacencia[sectorActual][vecino] != INT_MAX &&
                distancias[sectorActual] + matrizAdyacencia[sectorActual][vecino] < distancias[vecino])
            {
                // ¡Encontramos una ruta mejor! La actualizamos.
                distancias[vecino] = distancias[sectorActual] + matrizAdyacencia[sectorActual][vecino];
                previo[vecino] = sectorActual; // Anotamos que para llegar al vecino, vinimos desde sectorActual.
            }
        }

    }

    // --- 3. IMPRESIÓN DE RESULTADOS ---
    if (distancias[destino] == INT_MAX) {
        std::cout << "No se pudo encontrar una ruta desde el sector " << origen << " al sector " << destino << "." << std::endl;
    } else {
        std::cout << "\n--- RUTA OPTIMA ENCONTRADA ---" << std::endl;
        std::cout << "Distancia total del recorrido: " << distancias[destino] << " km." << std::endl;
        std::cout << "Secuencia de la ruta: ";

        // Usamos una pila (stack) para invertir la ruta y mostrarla en el orden correcto.
        std::stack<int> ruta;
        int paso = destino;
        while (paso != -1) {
            ruta.push(paso);
            paso = previo[paso];
        }

        // Imprimimos la ruta desde el origen al destino.
        while (!ruta.empty()) {
            std::cout << ruta.top();
            ruta.pop();
            if (!ruta.empty()) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}