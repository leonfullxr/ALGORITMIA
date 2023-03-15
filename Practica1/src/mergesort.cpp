#include <cstdlib> // srand y rand
#include <chrono>
#include <iostream>
#include <cstring> // memcpy

typedef unsigned long int uli;
typedef unsigned long ul;

using namespace std;

void merge(int *v, int beg, int mid, int end, int *vaux) {
  int i = beg;
  int j = mid;
  int k = 0;

  while(i < mid && j < end) {
    if(v[i] <= v[j])  vaux[k++] = v[i++];
    else              vaux[k++] = v[j++];
  }

  while(i < mid)  vaux[k++] = v[i++]; 
  while(j <= end) vaux[k++] = v[j++];

  memcpy(v+beg, vaux, k*sizeof(int));
}

void MergeSort(int *v, int beg, int end, int *vaux) {
  if(beg >= end) return;

  int mid = (beg+end) / 2;

  MergeSort(v, beg, mid, vaux);
  MergeSort(v, mid+1, end, vaux);
  merge(v, beg, mid+1, end, vaux);
}

int main(int argc, char *argv[]) {
  if(argc <= 2) {
    cerr << "Error: Use ./program <Seed_Value> <Array_Size_1> <Array_Size_2> ... <Array_Size_n>" << endl;
    return 1;
  }

  uli seed = atoi(argv[2]);
  srand(seed);

  for(int arg = 3; arg < argc; ++arg) {
    int vsize = atoi(argv[arg]);

    int *v = new int[vsize];
    int *vaux = new int[vsize];

    for(int i = 0; i < vsize; ++i)
      v[i] = rand()%vsize;

    chrono::time_point<std::chrono::high_resolution_clock> t_begin, t_end;

    t_begin = std::chrono::high_resolution_clock::now();

    MergeSort(v, 0, vsize-1, vaux);

    t_end = std::chrono::high_resolution_clock::now();

    ul T;

    T = std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_begin).count();

    cout << "Size: " << vsize << "\nTime: " << T << " µs\n" << endl;

    delete [] v;
    delete [] vaux;
  }

  return 0;
}
