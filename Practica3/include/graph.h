#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <sstream>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>
#include "node.h"

template<typename T>
class Node;

/**
 * @brief Represents an undirected graph with no whwights on its edges and in
 * which every node is identified by a unique tag.
 */
template<typename T>
class Graph {
public:    
    /**
     * @brief Acceses the node with value val of the graph, if it doesn't exist
     * it creates it.
     * @retrun a reference to that node with tag value.
     */
    Node<T> & node(T value) {
        Node<T> inserting = Node<T>(value, *this);
        auto insertion_res = nodes.insert({value, inserting});
        return (*(insertion_res.first)).second;
    }

    /**
     * @pre There must be a node in the graph
     * @return Returns the node with smaller tag
     */
    Node<T> & getNode() {
        return (*(nodes.begin())).second;
    }
    
    /**
     * @return true if the graph contains a node with value val
     */
    bool has(T value) const{
        return nodes.find(value) != nodes.end();
    }
    
    /**
     * @return a list with pointers to all nodes
     */
    std::list<Node<T>*> getNodes() {
        std::list<Node<T>*> nodes_ret;
        
        for(std::pair<const T, Node<T>> &ele : nodes) {
            nodes_ret.push_back(&(ele.second));
        }
        
        return nodes_ret;
    }
    std::list<const Node<T>*> getNodes() const {
        std::list<const Node<T>*> nodes_ret;
        
        for(const std::pair<const T, Node<T>> &ele : nodes) {
            nodes_ret.push_back(&(ele.second));
        }
        
        return nodes_ret;
    }
    
    /**
     * @brief removes a node from the graph
     * @return true if and only if the node has been removed
     */
    bool deleteNode(Node<T> &node) {
        if(node.graph != this) return false;
        
        node.removeAllEdges();
        node.graph = nullptr;
        nodes.erase(*node);
        return true;
    }
    
    /**
     * @brief removes a node from the graph
     * @return true if and only if the node has been removed
     */
    bool deleteNode(T value) {
        auto it = nodes.find(value);
        if (it == nodes.end()) return false;
        
        return deleteNode((*it).second);
    }
    
    /**
     * @brief Inizializes the graph as an Euler graph, that is it is conex, and
     * has en Eurler circuit
     * @param tags The tags of the nodes with wich the graph will be initialized
     * @param density_of_edges The generated graph has at least tags.size() - 1.
     * Which is the minimum for an Euler graph. desisty_of_edges specifies how
     * many more edges should be added. It adds round(density_of_edges * tags.size())
     * edges.
     * @param seed seed for the random number generation
     */
    void initializeAsEulerGraph(const std::set<T> & tags, float density_of_edges) {
        clear();
        if(tags.size() == 0) return;
        
        std::vector<Node<T> *> inserted;
        for(const T & tag : tags) {
            Node<T> & inserting = node(tag);
            
            if (inserted.size() == 0) {
                inserted.push_back(&inserting);
                continue;
            }
            
            inserting.createEdgeTo(*(inserted.back()));
            inserted.push_back(&inserting);
        }
        (*(inserted.front())).createEdgeTo(*(inserted.back()));
        
        
        const int EDGES_TO_POSITION = std::round(density_of_edges * inserted.size());
        const float AVARAGE_LENGTH_OF_CYCLE = node_n() * 0.6;
        float expected_num_of_cycles = EDGES_TO_POSITION / AVARAGE_LENGTH_OF_CYCLE;
        std::poisson_distribution<> cycles_poiss(expected_num_of_cycles - 1);

        std::random_device rd;
        std::mt19937 gen(rd());
        int num_of_cycles = std::min(EDGES_TO_POSITION, cycles_poiss(gen) + 1);
        
        int edges_left = EDGES_TO_POSITION;argument discards qualifiers bracket operator
        std::normal_distribution<> cycle_length_normal;
        for(int cycle=1; cycle<=num_of_cycles - 1; cycle++) {
            int cycles_left = num_of_cycles - cycle; // without counting this one
            double next_expected_length = ((double)edges_left) / (cycles_left + 1);
            std::normal_distribution<double>::param_type new_params(
                    (double)next_expected_length, next_expected_length * 0.4);
            cycle_length_normal.param(new_params);
            int max_cycle_length = edges_left - cycles_left;
            int cycle_length = std::round(std::clamp(cycle_length_normal(gen), 
                                                     1.0, (double)max_cycle_length));
            
            addCycle(cycle_length);
            
            edges_left -= cycle_length;
        }
        addCycle(edges_left);
    }
    
    /**
     * @return the number of nodes
     */
    int node_n() const {
        return nodes.size();
    }
    
    /**
     * @return the number of edges
     */
    int edge_n() const {
        int total = 0;
        
        for(const std::pair<const T, Node<T>> & ele : nodes) {
            total += ele.second.degree();
        }
        
        return total/2;
    }
    
    /**
     * @brief Empties the graph.
     */
    void clear(){
        nodes.clear();
    }
    
    Graph<T> & operator=(const Graph<T> &other) const {
        std::stringstream in_out;
        in_out << other;
        in_out >> *this;
        return *this;
    }
    
