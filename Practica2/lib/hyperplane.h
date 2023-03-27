#ifndef __HYPERPLANE__
#define __HYPERPLANE__

#include <vector>
#include <cstdlib>
#include <iostream>

#define MAX_VALUE 53

typedef long long ll;
typedef unsigned int ui;

using namespace std;

class node {
private:
  vector<ll> K_values;
  bool dominated;

public:
  node(): K_values(0, 0), dominated(false) {}

  node(ui size, bool random=false) {
    dominated = false;

    for(ui i = 0; i < size; ++i)
      K_values.push_back((random) ? (ll)rand()%MAX_VALUE : 0);
  }

  ui size() {
    return K_values.size();
  }

  /**
  inline bool operator< (const node &lhs, const node &rhs) {
    bool c1 = false;  // vi[a] >= vj[a] para todo a
    bool c2 = false   // vi[a] > vj[a] para al menos un a

    return true;
  }
  **/

  const ll &operator[] (size_t idx) const { return K_values[idx]; }
};

class Hyperplane {
private:
  ui size;  // C size
  ui K;     // dimension
  vector<node> C; // Set of points

  void initialize(int seed = -1) {
    srand(seed);
    bool r_flag = true;

    for(ui i = 0; i < size; ++i) {
      
      if(seed != -1) {
        node aux_n(K, r_flag);
        C.push_back(aux_n);
      } else {
        node aux_n(K);
        C.push_back(aux_n);
      }
    }
  }

public:
  Hyperplane() {    
    size = 
    K = 10;

    initialize();
  }

  Hyperplane(ui size, ui K) {
    this->size = size;
    this->K = K;

    initialize();
  }

  Hyperplane(ui size, ui K, ui seed) {
    this->size = size;
    this->K = K;

    initialize(seed);
  }

  void print() {
    for(ui i = 0; i < size; ++i) {
      cout << "\nC[" << i << "] = " << C[i][0];
      
      for(ui j = 1; j < K; ++j)
        cout << " ; " << C[i][j];
    }
  }

private:

public:
};

#endif /*__HYPERPLANE__*/
