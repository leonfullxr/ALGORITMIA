#include <iostream>
#include <chrono>
#include <cstdlib>

typedef unsigned long ul;

using namespace std;

void insertInPos(double *tree, int pos) { /** T(n/2) + 1 **/
  int idx = pos - 1;
  int parent;       

  if(idx > 0) {       /* T(n/2) + 1 */
    parent = (idx - ((idx%2 == 0) ? 2 : 1)) / 2;

    if(tree[parent] > tree[idx]) {  /* T(n/2) + 1 */
      double tmp = tree[idx];

      tree[idx] = tree[parent];
      tree[parent] = tmp;

      insertInPos(tree, parent+1);  // T(n/2) + 1
    }
  }
}

void restructRoot(double *tree, int pos, int tree_size) { /** T(n/2) + 1 **/
  int min;  // minimum son

  if((pos << 1) + 1 < tree_size) { /* T(n/2) + 1 */
    min = (pos << 1) + 1;

    if((min+1 < tree_size) && (tree[min] > tree[min+1])) /* T(1) */
      ++min;

    if(tree[pos] > tree[min]) { /* T(n/2) + 1 */
      double tmp = tree[pos];

      tree[pos] = tree[min];
      tree[min] = tmp;

      restructRoot(tree, min, tree_size); /* T(n/2) + 1 */
    }
  }
}

void HeapSort(int *v, int n) { /** nT(log(n)) **/
  double *tree = new double[n];

  int tree_size = 0;

  for(int i = 0; i < n; ++i) { /* nT(log(n)) */
    tree[tree_size++] = v[i];

    insertInPos(tree, tree_size); // T(log(n))
  }

  for(int i = 0; i < n; ++i) { /* nT(log(n)) */
    v[i] = tree[0];

    tree[0] = tree[--tree_size];

    restructRoot(tree, 0, tree_size); // T(log(n))
  }

  delete [] tree;
}

int main(int argc, char *argv[]) {
  if(argc <= 3) {
    cerr << "Error: Use ./program <Seed> <Max_Value> <Array_Size_1> <Array_Size_2> ... <Array_Size_n>" << endl;
    return 1;
  }

  int seed = atoi(argv[1]);
  int vmax = atoi(argv[2]);

  if(vmax <= 0) {
    cerr << "Error: Values out of bounds (Array_Size <= 0 or Max_Value <= 0)" << endl;
    return 1;
  }

  cout << "Size\tTime" << endl;
  for(int arg = 3; arg < argc; ++arg) {
    int vsize = atoi(argv[arg]);

    if(vsize <= 0) {
      cerr << "Error: Values out of bounds (Array_Size <= 0 or Max_Value <= 0)" << endl;
      return 1;
    }

    srand(seed);

    int *v = new int[vsize];


    for(int i = 0; i < vsize; ++i) {
      v[i] = rand()%vmax;
//      fprintf(stdout, "v[%d] = %d\n", i, v[i]);
    }

    chrono::time_point<std::chrono::high_resolution_clock> t_begin, t_end;

    t_begin = std::chrono::high_resolution_clock::now();

    HeapSort(v, vsize);

    t_end = std::chrono::high_resolution_clock::now();

    ul T;

    T = std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();
    
//    for(int i = 0; i < vsize; ++i)
//      fprintf(stdout, "v[%d] = %d\n", i, v[i]);

    cout <<  vsize << "\t" << T << endl;

    delete [] v;
  }

  return 0;
}