    bool operator==(Graph &other) const {
        std::stringstream me_str;
        std::stringstream other_str;
        me_str << *this;
        other_str << other;
        return me_str.str() == other_str.str();
    }
    
    
    /**
     * @returns an string with a template of the input format for number_of_nodes
     * nodes.
     */
    static std::string templateInput(int number_of_nodes) {
        std::stringstream ret_string;
        ret_string << "Number of nodes: " << number_of_nodes << "\n";
        ret_string << "\n";
        
        for(int node_n = 1; node_n <= number_of_nodes; node_n++) {
            ret_string << "Tag: _tag" << node_n << "_\n";
            ret_string << "Number of edges: _num_of_edges_node_" << node_n << "_\n";
            ret_string << "Has edges to nodes:\n";
            ret_string << "_tag_connection_1_node" << node_n << "_ ... _tag_last_connection_node_" << node_n << "_\n\n";
        }
        
        return ret_string.str();
    }
    
    /**
     * @brief Saves the graph to a file 
     * @return true if and only if it has been succesfully saved
     */
    bool save(std::string file_route) {
        std::ofstream out;
        out.open(file_route);
        if(not out.is_open()) return false;
        out << *this;
        out.close();
        return true;
    }
    
    /**
     * @brief Loads the graph from a file 
     * @return true if and only if it has been succesfully loaded
     */
    bool load(std::string file_route) {
        std::ifstream in;
        in.open(file_route);
        if(not in.is_open()) return false;
        in >> *this;
        in.close();
        return true;
    }
    
private:
    std::map<T, Node<T>> nodes;
    
    /**
     * @brief Adds a random cycle to the graph of the specified length
     */
    void addCycle(int length) {
        std::list<Node<T> *> nodes_l = getNodes();
        std::vector<Node<T> *> nodes_v(nodes_l.begin(), nodes_l.end());
        
        Node<T> & first_node = *(nodes_v[rand() % nodes_v.size()]);
        Node<T> * last_node = &first_node;
        for(int i = 0; i<length-1; i++) {
            Node<T> & next_node = *(nodes_v[rand() % nodes_v.size()]);
            (*last_node).createEdgeTo(next_node);
            last_node = &next_node;
        }
        if(length > 0) (*last_node).createEdgeTo(first_node);
    }
};



/*
    Outputs the graph a graph with N nodes with the following format:
    
    Number of nodes: <Numebr of nodes>
    
    Node 1:
    Tag: <node1's tag> 
    Number of edges: <node1's number of edges>
    Has edges to nodes (repeat if more than one edge should be created):
    <node1's conexion1's tag> ... <node1's last_conexion's tag>
    
    ...
    
    Node N:
    Tag: <nodeN's tag> 
    Number of edges: <nodeN's number of edges>
    Has edges to nodes (repeats if more than one edge for the same node exists):
    <nodeN's conexionN's tag> ... <nodeN's last_conexion's tag>
*/
template<typename T>
std::ostream & operator <<(std::ostream & out, const Graph<T> & graph) {
    out << "Number of nodes: " << graph.node_n() << "\n";
    out << "\n";
    
    std::list<const Node<T>*> nodes = graph.getNodes();
    for(const Node<T> * node_ptr : nodes) {
        const Node<T> & actual_node = *node_ptr;
        std::list<const Node<T> *> connections = actual_node.getConnections();
        
        out << "Tag: " << *actual_node << "\n";
        out << "Number of edges: " << actual_node.degree() << "\n";
        out << "Has edges to nodes:\n";
        
        for(const Node<T> * connection_ptr : connections) {
            const Node<T> & actual_connection = *connection_ptr;
            out << *actual_connection << " ";
        }
        out << "\n";
        out << "\n";
    }
    
    return out;
}

/*
Loads to a graph from the output of the >> operator.
*/
template<typename T>
std::istream & operator >>(std::istream & in, Graph<T> & graph) {
    graph.clear();
    
    std::string _;
    
    int n_nodes;
    std::getline(in, _, ':');
    in >> n_nodes;
    
    for(int n_node=1; n_node<=n_nodes; n_node++) {
        T node_tag;
        int num_of_edges;
        
        std::getline(in, _, ':');
        in >> node_tag;
        std::getline(in, _, ':');
        in >> num_of_edges;
        std::getline(in, _, ':');
        
        graph.node(node_tag);
        
        std::set<T> should_insert_again;
        for(int n_connection = 0; n_connection < num_of_edges; n_connection++) {
            T connection;
            in >> connection;
            if(connection == node_tag)  {
                in >> connection;
                n_connection++;
            }
            
            if (should_insert_again.find(connection) != should_insert_again.end()) {
                graph.node(node_tag).createEdgeTo(connection);
                continue;
            }
            
            if (graph.node(node_tag).hasEdgeTo(connection)) continue;
            
            graph.node(node_tag).createEdgeTo(connection);
            should_insert_again.insert(connection);
        }
    }
    
    return in;
}

#endif /* __GRAPH__ */

