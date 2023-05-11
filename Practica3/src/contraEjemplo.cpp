/*
Compile from the project's root folder with:
g++ ./include/* ./src/contraEjemplo.cpp -o ./bin/contraEjemplo.bin

Execute it from the project's root folder with:
./bin/contraEjemplo.bin
*/

#include <iostream>
#include "../include/graph.h"
#include "../include/node.h"
#include "../include/camino_de_euler.h"

using namespace std;

int main() {
    Graph<int> contra_ejemplo;
    
    for(int heptagono = 0; heptagono < 3; heptagono++) {
        for(int nodo = heptagono*7; nodo < (heptagono+1)*7; nodo++) {
            for(int conexion = nodo+1; conexion < (heptagono+1)*7; conexion++) {
                contra_ejemplo.node(nodo).createEdgeTo(conexion);
            }
        }
    }
    
    contra_ejemplo.node(0).createEdgeTo(7);
    contra_ejemplo.node(7).createEdgeTo(14);
    contra_ejemplo.node(14).createEdgeTo(0);
    
    cout << contra_ejemplo;
    
    cout << "Ejes del grafo: " << contra_ejemplo.edge_n() << endl;
    list<Node<int>*> euler_circuit = findEulerCircuit<int>(contra_ejemplo);    
    cout << "Tamaño del circuito: " << euler_circuit.size() << endl;
}
