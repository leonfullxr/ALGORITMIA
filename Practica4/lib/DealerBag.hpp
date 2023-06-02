#ifndef DEALERBAG
#define DEALERBAG

#include <chrono>
#include "Medicines.hpp"

class DealerBag {
private:
  MedicineStock stock;
  MedicineType stock_type;

  int max_weight;
  int col_weight;
  vector<vector<int>> solution;

public:
  DealerBag() {
    this->max_weight = MAX_WEIGHT;
    this->col_weight = COL_WEIGHT;
  }

  DealerBag(const MedicineType &stock_type, const int &max_weight=MAX_WEIGHT, const int &col_weight=COL_WEIGHT) {
    initializeWithExample(stock_type);

    this->max_weight = max_weight;
    this->col_weight = col_weight;
    
    initializeSolution();
  }

  void initializeBenchmark(const int &number_of_elements, const int &max_weight, const int &col_weight) {
    stock.randomFill(number_of_elements);

    this->max_weight = max_weight;
    this->col_weight = col_weight;
 
    initializeSolution();
  }

  void defaultOptions(const int &option) {
    switch(option) {
      case 1:
        initializeWithExample(STIMULANTS);
        break;
      case 2:
        initializeWithExample(OPIOIDS);
        break;
      case 3:
        initializeWithExample(DEPRESSANTS);
        break;
      case 4:
        initializeWithExample(HALLUCINOGENS);
        break;
      case 5:
        initializeWithExample(DISSOCIATIVES);
        break;
      case 6:
        initializeWithExample(INHALANTS);
        break;
      case 7:
        initializeWithExample(CANNABIS);
        break;

      default:
        cerr << "ERROR: Non valid option" << endl;
        break;
    }
  }

  void fillBag(const bool &show_flag=false) {
    string medicine_name;

    switch(stock_type) {
      case STIMULANTS:
        medicine_name = "Stimulants";
        break;

      case OPIOIDS:
        medicine_name = "Opioids";
        break;

      case DEPRESSANTS:
        medicine_name = "Depressants";
        break;

      case HALLUCINOGENS: 
        medicine_name = "Hallucinogens";
        break;

      case DISSOCIATIVES:  
        medicine_name = "Dissociatives";
        break;

      case INHALANTS:
        medicine_name = "Inhalants";
        break;

      case CANNABIS:
        medicine_name = "Cannabis";
        break;

      default:
        medicine_name = "Custom";
        break;
    }

    this->stock.showStock(medicine_name, show_flag);

    chrono::time_point<std::chrono::high_resolution_clock> t_begin, t_end;

    t_begin = std::chrono::high_resolution_clock::now();

    fillBag_DP();

    t_end = std::chrono::high_resolution_clock::now();

    unsigned long T;

    T = std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
    
    cout << "Time: " << T << " µs\n" << endl;
    showSolution(show_flag); 
  } 

  bool save(const string &file_path) {
    ofstream out;
    out.open(file_path);

    if(not out.is_open()) return false;

    out << this->stock;

    out.close();

    return true;
  }
    
  bool load(const string &file_path) {
    ifstream in;

    in.open(file_path);

    if(not in.is_open()) return false;

    in >> this->stock;
    in.close();

    initializeSolution();

    return true;
  }

private: 
  void initializeSolution() {
    int cols = this->max_weight/this->col_weight;

    vector<int> aux(cols, 0); 

    int rows = this->stock.size();

    for(int i = 0; i < rows; ++i)
      solution.push_back(aux); 
  }

  void initializeWithExample(const MedicineType &stock_type) {
    this->stock_type = stock_type;
    Examples stock_examples;

    switch(stock_type) {
      case STIMULANTS:
        this->stock = stock_examples.stimulants_stock;
        break;

      case OPIOIDS:
        this->stock = stock_examples.opioids_stock;
        break;

      case DEPRESSANTS:
        this->stock = stock_examples.depressants_stock;
        break;

      case HALLUCINOGENS: 
        this->stock = stock_examples.hallucinogens_stock;
        break;

      case DISSOCIATIVES: 
        this->stock = stock_examples.dissociatives_stock;
        break;

      case INHALANTS:
        this->stock = stock_examples.inhalants_stock;
        break;

      case CANNABIS:
        this->stock = stock_examples.cannabis_stock;
      break;
    }
  
    initializeSolution();
  }

  void fillBag_DP() {
    int bag_size = this->stock.size();
    int steps = this->solution[0].size();

    for(int i = 0; i < bag_size; ++i) {
      int idx_cost = this->stock[i].cost();
      int idx_weight = this->stock[i].weight();

      for(int j = 0; j < steps; ++j) {
        if(i == 0) {
          if(j+1 >= idx_weight)
            this->solution[i][j] = idx_cost;
        } else {
          if(j+1 < idx_weight)
            this->solution[i][j] = this->solution[i-1][j];
          else
            this->solution[i][j] = max(this->solution[i-1][j], idx_cost+this->solution[i-1][j-idx_weight]);
        }
      }
    }
  }

  void showSolution(const bool &show_flag) {
    int rows = solution.size();
    int cols = solution[0].size();

    if(show_flag) {
      for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
          if(i == 0) {
            if(j == 0)
              cout << "   ELEMENT\\WEIGHT   ";
            
            cout << "\t" << j+1;
          } else {
            if(j == 0)
              cout << stock[i].name();
            
            cout << "\t" << solution[i][j];
          }
        }
  
        cout << endl;
      }
    }

    cout << "Final solution = " << solution[rows-1][cols-1] << endl;
  }
};
#endif /* DEALERBAG */
