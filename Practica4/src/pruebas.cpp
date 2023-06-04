/**
* Fichero para realizar las pruebas de eficiencia 
* Incluye casos de 1000 items hasta 100.000
*/
#include "../lib/DealerBag.hpp"
#include <iostream>
#include <fstream>
#include "../lib/DealerBag.hpp"
#include <numeric>

using namespace std;

int main() {
	// Como mucho un elemento puede pesar 10g y valer 450$
  int start_value = 1000;
  int increment = 100;
  int iterations = 5;

  DealerBag dealerBag;

  std::ofstream outputFile("./data/output.txt");

  std::streambuf* coutBuffer = std::cout.rdbuf();
  std::cout.rdbuf(outputFile.rdbuf());

  for (int i = start_value; i < 100000; i += increment) { // 10kg
    int gcd = dealerBag.getStock()[0].cost();
	for (int i = 1; i < dealerBag.getStock().size(); ++i) {
	  gcd = std::gcd(gcd, dealerBag.getStock()[i].cost());
	}
    dealerBag.initializeBenchmark(i, 10000, gcd);
    dealerBag.fillBag(false);
  }

  std::cout.rdbuf(coutBuffer);

  outputFile.close();

  return 0;
}
