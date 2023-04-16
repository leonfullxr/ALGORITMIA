#ifndef ND_SENCILLO
#define ND_SENCILLO

#include <vector>
#include "punto.h"

namespace nd_sencillo {
    /**
     * @brief Encuentra los puntos no dominados en un conjunto de puntos.
     * @return vector con los puntos no dominados en el conjunto.
     */
    std::vector<Punto> noDominados(const std::vector<Punto>& puntos) {
        std::vector<Punto> no_dominados;
        no_dominados.reserve(puntos.size());
        for (const Punto & candidato : puntos) {
            bool dominado = false;
            
            for (const Punto & posible_dominante : puntos) {
                if (posible_dominante > candidato) { 
                    dominado = true;
                    break;
                }
            }
            
            if (not dominado) { 
                no_dominados.push_back(candidato);
            }
        }
        return no_dominados;
    }
}

#endif /* ND_SENCILLO */
