#ifndef FUNC_TESTS
#define FUNC_TESTS

#include <vector>
#include <chrono>
#include "punto.h"


namespace para_tests {
    /**
     * @brief Iniciliza vec con tam puntos de de dimension dimension, cuyas coordenadas
     * son aleatorias.
     */
    void inicializaConPuntosAleatorios(std::vector<Punto> & vec, int tam, int dimension) {
        vec.clear();
        for(int i=0; i < tam; i++) {
            vec.push_back(Punto(dimension));
        }
    }


    /**
     * @return Devuelve cuantos ms tarda no_ominados cuando se ejecuta con puntos
     */
    int cuantoTarda(std::vector<Punto> (*noDominados)(const std::vector<Punto> &), std::vector<Punto> puntos) {
        auto momento_inicio = std::chrono::high_resolution_clock::now();
        noDominados(puntos);
        auto momento_final =  std::chrono::high_resolution_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(momento_final - momento_inicio);
        return duracion.count();
    }
}

#endif /* FUNC_TESTS */
