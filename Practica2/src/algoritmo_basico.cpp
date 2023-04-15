#include <iostream>
#include <cstdlib>
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
 * @brief Encuentra los puntos no dominados en un conjunto de puntos.
 * 
 * @param C Conjunto de puntos.
 * @param K Dimensión del espacio en el que están los puntos.
 * @return Vector con los puntos no dominados en el conjunto.
 */
vector<Punto> encontrar_no_dominados(const vector<Punto>& C, int K) {
    vector<Punto> no_dominados; // Vector para almacenar los puntos no dominados
    for (const Punto& pi : C) { // Recorremos todos los puntos del conjunto
        bool dominado = false;
        for (const Punto& pj : C) { // Comparamos el punto con todos los demás puntos del conjunto
            if (&pi != &pj && domina(pj, pi, K)) { // Si un punto domina al punto actual, lo marcamos como dominado y salimos del ciclo
                dominado = true;
                break;
            }
        }
        if (!dominado) { // Si el punto no ha sido dominado por ningún otro, lo agregamos al vector de puntos no dominados
            no_dominados.push_back(pi);
        }
    }
    return no_dominados;
}

int main(int argc, char **argv) {
    if (argc != 5) {
        cout << "Usage: ./algoritmo_basico <seed> <N> <K> <trials>" << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    int N = atoi(argv[2]);
    int K = atoi(argv[3]);
    int pruebas = atoi(argv[4]);

    srand(seed);

    NonDominatedTester tester;
    cout << "Algoritmo basico." << endl;
    cout << "Ejecutado pruebas para N=" << N << ", K=" << K << ", pruebas=" << pruebas << endl;
    tester.test(N, pruebas);
    
    return 0;
}
