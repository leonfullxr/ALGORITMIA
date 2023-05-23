#ifndef DEALER_BAG
#define DEALER_BAG

#include "Medicines.h"
#include <vector>

class DealerBag {
private:
  Stimulants stimulants_stock;
  Opioids opioids_stock;
  Depressants depressants_stock;
  Hallucinogens hallucinogens_stock;
  Dissociatives dissociatives_stock;
  Inhalants inhalants_stock;
  Cannabis cannabis_stock;

  MedicineType stock_type;

public:
  DealerBag() {
    srand(time(NULL));

    type = STIMULANTS;

    


  }


};

#endif /* DEALER_BAG */
