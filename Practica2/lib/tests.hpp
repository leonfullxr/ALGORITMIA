#ifndef __TESTS__
#define __TESTS__

#include "hyperplane.hpp"
#include <chrono>

using namespace std;

/**
 * @brief Clase para generar casos de prueba y verificar los resultados de los algoritmos.
 */
class Tests {
public:
    static const int K = 10; /**< Dimensión del espacio de características. */

    vector<point> generate_random_points(int N, int dim) {
        vector<point> points(N);
        for (int i = 0; i < N; i++) {
            points[i].coords = generate_random_point(dim);
        }
        return points;
    }

    bool compare_non_dominated(vector<point> non_dominated1, vector<point> non_dominated2) {
        if (non_dominated1.size() != non_dominated2.size()) {
            return false;
        }
        for (const point &p1 : non_dominated1) {
            bool found = false;
            for (const point &p2 : non_dominated2) {
                if (p1.coords == p2.coords) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }

    void test_algorithm(int N, int trials, int dim, int seed, vector<point>(*algorithm)(const vector<point>&, int)) {
        srand(seed);
        for (int i = 0; i < trials; i++) {
            vector<point> points = generate_random_points(N, dim);

            // Registra el tiempo antes de ejecutar el algoritmo
            auto start_time = chrono::high_resolution_clock::now();

            vector<point> non_dominated = algorithm(points, dim);

            // Registra el tiempo después de ejecutar el algoritmo
            auto end_time = chrono::high_resolution_clock::now();

            // Calcula el tiempo transcurrido
            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

            cout << N << "\t" << duration << endl;
        }
    }

    void print_non_dominated(const vector<point>& non_dominated) {
      for (const point& point_idx : non_dominated) {
        for (size_t j = 0; j < point_idx.coords.size(); ++j) {
            cout << point_idx.coords[j];
            if (j < point_idx.coords.size() - 1) {
                cout << "\t";  // Imprime un carácter de tabulación entre coordenadas
            }
        }
        cout << endl;
      }
    }
    
    void print_points(const vector<point>& points) {
        cout << "Points:" << endl;
        for (const point& point_idx : points) {
            for (size_t j = 0; j < point_idx.coords.size(); ++j) { cout << point_idx.coords[j];
                if (j < point_idx.coords.size() - 1) {
                    cout << "\t";  // Imprime un carácter de tabulación entre coordenadas
                }
            }
            cout << endl;
        }
    }

private:
    vector<double> generate_random_point(int dim) {
        vector<double> point(dim);
        for (int i = 0; i < dim; i++) {
            point[i] = (double)rand() / RAND_MAX;
        }
        return point;
    }
    
    void print_point(const point &point_arg) {
        cout << "(";
        for (size_t j = 0; j < point_arg.coords.size(); j++) {
            cout << point_arg.coords[j];
            if (j < point_arg.coords.size() - 1) {
                cout << ",";
            }
        }
        cout << ")";
    }
};


#endif /*__TESTS__*/
