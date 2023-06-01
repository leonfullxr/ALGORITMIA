#include "DealerBag.hpp"

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

int main(int argc, char *argv[]) {
  if(argc < 4) {
    cerr << "ERROR: Use -f <FILE> | -s <SEED> (RANDOM EXAMPLE AND VALUES) | -d < 1 (STIMULANTS) | 2 (OPIOIDS) | 3 (DEPRESSANTS) | 4 (HALLUCINOGENS) | 5 (DISSOCIATIVES) | 6 (INHALANTS) | 7 (CANNABIS) > && <-v (INFO) | -n (NO INFO)>" << endl;
    return 1;
  }

  char* option = argv[1];
  char* option_arg = argv[2];
  string show_option = "";

  if(argc == 4)
    show_option = argv[3];

  bool show_flag = (show_option == "-v");

  DealerBag bag;

  if(option == "-f") {
    bag.load("./data/example1.txt");
  } else if(option_arg == "-s") {
    srand(atoi(option_arg));
    defaultOptions(rand()%7+1, bag);
  } else if(option_arg == "-d") {
    defaultOptions(atoi(option_arg), bag);
  }

  bag.fillBag(show_flag);
}
