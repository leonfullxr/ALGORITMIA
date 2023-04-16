#ifndef ND_DYV2
#define ND_DYV2

#include <vector>
#include "punto.h"

namespace nd_DyV2 {
    
    std::vector<Punto> fusiona_no_dominados(const std::vector<Punto> & izquierda, const std::vector<Punto> & derecha) {
        std::vector<Punto> fusion = izquierda;
        fusion.reserve(izquierda.size() + derecha.size());
        int cant_no_dominados_iz = fusion.size();

        for (const Punto& posible_dominante_der : derecha) {
            bool no_dominado = true;

            for (int i = 0; i < cant_no_dominados_iz; i++) {
                if (fusion[i] > posible_dominante_der) {
                    no_dominado = false;
                    break;
                } else if (posible_dominante_der > fusion[i]) {
                    fusion.erase(fusion.begin() + i);
                    cant_no_dominados_iz--;
                    i--;
                }
            }

            if (no_dominado) {
                fusion.push_back(posible_dominante_der);
            }
        }

        return fusion;
    }
    
    /**
     * @brief Encuentra los puntos no dominados en un conjunto de puntos.
     * @return vector con los puntos no dominados en el conjunto.
     */
    std::vector<Punto> noDominados(const std::vector<Punto>& puntos) {
        if (puntos.size() <= 1) {
            return puntos;
        }

        int medio = puntos.size() / 2;
        std::vector<Punto> izquierda(puntos.begin(), puntos.begin() + medio);
        std::vector<Punto> derecha(puntos.begin() + medio, puntos.end());

        std::vector<Punto> no_dominados_izquierda = noDominados(izquierda);
        std::vector<Punto> no_dominados_derecha = noDominados(derecha);

        return fusiona_no_dominados(no_dominados_izquierda, no_dominados_derecha);
    }

}

#endif /* ND_DYV2 */
