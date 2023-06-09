#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <cstdlib> // Para usar srand y rand

using namespace std;

void eliminaDuplicadosOrdenados(int & numElementos, int *& elementos){
	int *auxiliar = new int[numElementos];  // Guardará los elementos no repetidos
	int j = 0;                              // Tam de auxiliar
	
	if (numElementos > 0) 
		auxiliar[j++] = elementos[0];
	
	for(int i = 0; i < numElementos - 1; i++)   /* se repite n veces */
		if(elementos[i] != elementos[i+1])
			auxiliar[j++] = elementos[i+1];
	
	if (j == numElementos) {
		delete [] auxiliar;
		return;
	}
	
	delete [] elementos;
	numElementos = j;
	elementos = new int[numElementos];
	
	for(int i = 0; i < numElementos; i++)   /* se repite n veces */
		elementos[i] = auxiliar[i];
	
	delete [] auxiliar;
}

int main(int argc, char **argv){
	int *v;
	int n, i, argumento, orig_size;
    	chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		orig_size = n;
		
		// Reservamos memoria para el vector
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
	    
	    //Ordeno los valores
	    sort(v, v+n);
		
		cerr << "Ejecutando eliminaDuplicadosOrdenados para tam. caso: " << orig_size << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		eliminaDuplicadosOrdenados(n, v); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< orig_size<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<orig_size<<"\t"<<tejecucion<<"\n";
		
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
