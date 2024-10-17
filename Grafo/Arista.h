#ifndef ARISTA_H
#define ARISTA_H

#include "Vertice.h"

class Arista {
private:
    Vertice* vertice1;
    Vertice* vertice2;

public:
    Arista(Vertice* v1, Vertice* v2) : vertice1(v1), vertice2(v2) {} 


    // Obtener el primer vértice
    Vertice* obtenerVertice1() const {
        return vertice1;
    }

    // Obtener el segundo vértice
    Vertice* obtenerVertice2() const {
        return vertice2;
    }

    // Comparar aristas
    bool operator==(const Arista& otra) const {
        return (vertice1 == otra.vertice1 && vertice2 == otra.vertice2) ||
               (vertice1 == otra.vertice2 && vertice2 == otra.vertice1);
    }
};

#endif // ARISTA_H