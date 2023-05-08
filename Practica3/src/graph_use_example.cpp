/*
Compile from the project's root folder with:
g++ ./include/* ./src/graph_use_example.cpp -o ./bin/graph_use_example.bin

Execute it from the project's root folder with:
./bin/graph_use_example.bin
*/

#include <iostream>
#include <fstream>
#include "../include/graph.h"
#include "../include/node.h"
#include "./algoritmo.cpp"

using namespace std;

void printEulerCircuit(std::list<Node<int>*> circuit) {
    std::cout << "Circuito de Euler encontrado: ";
    for (auto node : circuit) {
        std::cout << *(*node) << " -> ";
    }
    std::cout << "Inicio" << std::endl;
}

int main() {
    // Crear un grafo con nodos de grado par y conexo
    Graph<int> graph;

    // Agregar nodos y aristas
    graph.load("./data/example_euler_graph.txt");

    // Encontrar el circuito de Euler
    std::list<Node<int>*> euler_circuit = findEulerCircuit<int>(graph,1);

    // Imprimir el circuito de Euler
    printEulerCircuit(euler_circuit);
	
    // Agregar un segundo caso de prueba
    Graph<int> graph2;

    graph2.node(1).createEdgeTo(2);
    graph2.node(1).createEdgeTo(3);
    graph2.node(2).createEdgeTo(3);
    graph2.node(2).createEdgeTo(4);
    graph2.node(3).createEdgeTo(4);
    graph2.node(1).createEdgeTo(4);

    std::list<Node<int>*> euler_circuit2 = findEulerCircuit<int>(graph2,3);
    printEulerCircuit(euler_circuit2);

    return 0;
}


