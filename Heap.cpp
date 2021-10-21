/*
Actividad 3.2 - Árbol Heap: Implementando una fila priorizada.
- Realiza en forma individual una clase en C++ llamada "priority_queue" 
  que tenga las siguientes operaciones utilizando un heap y simulando una fila priorizada 
  de enteros con prioridad de valor mayor.
Autor:
- Jeshua Nava Avila | A01639282
Fecha de creación y última modificación:
- 20/10/2021
- 20/10/2021 
*/

// Librerias
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Clase
class priority_queue {
    vector<int> arr;
    int sizeArr;

    public:
        priority_queue(); // Constructor.

        void swap(int *x, int *y); // Intercambia el valor de dos variables.

        void print_queue(); // Imprime los elementos del arreglo.

        /** Regresa el índice del padre de un elemento.
         * Complejidad Computacional: O(1).
         * @param i Índice al cual encontrar su padre.
         * @return El índice del padre de i.
         */ 
        int parent(int i) {return (floor((i-1)/2));}

        /** Regresa el índice del hijo izquierdo del elemento en índice i.
         * Complejidad Computacional: O(1).
         * @param i Índice al cual se quiere encontrar el índice del hijo izquierdo.
         * @return El índice del hijo izquierdo de i.
         */
        int left(int i){return (2*i + 1);}
        
        /** Regresa el índice del hijo derecho del elemento en índice i.
         * Complejidad Computacional: O(1).
         * @param i Índice al cual se quiere encontrar el índice del hijo derecho.
         * @return El índice del hijo derecho de i.
         */
        int right(int i){return (2*i + 2);}

        /** Regresa el tamaño del arreglo.
         * Complejidad Computacional: O(1).
         * @return int de valor del tamaño del arreglo.
         */
        int size(){return sizeArr;}

        void push(int n); // Para insertar un elemento.

        void pop(); // Borra el primer elemento del arreglo.

        int top(); // Regresa el primer elemento del arreglo sin borrarlo.

        bool empty(); // Revisar si está vacio el arreglo.

        void organiza(int i); // Organiza el arreglo siguiendo MAX HEAP.
};
priority_queue::priority_queue(){
    vector<int> temp;
    arr = temp; 
    sizeArr = 0;
}

/** Inrecambia dos valores en la dirección de otro.
 * Complejidad Computacional: O(1).
 * @param x Dirección de un valor a intercambiar.
 * @param y Dirección del otro valor a intercambiar.
 */
void priority_queue::swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/** Imprime los elementos dentro del arreglo.
 * Complejidad Computacional: O(n).
 */
void priority_queue::print_queue(){
    for(int i = 0; i < sizeArr; i++){
        cout << arr[i] << " - ";
    }
    cout << "." << endl;
}

/** Insertar un elemento dentro del arreglo heap.
 * Complejidad Computacional: [].
 * @param n Elemento que se quiere insertar.
 */
void priority_queue::push(int n){
    int i = 0;
    sizeArr++; // Incrementamos el valor de size en un valor.
    arr.push_back(n); // Ingresamos el valor n al final.
    // Revisar si se cumple que todos los hijos son menores que los padres.
    i = sizeArr - 1; // Última posición.
    while(i != 0 && arr[parent(i)] < arr[i]){
        swap(&arr[i], &arr[parent(i)]);
        i = parent(i);
    }
}

/** Borra el primer elemento del arreglo, lo cual después reacomoda el arreglo de manera recursiva.
 * Complejidad Computacional: O(1).
 */
void priority_queue::pop(){
    vector<int>::iterator it;
    if(sizeArr > 1){
        arr[0] = arr[sizeArr-1];
        sizeArr--;
        arr.pop_back();
        //it = arr.begin(); // Iterador para borrar el primer elemento.
        //arr.erase(it); // Borramos el primer elemento.
        //swap(&arr[0], &arr[sizeArr-1]);// Movemos el último elemento al "root" para crear una desigualdad y empezar desde ahí acomodar.
        organiza(0);
    } else if (sizeArr == 1){
        sizeArr--;
        it = arr.begin(); // Iterador para borrar el primer elemento.
        arr.erase(it); // Borramos el primer elemento.
    } else {
        cout << "El arreglo no tiene ningun elemento a borrar porque esta vacio!" << endl;
    }
    
}

/** Organiza de manera MAX HEAP al arreglo.
 * Complejidad Computacional: O(n).
 * Dependiendo del tamaño del arreglo, será la cantidad de pasos para organizar el arreglo de manera recursiva.
 */
void priority_queue::organiza(int i){
    int LC = 0, RC = 0, mayor = 0;
    // Guardamos los índices, por un potencial mayor que esté en un extremo equivocado, o un menor en el otro.
    LC = left(i);
    RC = right(i);
    mayor = i;
    if(LC < sizeArr && arr[LC] > arr[i]){ 
        mayor = LC;
    }
    if(RC < sizeArr && arr[RC] > arr[mayor]){
        mayor = RC;
    }
    if(mayor != i){
        swap(&arr[i], &arr[mayor]); // Dependiendo cual hijo es mayor, el padre va cambiar con el.
        organiza(mayor);
    }
}

/** Regresa el primer valor del arreglo.
 * Complejidad Computacional: O(1).
 * @return valor del primer elemento en el arreglo.
 */
int priority_queue::top(){
    if(sizeArr > 0){
        return arr[0];
    } else {
        cout << "El arreglo esta vacio! Regresando 0..." << endl;
        return 0;
    }
}

/** Regresa un True o False si el arreglo está vacio o no.
 * Complejidad Computacional: O(1).
 * @return True o False.
 */ 
bool priority_queue::empty(){
    if(sizeArr == 0){
        return true;
    } else {
        return false;
    }
}
  
int main(){
    srand (time(NULL)); // Random seed para generar nuevos números aleatorios cada vez que se ejecuta el programa.
    priority_queue caso1, caso2, caso3, caso4;
    vector<priority_queue> casos {caso1, caso2, caso3, caso4};
    // Llenamos cada caso con números aleatorios, de un tamaño de 0 a 25.
    for(int i = 0; i < 4; i++){
        int times = rand() % 25 + 0;
        for(int e = 0; e < times; e++){
            int num = rand() % 1000 + 1;
            casos[i].push(num);
        }
    }
    // Ejecutamos funciones en cada caso.
    for(int i = 0; i < 4; i++){
        cout << endl << "Caso " << i+1 << endl;
        cout << "El arreglo esta vacio? [0 = no, 1 = si] " << casos[i].empty() << endl;
        cout << "Cuantos elementos tiene? " << casos[i].size() << endl;
        cout << "Elementos: " << endl;
        casos[i].print_queue();
        cout << "Valor del primer elemento: " << casos[i].top() << endl;
        int timesPop = rand() % 5 + 0;
        cout << "Cantidad de veces que voy hacer pop: " << timesPop << endl;
        for(int j = 0; j < timesPop; j++){
            casos[i].pop();
        }
        cout << "El arreglo esta vacio? [0 = no, 1 = si] " << casos[i].empty() << endl;
        cout << "Cuantos elementos tiene? " << casos[i].size() << endl;
        cout << "Elementos: " << endl;
        casos[i].print_queue();
        cout << "Valor del primer elemento: " << casos[i].top() << endl << endl;
    }
    
}