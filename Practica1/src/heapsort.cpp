#include <iostream>
#include <chrono>
#include <cstdlib>

typedef unsigned long ul;

using namespace std;

void insertInPos(double *tree, int pos) { /** O( ) **/
  int idx = pos - 1;
  int parent;       

  if(idx > 0) {       /* O( ) */
    parent = (idx - ((idx%2 == 0) ? 2 : 1)) / 2;

    if(tree[parent] > tree[idx]) {  /* O( ) */
      double tmp = tree[idx];

      tree[idx] = tree[parent];
      tree[parent] = tmp;

      insertInPos(tree, parent+1);  // O( )
    }
  }
}

void restructRoot(double *tree, int pos, int tree_size) { /** O( ) **/
  int min = 0;  // hijo minimo

  if((min+1 < tree_size) && (tree[min] > tree[min+1])) /* O(1) */
    ++min;

  if(tree[pos] > tree[min]) { /* O( ) */
    double tmp = tree[pos];

    tree[pos] = tree[min];
    tree[pos] = tmp;

    restructRoot(tree, min, tree_size); /* O() */
  }
}

void HeapSort(int *v, int n) { /** O( ) **/
  double *tree = new double[n];

  int tree_size = 0;

  for(int i = 0; i < n; ++i) { /* O( ) */
    tree[tree_size++] = v[i];

    insertInPos(tree, tree_size); // O( )
  }

  for(int i = 0; i < n; ++i) { /* O( ) */
    v[i] = tree[0];

    tree[0] = tree[--tree_size];

    restructRoot(tree, 0, tree_size); // O( )
  }

  delete [] tree;
}

int main(int argc, char *argv[]) {
  if(argc <= 2) {
    cerr << "Error: Use ./program <Max_Value> <Array_Size_1> <Array_Size_2> ... <Array_Size_n>" << endl;
    return 1;
  }

  int vmax = atoi(argv[1]);

  if(vmax <= 0) {
    cerr << "Error: Values out of bounds (Array_Size <= 0 or Max_Value <= 0)" << endl;
    return 1;
  }

  for(int arg = 2; arg < argc; ++arg) {
    int vsize = atoi(argv[arg]);

    if(vsize <= 0) {
      cerr << "Error: Values out of bounds (Array_Size <= 0 or Max_Value <= 0)" << endl;
      return 1;
    }

    int *v = new int[vsize];

    int value = vsize-1;

    for(int i = 0; i < 0; ++i)
      v[i] = value--;

    chrono::time_point<std::chrono::high_resolution_clock> t_begin, t_end;

    t_begin = std::chrono::high_resolution_clock::now();

    HeapSort(v, vsize);

    t_end = std::chrono::high_resolution_clock::now();

    ul T;

    T = std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

    cout << "Size: " << vsize << "\nTime: " << T << " µs\n" << endl;

    delete [] v;
  }

  return 0;
}

