/**
 * @file no_dominado.cpp
 * @brief Implementación de algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional.
 * @author [Leon Elliott Fuller]
 */
 
/*
El código implementa dos algoritmos para encontrar los puntos no dominados en un conjunto de puntos en un espacio K-dimensional. El problema consiste en encontrar los puntos que no son dominados por ningún otro punto del conjunto, es decir, aquellos puntos que tienen todas sus coordenadas mayores o iguales que las de otro punto, y al menos una coordenada mayor.

El primer algoritmo, llamado "algoritmo básico", recorre todos los puntos del conjunto y verifica si cada punto es dominado por algún otro punto. Si un punto no es dominado por ningún otro, se añade a una lista de puntos no dominados.

El segundo algoritmo, llamado "algoritmo Divide y Vencerás", divide el conjunto de puntos en dos subconjuntos de tamaño aproximadamente igual, resuelve el problema en cada subconjunto de manera recursiva y fusiona las soluciones en un único conjunto de puntos no dominados.

Ambos algoritmos utilizan la función domina() para verificar si un punto domina a otro, es decir, si todas las coordenadas del primer punto son mayores o iguales que las del segundo punto y al menos una coordenada del primer punto es mayor que la del segundo punto.

La función main() crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando ambos algoritmos. Los resultados se imprimen en la consola.
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "tests.h"

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
bool domina(const Punto& p1, const Punto& p2, int K) {
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

/**
 * @brief Fusiona dos listas de puntos no dominados.
 * 
 * @param A Lista de puntos no dominados.
 * @param B Lista de puntos no dominados.
 * @param K Dimensión del espacio en el que están los puntos.
 * @return Lista con los puntos no dominados de ambas listas.
 */
vector<Punto> fusionar(const vector<Punto>& A, const vector<Punto>& B, int K) {
    vector<Punto> no_dominados; // Vector para almacenar los puntos no dominados
    // Comparamos cada punto de A con los puntos de B para determinar si es dominado por algún punto de B
    for (const Punto& pi : A) {
        bool dominado = false;
        for (const Punto& pj : B) {
            if (domina(pj, pi, K)) { // Si un punto de B domina al punto de A, lo marcamos como dominado y salimos del ciclo
                dominado = true;
                break;
            }
        }
        if (!dominado) { // Si el punto de A no ha sido dominado por ningún punto de B, lo agregamos al vector de puntos no dominados
            no_dominados.push_back(pi);
        }
    }
    // Comparamos cada punto de B con los puntos de A para determinar si es dominado por algún punto de A
    for (const Punto& pi : B) {
        bool dominado = false;
        for (const Punto& pj : A) {
            if (domina(pj, pi, K)) { // Si un punto de A domina al punto de B, lo marcamos como dominado y salimos del ciclo
                dominado = true;
                break;
            }
        }
        if (!dominado) { // Si el punto de B no ha sido dominado por ningún punto de A, lo agregamos al vector de puntos no dominados
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

@brief Función principal del programa.
La función crea un conjunto de puntos aleatorios y encuentra los puntos no dominados usando los algoritmos básico y Divide y Vencerás.
@return Código de salida del programa.
*/
int main(int argc, char **argv) {
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

