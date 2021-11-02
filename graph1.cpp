// A simple representation of graph using STL
#include<vector>
#include<iostream>
using namespace std;
  
// A utility function to add an edge in an
// undirected graph.

//Ver si existe 
/*bool existeEnVector(vector<string> v, string busqueda) {
    //return find(v.begin(), v.end(), busqueda) != v.end();
}
bool VerifyU = existeEnVector(adj, u);
bool VerifyV = existeEnVector(adj, v);
*/

int cont=0;
void addEdge(vector<int> adj[], int u, int v){
    bool verifyV = 0; 
    bool verifyU = 0; 
    for(auto x : adj[u])
      if(x == v) verifyV = 1;
    for(auto x : adj[v])
      if(x == u) verifyU = 1;
    
    
    if(!verifyV && !verifyU){
      cout<<cont++<<endl;
      //No existe en la lista de adjacencia
      adj[u].push_back(v); // En nodo u agregar a la lista el nodo v.
      adj[v].push_back(u); // En nodo v agregar a la lista el nodo u. 
    }


}
  
// A utility function to print the adjacency list
// representation of graph
void printGraph(vector<int> adj[], int V){

    for (int v = 0; v < V; ++v){
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
}
  
// Driver code
int main()
{
    int V = 5; //Vertices
    vector<int> adj[V]; 
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 2, 3); // Repetido (no se agrega)
    addEdge(adj, 3, 4);
    addEdge(adj, 7, 0); //Fuera de rango (no se agrega)
    printGraph(adj, V);
    return 0;
}