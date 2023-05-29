#ifndef MEDICINES
#define MEDICINES

#include <cstdlib>    // srand & rand
#include <cfloat>     // DBL_MAX
#include <vector>     // stl vector
#include <algorithm>  // sort
#include <iostream>

#define MAX_COST 450    // euros
#define MAX_WEIGHT 9    // grams

#define INC_COST 50     // cost increment
#define INC_STEPS 10    // possible increments until MAX_COST

using namespace std;

enum MedicineType {
  STIMULANTS, OPIOIDS, DEPRESSANTS, HALLUCINOGENS, DISSOCIATIVES, INHALANTS, CANNABIS, ALL, NONE
};

class Medicine {
private:
  string m_name;
  unsigned int m_cost;
  unsigned int m_weight;
  double m_cost_weight_factor;

public:
  Medicine() {
    m_name = "";
    m_cost = 
    m_weight = 0;
    m_cost_weight_factor = 0;
  }

  Medicine(string m_name, unsigned int m_cost, unsigned int m_weight) {
    this->m_name = m_name;
    this->m_cost = m_cost;
    this->m_weight = m_weight;

    this->m_cost_weight_factor = (this->m_weight != 0) ? (double)this->m_cost/this->m_weight : DBL_MAX;
  }

  string name() const {
    return this->m_name;
  }

  unsigned int cost() const {
    return this->m_cost;
  }

  unsigned int weight() const {
    return this->m_weight;
  }

  void showMedicine() const {
    cout << this->m_name << endl;
    cout << "Cost (€): " << this->m_cost << endl;
    cout << "Weight (g): " << this->m_weight << endl;
    cout << "Factor (cost/weight): " << this->m_cost_weight_factor << endl;
    cout << endl;
  }

  friend bool operator<(const Medicine &l, const Medicine &r) {
    return l.m_cost_weight_factor < r.m_cost_weight_factor;
  }
};

class MedicineStock {
private:
  vector<Medicine> stock;

public:
  MedicineStock() {}; /* default */

  void showStock(string medicine_type) {
    cout << endl << endl;
    cout << "***************************" << endl;
    cout << medicine_type << endl;
    cout << "***************************" << endl;    

    int stock_size = stock.size();
    for(int i = 0; i < stock_size; ++i)
      stock[i].showMedicine();
  }

  void refill(vector<string> stock_names) {
    int stock_size = stock_names.size();
    for(int i = 0; i < stock_size; ++i)
      this->stock.push_back({stock_names[i], (unsigned int)(rand()%MAX_COST+INC_COST), (unsigned int)(rand()%MAX_WEIGHT+1)});

    sort(this->stock.begin(), this->stock.end());
  }

  size_t size() {
    return stock.size();
  }
 
  const Medicine operator[](int idx) const {
    return stock[idx];
  }
};

class Stimulants : public MedicineStock {
private:
  vector<string> medicine_names = { "Adderall············", 
                                    "Ritalin·············", 
                                    "Synthetic marijuana·", 
                                    "Cocaine·············", 
                                    "Methamphetamine·····", 
                                    "Ecstasy·············", 
                                    "Caffeine············" };

public:
  Stimulants() { this->refill(medicine_names); }
};

class Opioids : public MedicineStock {
private:
  vector<string> medicine_names = { "Heroin······",
                                    "Morphine····",
                                    "Hydrocodone·",
                                    "Opium·······",
                                    "Vidodim·····",
                                    "Oxycontin···",
                                    "Percocet····",
                                    "Codeine·····" };

public:
  Opioids() { this->refill(medicine_names); }
};

class Depressants : public MedicineStock { 
private:
  vector<string> medicine_names = { "Phenobarbital·",
                                    "Pentobarbital·",
                                    "Rohypnol······",
                                    "Xanax·········",
                                    "Valium········",
                                    "Alcohol·······",
                                    "Tobaco········" };

public:
  Depressants() { this->refill(medicine_names); }
};

class Hallucinogens : public MedicineStock {
private:
  vector<string> medicine_names = { "Psilocybin·",
                                    "Peyote·····",
                                    "LSD········" };

public:
  Hallucinogens() { this->refill(medicine_names); }
};

class Dissociatives : public MedicineStock {
private:
  vector<string> medicine_names = { "Ketamina·",
                                    "DXM······",
                                    "PCP······" };

public:
  Dissociatives() { this->refill(medicine_names); }
};

class Inhalants : public MedicineStock {
private:
  vector<string> medicine_names = { "Glue··········",
                                    "Gasoline······",
                                    "Nitrous oxide·",
                                    "Aerosol·······",
                                    "Deodorizers···" };

public:
  Inhalants() { this->refill(medicine_names); }
};

class Cannabis : public MedicineStock {
public:
  vector<string> medicine_names = { "Marijuana···",
                                    "Hashish·····",
                                    "Hashish oil·",
                                    "Sativex·····" };

public:
  Cannabis() { this->refill(medicine_names); }
};

// Save state
friend std::ostream& operator<<(std::ostream& os, const Medicine& m) {
    os << m.m_name << '\n'
       << m.m_cost << '\n'
       << m.m_weight << '\n';
    return os;
}

// Load state
friend std::istream& operator>>(std::istream& is, Medicine& m) {
    is >> m.m_name
       >> m.m_cost
       >> m.m_weight;
    return is;
}


#endif /* MEDICINES */
