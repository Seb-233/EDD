/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/****************
Autor: David León
Materia: Estructura de Datos
Fecha 06-11-2024
Tema: Laboratorio grafos
*****************/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;


struct Edge {
    int dest;
    int peso;
};

typedef vector<vector<Edge>> Graph;


void addEdge(Graph &graph, int u, int v, int peso) {
    graph[u].push_back({v, peso});
    graph[v].push_back({u, peso});  //grafo no dirigido
}

void dijkstra(const Graph &graph, int src) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[src] = 0;

    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : graph[u]) {
            int v = edge.dest;
            int peso = edge.peso;
            
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    
    cout << "Nodo origen: " << src + 1 << "\n";
    for (int i = 0; i < n; i++) {
        if (i != src) {
            cout << "1->" << i + 1 << " Distancia: " << dist[i] << " Camino: ";
            stack<int> path;
            for (int v = i; v != -1; v = parent[v]) {
                path.push(v + 1);
            }
            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
    }
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

    cout << "Algoritmo de Dijkstra:\n";
    dijkstra(graph, 0); 

    return 0;
}
