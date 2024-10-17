#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include "Vertice.h"
#include "Arista.h"

using namespace std;

class Grafo {
private:
    vector<Vertice*> vertices;  // Lista de punteros a vértices
    vector<Arista*> aristas;    // Lista de punteros a aristas

public:
    // Destructor para liberar memoria
    ~Grafo() {
        for (auto vertice : vertices) {
            delete vertice; // Liberar memoria de cada vértice
        }
        for (auto arista : aristas) {
            delete arista; // Liberar memoria de cada arista
        }
    }

    // Agregar un vértice al grafo
    void agregarVertice(int id) {
        Vertice* nuevoVertice = new Vertice(id);
        if (!buscarVertice(id)) {
            vertices.push_back(nuevoVertice);
        } else {
            cout << "Vertice con id " << id << " ya existe." << endl;
            delete nuevoVertice; // Liberar la memoria del vértice no agregado
        }
    }

    // Agregar una arista al grafo
    void agregarArista(int id1, int id2) {
        if (!buscarVertice(id1) || !buscarVertice(id2)) {
            cout << "Ambos vertices deben existir para crear una arista." << endl;
            return;
        }

        Vertice* vertice1 = obtenerVerticePorId(id1);
        Vertice* vertice2 = obtenerVerticePorId(id2);

        Arista* nuevaArista = new Arista(vertice1, vertice2);
        if (!buscarArista(id1, id2)) {
            aristas.push_back(nuevaArista);
        } else {
            cout << "Arista entre " << id1 << " y " << id2 << " ya existe." << endl;
            delete nuevaArista; // Liberar la memoria de la arista no agregada
        }
    }

    // Buscar un vértice por su id
    bool buscarVertice(int id) const {
        for (const auto& vertice : vertices) {
            if (vertice->obtenerId() == id) {
                return true;
            }
        }
        return false;
    }

    // Buscar un vértice por su id y devolver el puntero
    Vertice* obtenerVerticePorId(int id) const {
        for (const auto& vertice : vertices) {
            if (vertice->obtenerId() == id) {
                return vertice;
            }
        }
        return nullptr; // Devuelve nullptr si no se encuentra el vértice
    }

    // Buscar una arista entre dos vértices
    bool buscarArista(int id1, int id2) const {
        Vertice* vertice1 = obtenerVerticePorId(id1);
        Vertice* vertice2 = obtenerVerticePorId(id2);
        for (const auto& arista : aristas) {
            if (*arista == Arista(vertice1, vertice2)) {
                return true;
            }
        }
        return false;
    }

    // Imprimir el grafo actual (vértices y aristas)
    void imprimirGrafo() const {
        cout << "Vertices:" << endl;
        for (const auto& vertice : vertices) {
            cout << "  Vertice " << vertice->obtenerId() << endl;
        }

        cout << "Aristas:" << endl;
        for (const auto& arista : aristas) {
            cout << "  Arista entre " << arista->obtenerVertice1()->obtenerId() 
                 << " y " << arista->obtenerVertice2()->obtenerId() << endl;
        }
    }
};

#endif // GRAFO_H