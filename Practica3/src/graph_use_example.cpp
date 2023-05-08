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

using namespace std;

int main() {
    Graph<int> example_graph;
    
    // Creating new nodes:
    // You can only create and delete nodes from the graph they are in
    Node<int> &node1 = example_graph.node(1);
    Node<int> &node2 = example_graph.node(2);
    example_graph.node(-5);
    example_graph.node(10);
    
    // Acces nodes, and their tags
    int tag_node2 = *node2;
    int tag_node1 = *(example_graph.node(1));
    
    // Conecting nodes:
    node1.createEdgeTo(node2);
    node2.createEdgeTo(example_graph.node(-5));
    example_graph.node(10).createEdgeTo(1);
    example_graph.node(10).createEdgeTo(10);
    example_graph.node(-5).createEdgeTo(10);
    node1.createEdgeTo(1);
    node1.createEdgeTo(1);
    
    // You can connect to a node that doesn't exist, it gets created:
    Node<int> & node3 = node1.createEdgeTo(3);
    
    // Removing connections
    example_graph.node(10).removeEdgeTo(10);
    example_graph.node(3).removeAllEdges();
    
    // Acces node information
    int degree2 = node2.degree();
    list<Node<int> *> connections1 = node1.getConnections();
    node1.hasEdgeTo(1);
    node1.hasEdgeTo(node3);
    Graph<int> & example_graph_ref = node1.getGraph();
    
    // Deleting nodes
    // You can only create and delete nodes from the graph they are in
    example_graph.deleteNode(-5);
    example_graph.deleteNode(node2);
    
    // Accesing graph information
    int number_of_nodes = example_graph.node_n();
    int number_of_edges = example_graph.edge_n();
    list<Node<int>*> nodes = example_graph.getNodes();
       
    // Print graph to estrandart output
    cout << example_graph;
    
    // You could load it from a instream with the same format like this:
    // file >> example_graph;
    
    // It has functions to directlly save and load that ouput to and from a file:
    example_graph.save("./data/example_graph1.txt");
    example_graph.load("./data/example_graph1.txt");
    
    // To obtain a template to create your own graph you can use:
    int node_ammount = 3;
    cout << Graph<int>::templateInput(number_of_nodes);
    
    // In this assignement we are asked to solve problems involving Euler graphs
    // with this function you can create one:
    set<int> etiquetas;
    for(int i=1; i<=100; i++) etiquetas.insert(i);
    Graph<int> euler_graph;
    euler_graph.initializeAsEulerGraph(etiquetas, 2.5f, 0);
    euler_graph.save("./data/example_euler_graph.txt");

    // You can compare and copy graphs
    example_graph = euler_graph;
    if(example_graph == euler_graph) cout << "They are equal" << endl;
    
    // But you musn't do that with nodes
}
