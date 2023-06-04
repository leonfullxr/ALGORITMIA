#ifndef MEDICINES
#define MEDICINES

#include <cstdlib>    // srand & rand
#include <cfloat>     // DBL_MAX
#include <vector>     // stl vector
#include <algorithm>  // sort
#include <fstream>    // files
#include <iostream>

#define MAX_COST 450    // euros
#define MAX_WEIGHT 10    // grams

#define INC_COST 50     // cost increment
#define COL_WEIGHT 1    // weight per column

using namespace std;

enum MedicineType {
  STIMULANTS, OPIOIDS, DEPRESSANTS, HALLUCINOGENS, DISSOCIATIVES, INHALANTS, CANNABIS
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

  // Save state
  friend ostream& operator<<(ostream& os, const Medicine& m) {
    os << m.m_name << '\n'
       << m.m_cost << '\n'
       << m.m_weight << '\n';

    return os;
  }

  // Load state
  friend istream& operator>>(istream& is, Medicine& m) {
    is >> m.m_name
       >> m.m_cost
       >> m.m_weight;

    m.m_cost_weight_factor = (double)m.m_cost/m.m_weight;

    return is;
  }

};

class MedicineStock {
protected:
  vector<string> medicine_names;
  vector<Medicine> stock;

public:
  MedicineStock() {}; /* default */

  void randomFill(const int &number_of_elements) {
    string points = "············";
    int point_flag = 10;
    srand(time(NULL));

    for(int i = 0; i < number_of_elements; ++i) {
      if(i == point_flag) {
        points.pop_back();
        point_flag *= 10;
      }

      this->medicine_names.push_back("Element" + to_string(i) + points); // element name

      this->stock.push_back({this->medicine_names[i], (unsigned int)(rand()%MAX_COST+INC_COST), (unsigned int)(rand()%MAX_WEIGHT+1)});
    }

//    sort(this->stock.begin(), this->stock.end());    
  }

  /**
   * showStock: Prints stock elements details
   **/  
  void showStock(string medicine_type, bool show_flag=false) {
    if(show_flag) {
      cout << endl << endl;
      cout << "***************************" << endl;
      cout << medicine_type << endl;
      cout << "***************************" << endl;    

      int stock_size = stock.size();
      for(int i = 0; i < stock_size; ++i)
        stock[i].showMedicine();
    }
  }

  /**
   * refill: Assign random values to each stock variable element
   **/  
  void refill() {
    int stock_size = this->medicine_names.size();
    for(int i = 0; i < stock_size; ++i)
      this->stock.push_back({this->medicine_names[i], (unsigned int)(rand()%MAX_COST+INC_COST), (unsigned int)(rand()%MAX_WEIGHT+1)});

    sort(this->stock.begin(), this->stock.end());
  }

  void resize(size_t size) {
    stock.resize(size);
  }

  /**
   * size: Returns stock size
   **/
  size_t size() const {
    return stock.size();
  }

  /**
   * &operator[]: Overload operator [] to set element at pos idx
   **/ 
  Medicine &operator[](const int &idx) {
    return stock[idx];
  }
  
  /**
   * operator=: Overload operator =
   **/  
  MedicineStock &operator=(const MedicineStock &new_medicine) {
    this->stock = new_medicine.stock;
    return *this;
  }

  // Save state
  friend ostream& operator<<(ostream& os, MedicineStock &ms) {
    os << ms.stock.size() << '\n';

    for(int i = 0; i < (int)ms.stock.size(); ++i) {
      os << ms.stock[i];
    }
    
    return os;
  }

  // Load state
  friend istream& operator>>(istream& is, MedicineStock &ms) {
    int size;
    is >> size;

    for(int i = 0; i < size; ++i) {
      Medicine aux;
      is >> aux;
      ms.stock.push_back(aux);
    }
   
    return is;
  }
};




/////////////////////////////
// Medicine Stock Examples //
/////////////////////////////

class Stimulants : public MedicineStock {
public:
  Stimulants() { 
    vector<string> stimulants_names = { "Adderall············", 
                                        "Ritalin·············", 
                                        "Synthetic marijuana·", 
                                        "Cocaine·············", 
                                        "Methamphetamine·····", 
                                        "Ecstasy·············", 
                                        "Caffeine············" };

    this->medicine_names = stimulants_names;
    this->refill(); 
  }
};

class Opioids : public MedicineStock {
public:
  Opioids() { 
    vector<string> opioids_names = { "Heroin··············",
                                     "Morphine············",
                                     "Hydrocodone·········",
                                     "Opium···············",
                                     "Vidodim·············",
                                     "Oxycontin···········",
                                     "Percocet············",
                                     "Codeine·············" };

    this->medicine_names = opioids_names;
    this->refill(); 
  }
};

class Depressants : public MedicineStock { 
public:
  Depressants() { 
    vector<string> depressants_names = { "Phenobarbital·······",
                                         "Pentobarbital·······",
                                         "Rohypnol············",
                                         "Xanax···············",
                                         "Valium··············",
                                         "Alcohol·············",
                                         "Tobaco··············" };

    this->medicine_names = depressants_names;
    this->refill(); 
  }
};

class Hallucinogens : public MedicineStock {
public:
  Hallucinogens() { 
    vector<string> hallucinogens_names = { "Psilocybin··········",
                                           "Peyote··············",
                                           "LSD·················" };

    this->medicine_names = hallucinogens_names;
    this->refill(); 
  }
};

class Dissociatives : public MedicineStock {
public:
  Dissociatives() { 
    vector<string> dissociatives_names = { "Ketamina············",
                                           "DXM·················",
                                           "PCP·················" };

    this->medicine_names = dissociatives_names;
    this->refill(); 
  }
};

class Inhalants : public MedicineStock {
public:
  Inhalants() { 
    vector<string> inhalants_names = { "Glue················",
                                       "Gasoline············",
                                       "Nitrous oxide·······",
                                       "Aerosol·············",
                                       "Deodorizers·········" };

    this->medicine_names = inhalants_names;
    this->refill(); 
  }
};

class Cannabis : public MedicineStock {
public:
  Cannabis() { 
    vector<string> cannabis_names = { "Marijuana···········",
                                      "Hashish·············",
                                      "Hashish oil·········",
                                      "Sativex·············" };
    
    this->medicine_names = cannabis_names;
    this->refill(); 
  }
};

struct Examples { 
  Stimulants stimulants_stock;
  Opioids opioids_stock;
  Depressants depressants_stock;
  Hallucinogens hallucinogens_stock;
  Dissociatives dissociatives_stock;
  Inhalants inhalants_stock;
  Cannabis cannabis_stock;
};

#endif /* MEDICINES */
