#ifndef MEDICINES
#define MEDICINES

#include <cstdlib>  // srand & rand

#define MAX_COST 500    // euros
#define MAX_WEIGHT 10   // grams

#define INC_COST 50     // cost increment
#define INC_STEPS 10    // possible increments until MAX_COST

enum MedicineTypes {
  STIMULANTS, OPIOIDS, DEPRESSANTS, HALLUCINOGENS, DISSOCIATIVES, INHALANTS, CANNABIS
};

struct Medicine {
  unsigned int cost
  unsigned int weight;

  Medicine() {
    cost = 
    weight = 0;
  }

  Medicine(unsigned int cost, unsigned int weight) {
    this->cost = cost;
    this->weight = weight;
  }

  friend bool operator(const Medicine &l, const Medicine &r) {
    return ( ((double)l.cost/l.weight) < ((double)r.cost/r.weight) );
  }
}

class MedicineStock {
  vector<Medicine> stock();

  MedicineStock() {}; /* default */

  MedicineStock(size_t stock_size) {
    for(int i = 0; i < stock_size; ++i)
      stock.push_back({ (MAX_COST - INC_COST*rand()%INC_STEPS), (rand()%MAX_WEIGHT) });
  }
};

class Stimulants : public MedicineStock {
  vector<string> medicine_names = { "adderall", 
                                    "ritalin", 
                                    "synthetic_marijuana", 
                                    "cocaine", 
                                    "methamphetamine", 
                                    "ecstasy", 
                                    "caffeine" };

  Stimulants() : MedicineStock(medicine_names.size());
};

class Opioids : public MedicineStock {
  vector<string> medicine_names = { "heroin",
                                    "morphine",
                                    "hydrocodone",
                                    "opium",
                                    "vidodim",
                                    "oxycontin",
                                    "percocet",
                                    "codeine" };

  Opioids() : MedicineStock(medicine_names.size());
};

class Depressants : public MedicineStock { 
  vector<string> medicine_names = { "phenobarbital",
                                    "pentobarbital",
                                    "rohypnol",
                                    "xanax",
                                    "valium",
                                    "alcohol",
                                    "tobaco" };

  Depressants() : MedicineStock(medicine_names.size());
};

class Hallucinogens : public MedicineStock {
  vector<string> medicine_names = { "psilocybin",
                                    "peyote",
                                    "lsd" };

  Hallucinogens() : MedicineStock(medicine_names.size());
}

class Dissociatives : public MedicineStock {
  vector<string> medicine_names = { "ketamina",
                                    "dxm",
                                    "pcp" };
 
  Dissociatives() : MedicineStock(medicine_names.size());
};

class Inhalants : public MedicineStock {
  vector<string> medicine_names = { "glue",
                                    "gasoline",
                                    "nitrous_oxide",
                                    "aerosol",
                                    "deodorizers" };
 
  Inhalants() : MedicineStock(medicine_names.size());
};

class Cannabis : public MedicineStock {
  vector<string> medicine_names = { "marijuana",
                                    "hashish",
                                    "hashish_oil",
                                    "sativex" };
  
  Cannabis() : MedicineStock(medicine_names.size());
};

#endif /* MEDICINES */
