/** DISEÑO PROPUESTO DEL ALGORITMO **/
/*
Inicializar S (una lista para almacenar el circuito de Euler) y Stack (una pila para almacenar los nodos a visitar) como vacíos.
Asumir que G es un grafo conexo de Euler con nodos y aristas.
Elegir un nodo inicial v que pertenezca a G.
Si el número de nodos en G (|G|) es mayor que 1:
    Insertar v en Stack.
    Mientras Stack no esté vacía:
        Establecer v como el nodo en la cima de Stack.
        Si v tiene aristas no visitadas:
            Para todas las aristas incidentes en v que no hayan sido visitadas, seleccionar una arista a que tenga un nodo w con el mayor número de aristas incidentes no visitadas.
            Insertar w en Stack.
            Marcar a como visitada.
        Si v no tiene más aristas no visitadas, sacarlo de Stack e insertarlo en S.
    Devolver S como el circuito de Euler encontrado.
Si |G| es igual a 1, informar que no es un grafo válido (solo tiene un vértice).

Notas:
v: Corresponde al nodo actual en la iteración.
w: Es el nodo con menos incidencias.
| |: Indica el tamaño, ya sea de vértices o aristas según el contexto.
Al seleccionar una arista a, si para todas las posibles, su nodo w tiene las mismas incidencias, se elegirá una de forma arbitraria, puede ser la primera o una aleatoria para que haya variación en los caminos.

/** MIS NOTAS **/
/*
1.2. Diseñe las componentes greedy del algoritmo:
Inicialización: Se selecciona un nodo inicial arbitrariamente y se inicializan las estructuras de datos necesarias para almacenar el circuito de Euler (la lista de nodos visitados) y la pila de nodos a visitar.

Función de selección: En cada paso, se selecciona el siguiente nodo a visitar como el nodo adyacente al nodo actual que tiene el mayor número de aristas incidentes no visitadas. Si hay varios nodos que cumplen este criterio, se selecciona uno arbitrariamente. Si el nodo actual no tiene nodos adyacentes no visitados, se retrocede al nodo anterior en la pila.

Función de factibilidad: Se verifica que el nodo seleccionado sea adyacente al nodo actual y que la arista que los conecta no haya sido visitada antes. Si el nodo seleccionado no cumple estos criterios, se selecciona un nodo diferente.

Función de solución: Se verifica si se han visitado todas las aristas del grafo. Si es así, se ha encontrado un circuito de Euler y se devuelve la lista de nodos visitados.

Función de objetivo: No es necesario establecer una función de objetivo para este problema, ya que el objetivo es simplemente encontrar un circuito de Euler, si existe. No hay una "mejor" solución en el sentido de que algunas soluciones tengan un valor objetivo más alto que otras. Sin embargo, el enfoque greedy de seleccionar el nodo con el mayor número de aristas incidentes no visitadas en cada paso tiene como objetivo maximizar la probabilidad de encontrar un circuito de Euler, si existe.

Implementación del algoritmo:
/** ASUMO EN TODA REGLA QUE TRABAJAMOS CON NODOS DE GRADO PAR Y CONEXOS **/

#include <iostream>
#include <stack>
#include "../include/graph.h"
#include "../include/node.h"

template <typename T>
bool esConexo(Graph<T>& graph, Node<T>* nodoInicial, Node<T>* nodoAComprobar) {
/*
iniciamos la lista con el nodo

mientras familiares != comprobados: SE ALTERA ENTRE LAS LISTAS DE LOS DOS NODOS INICIALES
    cojemos uno en familiares que no este en comprobados
    para cada vecino de este nodo:
        comprobamos que no este en familiares del otro nodo inicial -> SI LO ESTA ES CONEXO
        lo metemos en familiares

SI FAMILIARES == COMPROBADOS Y NO TIENE TANTOS NODOS COMO EL GRAFO, NO ES CONEXO
*/
	std::set<Node<T>*> lista1, lista2, lista_comprobados1, lista_comprobados2;
	lista1.insert(nodoInicial);
    auto iterador_lista1 = lista1.begin();
    auto iterador_lista2 = lista2.begin();
    Node<T>* nodoActual;
	
	while(lista1.size() != lista_comprobados1.size()) {
        // Para cada nodo saco los familiares
        nodoActual = *iterador_lista1;
        lista_comprobados1.insert(nodoActual);
        for (Node<T>* vecino : nodoActual->getConnections()) {
            lista1.insert(vecino);
        }
        for (Node<T>* vecino : nodoAComprobar->getConnections()) {
            lista2.insert(vecino);
        }
        // Cojemos uno en familiares que no este en comprobados
        for (auto it = lista1.begin(); it != lista1.end(); ++it) {
            if (lista2.find(*it) != lista_comprobados1.end()) {
                return true;
            }
        }
        iterador_lista1++;
        iterador_lista2++;
	}
	
	return false;
}

template <typename T>
std::list<Node<int>*> findEulerCircuit(Graph<int>& graph) {
    std::list<Node<int>*> circuit; 
    if (graph.node_n() == 0)
        return circuit; 

    std::stack<Node<int>*> stack;
    Node<int>* v = &graph.node(1); 

    stack.push(v);
    while (!stack.empty()) { 
        v = stack.top();
        if (v->degree() > 0) {
            // Encontrar el nodo no visitado con más aristas incidentes no visitadas
            Node<int>* w = nullptr;
            int maxDegree = -1;
            for (Node<int>* connection : v->getConnections()) {
                if (connection->degree() > maxDegree) {
                    v->removeEdgeTo(*connection);
                    if (esConexo<int>(graph,v,connection)) {
		                w = connection;
		                maxDegree = connection->degree();
		            }
		            v->createEdgeTo(*connection);
                }
            }
            stack.push(w);
            v->removeEdgeTo(*w); 
        } else { 
            stack.pop();
            circuit.push_back(v);
        }
    }
    return circuit;
}

/*
// TODO: incluir la eficiencia de esConexo
Eficiencia en el caso peor del algoritmo:
En el peor de los casos, si cada nodo está conectado a todos los demás (es decir, 
el grafo es completamente conexo), entonces esta operación adicional podría hacer que 
la eficiencia del algoritmo sea O(E^2*), ya que para cada arista, puede necesitar revisar 
todas las demás aristas para encontrar el nodo con más aristas incidentes no visitadas.

En la práctica, la eficiencia del algoritmo dependerá del grado medio de los nodos en el grafo. 
Si la mayoría de los nodos tienen un grado relativamente bajo (es decir, están conectados solo a 
unos pocos otros nodos), entonces la eficiencia del algoritmo todavía estará cerca de O(E). 
Sin embargo, si muchos nodos tienen un grado alto, entonces la eficiencia del algoritmo podría acercarse más a O(E^2).

*/				
