/*
Actividad 1.2 - Algoritmos de Búsqueda y Ordenamiento
- Programa que ordena vectores y busca los índices de elementos deseados dentro del vector.
Autor:
- Jeshua Nava Avila | A01639282
Fecha de creación y última modificación:
- 23/08/2021
- 26/08/2021
*/
#include <iostream>
#include <vector>
#include <time.h>
#include <cmath> // Para utilizar floor function.
#include <unistd.h> // Agregar sleep en el programa.
#include <stdlib.h> // Incluir rand.
using namespace std;

/**
 * Imprime en consola un string de manera "animada".
 * Complejidad computacional: O(n).
 * Recorre por un string cada char.
 * 
 * @param txt string el cual se va imprimir.
 */
void imprimeTexto(string txt){
    for (char const &c: txt){
        cout << c;
        usleep(35000);
    }
    cout << endl;
}

/**
 * Crea un vector de tamaño 1-20 con elementos aleatorios (de 0-1000).
 * Complejidad computacional: O(n)
 * n (random) de pasos que realiza.
 * 
 * @return un vector de n tamaño.
 */
vector<int> vectorRandom(){
    int n = rand() % 15 + 5; // Tamaño del vector.
    vector<int> V(n, 0);
    for (int i=0; i<n; i++){
        V[i] = rand() % 1000 + 0;
    }
    return V;
}

/**
 * Imprime en consola los elementos de un vector.
 * Complejidad computacional: O(n)
 * Es una función iterativa, para imprimir i elemento de un vector.
 * 
 * @param V vector tipo int que se desea imprimir sus elementos.
 * @param name nombre del vector, para imprimirlo también.
 */
void imprimeVector(vector<int> V, string name = "x"){
    cout << "Vector " << name << ": {";
    for (int i=0; i < V.size(); i++){
        if (i==V.size()-1){
            cout << V[i] << "}" << endl; // Imprimir el último elemento.
        }
        else {
            cout << V[i] << ", ";
        }
    }
}

/**
 * Ordena un vector con el algoritmo Insertion Sort.
 * Complejidad computacional (promedio): O(n^2)
 * Tenemos un for que va hasta n, pero dentro de este contamos con un while que puede recorrer hasta n (o menos).
 * 
 * @param V vector tipo int que se desea ordenar.
 */
void ordenaIntercambio(vector<int>& V){
    int n = V.size(), key = 0, j = 0;
    for (int i=1; i<n ; i++){
        key = V[i];
        j = i-1;
        while (j >= 0 && V[j] > key){
            V[j+1] = V[j];
            j -= 1;
        }
        V[j+1] = key;
    }
}

/**
 * Ordena un vector con el algoritmo Bubble Sort.
 * Complejidad computacional (promedio): O(n^2)
 * Por tener dos loops, y si los dos llegan a iterarse a un valor cerca de n, el tiempo es n^2.
 * 
 * @param V vector tipo int que se desea ordenar.
 */
void ordenaBurbuja(vector<int>& V){
    int n = V.size(), temp = 0;
    for (int i=0; i < n-1; i++){
        for (int e=0; e < n-i-1; e++){
            if (V[e] > V[e+1]){
                temp = V[e];
                V[e] = V[e+1];
                V[e+1] = temp;
            }
        }
    }
}

/**
 * Función que compara elementos de un vector y los ordena (parte del función Merge Sort).
 * Complejidad computacional: O(n)
 * Aunque tenga varios for loops y whiles, ninguno está anidado (en total n pasos para completar merge).
 * 
 * @param V vector tipo int que se desea ordenar.
 * @param l int index del inicio del vector.
 * @param m int index del punto medio del vector.
 * @param r int index del final de un vector.
 */
