#ifdef __TESTS__
#define __TESTS__

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief Clase para generar casos de prueba y verificar los resultados de los algoritmos.
 */
class NonDominatedTester {
public:
    /**
     * @brief Genera un conjunto de puntos aleatorios en el rango [0, 1] en un espacio K-dimensional.
     * 
     * @param N Número de puntos que se generarán.
     * @return Conjunto de puntos generados.
     */
    vector<array<double, K>> generate_random_points(int N) {
        vector<array<double, K>> points;
        for (int i = 0; i < N; i++) {
            array<double, K> point = generate_random_point();
            points.push_back(point);
        }
        return points;
    }
    
    /**
     * @brief Verifica si dos listas de puntos contienen los mismos puntos no dominados.
     * 
     * @param non_dominated1 Lista de puntos no dominados.
     * @param non_dominated2 Lista de puntos no dominados.
     * @return Verdadero si las dos listas contienen los mismos puntos no dominados, falso en caso contrario.
     */
    bool compare_non_dominated(vector<array<double, K>> non_dominated1, vector<array<double, K>> non_dominated2) {
        if (non_dominated1.size() != non_dominated2.size()) {
            return false;
        }
        for (int i = 0; i < non_dominated1.size(); i++) {
            bool found = false;
            for (int j = 0; j < non_dominated2.size(); j++) {
                if (non_dominated1[i] == non_dominated2[j]) {
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

    /**
     * @brief Ejecuta varios tests aleatorios de los algoritmos básico y Divide y Vencerás y verifica si los resultados son iguales.
     * 
     * @param N Número de puntos en cada conjunto de prueba.
     * @param trials Número de pruebas aleatorias que se realizarán.
     */
    void test(int N, int trials) {
        srand(0); // establecemos la semilla aleatoria para obtener los mismos resultados en cada ejecución
        for (int i = 0; i < trials; i++) {
            // Generamos un conjunto de puntos aleatorios
            vector<array<double, K>> points = generate_random_points(N);
            // Ejecutamos los algoritmos básico y Divide y Vencerás
            vector<array<double, K>> non_dominated_basic = basic_algorithm(points);
            vector<array<double, K>> non_dominated_divide_and_conquer = divide_and_conquer_algorithm(points);
            // Verificamos si los resultados son iguales
            bool equal = compare_non_dominated(non_dominated_basic, non_dominated_divide_and_conquer);
            // Imprimimos información sobre el resultado del test
            cout << "Test " << i << ": ";
            if (equal) {
                cout << "OK" << endl;
            } else {
                cout << "FAILED" << endl;
                cout << "Points:" << endl;
                for (int j = 0; j < points.size(); j++) {
                    cout << "(";
                    for (int k = 0; k < K; k++) {
                        cout << points[j][k];
                        if (k < K - 1) {
                            cout << ",";
                        }
                    }
                    cout << ")" << endl;
                }
                cout << "Basic algorithm: ";
                print_non_dominated(non_dominated_basic);
                cout << "Divide and conquer algorithm: ";
                print_non_dominated(non_dominated_divide_and_conquer);
            }
        }
    }
    
    /**
     * @brief Imprime la lista de puntos no dominados.
     * 
     * @param non_dominated Lista de puntos no dominados.
     */
    void print_non_dominated(vector<array<double, K>> non_dominated) {
        cout << "{";
        for (int i = 0; i < non_dominated.size(); i++) {
            cout << "(";
            for (int j = 0; j < K; j++) {
                cout << non_dominated[i][j];
                if (j < K - 1) {
                    cout << ",";
                }
            }
            cout << ")";
            if (i < non_dominated.size() - 1) {
                cout << ",";
            }
        }
        cout << "}" << endl;
    }
    
private:
    /**
     * @brief Genera un punto aleatorio en el rango [0, 1] en un espacio K-dimensional.
     * 
     * @return Punto aleatorio generado.
     */
    array<double, K> generate_random_point() {
        array<double, K> point;
        for (int i = 0; i < K; i++) {
            point[i] = (double)rand() / RAND_MAX;
        }
        return point;
    }
};

#endif /*__TESTS__*/
