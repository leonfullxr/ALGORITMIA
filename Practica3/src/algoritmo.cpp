/** PROBLEMA A RESOLVER **/
/*
Euler definió un tipo particular de grafo, denominado grafo de Euler, como aquel tipo de
grafo que contiene un circuito de Euler. La definición formal de circuito de Euler es:

Sea G un grafo conexo. Un camino de Euler sobre el grafo es un camino que no repite
aristas y en el que aparecen todas las aristas del grafo. Un circuito de Euler es un ciclo
(comienza y termina en el mismo nodo/vértice) y que, además, es un camino de Euler.

Como ejemplo, el grafo de la siguiente figura es un grafo de Euler, donde el recorrido por
los nodos (1, 2, 4, 6, 5, 3, 2, 5, 4, 3, 1) proporciona un circuito de Euler.

Se cumple que un grafo no dirigido conexo es también un grafo de Euler si, y sólo si,
todos los nodos del grafo tiene grado par; es decir, si en todos los nodos del grafo inciden
un número par de aristas. Existe un algoritmo (algoritmo de Fleury) que permite
encontrar un camino de Euler sobre un grafo de Euler, cuya descripción de
funcionamiento es la siguiente:
	1. Se parte de un nodo dado v del grafo G.
	2. Si G contiene sólo un nodo v, el algoritmo termina.
	3. Si hay una única arista a que incide en v, entonces llamamos w al otro vértice que
conecta la arista a, y la quitamos del grafo. Vamos después al paso 5. En otro caso,
seguimos en el paso 4.
	4. Como hay más de un lado que incide en v, elegimos uno de estos (lo llamamos w)
de modo que al quitarlo del grafo G, el grafo siga siendo conexo. Cogemos la arista
que une v con w y la quitamos del grafo.
	5. Cambiamos el nodo v por el nodo w y volvemos al paso 3 hasta que terminemos de
hacer el circuito de Euler.


/** DISEÑO PROPUESTO **/
/*
Inicializar S, A y G como vacíos.
Asumir que G es un grafo conexo de Euler con nodos {1, 2, 3, 4, 5, 6} y aristas A.G.
Elegir un nodo inicial v que pertenezca a G.
Si |G| > 1:
	4.1. Insertar v en S.
	4.2. Mientras |A| no sea igual a |A.G|:
		4.2.1. Para todas las aristas incidentes en v que no pertenezcan a A, seleccionar una arista a que no desconecte el grafo y tenga un nodo w con la menor cantidad de incidencias.
		4.2.2. Insertar a en A.
		4.2.3. Establecer v = w.
	4.3. Devolver S como el circuito de Euler encontrado.
Si |G| = 1, informar que no es un grafo válido (solo tiene un vértice).

Notas:
v: Corresponde al nodo actual en la iteración.
w: Es el nodo con menos incidencias.
| |: Indica el tamaño, ya sea de vértices o aristas según el contexto.
Al seleccionar una arista a, si para todas las posibles, su nodo w tiene las mismas incidencias, se elegirá una de forma arbitraria, puede ser la primera o una aleatoria para que haya variación en los caminos.

/** MIS NOTAS **/
/*
Formalización del algoritmo de Fleury como un algoritmo Greedy:
1.1. Compruebe si se puede resolver mediante Greedy:

Sí, el algoritmo de Fleury puede ser resuelto utilizando un enfoque Greedy, ya que se seleccionan aristas de forma local y óptima, considerando las aristas que no desconecten el grafo.

1.2. Diseñe las componentes greedy del algoritmo:

Función de selección: En cada paso, elegir una arista 'a' incidente en el nodo actual 'v' que no desconecte el grafo al ser removida. Si todas las aristas restantes desconectan el grafo, seleccionar la arista que tenga el nodo 'w' con menos incidencias.

Función de factibilidad: Asegurar que al quitar la arista 'a' del grafo, este siga siendo conexo. Si todas las aristas restantes desconectan el grafo, seleccionar la arista que tenga el nodo 'w' con menos incidencias.

Función objetivo: Encontrar un circuito de Euler que recorra todas las aristas del grafo.

Función de solución: El algoritmo termina cuando todas las aristas del grafo han sido recorridas.

1.3. Adapte la plantilla de diseño Greedy a las componentes propuestas:

Inicializar el conjunto de soluciones S y el conjunto de aristas recorridas A como vacíos.
Elegir un nodo inicial 'v' perteneciente al grafo G.
Mientras que no se hayan recorrido todas las aristas del grafo G:
1. Seleccionar una arista 'a' incidente en 'v' que no desconecte el grafo al ser removida, utilizando la función de selección.
2. Verificar la factibilidad de la arista 'a' seleccionada con la función de factibilidad.
3. Actualizar el conjunto de soluciones S y el conjunto de aristas recorridas A.
4. Cambiar el nodo actual 'v' por el nodo 'w'.
Devolver S como la solución al problema.

Implementación del algoritmo:
/** ASUMO EN TODA REGLA QUE TRABAJAMOS CON NODOS DE GRADO PAR Y CONEXOS **/

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../include/graph.h"
#include "../include/node.h"

