# Tema 1: La eficiencia de los algoritmos
## Índice
1. [El concepto de algoritmo](#introduction)
2. [Calculo de la eficiencia de un algoritmo](#paragraph1)
    1. [Principio de invarianza](#subparagraph1)
    2. [Notacion O](#subparagraph2)
        1. [Equivalencia entre ordenes de eficiencia](subsubparagraph1)
    3. [Notacion Ω](#subparagraph3)
    3. [Notacion Θ](#subparagraph3)
    3. [Propiedades de las ordenes de eficiencia](#subparagraph5)
3. [Análisis de algoritmos](#paragraph2)
3. [Eficiencia de una funcion](#paragraph3)
3. [Resolucion de recurrencias](#paragraph4)

## 1. El concepto de algoritmo [](#){name=paragraph1}
Secuencia finita ordenada de pasos exentos de ambigüedad tal que, al llevarse a cabo con fidelidad, dará como resultado la tarea para la que se ha diseñado.
Las principales caracterı́sitcas de un algoritmo son:
* `Es una noción abstracta`: No depende del lenguaje donde se implemente.
* `Está bien definido`: cada paso es´ta claramente expresado y sin ambigüedades.
* `Es coherente`: con los mismos datos iniciales se obtiene el mismo resultado.
* `Finitud`: el algorimto debe terminar.
* `Efectividad`: debe resolver el problema planteado.
Si alguna de estas caracterı́sticas se incumple, entonces no es un algoritmo

## 2. Calculo de la eficiencia de un algoritmo <a name="paragraph1></a>
Las formas de calcular la efiencia de un algoritmo son:
* `Método empı́rico`: se implementa le algoritmo y se mide le tiempo de ejecución.
* `Método teórico`: se calcula una función matemática que indique cómo evolucionará el tiempo de ejecución del algoritmo según varı́e el tamaño n del caso.
* `Método hı́brido`: mezcla de ambos.

### 2.1 Principio de invarianza
Dadas dos implementaciones I1 e I2 de un mismo algoritmo, el tiempo de ejecución para una misma instancia de tamaño n, TI1 (n) y TI2 (n), no diferirá en más de una constante multiplicativa. Es decir, existe una constante positiva K que verifica:
 >   TI1 (n) = K · TI2 (n)
 ### 2.2 Notacion O
 Se dice que un algoritmo A es de orden O(f (n)), donde f (n) es una función matemática f (n) : N → R+ , cuando exsite una implementación del mismo cuyo tiempo de ejecución TA (n) es menor o igual que K · f (n), donde K es constante, para ”tamaños de casos grandes”.

La notación O nos permite conocer cómo se compartará el algoritmo en términos de eficiencia en instancias del caso peor del problema. Como mucho, sabemos que el algoritmo no tardará más de K · f (n) en ejecutarse, en el peor de los casos.

Si decimos que un algoritmo A es de orden O(f (n)), queremos decir que siempre podremos encontrar una constante K tal que, para valores muy grandes del tamaño de caso n, el tiempo de ejecución del algoritmo siempre será inferior o igual a K multiplicando a f (n):
> TA (n) = K · f (n)

#### 2.2.1 Equivalencia entre ordenes de eficiencia
Para saber si dos órdenes de efiencia O(f (n)) y O(g(n)) son equivalentes o no, podemos aplicar las siguientes reglas:
> O(f (n)) ≡ O(g(n)) si : lím n→∞ f(n) / g(n) → K ∈ R+
>O(f (n)) > O(g(n)) si : lı́m n→∞ f(n)/g(n) → ∞
>O(f (n)) < O(g(n)) si : lím n→∞ f(n)/g(n) → 0

### 2.3 Notacion Ω
Se dice que un algoritmo A es de orden Ω(f (n)), donde f (n) es una función matemática f (n) : N → R+ , cuando existe una implementación del mismo cuyo tiempo de ejecución TA (n) es mayor o igual que K · f (n), donde K es constnate, para ”tamaños de casos grandes”.

La notación Ω nos permite conocer cómo se compartará el algoritmo en términos de eficiencia en instancias del caso mejor del problema. Como poco, sabemos que el algoritmo no tardará menos de K · f (n) en ejecutarse, en el mejor de los casos.

### 2.4 Notacion Θ
Se dice que un algoritmo A es de orden Ω(f (n)), donde f (n) es una función matemática f (n) : N → R+ , cuando el tiempo de ejecución del algoritmo puede expresarse como TA (n) = k ·f (n). En este caso, el algoritmo es simultáneamente de orden O(f (n)) y Ω(f (n)).

### 2.5 Propiedades de las ordenes de eficiencia
Las princiapales propiedades son:
* `Regla del máximo`: O(f (n) + g(n)) = max {O(f (n)), O(g(n))}.
* `Regla de la suma`: O(f (n) + g(n)) = O(f (n)) + O(g(n)).
* `Regla del producto`: O(f (n) · g(n)) = O(f (n)) · O(g(n)).

## 3. Analisis de algoritmos
### 3.1 Sentencias condicionales
Nos encontramos con dos casos:
* Caso peor:
> max {O(EvaluacionCondicional), O(BloqueSentencias1), O(BloqueSentencias2)}.
* Caso mejor:
> Ω(EvaluacionCondicion)+min {Ω(BloqueSentencias1), Ω(BloqueSentencias2)}.

### 3.2 Sentencias repetitivas
El calculo de eficiencia sera:
> O(g(n) + h(n) · (g(n) + f (n)))
Suponiendo que:
* f (n): eficiencia del bloque de sentencias.
* g(n): eficiencia de la evaluación de la condición.
* h(n): número de veces que se ejecuta el bucle.

### 3.3 Eficiencia de bucles for
La eficiencia de estos bucles sera:
> O(i(n) + g(n) + h(n) · g(n) + f (n) + a(n))
Suponiendo que:
* f (n): eficiencia del bloque de sentencias.
* g(n): eficiencia de la evaluación de la condición.
* h(n): número de veces que se ejecuta el bucle.
* a(n): eficiencia de la actualización.
* i(n): eficiencia la inicialización.

## 4. Eficiencia de una funcion
La efiencia de una función es el máximo entre las eficiencias de las sentencias que la componen. La eficiencia de una llamda a función dependerá de sus parámeros de entrada dependen o no del tamaño del problema.

### 4.1 Eficiencia de una funcion recursiva
Se calcula que le tiempo de ejecución T (n) de la función con respecto al tamaño n del caso del problema, considerando el tamaño que resuelven las llamadas recursivas. Se expresa cmo una ecuación en recurrencias. Se debe resolver la ecuación en recurrencias para calcular le orden de eficiencia.
*Ejemplo*
```c++
unsigned long factorial(int n){
    if (n <= 1) return 1;
    else return n * factorial (n-1);
}
```
Primero debemos determinar una serie de elementos:
* `Variable de la que depende el tamaño del problema: n.
* `Tiempo que tarda en ejecutarse la función`: T (n).
* `Evaluación de la condición`: O(1).
* `Tiempo del bloque if` : O(1).
* `Tiempo del bloque else`: O(1) + lo que tarde la función en resolver el problema del tamaño n: T (n − 1) → 1 + T (n − 1).
Cuando realizamos el análisis de una función recursiva debemos determinar:
* Caso base: no depende de la recursividad.
* Casos generales: depende de la recursividad.
* Mejor caso: el caso general más favorable.
* Caso peor: el caso general más desfavorable.
*Ejemplo 2*
```c++
int BusquedaBinaria(double *v, int posIni, int posFin, double aBuscar){
    int centro (posIni + posFin) / 2;
    if (posIni > posFin) return -1;
    else if (v[centro] == aBuscar) return centro;
    else if (aBuscar < v[centro])
        return BusquedaBinaria(v, posIni, centro, aBuscar);
    else
        return BusquedaBinaria(v, centro, posFin, aBuscar);
}
```
A continuación se realiza el análisis de la función:
* Variables de las que depende el problema: n = posF in − posIni + 1.
* Tiempo de ejecución de la función: T (n).
* Lı́neas 11-14: máx {condicion, Bloque − If, Bloque − Else} == máx {O(1), T (n/2), T (n/2)}
En cuanto al caso base y al caso general:
* Caso base:
    * T (n) = O(1) si n < 1 (primer if )
    * T (n) = O(1) si v[n/2] = aBuscar
* Caso general: T (n) = 1 + T (n/2)
Por tanto:
T (n) = 
> 1 caso base
> T (n − 1) + T (n − 2) caso general

## 5. Resolucion de recurrencias
La explicación se realiza mediante un ejemplo:
*Ejemplo*: T (n) = T (n − 1) + T (n − 2) Pasamos todas las T ′ s hacia un lado, como por ejemplo:
> T (n) − T (n − 1) + T (n − 2) = 0
Se reescribe T (n − i) como xi , y se pasan todos los términos hacia un lado:
> x^n − x^n−1 − x^n−2 = 0
Se saca factor común xn−k :
> (x^2 − x − 1)x^n−2 = 0
Por el teorema fundamental del Álgebra, sabemos que:
> P (x) = (x − R1 ) · (x − R2 ) · ... · x − Rk
Como las raices de p(x) son:
> 1. R1 = 1+sqrt(5) → M1 = 1
> 2. R2 = 1−sqrt(5) → M2 = 1
Tenemos que:
> p(x) = (x- 1+sqrt(5)/2) * - 1-sqrt(5)/2
Por tanto:
> tn = c10*(1+sqrt(5)/2)^n c20(1-sqrt(5)/2)^n

### 5.1 Ecuaciones lineales no homogeneas de coeficinetes constantes (ENLH)
*Ejemplo*: T (n) = T (n − 1) + 1 Pasamos todas las T ′ s hacia un lado, como por ejemplo:
> T (n) − T (n − 1) = 1
Se reescribe la parte Homogénea T (n − i) como xi , y se pasan todos los términos hacia un lado:
> xn − xn−1 = 1
Se saca factor común x^n−k :
> (x − 1)^xn−1 = 0
A la anterior expresión se le denomina polinomio caracterı́stico, es decir, a:
> pH (x) = x − 1
A continuación resolvemos la parte No Homogénea:
Hacemos 1 = bn1 · q1 (n); entonces b1 = 1, q1 (n) = 1 con grado d1 = 0.
Por tanto:
> p(x) = (x − 1) · (x − b1 )^d1+1 = (x − 1)(x − 1)1 = (x − 1)2
De manera que: R1 = 1 → M1 = 2
Finalente: tn = c10*1n*n0 + c11*1n*n1


# Tema 2: Divide y Vencerás
## Índice
1. [Situaciones en las que se puede aplicar Divide y Vencerás](#situaciones)
2. [El problema de ordenación](#ordenacion)
    1. [Algoritmo MergeSort O(nlog(n))](#mergesort)
        1. [Algoritmo MergeSort - Como Funciona](#mergesort-funciona)
3. [La técnica Divide y Vencerás](#divide-vencerás)
    1. [Requisitos para poder aplicar DyV](#requisitos-dyv)
4. [Búsqueda binaria log2 (n)](#búsqueda-binaria)
    1. [Método básico](#método-básico)
    2. [Idea general](#idea-general)
    3. [Diseño](#diseño)
        1. [Caso base](#caso-base)
5. [Ordenación Rápida: QuickSort O(n2 ) O(nlog(n))](#quicksort)
    1. [La idea general](#quicksort-general)
    2. [Diseño](#quicksort-diseño)
        1. [Diseño: 1. División del problema en subproblemas](#división-subproblemas)
        2. [Diseño: 2. Resolución de cada subproblema y combinación](#resolución-combinación)
        3. [Diseño: 3. Caso base](#caso-base-quicksort)
        4. [Diseño: 4. Adaptación de la plantilla DyV](#adaptación-dyv)
    3. [Implementación en C++](#implementación-cpp)
    4. [Eficiencia de QuickSort](#eficiencia-quicksort)
6. [El problema de seleccion O(n2 ) O(n)](#seleccion)
    1. [Definición del problema](#definición-problema)
    2. [Método básico](#método-básico-seleccion)
    3. [La idea general](#idea-general-seleccion)
    4. [Diseño: 2. Divisón del problema en subproblemas](#división-subproblemas-seleccion)
    5. [Diseño: 3. Resolución de cada subproblema y combinación](#resolución-combinación-seleccion)
    6. [Diseño: 4. Método Pivotar](#método-pivotar)
    7. [Diseño: 5. Caso base](#caso-base-seleccion)
    8. [Diseño: 6. Adaptación de la plantilla DyV](#adaptación-dyv-seleccion)
    9. [Implementación en C+](#implementación-cplus)
    10. [Eficiencia de Seleccion](#eficiencia-seleccion)
7. [Múltiplicación rápida de enteros largos O(nlog2 3)](#multiplicación-rápida)
    2. [Método básico](#método-básico-multiplicación)
    3. [La idea general](#idea-general-multiplicación)
    4. [Diseño: 1. División del problema en subproblemas](#división-subproblemas-multiplicación)
    5. [Diseño: 2. Resolución de cada subproblema y combinación](#resolución-combinación-multiplicación)
    6. [Diseño: 3. Caso base](#caso-base-multiplicación)
    7. [Eficiencia](#eficiencia-multiplicación)
    8. [Diseño: 4. Adaptación de la plantilla DyV](#adaptación-dyv-multiplicación)
    9. [Ejemplo](#ejemplo-multiplicación)
8. [Multiplicación rápida de matrices O(n^log2 (7))](#multiplicación-matrices)
    1. [La idea general](#idea-general-matrices)
    2. [Diseño: 1. Divisón del problema en subproblemas](#división-subproblemas-matrices)
    3. [Diseño: 2. Resolución de cada subproblema y combinación](#resolución-combinación-matrices)
    4. [Diseño: 3. Caso base](#caso-base-matrices)
    5. [Adaptacion de la plantilla DyV](#adaptación-dyv-matrices)
    6. [Eficiencia](#eficiencia-matrices)
    7. [Ejemplo](#ejemplo-matrices)
9. [La lı́nea del horizonte O(n)](#línea-horizonte)
    1. [Enunciado](#enunciado)
    2. [Idea del algoritmo básico](#algoritmo-básico)
    3. [Diseño: Algoritmo Básico](#diseño-básico)
    4. [Diseño DyV: Idea general](#diseño-dyv-general)
        1. [División del problema en subproblemas](#división-subproblemas-horizonte)
        2. [Combinación de soluciones](#combinación-soluciones)
    5. [Caso base](#caso-base-horizonte)
    6. [Diseño DyV: Estructura del algoritmo](#estructura-algoritmo)
    7. [Diseño DyV: Estructura de la combinación](#estructura-combinación)

## <a name="situaciones"></a>Situaciones en las que se puede aplicar Divide y Venceras
Las principales situaciones en las que se puede aplicar Divide y Vencerás son:
* Cuando el caso de un problema ”muy grande”, en ocasiones puede dividirse en casos más pequeños que sean más fáciles de resolver, con el fin de mejorar la eficiencia y resolver el problema más rapidamente.
* La solución al caso inicial (el ”muy grande”) puede construirse después combinando las soluciones de los casos más pequeños en los que se ha dividido.
* Debe exsitir un caso base indivisible o, en su defecto, un algoritmo básico que resuelva el problema.

## 2. El problema de la ordenacion
Sea una secuencia V de n elementos V = (v1 , v2 , ..., vn ). El problema consiste en encontrar una permutación W de n elementos y construir una secuencia V ′ = (vw(1) , Vw(2) , ..., V2!‘w(n) ), tal que se cumpla:
> vw(i) ≤ vw(j) ∀i ≤ j

### 2.1 Algoritmo MergeSort
El algoritmo MergeSort permite ordenadar un vector de tamaño n ”por partes”, es decir, en lugar de resolver el problema de ordenación completo, dividir el vector en dos subvectores de tamaño n/2, que se ordenan de forma independiente.

Se combinan los dos subvectores de tamaño n/2 ordenados para generar el vector ordenado del tamaño inicial n.

Podrı́amos aplicar este procedimiento recursiviamente, hasta legar a un caso base.

#### 2.1.1 Como funciona
Su funcionamiento consiste en:
* Dividir el vector en 2 partes.
* Seguir dividiendo (hasta un caso base).
* Resuelve cada parte por separado.
* Combina las subsoluciones.
* Devuelve la solución a la llamada recursiva anterior.

**Como funciona la combinacion**
El funcionamiento de la combinación consiste en:
* Hay dos ı́ndices, uno al comienzo de cada subvector.
* Se comprueba qué subvector tiene el elemento menor.
* Se inserta ese elemento y se actualiza el ı́ndice afectado.
* Al terminar un subvector, se copia el resto del otro subvector a la salida.
```c++
void MergeSort(int *v, int ini, int fin){
    if (ini < fin){
        int med = (ini + fin) / 2;
        MergeSort(v, ini, med);
        MergeSort(v, med + 1, fin);
        combina(v, ini, med, fin);
    }
}
Su eficiencia es T (n) = 2 · T (n/2) + Tcombina (n).
void combina(int *v, int ini, int med, int fin){
    int vtam = fin - ini + 1;
    int *aux = new int[vtam];
    int i = ini, j = med + 1, k = 0;
    while (i <= med && j <= fin){
        if (v[i] < v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }
    while (i <= med) {
        aux[k] = v[i];
        i++;
        k++;
    }
    while (j <= fin){
        aux[k] = v[j];
        j++;
        k++;
    }
    for (int n = 0; n < vtam; n++)
        v[ini+n] = aux[n];
    delete [] aux;
}
La eficiencia de combina es: Tcombina (n) = n.
Por tanto, la eficiencia del algoritmo de ordenación MergeSort:
> T (n) = 2 · T (n/2) + n
Resolviendo la ecuación, MergeSort es O(n · log(n)).
```
## 3. La tecnica Divide y Venceras
La técnica Divide y Vencerás consiste en ir dividiendo de forma recursiva un problema ”grande”ne otros más pequeños, que se puedan resolver por separado.

Se dejará de dividir el problema recursivamente cuando se llegue a un caso base o cuando el problema sea ya indivisible.

Se resolverá cada subproblema por separado, y se combinarán las subsoluciones para dar lugar a la solución final del problema ”grande”propuesto inicialmente.

### 3.1 Requisitos para poder aplicar DyV
Los principales requisitos son:
* El caso del problema debe poder dividirse en uno o más casos equivalentes de tamaño menor, independientes entre sı́, que puedan resolverse por separado.
* Las soluciones a los casos de tamaño menor deben poder combinanrse entre sı́ para poder dar lugar a la solución del caso inicial.
* Debe existir, a priori, un método básico que resuelva el problema, o en su defecto, un caso base indivisible donde el problema esté resuelto.

## 4. Busqueda binaria log2(n)
Sea v un vector de tamaño n. El problema consiste en buscar un elemento x dentro del vector, y devolver su psoición.

### 4.1 Metodo basico
El método básico consiste en recorrer el vector comprobando el valor de cada componente y, devolver el ı́ndice de x cuando se encuentre.
```c++
int BusquedaBinaria(double *v, const int ini, const int fin, const double x){
    for (int i = ini; i < fin; i++)
        if (v[i] == x) return i;
    return -1;
}
```
### 4.2 Idea general
Sea v un vector de tamaño n, ordenado ascendentemente. El problema consiste en buscar un elemento x dentro del vector, y devolver su posición.

Si el vector está ordenado, podemos comprobar el valor de su elemento central. Si es mayor que el elemento x buscado, podemos descartar la mitad derecha del vector.

En otro caso, si es menor que el elemento x buscado, podemos descartar la mitad izquierda del vector.

### 4.3 Diseño
Para buscar un elemento x en un vector v de tamaño n, el cual ya se encuentra ordenado, podrı́amos dividir el vector en un de la mitad de tamaño (n/2), indepndiente y que pude resolverse por separado. Para dividir el vector, seleccionaremos su posición central.

Si el elemento central del vector contiene el elemento requerido, se devuelve su ı́ndice.

Si x es menor que el elemento central, reduciremos la búsqueda a la primera mitad del vector y lo resolveremos recursivamente. Si es mayor, la búsqueda la reduciremos a la segunda mitad del vector.

No hace alta combinar soluciones, puesto que el problema se reduce a un problema de tamaño más reducido.

#### 4.3.1 Caso base
Se parará la recursividad cuando el vector a ordenar tenga tamaño 0 (el elemento no se encuentra) o cuando se encuentre el elemento en el centro del vector.
```c++
int BusquedaBinaria(double *v, const int ini, const int fin, const double x){
    int centro = (ini + fin) / 2;

    if (v[centro] == x) return centro;
    else if (x < v[centro]) return BusquedaBinaria(v, ini,centro-1, x);
    else return BusquedaBinaria(v, centro + 1, fin, x);
}
```
**Ecuacion de recurrencia:** `T (n) = 1 + T (n/2)`.
**Eficiencia:** `O(log2 (n))`

## 5. Ordenacion Rapida: QuickSort O(n^2) O(nlog(n))
### 5.1 La idea general
El algoritmo Quicksort (Ordenación Rápida) es el mejor algoritmo DyV de ordenación, en caso promedio.

La idea básica de Quicksort, para ordenar un vector v de tamaño n es la siguiente:
* Detemrinar un elemento ”pivote”, para dividir el vector en 2 partes con elementos < pivote y >= que pivote, respectivamente.
* Ordenar los dos subvectores generados.
* Combinar las dos soluciones para obtener v ordenado.

### 5.2 Diseño
#### 5.2.1 Diseño: 1. Division del problema en subproblemas
La división del problema consiste en:
* Podrı́amos dividir el vector en dos de tamaño parecido (n/2) independientes y que pueden resolverse por separado.
* Para dividir el vector, seleccionaremos un elemento al que llamaremos pivote, de modo que los elementos menores que el pivote queden a la izquierda del vector, y os mayores o iguales a la derecha.
* En un caso óptimo, el pivote dividirá al vector en dos mitades iguales. En el peor caso, dejará un subvecgtor con 1 elemento y otro subvector con n−1 elementos.

#### 5.2.2 Diseño: 2. Resolucion de cada problema y combinacion
La resolución de los subproblemas y su combinación consiste en:
* Se reordenarán los dos subvectores. Al llegar a un caso base de 1 elemento, el vector estará ordenado.
* La penúltima llamada recursiva (vector de 2 elementos) también hará que el vector resultante esté ordenada, poruqe hemos pivotado y el elemento mayor estará en la segunda posición, mientras que el elemento menor estará en la primera.
* En las llamadas recursivas aneriores, pasará lo mismo gracias a que se va pivotando cada vez que se ejecuta la función.
* Por tanto, no se requiere combinación adicional para Quicksort: los métodos de pivotaje y las llamadas recursivas lo aplican inherentemente.

#### 5.2.3 Diseño: 3. Caso base
Se pasará cuando el vector a ordenar tengo tamaño 1.

#### 5.2.4 Diseño: 4. Adaptacion a la plantilla DyV
Su adaptación será:
```c++
    Funcion S = QS(V, ini, fin)
        SI ini >= fin DEVOLVER S = vacio;

        En otro caso, hacer:
            [PosPivote, V] = Pivotar(V, ini, fin);
            V = QS(V, ini, PosPivote);
            V = QS(V, PosPivote + 1, fin);
        
        Fin-En otro caso
        DEVOLVER V

La adaptacion del metodo Pivotar es:
    Funcion [PosPivote, V] = Pivotar(V, ini, fin)
        Pivote = V[ini];
        i = ini + 1;
        j = fin;
        Mientras (i <= j) Hacer:
            Intercambiar(V[i], V[j]);
            Mientras (V[i] < Pivote && i <= j) Hacer:
                i = i + 1;
            Mientras (V[j] >= Pivote && i <= j) Hacer:
                j = j - 1;
        Fin - Mientras;

        Si (ini < j)
            Intercambiar(V[ini], V[j]);

        Devolver [j, V];
```
### 5.3 Implementacion en C++
>**Implementación QuickSort**
```c++
void QuickSort(double *v, const int ini, const int fin){
    if (ini < fin){
        int posPivote = pivotar(v, ini, fin);
        QuickSort(v, ini, posPivote);
        QuickSort(v, posPivote + 1, fin);
    }
}
```
>**Implementacion Pivotar**
```c++
int pivotar(double *v, const int ini, const int fin){
    double pivote = v[ini];
    double aux;

    while (i <= j){
        while (v[i] < pivote && i <= j) i++;
        while (v[j] >= pivote && i <= j) j--;

        if (i < j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    if (j > ini){
        v[ini] = v[j];
        v[j] = pivote;
    }
    return j;
}
```
## 5.4 Eficiencia QuickSort
La eficiencia:
* `En el peor de los casos:` T (n) = T (n − 1) + n → Eficiencia `O(n²)`.
* `En el mejor de los casos:` T (n) = 2 · T (n/2) + n → Eficiencia `Ω(n · log(n))`
En caso promedio, Quicksort, se comporta mejor que los demás algoritmos de ordenación (incluyendo MergeSort), debido a que la probabilidad de que ocurra el peor caso es muy baja.

# 6. El problema de seleccion O(n²) O(n)
## 6.1 Definicion del problema
Sea un vector v de n componentes. Se desea conocer qué elemento se situarı́a ne la i-ésima posición del vector en caso de que este estuviese ordenado.

## 6.2 Metodo basico
Bastarı́a con ordenar el vector y devolver el elemento que hubiese en la i-ésima posición. La complejidad del método es O(n · log(n)), dado que la ordenación tiene esa eficiencia y es la operación más compleja que se realiza.

## 6.3 La idea general
No necesitamos que el vector esté ordenado completamente. Basta con que el elemento de la i-ésima posición esté ordenado.

Podemos reutilizar la **función pivotar de QuickSort** para resolver el problema dado que, al terminar su ejecución, en la j-ésima posición del vector se encuentra el pivote y todos los elementos a su izquierda son menores que él, por lo que se encuentra en su posición ordenada.

## 6.4 Diseño: 2. Division del problema en subproblemas
La división en subproblemas consiste en:
* Para encontrar el elemento en la i-ésima posición del vector, colocaremos todos los elementos menores que un pivote a la izquierda del vector, y los elemenots mayores o iguales en la parte derecha. La posición del pivote, posPivote, estará ordenada por tanto.
* Si la posición i que buscamos es la posición del pivote, hemos terminado.
* Si la posición i que buscamos es inferior a posPivote, entonces dividimos el problema en 1 subproblema (vector v desde la primera posición hasta posPivote).
* Si la posición i que buscamos es superior a posPivote, entonces dividimos el problema en 1 subproblema (vector v desde posPivote+1 hasta la última componente).

## 6.5 Diseño: 3. Resolucion de cada subproblema y combinacion
* Se volverá a calcular el pivote para el subvector generado, aplicando recursivamente el procedimiento hasta que se encuentre la i-ésima posición.
* Como la función de pivotar deja en posPivote el elemento que estamos buscando, y sólo dividimos el problema en 1 subproblema, no es necesario realizar combinación ni operaciones adicionales.

## 6.6 Diseño: 4. Metodo Pivotar
```c++
Funcion [PosPivote, V] = Pivotar(V, ini, fin)
    Pivote = V[ini];
    i = ini + 1;
    j = fin;

    Mientras (i <= j) Hacer:
        Intercambiar(V[i], V[j]);
        Mientras (V[i] < Pivote && i <= j) Hacer:
            i = i + 1;
        Mientras (V[j] >= Pivote && i <= j) Hacer:
            j = j - 1;
    Fin - Mientras;

    Si (ini < j)
        Intercambiar(V[ini], V[j]);

    Devolver [j, V];
```
## 6.7 Diseño: 5. Caso base
Se pasará cuando posPivote sea la componente i deseada.

## 6.8 Diseño: 6. Adaptacion de la plantilla DyV
```c++
Funcion S = Seleccion(V, ini, fin, i)
    SI ini == fin DEVOLVER S = V[ini];

    EN OTRO CASO, HACER:
            [posPivote, V] = Pivotar(V, ini, fin)
            SI (posPivote == i) DEVOLVER V[posPivote]:
            EN OTRO CASO
                SI (posPivote > i) DEVOLVER Seleccion(V, ini,posPivote-1);
        EN OTRO CASO
        SI (posPivote < i) DEVOLVER Seleccion(V, posPivote, +1, fin, i);
        FIN - EN OTRO CASO
```

## 6.9 Implementacion en c++
```c++
double Seleccion(double *v, const int ini, const int fin, const int i){
    if (ini == fin) return v[ini];

    int posPivote = pivotar(v, ini, fin);

    if (posPivote == i) return v[posPivote];
    if (posPivote > i) return Seleccion(v, ini, posPivote-1, i);

    return Seleccion(v, posPivote+1, fin, i);
}

int pivotar(double *v, const int ini, const int fin){
    double pivote = v[ini];
    double aux;

    while (i <= j){
        while (v[i] < pivote && i <= j) i++;
        while (v[j] >= pivote && i <= j) j--;

        if (i < j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    if (j > ini){
        v[ini] = v[j];
        v[j] = pivote;
    }
    return j;
}
```
## 6.10 Eficiencia de Seleccion
La efiencia en distintos casos:
* `En el peor de los casos:` Selección divide al vector en dos partes, de tamaño 1 y n−1 respectivamente. Por tanto su eficiencia será: T (n) = T (n−1)+n → `O(n²)`
* `En el mejor caso:` Selección divide al vector en dos partes de igual tamaño n/2. Por tanto su efiencia será: T (n) = T (n/2) + n → `Ω(n).`
* Al igual que ocurre con QuickSort, es muy improbable que se dé el peor caso, por lo que en promedio se comporta como Ω(n).

# 7. Multiplicacion rapida de enteros largos O(n^log2³)
## 7.1 Definicion del problema
Sean dos números positivos A y B con n dı́gitos cada uno. Se desea calcular la multiplicación C = A · B.

## 7.2 Metodo basico
Existen multitud de métodos de multiplicación. El método más básico tiene una eficiencia de O(n²).

## 7.3 La idea general
Haciendo una descomposición de cada entero en sumas de coeficientes por potencias de 10, intentar dividir el problema en varios subproblemas más pequeños:
> A = a0 + 10a1 + 102 a2 + ... + 10n an
> B = b0 + 10b1 + 102 b2 + ... + 10n bn

## 7.4 Diseño: 1. Division del problema en subproblemas
Dividiremos cada entero A y B, de tamaño n, en dos enteros de tamaño n/2 cada uno:
> A = a0 + 10^n/2 * a1
> B = b0 + 10^n/2 * b1

Dividimos el problema en 3 subproblemas:
* P 1 = (a0 + a1 ) · (b0 + b1 )
* P 2 = a1 · b1
* P 3 = a0 · b0

## 7.5 Diseño: 2. Resolucion de cada subproblema y combinacion
Los subproblemas P 1, P 2, P 3 son independientes y se resolverán por separado. Llamemos S1, S2, S3 a la subsoluciones de cada uno de los subproblemas.

Combinaremos las subsoluciones de la siguiente forma para llegar a la solución global S:
* Parcial: S1 − S2 − S3 (el cálculo de (a1 b0 + a0 b1 )).
* S = 10^n * S2 + 10^n/2 · Parcial + S3.

## 7.6 Diseño: 3. Caso base
Se parará cuando n = 1, es decir, multiplicación de números de 1 dı́gito.

## 7.7 Eficiencia
La eficiencia de la función:
* Reescribir los números A = (a0 , a1 ), B = (b0 , b1 ) es O(1)
* El algoritmo tiene 3 llamadas recursivas para resolver el problema de tamaño n/2.
* Suponemos que las sumas y restas podrı́an ser implementadas como O(n).
Por tanto, la ecuación de recurrencias es:
> T (n) = 3T (n/2) + n
Resolviendo la ecuación, obtenemos que la eficiencia es `O(nlog_2(3))`

## 7.8 Diseño: 4. Adaptacion a la plantilla DyV
```c++
Funcion S = Multiplica(A, B)
    SI n = 1, ENTONCES S = A * B;

    EN OTRO CASO, HACER:
        Reescribir A = (a0, a1), B = (b0, b1)
        S3 = Multiplica(a0, b0)
        S2 = Multiplica(a1, b1)
        S1 = Multiplica(a0+a1, b0+b1)
        Parcial = S1-S2-S3
        S = 10^n * S2 + 10^(n/2) * Parcial + S3
    FIN - EN OTRO CASO
    DEVOLVER S
```

##7.9 Ejemplo




