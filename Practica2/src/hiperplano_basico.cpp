#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include "tests.hpp"

using namespace std;

int main(int argc, char **argv) {
  if(argc != 5) {
    cerr << "ERROR: Use ./hiperplano_basico.cpp <seed> <N> <K> <trials>" << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  int N = atoi(argv[2]);
  int K = atoi(argv[3]);
  int pruebas = atoi(argv[4]);

  srand(seed);

  Tests tests;
  cout << "Algoritmo basico:" << endl;
  cout << "Ejecutado pruebas para N = " << N << ", K = " << K << ", Pruebas = " << pruebas << endl;
    tests.test_algorithm(N, pruebas, K, seed, encontrar_no_dominados);
    tests.test_algorithm(N, pruebas, K, seed, encontrar_no_dominados);
    tests.test_algorithm(N, pruebas, K, seed, encontrar_no_dominados);
    
    return 0;
}
