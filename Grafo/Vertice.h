#ifndef VERTICE_H
#define VERTICE_H

class Vertice {
private:
    int id;  // Identificador único del vértice

public:
    // Constructor
    Vertice(int id) : id(id) {}

    // Obtener el identificador del vértice
    int obtenerId() const {
        return id;
    }

    // Sobrecargar el operador de igualdad para comparar vértices
    bool operator==(const Vertice& otro) const {
        return id == otro.id;
    }
};

#endif // VERTICE_H