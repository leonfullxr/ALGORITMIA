// compilar desde la raiz del proyecto con g++ ./src/tests.cpp ./lib/*.h -o ./bin/tests.bin

#include <iostream>
#include <fstream>
#include <chrono>
#include <cctype>
#include "../lib/punto.h"
#include "../lib/funiciones_tests.h"
#include "../lib/no_dominados_sencillo.h"
#include "../lib/no_dominados_DyV.h"

using namespace std;

const string test_results_dir = "./data/";

int main(int argc, char * argv[]) {
    const string ARGUMETNOS = "<repeticiones por muestra> <provar con alg sencillo (S/N)> <provar con alg DyV (S/N)> <paso> <maximo> <dimension>";
    int REP_POR_MUESTRA = 1;
    char PROBAR_SECILLO_C = "S";
    char PROBAR_DyV_C = "S";
    int PASO = 500;
    int MAXIMO = 50000;
    int DIMENSION = 10;
    
    if (argc > 7) {
        cerr << "ERROR - Los argumentos del programa son:" << endl;
        cerr << ARGUMETNOS << endl;
        cerr << "y sus valores por defecto:" << endl;
        cerr << REP_POR_MUESTRA << " " << PROBAR_SECILLO_C << " " << PROBAR_DyV_C << " " << PASO << " " << MAXIMO << " " << DIMENSION << endl;
        exit(-1);
    }
    
    switch(argc) {
    case 7:
        DIMENSION = stoi(argv[6]);
    case 6:
        MAXIMO = stoi(argv[5]);
    case 5:
        PASO = stoi(argv[4]);
    case 4:
        PROBAR_DyV = toupper(argv[3]);
    case 3:
        PROBAR_SECILLO = toupper(argv[2]);
    case 2:
        REP_POR_MUESTRA = stoi(argv[1]);
    break;
    }
    
    bool probar_sencillo = PROBAR_SECILLO_C != "N";
    bool probar_DyV = PROBAR_DyV_C != "N";
    
    if((not probar_sencillo) and (not probar_DyV)) {
        cout << "Selecciona al menos un algoritmo que probar" << endl;
        exit(0);
    }
    
    cout << "Iniciando pruebas." << endl;
    cout << "Se harán " << MAXIMO/PASO << " pruebas para los siguientes algoritmos:" << endl;
    if (probar_sencillo) cout << "No dominados sencillo." << endl;
    if (probar_DyV) cout << "No dominados divede y vencerás." << endl;
    cout << "La primera será con " << PASO << " número de puntos, y se irá incrementadno en " 
         << PASO << " puntos cada vez hasta llegar a " << MAXIMO << "." <<  endl;
    cout << "Para cada numero de puntos se harán " << REP_POR_MUESTRA << " pruebas y se tomará el tiempo como su media." << endl;
    cout << "Para cambiar estos parametros llamar al ejecutable con los siguentes argumentos:" << endl;
    cout << ARGUMETNOS << endl;
    
    ofstream resutlados;
    
    auto ahora = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string fecha = ctime(&ahora);
    string fecha,pop_back();
    resutlados.open(test_results_dir + "resultados - " + fecha + ".csv");
    
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
            if (probar_sencillo)
                duracion_sencillo += (float)para_tests::cuantoTarda(&nd_sencillo::noDominados, puntos);
            if (probar_DyV)
                duracion_DyV += (float)para_tests::cuantoTarda(&nd_DyV::noDominados, puntos);
        }
        duracion_sencillo /= REP_POR_MUESTRA;
        duracion_DyV /= REP_POR_MUESTRA;
        
        resutlados << num_puntos << ";";
        if (probar_sencillo) resutlados << duracion_sencillo; else resultados << "no provado";
        cout << ";";
        if (probar_DyV) resutlados << duracion_DyV; else resultados << "no provado";
        cout << ";";
        resultados << endl;
    }
    
    resutlados.close();
    
    cout << "Fin de las pruebas." << endl;
}
