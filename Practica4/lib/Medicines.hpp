#ifndef MEDICINES
#define MEDICINES

#include <cstdlib>  // srand & rand
#include <cfloat> // DBL_MAX
#include <vector>   // stl vector
#include <set>      // stl set
#include <iostream>

#define MAX_COST 500    // euros
#define MAX_WEIGHT 10   // grams

#define INC_COST 50     // cost increment
#define INC_STEPS 10    // possible increments until MAX_COST

using namespace std;

enum MedicineType {
  STIMULANTS, OPIOIDS, DEPRESSANTS, HALLUCINOGENS, DISSOCIATIVES, INHALANTS, CANNABIS, ALL
};

struct Medicine {
  string name;
  unsigned int cost;
  unsigned int weight;
  double cost_weight_factor;

  Medicine() {
    name = "";
    cost = 
    weight = 0;
    cost_weight_factor = 0;
  }

  Medicine(string name, unsigned int cost, unsigned int weight) {
    this->name = name;
    this->cost = cost;
    this->weight = weight;

    this->cost_weight_factor = (weight != 0) ? (double)this->cost/this->weight : DBL_MAX;
  }

  void showMedicine() const {
    cout << name << endl;
    cout << "Cost (€): " << cost << endl;
    cout << "Weight (g): " << weight << endl;
    cout << "Factor (cost/weight): " << cost_weight_factor << endl;
    cout << endl;
  }

  friend bool operator<(const Medicine &l, const Medicine &r) {
    return l.cost_weight_factor < r.cost_weight_factor;
  }
};

class MedicineStock {
  set<Medicine> stock;

public:
  MedicineStock() {}; /* default */

  MedicineStock(vector<string> stock) {
    int stock_size = stock.size();
    for(int i = 0; i < stock_size; ++i) {
      Medicine aux(stock[i], (MAX_COST - INC_COST*rand()%INC_STEPS), (rand()%MAX_WEIGHT));
      this->stock.insert(aux);
    }
  }

  void showStock(string medicine_type) {
    cout << "***************************" << endl;
    cout << medicine_type << endl;
    cout << "***************************" << endl;    

    set<Medicine>::iterator it;
    for(it = stock.begin(); it != stock.end(); ++it)
      it->showMedicine();
  }
};

class Stimulants : public MedicineStock {
public:
  Stimulants() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "adderall", 
                                    "ritalin", 
                                    "synthetic_marijuana", 
                                    "cocaine", 
                                    "methamphetamine", 
                                    "ecstasy", 
                                    "caffeine" };
};

class Opioids : public MedicineStock {
public:
  Opioids() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "heroin",
                                    "morphine",
                                    "hydrocodone",
                                    "opium",
                                    "vidodim",
                                    "oxycontin",
                                    "percocet",
                                    "codeine" };
};

class Depressants : public MedicineStock { 
public:
  Depressants() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "phenobarbital",
                                    "pentobarbital",
                                    "rohypnol",
                                    "xanax",
                                    "valium",
                                    "alcohol",
                                    "tobaco" };
};

class Hallucinogens : public MedicineStock {
public:
  Hallucinogens() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "psilocybin",
                                    "peyote",
                                    "lsd" };
};

class Dissociatives : public MedicineStock {
public:
  Dissociatives() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "ketamina",
                                    "dxm",
                                    "pcp" };
};

class Inhalants : public MedicineStock {
public:
  Inhalants() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "glue",
                                    "gasoline",
                                    "nitrous_oxide",
                                    "aerosol",
                                    "deodorizers" };
};

class Cannabis : public MedicineStock {
public:
  Cannabis() : MedicineStock(medicine_names) {};

  vector<string> medicine_names = { "marijuana",
                                    "hashish",
                                    "hashish_oil",
                                    "sativex" };
};

#endif /* MEDICINES */
