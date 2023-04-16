#ifndef ND_SKILINE
#define ND_SKILINE

#include <vector>
#include "punto.h"

namespace nd_skiline {
    
    vector<point> merge_skyline(const vector<point>& A, const vector<point>& B, int K) {
		vector<point> no_dominados = A;

		for (const point& p : B) {
		    bool no_dominado = true;

		    for (int i = 0; i < no_dominados.size(); i++) {
		        if (domina(no_dominados[i], p, K)) {
		            no_dominado = false;
		            break;
		        } else if (domina(p, no_dominados[i], K)) {
		            no_dominados.erase(no_dominados.begin() + i);
		            i--;
		        }
		    }

		    if (no_dominado) {
		        no_dominados.push_back(p);
		    }
		}

		return no_dominados;
	}
	
	/**
     * @brief Encuentra los puntos no dominados en un conjunto de puntos.
     * @return std::vector con los puntos no dominados en el conjunto.
     */
	std::vector<point> noDominados(const std::vector<point>& C, int K) {
		if (C.size() <= 1) {
		    return C;
		}

		int medio = C.size() / 2;
		std::vector<point> izquierda(C.begin(), C.begin() + medio);
		std::vector<point> derecha(C.begin() + medio, C.end());

		std::vector<point> no_dominados_izquierda = skyline_divide_venceras(izquierda, K);
		std::vector<point> no_dominados_derecha = skyline_divide_venceras(derecha, K);

		return merge_skyline(no_dominados_izquierda, no_dominados_derecha, K);
	}

}

#endif /* ND_SKILINE */
