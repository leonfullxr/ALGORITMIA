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
  DealerBag() { stock_type = ALL; }

  DealerBag(MedicineType stock_type) {
    this->stock_type = stock_type;
  }

  void fillBag(int max_weight, int inc_weight=1) {
    if(stock_type == ALL || stock_type == STIMULANTS) {
      stimulants_stock.showStock("Stimulants");
      fillBag_DP(stimulants_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == OPIOIDS) {
      opioids_stock.showStock("Opioids");
      fillBag_DP(opioids_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == DEPRESSANTS) {
      depressants_stock.showStock("Depressants"); 
      fillBag_DP(depressants_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == HALLUCINOGENS) {
      hallucinogens_stock.showStock("Hallucinogens");
      fillBag_DP(hallucinogens_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == DISSOCIATIVES) {
      dissociatives_stock.showStock("Dissociatives");
      fillBag_DP(dissociatives_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == INHALANTS) {
      inhalants_stock.showStock("Inhalants");
      fillBag_DP(inhalants_stock, max_weight, inc_weight);
    }

    if(stock_type == ALL || stock_type == CANNABIS) {
      cannabis_stock.showStock("Cannabis");
      fillBag_DP(cannabis_stock, max_weight, inc_weight);
    }
  } 

private:
  void fillBag_DP(MedicineStock bag_stock, int max_weight, int inc_weight=1) {
    int steps = max_weight/inc_weight;
    int bag_size = bag_stock.size();

    vector<int> aux(steps, 0);
    vector<vector<int>> solution(bag_size, aux);

    for(int i = 0; i < bag_size; ++i) {
      int idx_cost = bag_stock[i].cost();
      int idx_weight = bag_stock[i].weight();

      for(int j = 0; j < steps; ++j) {
        if(i == 0) {
          if(j+1 >= idx_weight)
            solution[i][j] = idx_cost;
        } else {
          if(j+1 < idx_weight)
            solution[i][j] = solution[i-1][j];
          else
            solution[i][j] = max(solution[i-1][j], idx_cost+solution[i-1][j-idx_weight]);
        }
      }
    }

    for(int i = 0; i < bag_size; ++i) {
      cout << bag_stock[i].name();

      for(int j = 0; j < steps; ++j)
        cout << "\t" << solution[i][j];

      cout << endl;
    }
  }
};


// Save state
friend std::ostream& operator<<(std::ostream& os, const DealerBag& db) {
    os << db.stimulants_stock.size() << '\n';
    for (const auto& item : db.stimulants_stock)
        os << item;

    // tengo que llenar los demas tipos..?
    
    return os;
}

// Load state
friend std::istream& operator>>(std::istream& is, DealerBag& db) {
    std::size_t size;
    is >> size;
    db.stimulants_stock.resize(size);
    for (auto& item : db.stimulants_stock)
        is >> item;

    // tengo que llenar los demas tipos..?
    
    return is;
}


#endif /* DEALER_BAG */
