#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <chrono>
#include "tests.hpp"

typedef unsigned int ui;

using namespace std;

int main(int argc, char **argv) {
  if(argc != 6) {
    cerr << "ERROR: Use ./hiperplano_basico.cpp <seed> <N> <K> <trials> <repetitions>" << endl;
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
  cout << "Algoritmo basico:" << endl;
  cout << "Ejecutado pruebas para N = " << N << ", K = " << K << ", Pruebas = " << pruebas << endl;
  
  for(ui r = 0; r < repeticiones; ++r) {
    chrono::time_point<chrono::high_resolution_clock> t_begin, t_end;

    t_begin = chrono::high_resolution_clock::now();
    tests.test_algorithm(N, pruebas, K, seed, encontrar_no_dominados);
    t_end = chrono::high_resolution_clock::now();

    T += chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count();
  }

  T /= (double)repeticiones;

  cout << "\n\n\tTiempo: " << T << "µs" << endl;
    
  return 0;
}
