#ifndef PUNTO
#define PUNTO

#include <iostream>

class Punto {
public:
    /**
     * @brief Inicializa el Punto con coordenadas aleatorias, cada componente de ellas entre 0 y 1000
     */
    Punto(int _dimension) {
        dimension = _dimension;
        coordenadas = new float [dimension];
        for (int i = 0; i < dimension;  i++)
            coordenadas[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/1000.0f);
    }
    
    float & operator[](const int & i) {
        return coordenadas[i];
    }
    
    float operator[](const int & i) const {
        return coordenadas[i];
    }
    
    bool operator >(const Punto & otro) const{
        if(dimension != otro.dimension) {
            std::cerr << "Comparando puntos de dimensiones distintas" << std::endl;
            exit(-1);
        }
    
        bool domina = false;
        for (int i=0; i<dimension; i++) {
            if ((*this)[i] < otro[i]) {
                return false;
            }
            else if ((*this)[i] > otro[i]) {
                domina = true;
            }
        }
        return domina;
    }
    
    friend std::ostream & operator<<(std::ostream & out, const Punto & punto) {
        out << "{";
        for (int i = 0; i < punto.dimension; i++) {
            out << punto[i];
            
            if(i != punto.dimension-1) {
                out << ", ";
            }
        }
        out << "}";
        
        return out;
    }
    
private:
    float * coordenadas;
    int dimension;
};

#endif /* PUNTO */
