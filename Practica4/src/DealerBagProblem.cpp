#include "DealerBag.hpp"

#define N_ELEMENTS 10000
#define N_COLUMNS 100000
#define COLUMN_STEP 1000

using namespace std;

void defaultOptions(const int &option, DealerBag &bag) {
  switch(option) {
    case 1:
      bag.initializeWithExample(STIMULANTS);
      break;
    case 2:
      bag.initializeWithExample(OPIOIDS);
      break;
    case 3:
      bag.initializeWithExample(DEPRESSANTS);
      break;
    case 4:
      bag.initializeWithExample(HALLUCINOGENS);
      break;
    case 5:
      bag.initializeWithExample(DISSOCIATIVES);
      break;
    case 6:
      bag.initializeWithExample(INHALANTS);
      break;
    case 7:
      bag.initializeWithExample(CANNABIS);
      break;

    default:
      cerr << "ERROR: Non valid option" << endl;
      break;
  }
}

void printError() {
  cerr << "ERROR: Use f <FILE> | b (10000 elements | 1000000 columns | 1 column step) | d < 1 (STIMULANTS) | 2 (OPIOIDS) | 3 (DEPRESSANTS) | 4 (HALLUCINOGENS) | 5 (DISSOCIATIVES) | 6 (INHALANTS) | 7 (CANNABIS) > && <v (INFO) | n (NO INFO)>" << endl; 
}

int main_to_fix(int argc, char *argv[]) {
  char* option = argv[1];
  char* file_name;
  int default_option = 0;
  char *show_option = argv[argc-1];
  bool show_flag = (show_option == "v");

  DealerBag bag;

  if(option == "f") {
    if(argc < 4) {
      printError();
      return 1;
    }

    file_name = argv[2];
    bag.load(file_name);
  }else if(option == "b"){
    cerr << "PRE" << endl;
    bag.initializeBenchmark(N_ELEMENTS, N_COLUMNS, COLUMN_STEP);
    cerr << "POS" << endl;
  } else if(option == "d") {
    if(argc < 4) {
      printError();
      return 1;
    }

    defaultOptions(default_option, bag);
  }

  bag.fillBag(show_flag);
}

int main(void) {
  DealerBag bag;

  bag.initializeBenchmark(N_ELEMENTS, N_COLUMNS, COLUMN_STEP);

  bag.fillBag();
}
