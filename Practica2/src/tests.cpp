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

int main(int argc, char * argv[]) {
    int REP_POR_MUESTRA = 1;
    int PASO = 500;
    int MAXIMO = 50000;
    int DIMENSION = 10;
    
    if (argc > 5) {
        cerr << "ERROR - Los argumentos del programa son:" << endl;
        cerr << "<repeticiones por muestra> <paso> <maximo> <dimension>" << endl;
        cerr << "y sus valores por defecto:" << endl;
        cerr << REP_POR_MUESTRA << " " << PASO << " " << MAXIMO << " " << DIMENSION << endl;
        exit(-1);
    }
    
    switch(argc) {
    case 5:
        DIMENSION = stoi(argv[4]);
    case 4:
        MAXIMO = stoi(argv[3]);
    case 3:
        PASO = stoi(argv[2]);
    case 2:
        REP_POR_MUESTRA = stoi(argv[1]);
    break;
    }
    
    cout << "Iniciando pruebas." << endl;
    cout << "Se harán " << MAXIMO/PASO << " pruebas para ambos algoritmos." << endl;
    cout << "La primera será con " << PASO << " número de puntos, y se irá incrementadno en " 
         << PASO << " puntos cada vez hasta llegar a " << MAXIMO << "." <<  endl;
    cout << "Para cada numero de puntos se harán " << REP_POR_MUESTRA << " pruebas y se tomará el tiempo como su media." << endl;
    
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
        cout << "Probando con " << num_puntos << " puntos." << endl;
        
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
    
    cout << "Fin de las pruebas." << endl;
}
