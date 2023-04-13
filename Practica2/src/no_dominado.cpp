/**
 * @file no_dominado.cpp
 * @brief Implementación de algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional.
 * @author [Leon Elliott Fuller]
 */
 
/*
El código implementa dos algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional. El problema consiste en encontrar los puntos que no son dominados por ningún otro punto del conjunto, es decir, aquellos puntos que tienen todas sus coordenadas mayores o iguales que las de otro punto, y al menos una coordenada mayor.

El primer algoritmo, llamado "algoritmo básico", recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a una lista de puntos no dominados.

El segundo algoritmo, llamado "algoritmo Divide y Vencerás", divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.

Ambos algoritmos utilizan la función is_dominated() para verificar si un punto domina a otro, es decir, si todas las coordenadas del primer punto son mayores o iguales que las del segundo punto y al menos una coordenada del primer punto es mayor que la del segundo punto.

La función main() crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando ambos algoritmos. Los resultados se imprimen en la consola.
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

const int K = 10; /**< Dimensión del espacio de características. */

/**
 * @brief Verifica si un punto domina a otro.
 * 
 * Un punto p1 domina a otro punto p2 si todas las coordenadas de p1 son mayores o iguales a las de p2 y al menos una coordenada de p1 es mayor a la de p2.
 * 
 * @param p1 Punto que se evalúa.
 * @param p2 Punto de referencia.
 * @return Verdadero si el punto p1 domina al punto p2, falso en caso contrario.
 */
bool is_dominated(array<double, K> p1, array<double, K> p2) {
    // Verificamos si todas las coordenadas del punto p1 son mayores o iguales que las coordenadas correspondientes del punto p2
    bool all_ge = true; // suponemos que todas las coordenadas de p1 son mayores o iguales que las de p2
    for (int i = 0; i < K; i++) {
        if (p1[i] < p2[i]) { // si encontramos alguna coordenada de p1 que es menor que la correspondiente coordenada de p2
            all_ge = false; // entonces p1 no domina a p2
            break; // podemos salir del ciclo porque ya sabemos que p1 no domina a p2
        }
    }
    if (all_ge) { // si todas las coordenadas de p1 son mayores o iguales que las de p2
        // Verificamos si al menos una coordenada del punto p1 es mayor que la correspondiente coordenada del punto p2
        for (int i = 0; i < K; i++) {
            if (p1[i] > p2[i]) { // si encontramos alguna coordenada de p1 que es mayor que la correspondiente coordenada de p2
                return true; // entonces p1 domina a p2
            }
        }
        return false; // si no encontramos ninguna coordenada de p1 mayor que la correspondiente coordenada de p2, entonces p1 no domina a p2
    } else { // si al menos una coordenada de p1 es menor que la correspondiente coordenada de p2
        return false; // entonces p1 no domina a p2
    }
}

/**
 * @brief Algoritmo básico para encontrar los puntos no dominados en un conjunto de puntos.
 * 
 * El algoritmo recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a la lista de puntos no dominados.
 * 
 * @param points Conjunto de puntos de entrada.
 * @return Lista de puntos no dominados.
 */
vector<array<double, K>> basic_algorithm(vector<array<double, K>> points) {
    vector<array<double, K>> non_dominated;
    for (int i = 0; i < points.size(); i++) {
        bool dominated = false;
        for (int j = 0; j < points.size(); j++) {
            if (i != j && is_dominated(points[j], points[i])) {
                dominated = true;
                break;
            }
        }
        if (!dominated) {
            non_dominated.push_back(points[i]);
        }
    }
    return non_dominated;
}

/**
 * @brief Algoritmo Divide y Vencerás para encontrar los puntos no dominados en un conjunto de puntos.
 * 
 * El algoritmo divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.
 * 
 * @param points Conjunto de puntos de entrada.
 * @return Lista de puntos no dominados.
 */
vector<array<double, K>> divide_venceras(vector<array<double, K>> points) {
    if (points.size() == 1) {
        return points;
    }
    
    int midpoint = points.size() / 2;
    
    auto left = divide_venceras(vector<array<double, K>>(points.begin(), points.begin() + midpoint));
    auto right = divide_venceras(vector<array<double, K>>(points.begin() + midpoint, points.end()));
    
    vector<array<double, K>> merged(left.size() + right.size());
    merge(left.begin(), left.end(), right.begin(), right.end(), merged.begin());
    vector<array<double, K>> non_dominated{merged[0]};
    
    for (int i = 1; i < merged.size(); i++) {
        if (none_of(non_dominated.begin(), non_dominated.end(), [&](array<double, K> p){return is_dominated(merged[i], p);})) {
            non_dominated.push_back(merged[i]);
        }
    }
    return non_dominated;
}

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


/**

@brief Función principal del programa.
La función crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando los algoritmos básico y Divide y Vencerás.
@return Código de salida del programa.
*/
int main() {
    const int N = 100; /**< Número de puntos en el conjunto de entrada. */
    vector<array<double, K>> points(N);
    for (auto& p : points) {
        for (int i = 0; i < K; i++) {
            p[i] = (double)rand() / RAND_MAX;
        }
    }
    auto no_dominado1 = basic_algorithm(points);
    auto no_dominado2 = divide_and_conquer(points);
    cout << "El algoritmo básico ha encontrado " << non_dominated1.size() << " puntos no dominados." << endl;
    cout << "El algoritmo divide y venceras " << non_dominated2.size() << " puntos no dominados." << endl;
    
    // Parte que usa la clase para hacer las pruebas del programa
    if (argc != 5) {
        cout << "Usage: ./non_dominated <seed> <N> <K> <trials>" << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    int N = atoi(argv[2]);
    int K = atoi(argv[3]);
    int pruebas = atoi(argv[4]);

    srand(seed);

    NonDominatedTester tester;

    cout << "Ejecutado pruebas para N=" << N << ", K=" << K << ", pruebas=" << pruebas << endl;
    tester.test(N, pruebas);
    
    return 0;
}

