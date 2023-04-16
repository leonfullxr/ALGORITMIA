/*
El código implementa dos algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional. El problema consiste en encontrar los puntos que no son dominados por ningún otro punto del conjunto, es decir, aquellos puntos que tienen todas sus coordenadas mayores o iguales que las de otro punto, y al menos una coordenada mayor.

El primer algoritmo, llamado "algoritmo básico", recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a una lista de puntos no dominados.

El segundo algoritmo, llamado "algoritmo Divide y Vencerás", divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.

Ambos algoritmos utilizan la función domina() para verificar si un punto domina a otro, es decir, si todas las coordenadas del primer punto son mayores o iguales que las del segundo punto y al menos una coordenada del primer punto es mayor que la del segundo punto.

La función main() crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando ambos algoritmos. Los resultados se imprimen en la consola.
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include "tests.hpp"

typedef unsigned int ui;

using namespace std;

int main(int argc, char **argv) { 
  if(argc != 6) {
    cerr << "ERROR: Use ./hiperplano_dyv.cpp <seed> <N> <K> <trials> <repetitions>" << endl;
    return 1;
  }

  ui seed = atoi(argv[1]);
  ui N = atoi(argv[2]);
  ui K = atoi(argv[3]);
  ui pruebas = atoi(argv[4]);
  ui repeticiones = atoi(argv[5]);

  double T = 0;

  srand(seed);

  Tests tests;
  cout << "Algoritmo Divide Y Venceras:" << endl;
  cout << "Ejecutado pruebas para N = " << N << ", K = " << K << ", Pruebas = " << pruebas << endl;

for(ui r = 0; r < repeticiones; ++r) {
    chrono::time_point<chrono::high_resolution_clock> t_begin, t_end;

    t_begin = chrono::high_resolution_clock::now();
    tests.test_algorithm(N, pruebas, K, seed, divide_venceras);
    t_end = chrono::high_resolution_clock::now();

    T += chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count();
  }

  T /= (double)repeticiones;

  cout << "\n\n\tTiempo: " << T << "µs" << endl;

  return 0;
}

