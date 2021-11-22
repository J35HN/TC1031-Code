/*
Actividad 5.1 - Implementación individual de operaciones sobre conjuntos.
- Tablas Hash, con manejo de colisiones a través de dirección abierta y cuadrática.
Autores:
- Jeshua Nava Avila | A01639282zz
- Carlos García Mercado | A01633757
- Alexa Serrano Negrete | A01654063
Fecha de creación y última modificación:
- 21/11/2021
- 22/11/2021
Aclaración:
- Parte del siguiente código se trabajo en un equipo temporal de manera remota en clase. Ya que se junto
  en clase para poder avanzar en la actividad. Solamente se trabajo hasta el Chain Method en equipo, lo resto ya
  es mi trabajo.
*/

// Librerías
#include "tabla_hash.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){
    TablaHash tablechain(1, 1000);
    TablaHash tablequad(2, 1000);
    int ran = 0;
    vector<string> nombres {"Nancy", "Jorge", "Daniel", "Mateo", "Alexa", "Jeshua", "Carlos", "Mariana", "Mariano", "Alejandra", "Alejandro", "Santiago", "Jonathan", "Joel", "Karla", "Sarah"};
    vector<string> insertados1, insertados2;
    for(int i = 0; i < 8; i++){
      srand(time(NULL)); // Random seed para generar nuevos números aleatorios cada vez que se ejecuta el programa o while.
      if(i < 4){
        for(int e = 0; e < 4; e++){
          ran = rand() % (nombres.size()-1) + 0;
          tablechain.insertar(nombres[ran]); // Insertar nombre a la tabla.
          insertados1.push_back(nombres[ran]);
        }
        ran = rand() % (insertados1.size()-1) + 0;
        cout << "Tabla Hash con Chain" << endl;
        cout << "Buscando el nombre: " << insertados1[ran] << endl;
        tablechain.exist(insertados1[ran]);
        cout << endl;
      } else {
        for(int e = 0; e < 4; e++){
          ran = rand() % (nombres.size()-1) + 0;
          tablequad.insertar(nombres[ran]); // Insertar nombre a la tabla.
          insertados2.push_back(nombres[ran]);
        }
        ran = rand() % (insertados2.size()-1) + 0;
        cout << "Tabla Hash con Quad" << endl;
        cout << "Buscando el nombre: " << insertados2[ran] << endl;
        tablequad.exist(insertados2[ran]);
        cout << endl;
      }
    }
    return 0;
}