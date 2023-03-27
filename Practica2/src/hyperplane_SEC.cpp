#include <iostream>
#include <chrono>
#include <cstdlib>
#include "hyperplane.h"

using namespace std;

int main(int argc, char *argv[]) {
  if(argc <= 3) {
    cerr << "Error: Use ./program <Seed> <K_Dimensions> <C_Size>" << endl; 
    return 1;
  }

  ui seed = (ui)atoi(argv[1]);
  ui K = (ui)atoi(argv[2]);
  ui C_size = (ui)atoi(argv[3]);

  if(K <= 0 || C_size <= 0) {
    cerr << "Error: Values out of bounds (K_Dimensions <= 0 or C_Size <= 0)" << endl;
    return 1;
  }

  Hyperplane hyperplane(C_size, K, seed);
  hyperplane.print();

  return 0;
}
