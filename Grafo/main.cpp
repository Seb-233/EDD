#include <iostream>
#include "grafo.h"

using namespace std;

int main() {
    Grafo grafo;

    // Agregar vértices
    grafo.agregarVertice(1);
    grafo.agregarVertice(2);

    // Agregar arista entre vértices
    grafo.agregarArista(1, 2);

    // Imprimir el grafo actual
    grafo.imprimirGrafo();

    return 0;
}
