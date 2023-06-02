#include "DealerBag.hpp"

#define N_ELEMENTS 10000
#define N_COLUMNS 100000
#define COLUMN_STEP 1000

using namespace std;

void printError() {
  cerr << "ERROR: Use f <FILE> | b (10000 elements | 1000000 columns | 1 column step) | d < 1 (STIMULANTS) | 2 (OPIOIDS) | 3 (DEPRESSANTS) | 4 (HALLUCINOGENS) | 5 (DISSOCIATIVES) | 6 (INHALANTS) | 7 (CANNABIS) > && <v (INFO) | n (NO INFO)>" << endl; 
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printError();
    return 1;
  }

  char option = argv[1][0];
  char* file_name;
  int default_option = 0;
  char show_option = argv[argc-1][0];
  
  if(show_option != 'v' && show_option != 'n') {
    printError();
    return 1;
  }

  bool show_flag = (show_option == 'v');

  DealerBag bag;

  switch(option) {
    case 'f':  
      if(argc < 4) {
        printError();
        return 1;
      }

      file_name = argv[2];
      bag.load(file_name);
      break;
    case 'b':
      if(argc < 3) {
        printError();
        return 1;
      }
  
      bag.initializeBenchmark(N_ELEMENTS, N_COLUMNS, COLUMN_STEP);
      break;
    case 'e':
      if(argc < 4) {
        printError();
        return 1;
      }

      default_option = atoi(argv[2]);

      bag.defaultOptions(default_option);
      break;
  }

  bag.fillBag(show_flag);
}
