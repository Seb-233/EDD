/**********************************************
Autores: David León, Sebastian Mendez, Juan Manuel Lopez, Sebastián Almanza
Materia: Estructura de Datos
Fecha 06-11-2024
Tema: Laboratorio grafos - ciclo de euler
***********************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int dest;
    int peso;
    bool used; // Para marcar si una arista ha sido usada
};

typedef vector<vector<Edge>> Graph;

void addEdge(Graph &graph, int u, int v, int peso) {
    graph[u].push_back({v, peso, false});
    graph[v].push_back({u, peso, false});  //grafo no dirigido
}

void findEulerianCycle(Graph &graph, int start) {
    stack<int> path;
    vector<int> cycle;
    path.push(start);

    while (!path.empty()) {
        int u = path.top();
        bool foundEdge = false;

        for (auto &edge : graph[u]) {
            if (!edge.used) {
                edge.used = true;
                for (auto &revEdge : graph[edge.dest]) {
                    if (revEdge.dest == u && !revEdge.used) {
                        revEdge.used = true;
                        break;
                    }
                }
                path.push(edge.dest);
                foundEdge = true;
                break;
            }
        }

        if (!foundEdge) {
            cycle.push_back(u + 1);
            path.pop();
        }
    }

    // Imprimir el ciclo de Euler
    cout << "Ciclo de Euler: ";
    for (int v : cycle) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    int n = 7;
    Graph graph(n);

    addEdge(graph, 0, 1, 1);  
    addEdge(graph, 0, 2, 7);  
    addEdge(graph, 0, 3, 6);  
    addEdge(graph, 1, 2, 9);  
    addEdge(graph, 1, 5, 3);  
    addEdge(graph, 2, 4, 2);  
    addEdge(graph, 2, 5, 3);  
    addEdge(graph, 2, 6, 1);  
    addEdge(graph, 3, 4, 2);  
    addEdge(graph, 4, 6, 5);  
    addEdge(graph, 5, 6, 3);  

    cout << "Ciclo de Euler:\n";
    findEulerianCycle(graph, 0); 

    return 0;
}