void merge(vector<int>& V, int l, int m, int r){
    vector<int> L, R; // Subarreglos temporales
    int n1 = m-l+1, n2 = r-m, i = 0, j = 0, k = l;
    for (int i=0; i<n1; i++){
        L.push_back(V[l+i]);
    }
    for (int j=0; j<n2; j++){
        R.push_back(V[m+j+1]);
    }
    i = j = 0;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        V[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        V[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Ordena un vector con el algoritmo MergeSort.
 * Complejidad computacional (promedio): O(nLog n)
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 * 
 * @param V vector tipo int que se desea ordenar.
 * @param l int index del inicio de un vector.
 * @param r int index del final de un vector (size - 1).
 */
void ordenaMerge(vector<int>& V, int l, int r){
    int m = 0;
    if (l<r){
        m = floor(((l+r)/2));
        ordenaMerge(V, l, m);
        ordenaMerge(V, m+1, r);
        merge(V, l, m, r);
    }
}

/**
 * Función que regresa el index de un elemento dentro de un vector, o -1 si no lo encuentra,
 * con el algoritmo Linear/Sequential Search.
 * Complejidad computacional: O(n)
 * Recorre por cada elemento del vector hasta encontrar el elemento.
 * 
 * @param V vector tipo int en donde se busca el elemento.
 * @param key elemento que se desea encontrar su index dentro del vector (si existe).
 */
int busqSecuencial(vector<int> V, int key){
    for (int i=0; i<V.size(); i++){
        if (V[i] == key){
            return i;
        }
    }
    return -1; // Si no encuentra el elemento, regresa -1.
}

/**
 * Función que regresa el index de un elemento dentro de un vector, o -1 si no lo encuentra,
 * con el algoritmo Binary Search.
 * Complejidad computacional: O(Logn)
 * Dividimos al arreglo de tamaño n en dos hasta llegar a un tamaño 1 (o un lugar en donde se encuentra el elemento).
 * 
 * @param V vector tipo int em donde se busca el elemento.
 * @param key elemento que se desea encontrar su index dentro del vector (si existe).
 */
int busqBinaria(vector<int> V, int key){
    int l = 0, r = V.size()-1, index = 0;
    while (r >= l){
        index = floor((l+r)/2);
        if (V[index] == key){
            return index;
        } else if (V[index] > key){
            r = index - 1;
        } else {
            l = index + 1 ;
        }
    }
    return -1; // Si no encuentra el elemento, regresa -1.
}

int main(){
    int menu = 1, n = 0, i = 0, search = 0;
    vector<int> V, busquedas, indicesSec, indicesBin;
    imprimeTexto("Hola usuario, soy la tarea de Jesh :)        ");
    while (menu != 0){
        srand (time(NULL)); // Random seed para generar nuevos números aleatorios cada vez que se ejecuta el programa o while.
        V = vectorRandom();
        ordenaMerge(V, 0, V.size()-1);
        imprimeTexto("Acabo de crear un vector random, por favor ingrese la cantidad de busquedas que desea realizar :)        ");
        imprimeVector(V, "Random");
        cout << "Tamanio del Vector Random: " << V.size() << endl;
        while (n <= 0 || n > V.size()){ // Verificar que el usuario ingrese un número válido para la cantidad de busquedas.
            cout << "Cantidad de busquedas:" << endl;
            cin >> n;
            if (n <= 0 || n > V.size()){
                cout << "Que no sea menor o igual a 0 o mayor que el tamanio :)     " << endl;
            }
        }
        imprimeTexto("Ahora ingresa los numeros que deseas buscar :)        ");
        while(i != n){ // De i hasta n elementos que se van a buscar.
            cout << "Busqueda " << i + 1 << ": ";
            cin >> search;
            busquedas.push_back(search);
            i++;
        }
        n = i = 0; // Los volvemos a sus estados originales.
        // Realizar busquedas de los elementos ingresados
        for (int e=0; e<busquedas.size(); e++){
            indicesSec.push_back(busqSecuencial(V, busquedas[e]));
            indicesBin.push_back(busqBinaria(V, busquedas[e]));
        }
        imprimeTexto("Ahora le mostrare los resultados :)        ");
        imprimeVector(V, "Random");
        imprimeVector(busquedas, "Busquedas");
        imprimeVector(indicesSec, "Indices Linear Search");
        imprimeVector(indicesBin, "Indices Binary Search");
        imprimeTexto("Ingrese 0 si desea salir del programa, u otro numero si quiere volver a repetir la actividad :)");
        cin >> menu;
        // Borramos los elementos de los vectores
        busquedas.clear();
        indicesBin.clear();
        indicesSec.clear();
        cout << endl << endl;
    }
}