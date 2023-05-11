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
*/

#include <queue>
#include <set>
#include <stack>
#include "./graph.h"
#include "./node.h"

/**
 * @brief Determina si dos elementos en un grafo estarien en la misma componente conexa de eleiminar un eje entre ellos
 * nodo1 y nodo2
 * @pre Existe un eje entre nodo1 y nodo2
 */
template <typename T>
bool mismaComponenteConexaAlDesconectar(const Graph<T>& graph, Node<T>& nodo1, Node<T>& nodo2) {
    /*
    iniciamos la lista con el nodo

    mientras familiares != comprobados: SE ALTERA ENTRE LAS LISTAS DE LOS DOS NODOS INICIALES
        cojemos uno en familiares que no este en comprobados
        para cada vecino de este nodo:
            comprobamos que no este en familiares del otro nodo inicial -> SI LO ESTA ES CONEXO
            lo metemos en familiares

    SI FAMILIARES == COMPROBADOS Y NO TIENE TANTOS NODOS COMO EL GRAFO, NO ES CONEXO
    */
    if (graph.node_n() <= 1 or &nodo1 == &nodo2) return true;

    nodo1.removeEdgeTo(nodo2);

    std::set<Node<T>*> familiares1, familiares2;
    std::queue<Node<T>*> siguiente_a_comprobar1, siguiente_a_comprobar2;
    familiares1.insert(&nodo1);
    siguiente_a_comprobar1.push(&nodo1);
    familiares2.insert(&nodo2);
    siguiente_a_comprobar2.push(&nodo2);
    
    while( (not siguiente_a_comprobar1.empty()) and 
           (not siguiente_a_comprobar2.empty()) ) {
        
        Node<T> &comprobando1 = *(siguiente_a_comprobar1.front());
        siguiente_a_comprobar1.pop();
        std::list<Node<T>*> vecinos1 = comprobando1.getConnections();
        Node<T> * vecino_anterior1_ptr = nullptr;
        for(Node<T>* vecino1_ptr : vecinos1) {
            if (vecino1_ptr == vecino_anterior1_ptr) continue;
            
            if(familiares1.insert(vecino1_ptr).second) {
                if(familiares2.find(vecino1_ptr) != familiares2.end()) {
                    nodo1.createEdgeTo(nodo2);
                    return true;
                }
                
                siguiente_a_comprobar1.push(vecino1_ptr);
            }
            
            vecino_anterior1_ptr = vecino1_ptr;
        }

        Node<T> &comprobando2 = *(siguiente_a_comprobar2.front());
        siguiente_a_comprobar2.pop();
        std::list<Node<T>*> vecinos2 = comprobando2.getConnections();
        Node<T> * vecino_anterior2_ptr = nullptr;
        for(Node<T>* vecino2_ptr : vecinos2) {
            if (vecino2_ptr == vecino_anterior2_ptr) continue;
            
            if(familiares2.insert(vecino2_ptr).second) {
                if(familiares1.find(vecino2_ptr) != familiares1.end()) {
                    nodo2.createEdgeTo(nodo1);
                    return true;
                }
                
                siguiente_a_comprobar2.push(vecino2_ptr);
            }
            
            vecino_anterior2_ptr = vecino2_ptr;
        }
    }
    
    nodo1.createEdgeTo(nodo2);
    return false;
}

/**
 * @pre graph es un grafo de Euler
 * @post elimina todos los ejes del grafo
 */
template <typename T>
std::list<Node<T>*> findEulerCircuit(Graph<T>& graph) {
    std::list<Node<T> *> circuit; 
    if (graph.node_n() == 0)
        return circuit;

    Node<T>* actual = &graph.getNode();
    circuit.push_back(actual);

    while(actual->degree() > 0) {
        std::list<Node<T> *> connections = actual->getConnections(); 
        auto connection_candidate = connections.begin();
        
        if (actual->degree() == 1) {
            actual->removeEdgeTo(**connection_candidate);
            circuit.push_back(*connection_candidate);
            actual = *connection_candidate;
            continue;
        }

        while(not mismaComponenteConexaAlDesconectar(graph, *actual, **connection_candidate)) {
            connection_candidate++;
        }
        actual->removeEdgeTo(**connection_candidate);
        circuit.push_back(*connection_candidate);
        actual = *connection_candidate;
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
