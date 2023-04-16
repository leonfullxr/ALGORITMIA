#include <iostream>
#include <algorithm>
#include "tests.hpp"
#include "hyperplane.hpp"
#include <chrono>

using namespace std;

int main(int argc, char **argv) { 
  if(argc < 4) {
    cerr << "ERROR: Use ./hiperplano_basico_tiempos.cpp <seed> <trials> <K> <N>" << endl;
    return 1;
  }

  int seed = atoi(argv[1]);
  int K = atoi(argv[3]);
  int pruebas = atoi(argv[2]);
  srand(seed);
  Tests tests;
 
  for(int arg = 4; arg < argc; ++arg) {
    int N = atoi(argv[4]);
    tests.test_algorithm(N, pruebas, K, seed, divide_venceras);
  }
    
  return 0;
}
