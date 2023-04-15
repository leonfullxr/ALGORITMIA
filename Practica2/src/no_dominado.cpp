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

struct Punto {    /**< Numero de coordenadas del punto. */
    vector<int> coordenadas;
};

/**
 * @brief Verifica si un punto domina a otro.
 * 
 * Un punto p1 domina a otro punto p2 si todas las coordenadas de p1 son mayores o iguales a las de p2 y al menos una coordenada de p1 es mayor a la de p2.
 * 
 * @param p1 Punto que se evalúa.
 * @param p2 Punto de referencia.
 * @param K Numero de dimensiones del espacio
 * @return Verdadero si el punto p1 domina al punto p2, falso en caso contrario.
 */
bool is_dominated(const Punto& p1, const Punto& p2, int K) {
    bool estrictamente_mayor = false;
    for (int i = 0; i < K; ++i) {
        if (p1.coordenadas[i] < p2.coordenadas[i]) {
            return false;
        }
        if (p1.coordenadas[i] > p2.coordenadas[i]) {
            estrictamente_mayor = true;
        }
    }
    return estrictamente_mayor;
}

vector<Punto> encontrar_no_dominados(const vector<Punto>& C, int K) {
    vector<Punto> no_dominados;
    for (const Punto& pi : C) {
        bool dominado = false;
        for (const Punto& pj : C) {
            if (&pi != &pj && domina(pj, pi, K)) {
                dominado = true;
                break;
            }
        }
        if (!dominado) {
            no_dominados.push_back(pi);
        }
    }
    return no_dominados;
}

/**
 * @brief Algoritmo básico para encontrar los puntos no dominados en un conjunto de puntos.
 * 
 * El algoritmo recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a la lista de puntos no dominados.
 * 
 * @param points Conjunto de puntos de entrada.
 * @return Lista de puntos no dominados.
 */
vector<Punto> basic_algorithm(const vector<Punto>& C, int K) {
    vector<Punto> no_dominados;
    for (const Punto& pi : C) {
        bool dominado = false;
        for (const Punto& pj : C) {
            if (&pi != &pj && domina(pj, pi, K)) {
                dominado = true;
                break;
            }
        }
        if (!dominado) {
            no_dominados.push_back(pi);
        }
    }
    return no_dominados;
}

vector<Punto> fusionar(const vector<Punto>& A, const vector<Punto>& B, int K) {
    vector<Punto> no_dominados;

    for (const Punto& pi : A) {
        bool dominado = false;
        for (const Punto& pj : B) {
            if (domina(pj, pi, K)) {
                dominado = true;
                break;
            }
        }
        if (!dominado) {
            no_dominados.push_back(pi);
        }
    }

    for (const Punto& pi : B) {
        bool dominado = false;
        for (const Punto& pj : A) {
            if (domina(pj, pi, K)) {
                dominado = true;
                break;
            }
        }
        if (!dominado) {
            no_dominados.push_back(pi);
        }
    }

    return no_dominados;
}

/**
 * @brief Algoritmo Divide y Vencerás para encontrar los puntos no dominados en un conjunto de puntos.
 * 
 * El algoritmo divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.
 * 
 * @param points Conjunto de puntos de entrada.
 * @return Lista de puntos no dominados.
 */
vector<Punto> divide_venceras(const vector<Punto>& C, int K) {
    if (C.size() <= 1) {
        return C;
    }

    int medio = C.size() / 2;
    vector<Punto> izquierda(C.begin(), C.begin() + medio);
    vector<Punto> derecha(C.begin() + medio, C.end());

    vector<Punto> no_dominados_izquierda = dividir_y_vencer(izquierda, K);
    vector<Punto> no_dominados_derecha = dividir_y_vencer(derecha, K);

    return fusionar(no_dominados_izquierda, no_dominados_derecha, K);
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
    srand(time(0));
    const int N = 1000;
    const int K = 10;

    vector<Punto> puntos(N);
    for (int i = 0; i < N; ++i) {
        puntos[i].coordenadas.resize(K);
        for (int j = 0; j < K; ++j) {
            puntos[i].coordenadas[j] = rand() % 100;
        }
    }

    clock_t inicio, fin;
    double tiempo;

    inicio = clock();
    vector<Punto> no_dominados_basic = encontrar_no_dominados(puntos, K);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Algoritmo básico:" << endl;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
    cout << "Número de puntos no dominados: " << no_dominados_basic.size() << endl;
    inicio = clock();
    vector<Punto> no_dominados_divyv = dividir_y_vencer(puntos, K);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Algoritmo Divide y Vencerás:" << endl;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
    cout << "Número de puntos no dominados: " << no_dominados_divyv.size() << endl;

    return 0;
    
    // Parte que usa la clase para hacer las pruebas del programa
    /*
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
    */
}

