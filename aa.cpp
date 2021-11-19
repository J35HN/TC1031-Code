
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
class ListaAdyacencia {
  public:
    std::map<string, vector<string>> l;
    ListaAdyacencia() {
    }
    
    void addVertice(string identifier, string vertex) {
      vector<string> identificadores = l[identifier];
      std::map<string,vector<string>>::iterator it = l.begin();
      
      l.find(vertex);      
      l[identifier].push_back(vertex);
      l[vertex].push_back(identifier);
    }    
    void showList() {
      for (auto const& x : l)
      {
          cout << x.first  // string (key)
            << ": ";
          for (int i = 0; i < x.second.size(); i++) {
            cout << x.second[i] << " ";
          }
          cout << endl;
      }
    }
};
void loadGraph(ListaAdyacencia list, ListaAdyacencia &returnlist){
  returnlist = list;
}
// bool isTree(vector<vector<int>>lista, int vertices, int edges) {
  
// }
int main() {
  ListaAdyacencia lista, returnlist;
  int n = 0;
  string from, to;
  cout << "Numero de conexiones" <<endl;
  cin >> n;
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
} 