#include "DealerBag.hpp"

using namespace std;

int main(void) {
  srand(time(NULL));
  DealerBag bag;
  bag.save("./data/example1.txt");

  bag.fillBag();
}
