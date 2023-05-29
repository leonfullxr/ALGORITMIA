#include "DealerBag.hpp"

using namespace std;

int main(void) {
  srand(time(NULL));
  DealerBag bag(STIMULANTS);

  bag.fillBag();
}
