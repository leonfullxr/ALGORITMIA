#ifndef ND_DYV
#define ND_DYV

#include <vector>
#include "punto.h"

namespace nd_DyV {
    std::vector<Punto> fusiona_no_dominados(const std::vector<Punto> & izquierda, const std::vector<Punto> & derecha) {
        std::vector<Punto> fusion;
        std::vector<Punto> fusion_tras_primera_iter;
        std::pair<const std::vector<Punto> *, const std::vector<Punto> *> candiadtos_posibles_dominantes[2];
        candiadtos_posibles_dominantes[0] = std::pair<const std::vector<Punto> *, const std::vector<Punto> *>(&izquierda, &derecha);
        candiadtos_posibles_dominantes[1] = std::pair<const std::vector<Punto> *, const std::vector<Punto> *>(&derecha, &fusion_tras_primera_iter);
        
        for(int i=0; i<2; i++) {
            const std::vector<Punto> & candidatos = (*candiadtos_posibles_dominantes[i].first);
            const std::vector<Punto> & posibles_dominantes = (*candiadtos_posibles_dominantes[i].second);
            
            for(const Punto & candidato : candidatos) {
                bool dominado = false;
                
                for(const Punto & posible_dominante : posibles_dominantes) {
                    if (posible_dominante > candidato) {
                        dominado = true;
                        break;
                    }
                }
                
                if (not dominado) {
                    fusion.push_back(candidato);
                }
            }
            
            if (i == 0) fusion_tras_primera_iter = fusion;
        }
        
        return fusion;
    }
    
    /**
     * @brief Encuentra los puntos no dominados en un conjunto de puntos.
     * @return std::vector con los puntos no dominados en el conjunto.
     */
    std::vector<Punto> noDominados(const std::vector<Punto> & puntos) {
        if(puntos.size() == 1) return puntos;
        
        
        auto primero_der_it = puntos.begin() + (puntos.size()/2);
        std::vector<Punto> parte_izq = std::vector<Punto>(puntos.begin(), primero_der_it);
        std::vector<Punto> parte_der = std::vector<Punto>(primero_der_it, puntos.end());
        
        std::vector<Punto> dominantes_iz = noDominados(parte_izq);
        std::vector<Punto> dominantes_der = noDominados(parte_der);
        
        return fusiona_no_dominados(dominantes_iz, dominantes_der);
    }
}

#endif /* DN_DYV */
