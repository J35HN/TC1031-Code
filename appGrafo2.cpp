/*
Actividad 4.2 - Grafos: Algoritmos complementarios.
Autores:
- Jeshua Nava Avila | A01639282
- Ricardo González Leal | A01639036 (Equipo Temporal)
- Barbara Nicole Vidal Sandoval | A01635233 (Equipo Temporal)
- Pablo Agustín Ortega Kral | A00344664 (Equipo Temporal)
Fecha de creación y última modificación:
- 16/11/2021
- 19/11/2021
Aclaración:
- El siguiente código se trabajo en un equipo temporal de manera remota en clase. Ya que se junto
  en clase para poder avanzar en la actividad.
*/

// Librerías
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class ListaAdyacencia {
  public:
    unordered_map<string, vector<string>> l;
    ListaAdyacencia(){};
    /**
     * Agrega un vertice o nodo a una lista de adyacencia.
     * Complejidad Computacional: O(1).
     * La utilización de un hash map hace nuestra operaciones O(1).
     * 
     * @param identifier Vertice en donde se conecta a la vertice a agregar (From where)-
     * @param vertex Vertice a agregar (To where).
     */
    void addVertice(string identifier, string vertex) {
      l.find(vertex);
      // Agregar al mapa mutuamente, las vertices, para que en la lista aparezcan conectados.
      l[identifier].push_back(vertex);
      l[vertex].push_back(identifier);
    }

    /**
     * Muestra el contenido de la lista de adyacencia mediante un iterador.
     * Complejidad Computacional: O(n).
     * Una lista de adyacencia siempre tendrá n nodos que tendremos que mostrar.
     */
    void showList() {
      for (auto const& x : l)
      {
          cout << x.first  // string (key o nodo)
            << ": ";
          for (int i = 0; i < x.second.size(); i++) {
            cout << x.second[i] << " ";
          }
          cout << endl;
      }
    }
};

/**
 * Función donde una lista de adyacencia copia la información de otra.
 * La lista se crea dentro de la clase, y esta función se utiliza para 
 * cumplir con lo requerido.
 * Complejidad Computacional: O(1).
 * Solamente igualamos una variable a otra.
 * 
 * @param list Lista o grafo a cual se le copiarán los datos.
 * @param returnlist Lista o grafo al cual tendrá la información de otra.
 */
void loadGraph(ListaAdyacencia list, ListaAdyacencia &returnlist){
  returnlist = list;
}

// FALTO
// bool isTree(vector<vector<int>>lista, int vertices, int edges) {}

int main() {
  ListaAdyacencia lista, returnlist;
  int n = 0;
  string from, to;
  // Las cuatro pruebas las hace el usuario.
  for(int i = 0; i < 4; i++){
    cout << "Prueba " << i+1 << "." << endl;
    cout << "Numero de conexiones [INT]: " <<endl;
    cin >> n;
    cout << endl << "Conexiones [STRING] >> " << endl;
    for(int i = 0; i<n; i++){
      cout<< "From: ";
      cin >> from;
      cout<<"to: ";
      cin >> to;
      cout << "\n";
      lista.addVertice(from, to);
    }
    loadGraph(lista, returnlist);
    returnlist.showList();
    cout << endl << endl;
  }
} 