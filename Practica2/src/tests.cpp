// compilar desde la raiz del proyecto con g++ ./src/tests.cpp ./lib/*.h -o ./bin/tests.bin

#include <iostream>
#include <fstream>
#include <chrono>
#include "../lib/punto.h"
#include "../lib/funiciones_tests.h"
#include "../lib/no_dominados_sencillo.h"
#include "../lib/no_dominados_DyV.h"

using namespace std;

const string test_results_dir = "./test_results/";

int main() {
    const int DIMENSION = 10;
    const int PASO = 50;
    const int MAXIMO = 500;
    const int REP_POR_MUESTRA = 1;
    
    
    ofstream resutlados;
    
    auto ahora = chrono::system_clock::to_time_t(chrono::system_clock::now());
    resutlados.open(test_results_dir + "resultados - " + ctime(&ahora) + ".ods");
    
    if (not resutlados.is_open()) {
        cerr << "Error al abrir el archivo de resultados" << endl;
        cerr << "¿Estas ejecutando deste la raiz del proyecto?" << endl;
        exit(-1);
    }
    
    resutlados << "Numero de puntos; Tiempo en ms del algoritmo sencillo:; Tiempo en ms del algiritmo DyV:;" << endl;
    
    for(int num_puntos = PASO; num_puntos <= MAXIMO; num_puntos += PASO) {
        float duracion_sencillo = 0;
        float duracion_DyV = 0;
        
        for(int rep=0; rep < REP_POR_MUESTRA; rep++) {
            vector<Punto> puntos;
            para_tests::inicializaConPuntosAleatorios(puntos, num_puntos, DIMENSION);
            duracion_sencillo += (float)para_tests::cuantoTarda(&nd_sencillo::noDominados, puntos);
            duracion_DyV += (float)para_tests::cuantoTarda(&nd_DyV::noDominados, puntos);
        }
        duracion_sencillo /= REP_POR_MUESTRA;
        duracion_DyV /= REP_POR_MUESTRA;
        
        resutlados << num_puntos << ";" << duracion_sencillo << ";" << duracion_DyV << ";" << endl;
    }
    
    resutlados.close();
}
