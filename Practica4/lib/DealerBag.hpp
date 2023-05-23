#ifndef DEALER_BAG
#define DEALER_BAG

#include "Medicines.hpp"

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
    stock_type = ALL;
  }

  DealerBag(MedicineType stock_type) {
    this->stock_type = stock_type;
  }

  void showMedicines() {
    if(stock_type == ALL || stock_type == STIMULANTS)
      stimulants_stock.showStock("Stimulants");

    if(stock_type == ALL || stock_type == OPIOIDS)
      opioids_stock.showStock("Opioids");

    if(stock_type == ALL || stock_type == DEPRESSANTS)
      depressants_stock.showStock("Depressants"); 

    if(stock_type == ALL || stock_type == HALLUCINOGENS)
      hallucinogens_stock.showStock("Hallucinogens");

    if(stock_type == ALL || stock_type == DISSOCIATIVES)
      dissociatives_stock.showStock("Dissociatives");

    if(stock_type == ALL || stock_type == INHALANTS)
      inhalants_stock.showStock("Inhalants");

    if(stock_type == ALL || stock_type == CANNABIS)
      cannabis_stock.showStock("Cannabis");
  }
};

#endif /* DEALER_BAG */
