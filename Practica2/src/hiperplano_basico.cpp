#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <chrono>
#include "tests.hpp"

typedef unsigned int ui;

using namespace std;

int main(int argc, char **argv) {
  if(argc < 4) {
    cerr << "ERROR: Use ./hiperplano_basico.cpp <seed> <trials> <K> <N>" << endl;
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
