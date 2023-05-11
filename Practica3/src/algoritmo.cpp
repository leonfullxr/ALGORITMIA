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

Inicialización:

Crear un conjunto de soluciones S y un conjunto de aristas recorridas A, ambos inicialmente vacíos.
Elegir un nodo inicial v del grafo G.
Mientras no se hayan recorrido todas las aristas del grafo G:

Selección: Buscar todas las aristas incidentes en v que no se encuentren en A. Seleccionar una arista a de ese conjunto que no desconecte el grafo G al ser removida. Si existen varias aristas que cumplen con este criterio, seleccionar la que tenga un nodo w con la menor cantidad de incidencias.
Factibilidad: Verificar si la arista a seleccionada puede ser añadida a A sin violar la restricción de que no se pueden recorrer las aristas más de una vez. Esto se puede hacer simplemente verificando si a ya está en A.
Actualización de la solución: Si la arista a es factible, añadirla a A y añadir el nodo w a S. Luego, cambiar el nodo actual v por el nodo w.
Función objetivo: La función objetivo en este caso podría ser simplemente el número de aristas en A, ya que queremos maximizar la cantidad de aristas recorridas. No necesitamos calcular explícitamente esta función en cada paso, ya que la condición del bucle garantiza que continuaremos hasta que hayamos recorrido todas las aristas.
Solución: Devolver S como la solución al problema. S representará el circuito de Euler en el grafo G

Implementación del algoritmo:
/** ASUMO EN TODA REGLA QUE TRABAJAMOS CON NODOS DE GRADO PAR Y CONEXOS **/

#include <iostream>
#include <stack>
#include "../include/graph.h"
#include "../include/node.h"

template <typename T>
bool esConexo(Graph<T>& graph, Node<T>& nodoInicial, Node<T>& nodoAComprobar) {
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
                    w = connection;
                    maxDegree = connection->degree();
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
Eficiencia en el caso peor del algoritmo:
En el peor de los casos, si cada nodo está conectado a todos los demás (es decir, 
el grafo es completamente conexo), entonces esta operación adicional podría hacer que 
la eficiencia del algoritmo sea O(E^2), ya que para cada arista, puede necesitar revisar 
todas las demás aristas para encontrar el nodo con más aristas incidentes no visitadas.

En la práctica, la eficiencia del algoritmo dependerá del grado medio de los nodos en el grafo. 
Si la mayoría de los nodos tienen un grado relativamente bajo (es decir, están conectados solo a 
unos pocos otros nodos), entonces la eficiencia del algoritmo todavía estará cerca de O(E). 
Sin embargo, si muchos nodos tienen un grado alto, entonces la eficiencia del algoritmo podría acercarse más a O(E^2).

*/				
