#ifndef __HYPERPLANE__
#define __HYPERPLANE__

#include <vector>
#include <cstdlib>
#include <iostream>

typedef long long ll;
typedef unsigned int ui;

using namespace std;

const int K = 10; /** Dimensión del espacio de características **/

struct point {    /** Numero de coordenadas del punto **/
    vector<double> coords;
};

/********************************************************
 * FUNCIONES GENERALES
 ********************************************************/

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
bool domina(const point& p1, const point& p2, int K) {
    bool estrictamente_mayor = false;
    for (int i = 0; i < K; ++i) {
        if (p1.coords[i] < p2.coords[i]) {
            return false;
        }
        if (p1.coords[i] > p2.coords[i]) {
            estrictamente_mayor = true;
        }
    }
    return estrictamente_mayor;
}

/********************************************************
 * FUNCIONES SECUENCIALES
 ********************************************************/

/**
 * @brief Encuentra los puntos no dominados en un conjunto de puntos.
 * 
 * @param C Conjunto de puntos.
 * @param K Dimensión del espacio en el que están los puntos.
 * @return Vector con los puntos no dominados en el conjunto.
 */
vector<point> encontrar_no_dominados(const vector<point>& C, int K) {
    vector<point> no_dominados; // Vector para almacenar los puntos no dominados
    for (const point& pi : C) { // Recorremos todos los puntos del conjunto
        bool dominado = false;
        for (const point& pj : C) { // Comparamos el punto con todos los demás puntos del conjunto
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

/********************************************************
 * FUNCIONES DIVIDE Y VENCERAS
 ********************************************************/

/**
 * @brief Fusiona dos listas de puntos no dominados.
 * 
 * @param A Lista de puntos no dominados.
 * @param B Lista de puntos no dominados.
 * @param K Dimensión del espacio en el que están los puntos.
 * @return Lista con los puntos no dominados de ambas listas.
 */
vector<point> fusionar(const vector<point>& A, const vector<point>& B, int K) {
    vector<point> no_dominados; // Vector para almacenar los puntos no dominados
    // Comparamos cada punto de A con los puntos de B para determinar si es dominado por algún punto de B
    for (const point& pi : A) {
        bool dominado = false;
        for (const point& pj : B) {
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
    for (const point& pi : B) {
        bool dominado = false;
        for (const point& pj : A) {
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
vector<point> divide_venceras(const vector<point>& C, int K) {
    if (C.size() <= 1) {
        return C;
    }

    int medio = C.size() / 2;
    vector<point> izquierda(C.begin(), C.begin() + medio);
    vector<point> derecha(C.begin() + medio, C.end());

    vector<point> no_dominados_izquierda = divide_venceras(izquierda, K);
    vector<point> no_dominados_derecha = divide_venceras(derecha, K);

    return fusionar(no_dominados_izquierda, no_dominados_derecha, K);
}

#endif /*__HYPERPLANE__*/
