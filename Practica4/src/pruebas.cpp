/**
* Fichero para realizar las pruebas de eficiencia 
* Incluye casos de 1000 items hasta 100.000
*/
#include "../lib/DealerBag.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

int main(int argc, char **argv) {
	// Hare un bucle donde se vayan creando objetos con pesos y valores distintos de manera random
	chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	ofstream fsalida;
	
	if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	for (int i = 1000; i < 100000; i += 1000) {
		DealerBag prueba;
		prueba.stock.refill();
		// cuento lo que tardo en ejecutar el algoritmo
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		prueba.fillBag_DP();
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< orig_size<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<orig_size<<"\t"<<tejecucion<<"\n";
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
