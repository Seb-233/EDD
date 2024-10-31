/*
 * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
 *  Laboratorio Dijkstra Estructuras Lineales
 *  Autor: 
 *  Johan Sebastian Mendez Ibarra 
 *  Descripción:
 *  Algoritmos de dijkstra 
 * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
 */

#include <iostream>
#include <climits>  // Necesario para usar INT_MAX
using namespace std;

// Función para encontrar el vértice con la distancia mínima
// que aún no ha sido procesado en el conjunto Tset
int miniDist(int distance[], bool Tset[]) {
    int minimum = INT_MAX;  // Variable para almacenar el valor mínimo encontrado
    int ind;                // Índice del vértice con distancia mínima

    // Recorremos todos los vértices (en este caso hay 7)
    for (int k = 0; k < 7; k++) {
        // Si el vértice no ha sido procesado y su distancia es menor que el mínimo actual
        if (Tset[k] == false && distance[k] <= minimum) {
            minimum = distance[k];  // Actualizamos el valor mínimo
            ind = k;                // Actualizamos el índice
        }
    }
    return ind;  // Retornamos el índice del vértice con la distancia mínima
}

// Implementación del algoritmo de Dijkstra
void DijkstraAlgo(int graph[7][7], int src) {
    int distance[7];  // Arreglo para almacenar la distancia mínima desde la fuente
    bool Tset[7];     // Arreglo para indicar si un vértice ha sido procesado

    // Inicializamos todas las distancias como infinitas y todos los vértices como no procesados
    for (int k = 0; k < 7; k++) {
        distance[k] = INT_MAX;
        Tset[k] = false;
    }

    // La distancia del vértice fuente a sí mismo es 0
    distance[src] = 0;

    // Iteramos para encontrar las distancias mínimas para todos los vértices
    for (int k = 0; k < 7; k++) {
        int m = miniDist(distance, Tset);  // Obtenemos el vértice con distancia mínima
        Tset[m] = true;                    // Marcamos el vértice como procesado

        // Actualizamos las distancias de los vértices adyacentes no procesados
        for (int k = 0; k < 7; k++) {
            // Si el vértice k no ha sido procesado, existe una arista desde m a k,
            // y la distancia acumulada es menor que la distancia actual, actualizamos
            if (!Tset[k] && graph[m][k] && distance[m] != INT_MAX 
                && distance[m] + graph[m][k] < distance[k]) {
                distance[k] = distance[m] + graph[m][k];
            }
        }
    }

    // Mostramos los resultados: la distancia mínima desde la fuente hasta cada vértice
    cout << "Vertice \t\t Distancia desde la fuente al Vertice" << endl;
    for (int k = 0; k < 7; k++) {
        char str = 65 + k;  // Convertimos el índice a una letra (A, B, C, etc.)
        cout << str << "\t\t\t" << distance[k] << endl;
    }
}

int main() {
    // Definimos el grafo como una matriz de adyacencia de 7x7
    int graph[7][7] = {
        {0, 2, 4, 0, 0, 0, 0},
        {2, 0, 0, 5, 0, 0, 0},
        {4, 0, 0, 8, 0, 0, 0},
        {0, 5, 8, 0, 10, 15, 0},
        {0, 0, 0, 10, 0, 6, 2},
        {0, 0, 0, 15, 6, 0, 6},
        {0, 0, 0, 0, 2, 6, 0}
    };

    // Ejecutamos el algoritmo de Dijkstra desde el vértice fuente (A = 0)
    DijkstraAlgo(graph, 0);

    return 0;
}
