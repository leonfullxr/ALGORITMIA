/** PROBLEMA A RESOLVER **/

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

/** TAREAS A REALIZAR **/
Se pide:
1. Formalizar, si es posible, la descripción de funcionamiento del método anterior
como un algoritmo Greedy. Para ello:
	1.1. Compruebe si se puede resolver mediante Greedy.
	1.2. Diseñe las componentes greedy del algoritmo.
	1.3. Adapte la plantilla de diseño Greedy a las componentes propuestas.
2. Implemente el algoritmo en una función C/C++.
3. Calcule la eficiencia en el caso peor del algoritmo

/** DISEÑO PROPUESTO **/

S = -
A = -
G = {1,2,3,4,5,6}
v pertenece G

si |G| != 1
	S = S U v	// insertamos v en el conjunto solucion
	mientras que |A| != |A.G|	// mientras que el numero de aristas recorridas no sea igual al de G para toda arista que incida en v comprobamos cual es a, dandose que a no pertenece A y |w| != 0:
	// si a no es recorrida y w tiene aristas por recorrer
	A = A U a	// insertamos a en las aristas recorridas
	v = w
	Devolvemos S
si |G| = 1
	Error no es un grafo, solo tiene un vertice
	
Notas:
-v: Corresponde al nodo actual en la iteracion
-w: Es el nodo con menos incidencias
-| |: indica el tamaño, ya sea vertices o aristas segun el contexto
-A la hora de seleccionar una arista a, si para todas las posibles su nodo w tienen las mismas incidencias, se elegira una de forma arbitraria, puede ser la primera o una aleatoria por que haya variacion en los caminos
						
