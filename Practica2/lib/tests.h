#ifndef __TESTS__
#define __TESTS__

#include <cstdlib>
#include <iostream>

using namespace std;

struct Punto {    /**< Numero de coordenadas del punto. */
    vector<double> coordenadas;
};

/**
 * @brief Clase para generar casos de prueba y verificar los resultados de los algoritmos.
 */
class Tests {
public:
    static const int K = 2; /**< Dimensión del espacio de características. */

    vector<Punto> generate_random_points(int N, int dim) {
        vector<Punto> points(N);
        for (int i = 0; i < N; i++) {
            points[i].coordenadas = generate_random_point(dim);
        }
        return points;
    }

    bool compare_non_dominated(vector<Punto> non_dominated1, vector<Punto> non_dominated2) {
        if (non_dominated1.size() != non_dominated2.size()) {
            return false;
        }
        for (const Punto &p1 : non_dominated1) {
            bool found = false;
            for (const Punto &p2 : non_dominated2) {
                if (p1.coordenadas == p2.coordenadas) {
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

    void test_algorithm(int N, int trials, int dim, int seed, vector<Punto>(*algorithm)(const vector<Punto>&, int)) {
        srand(seed);
        for (int i = 0; i < trials; i++) {
            vector<Punto> points = generate_random_points(N, dim);
            vector<Punto> non_dominated = algorithm(points, dim);

            cout << "Test " << i << " - Dimension: " << dim << endl;
            print_non_dominated(non_dominated);
        }
    }

    void print_non_dominated(const vector<Punto>& non_dominated) {
    for (const Punto& point : non_dominated) {
        for (size_t j = 0; j < point.coordenadas.size(); ++j) {
            cout << point.coordenadas[j];
            if (j < point.coordenadas.size() - 1) {
                cout << "\t";  // Imprime un carácter de tabulación entre coordenadas
            }
        }
        cout << endl;
    }
    
    void print_points(const vector<Punto>& points) {
        cout << "Points:" << endl;
        for (const Punto& point : points) {
            for (size_t j = 0; j < point.coordenadas.size(); ++j) {
                cout << point.coordenadas[j];
                if (j < point.coordenadas.size() - 1) {
                    cout << "\t";  // Imprime un carácter de tabulación entre coordenadas
                }
            }
            cout << endl;
        }
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
    
    void print_point(const Punto &point) {
        cout << "(";
        for (size_t j = 0; j < point.coordenadas.size(); j++) {
            cout << point.coordenadas[j];
            if (j < point.coordenadas.size() - 1) {
                cout << ",";
            }
        }
        cout << ")";
    }
};


#endif /*__TESTS__*/
