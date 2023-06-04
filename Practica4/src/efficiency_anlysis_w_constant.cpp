#include "../lib/DealerBag.hpp"
#include <iostream>
#include <fstream>
#include "../lib/DealerBag.hpp"
#include <numeric>

using namespace std;

int main() {
  // Como mucho un elemento puede pesar 10g y valer 450$
  int start_value = 10;
  int increment = 100;

  std::ofstream outputFile("./data/efficiency_analysis_w_constant.txt");

  std::streambuf* coutBuffer = std::cout.rdbuf();
  std::cout.rdbuf(outputFile.rdbuf());

  for (int i = start_value; i < 10000; i += increment) { // 10kg
    DealerBag dealerBag;
    dealerBag.initializeBenchmark(i, 10000);
    dealerBag.fillBag(false);
  }

  std::cout.rdbuf(coutBuffer);

  outputFile.close();

  // Filtrar las líneas del archivo y generar un nuevo archivo filtrado
  std::ifstream inputFile("./data/efficiency_analysis_w_constant.txt");
  std::ofstream filteredOutputFile("./data/efficiency_analysis_w_constant_filtered.txt");

  std::string line;
  while (std::getline(inputFile, line)) {
    // Si la línea no contiene "Final solution", escribir en el archivo filtrado
    if (line.find("Final solution") == std::string::npos) {
      filteredOutputFile << line << '\n';
    }
  }

  inputFile.close();
  filteredOutputFile.close();

  return 0;
}

