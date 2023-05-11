#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <list>
#include <map>
#include "graph.h"

template<typename T>
class Graph;

template<typename T>
class Node {
public:
    /**
     * @breif Getter fot the tag of a node
     */
    T operator *() const {
        return tag;
    }
    
    /**
     * @brief determines if the node is connected to a nother node of value val
     */
    bool hasEdgeTo(T val) const {
        auto it = connections.find(val);
        return it != connections.end();
    }
    
    /**
     * @brief determines if two nodes are connected
     */
    bool hasEdgeTo(const Node<T> &other) const {
        if(other.graph != graph) return false;
        return hasEdgeTo(*other);
    }
    
    /**
     * @brief Adds an edge btween two nodes, if they aren't from the same graph
     * it does nothing
     * @return Returns true if and only if a connection has taken place
     */
    bool createEdgeTo(Node<T> &other) {
        if(other.graph != graph) return false;
        
        connections.insert({*other, &other});
        other.connections.insert({tag, this});
        return true;
    }
    
    /**
     * @brief Adds an edge btwen itself and the other node of value val, if it
     * doesn't exist, it creates it.
     * @returns Returns true node it has created an edge btween
     * @pre node must be in a graph
     */
    Node<T> & createEdgeTo(T val) {
        Node &connected_to = (*graph).node(val);
        createEdgeTo(connected_to);
        return connected_to;
    }
    
    /**
     * @brief Removes the edge btween the node and other if at least one exists
     * @returns Returns true if and only if ta disconection has taken place
     */
    bool removeEdgeTo(Node<T> &other) {
        if(other.graph != graph) return false;
        
        auto it = connections.find(*other);
        if (it == connections.end()) return false;
        connections.erase(it);
        other.connections.erase(other.connections.find(tag));
        return true;
    }
    
    /**
     * @brief Removes the edge btween the node and the other of value val
     * @returns Returns true if and only if ta disconection has taken place
     */
    bool removeEdgeTo(T val) {
        auto it = connections.find(val);
        if(it == connections.end()) return false;
        return removeEdgeTo(*((*it).second));
    }
    
    void removeAllEdges() {
        for(auto it = connections.begin(); it != connections.end(); it++) {
            Node & ele_actual = *((*it).second);
            if (&ele_actual != this) {
                ele_actual.connections.erase(ele_actual.connections.find(tag));
            }
        }
        
        connections.clear();
    }
    
    /**
     * @return Return a list containing a pointer to a node, for each edge
     * connected to the node, if it is connected to itself, the pointer to
     * itself apears twice
     */
    std::list<Node<T>*> getConnections() {
        std::list<Node<T>*> ret_list;
        
        for(std::pair<const T, Node<T>*> & ele : connections) {
            ret_list.push_back(ele.second);
        }
        
        return ret_list;
    }
    std::list<const Node<T>*> getConnections() const{
        std::list<const Node<T>*> ret_list;
        
        for(const std::pair<const T, Node<T>*> & ele : connections) {
            ret_list.push_back(ele.second);
        }
        
        return ret_list;
    }
    
    /**
     * @returns The number of edges coming out of the node
     */
    int degree() const{
        return connections.size();
    }
    
    /**
     * @brief If the node has been destroyed from it's graph it is no longer in
     * it, and it won't be able to perform anny operation
     */
    bool isOnAGraph() const {
        return graph != nullptr;
    }
    
    Graph<T> & getGraph(){
        return *graph;
    }
    
    bool operator < (const Node<T> &other) {
        return tag < other.tag;
    }
    
    Node<T> & operator = (const Node<T> &other) = delete;
    
private:
    
    /**
     * @brief Value of the node 
     */
    T tag;
    std::multimap<T, Node<T> *> connections;
    Graph<T> *graph;
    
    /**
     * @brief Creats a node
     * Only accesible by the class graph
     */
    Node(T _tag, Graph<T> &creator) {
        tag = _tag;
        graph = &creator;
    }
    
    friend class Graph<T>;
    friend class std::map<T, Node<T>>;
};

#endif /* __NODE__ */
