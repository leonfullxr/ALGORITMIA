/*
El código implementa dos algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional. El problema consiste en encontrar los puntos que no son dominados por ningún otro punto del conjunto, es decir, aquellos puntos que tienen todas sus coordenadas mayores o iguales que las de otro punto, y al menos una coordenada mayor.

El primer algoritmo, llamado "algoritmo básico", recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a una lista de puntos no dominados.

El segundo algoritmo, llamado "algoritmo Divide y Vencerás", divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.

Ambos algoritmos utilizan la función domina() para verificar si un punto domina a otro, es decir, si todas las coordenadas del primer punto son mayores o iguales que las del segundo punto y al menos una coordenada del primer punto es mayor que la del segundo punto.

La función main() crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando ambos algoritmos. Los resultados se imprimen en la consola.
*/

#include <iostream>
#include <ctime>
#include "tests.hpp"
#include "hyperplane.hpp"
typedef unsigned int ui;

using namespace std;

int main(int argc, char **argv) { 
  if(argc < 4) {
    cerr << "ERROR: Use ./hiperplano_dyv.cpp <seed> <trials> <K> <N>" << endl;
    return 1;
  }

  int seed = atoi(argv[1]);
  int K = atoi(argv[3]);
  int pruebas = atoi(argv[2]);
  srand(seed);
  Tests tests;
 
  for(int arg = 4; arg < argc; ++arg) {
    int N = atoi(argv[arg]);
    tests.test_algorithm(N, pruebas, K, seed, divide_venceras);
  }
  
  return 0;
}

