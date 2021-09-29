/*
 Actividad 1 - Funciones Iterativas, Recursivas y su análisis de Complejidad
- Programa que calcula la sumatoria de 1 hasta n, modelado en tres distintas funciones.
Autor: 
- Jeshua Nava Avila | A01639282
Fecha de creación y última modificación:
- 13/08/2021
- 16/08/2021
*/
#include <iostream>
#include <stdlib.h> // Incluir números random.
#include <time.h> // Incluir time.
using namespace std; 

/**
 * Suma desde 1 hasta n de forma iterativa.
 * Complejidad computacional: O(n)
 * Debido que es iterativo, tenemos que sumar cada elemento i (empezando en 1) hasta llegar a n.
 * 
 * @param n valor tipo int que será el final de nuestra suma.
 * @return la sumatoria de 1 hasta n, o -1 si n es negativo ó cero (por precondición). 
 */
int sumaIterativa(int n) {
    if (n > 0) {
        int suma = 0;
        for (int i=1; i < n+1; i++) {
            suma += i;
        }
        return suma;
    } else {
        return -1; // Modifico la postcondición de hacer nada, ya que c++ levanta un warning.
    }
}

/**
 * Suma desde 1 hasta n de forma recursiva. 
 * Complejidad computacional: O(n).
 * Aunque es una función recursiva, es muy sencilla. Llama n veces la función. 
 * 
 * @param n valor tipo int que será el final de nuestra suma.
 * @return la sumatoria de 1 hasta n, o -1 si n es negativo ó cero (por precondición).
 */
int sumaRecursiva(int n) {
    if (n >= 1) {
       if (n == 1) {
            return 1;
        }
        else {
            return sumaRecursiva(n-1) + n;
        }
    } else {
        return -1; // Modifico la postcondición de hacer nada, ya que c++ levanta un warning.
    }
}

/**
 * Suma desde 1 hasta n de forma matemática. 
 * Complejidad computacional: O(1)
 * Esta función solamente usa una operación básica.
 * 
 * @param n valor tipo int que será el final de nuestra suma.
 * @return la sumatoria de 1 hasta n, o -1 si n es negativo ó cero (por precondición).
 */
int sumaDirecta(int n) {
    if (n > 0) {
        return (n*(n+1))/2;
    } else {
        return -1; // Modifico la postcondición de hacer nada, ya que c++ levanta un warning.
    }
}

// Main de nuestro programa.
int main(){
    srand (time(NULL)); // Random seed para generar nuevos números aleatorios cada vez que se ejecuta el programa.
    int casosPrueba[] = { rand() % 10 + 1, rand() % 100 + 10, rand() % 1000 + 100, rand() % 10000 + 1000}; // Generamos nuestros números aleatorios en un arreglo.
    for (int i = 0; i < size(casosPrueba); i++) {
        cout << endl << "Caso " << i+1 << " para las tres funciones: " << casosPrueba[i] << endl;
        cout << "Iteración: " << sumaIterativa(casosPrueba[i]) << endl << "Recursion: " << sumaRecursiva(casosPrueba[i]) << endl << "Suma Directa: " 
        << sumaDirecta(casosPrueba[i]) << endl;
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    }
}