template <typename T>
std::list<Node<T>*> findEulerCircuit(Graph<T>& graph, T startNodeValue) {
    // Inicializa la lista de circuito que almacenará el camino de Euler
    std::list<Node<T>*> circuit;
    // Inicializa el conjunto de aristas visitadas
    std::set<std::pair<T, T>> visitedEdges;

    // Verifica si el grafo tiene solo un vértice y, en ese caso, devuelve un error
    if (graph.node_n() == 1) {
        std::cout << "Error: no es un grafo válido (solo tiene un vértice)." << std::endl;
        return circuit;
    }

    // Selecciona un nodo inicial arbitrario
    Node<T>* currentNode = &graph.node(startNodeValue);
    // Añade el nodo inicial al circuito
    circuit.push_back(currentNode);

    // Continúa recorriendo el grafo mientras no se visiten todas las aristas y el grafo sigue siendo conexo
    while (visitedEdges.size() != graph.edge_n() && !circuit.empty()) {
        // Obtiene las conexiones (aristas) del nodo actual
        std::list<Node<T>*> connections = currentNode->getConnections();
        // Inicializa el nodo siguiente y el grado mínimo para la selección de nodos
        Node<T>* nextNode = nullptr;
        int minDegree = std::numeric_limits<int>::max();

        // Recorre todas las conexiones del nodo actual
        for (Node<T>* connection : connections) {
            // Obtiene el grado del nodo de conexión
            int currentDegree = connection->degree();
            // Crea un par ordenado que representa la arista entre el nodo actual y el nodo de conexión
            std::pair<T, T> edge = std::minmax(currentNode->operator*(), connection->operator*());

            // Si la arista no ha sido visitada y el grado del nodo de conexión es menor que el grado mínimo
            if (visitedEdges.count(edge) == 0 && currentDegree < minDegree) {
                // Actualiza el grado mínimo y el nodo siguiente
                minDegree = currentDegree;
                nextNode = connection;
            }
        }

        // Si se encuentra un nodo siguiente válido
        if (nextNode != nullptr) {
            // Añade la arista al conjunto de aristas visitadas
            visitedEdges.insert(std::minmax(currentNode->operator*(), nextNode->operator*()));
            // Establece el nodo siguiente como el nodo actual
            currentNode = nextNode;
            // Añade el nodo siguiente al circuito
            circuit.push_back(currentNode);
        } else {
            // No se encontró un nodo siguiente válido, por lo que se elimina el último nodo del circuito
            circuit.pop_back();
            // Si el circuito no está vacío, actualiza el nodo actual
            if (!circuit.empty()) {
                currentNode = circuit.back();
            }
        }
    }

    // Devuelve el circuito de Euler
    return circuit;
}

/*
Eficiencia en el caso peor del algoritmo:
La eficiencia de este algoritmo se ve afectada principalmente por dos bucles. El bucle while que se ejecuta hasta que se visitan todas las aristas del grafo, y el bucle for que itera sobre las conexiones (aristas) del nodo actual en cada iteración del bucle while.

El bucle while se ejecuta una vez por cada arista del grafo, es decir, |E| veces (donde |E| es el número de aristas). Dentro de este bucle, el bucle for itera sobre las conexiones de cada nodo. En el peor de los casos, un nodo podría estar conectado a todos los demás nodos del grafo, lo que llevaría a un grado máximo de |V|-1 (donde |V| es el número de nodos).

En general, este algoritmo tiene una complejidad en tiempo de O(|E| * (|V|-1)), o simplemente O(|E| * |V|) en términos asintóticos.	
*/				
