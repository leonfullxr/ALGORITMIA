#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib> // Para usar srand y rand

void eliminaDuplicadosOrdenados(int numElementos, *elementos){
  int j;  //Indice donde insertar los elementos no duplicados al Array auxiliar
  
  if(numElementos > 0)
    auxiliar[0] = elementos[0];
	
	for(int i = 1, j = 1; i < numElementos; i++){   //Recorro los valores del Array
		if(elementos[i] > elementos[i-1]){
       auxiliar[j] = elementos[i];
       j++;
    }
  }
	
	elementos = delete[];                   //Borro los datos del set
	elementos = new int[j];        //Reservo la cantidad de elementos que hay en el Array auxiliar
	
	for(int i = 0; i < j; i++)
	    elementos[i] = auxiliar[i];                 //Inserto los valores no duplicados del set al Array
}

int main(){
	int *v;
	int n, i, argumento;
    	chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
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
		
		// Reservamos memoria para el vector
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando Burbuja para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		eliminaDuplicadosOrdenados(n, v); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
