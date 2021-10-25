/*
Actividad 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia).
- Actividad integral donde regresamos un archivo conteniendo registros ordenados y limitados de una bitácora.
Autores:
- Jeshua Nava Avila | A01639282
- Barbara Nicole Vidal Sandoval | A01635233
- Renet de Jesus Perez Gomez | A01640555 
Fecha de creación y última modificación:
- 12/10/2021
- 21/10/2021 
*/

// Librerías
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Función que convierte un mes en un valor int, para poder comparar meses.
 * Complejidad computacional: O(1).
 * Como trabajamos con un unordered_map, que es implementado con un Hash Table, estos tienen un costo de búsqueda, insersión
 * y borrado de O(1).
 * 
 * @param mes String que contiene el mes que se quiere encontrar su equivalencia en int.
 * @return El int equivalente del mes, que es buscado en el unordered_map.
 */
int mesNum(string mes){
  unordered_map<string, int> meses({
    {"Ene", 1}, {"Feb", 2}, {"Mar", 3}, {"Abr", 4}, {"May", 5}, {"Jun", 6}, 
    {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dic", 12}
    });
    return meses[mes];
}

/**
 * Convierte el mes, día, hora, minuto y segundo en un número decimal.
 * Ejemplo: Oct 9 10:32:24  -> 1009103224.
 * Ejemplo: Oct 9 00:00:00  -> 1009000000.
 * Ejemplo: Oct 9 23:59:59  -> 1009235959.
 * Complejidad: O(1).
 * Como el input siempre es una línea de n carácteres, siempre realiza una serie determinada de pasos.
 * 
 * Orden de meses: Ene = 1 - Dec = 12.
 * Orden de los días: 1-31.
 * Orden de horas: 0 - 23.
 * Orden de minutos: 0 - 59.
 * Orden de segundos: 0 - 59.
 * @param linea Un string que contiene el registro (fecha).
 * @return Número equivalente a la fecha de registro.
 */
int tiempoDecimal(string linea){
    string mes, dia, hor, min, seg, temp;
    // Obtenemos mes en número y lo cambiamos a string.
    mes = to_string(mesNum(linea.substr(0, 3))); // mesNum no afecta complejidad, ya que también es O(1).
    // Obtenemos día, hora, minuto y segundos en strings.
    temp = linea[5];
    if(temp == " "){
      dia = "0"; // En la posicion 5 aveces sera un espacio, para conservar el formato agregamos 0 al inicio.
      dia += linea.substr(4, 1);
      hor = linea.substr(6, 2);
      min = linea.substr(9, 2);
      seg = linea.substr(12, 2);
    } else {
      dia = linea.substr(4, 2); 
      hor = linea.substr(7, 2);
      min = linea.substr(10, 2);
      seg = linea.substr(13, 2);
    }
    // Juntamos variables en un string y los convertimos en un int.
    return stoi(mes + dia + hor + min + seg); 
}

/** 
 * Función que regresa el mes y día de una línea de la bitacora.
 * Complejidad Computacional: O(1).
 * Siempre (dependiendo del caso), escogera los mismos carácteres de una línea de la bitacora.
 * 
 * @param linea Un renglon de bitacora.
 * @return String que indica mes y día.
 */
string tiempoString(string linea){
  string mes, dia, hor, min, seg, temp;
    // Obtenemos mes en número y lo cambiamos a string.
    mes = linea.substr(0, 3); // mesNum no afecta complejidad, ya que también es O(1).
    // Obtenemos día, hora, minuto y segundos en strings.
    temp = linea[5];
    if(temp == " "){
      dia = "0"; // En la posicion 5 aveces sera un espacio, para conservar el formato agregamos 0 al inicio.
      dia += linea.substr(4, 1);
    } else {
      dia = linea.substr(4, 2); 
    }
    return mes + " " + dia;
}

/** 
 * Obtiene el IP de una línea de bitacora, ya sea sin los puntos y doble puntos, o con ellos.
 * Complejidad Computacional: O(1).
 * Las IP tienen un tamaño similar, y solamente se selecionnan algunos carácteres.
 * 
 * @param linea Línea de la bitacora al cual se quiere obtener su IP.
 * @param modo Determina si se obtendrá el ip completo o solamente los números.
 * @return El IP de una línea de bitacora.
 */
string ipFromLine(string linea, int modo = 0){ //obtener el decimal de cada IP
  string temp = "", ip = "";
  int pos = 0;
  int suma = 0;
  temp = linea[14];
  if(temp == " "){ //Ip comienza en 15
    pos = 15;
    temp = linea[pos];
    while(temp!=" "){
      if(modo == 0){ // Revisamos en que modo.
        if (temp != "." && temp != ":"){
          ip += temp;
        }
        pos++;
        temp = linea[pos];
      } else {
        ip += temp;
        pos++;
        temp = linea[pos];
      }
    }    
  }else{ //Ip comienza en 16
    pos = 16;
    temp = linea[pos];
    while(temp!=" "){
      if(modo == 0){ // Revisamos en que modo.
        if (temp != "." && temp != ":"){
          ip += temp;
        }
        pos++;
        temp = linea[pos];
      } else {
        ip += temp;
        pos++;
        temp = linea[pos];
      }
    }
      
  }
  return ip;
}

/**
 * Función que compara elementos de un vector y los ordena (parte del función Merge Sort).
 * Complejidad computacional: O(n).
 * Aunque tenga varios for loops y whiles, ninguno está anidado (en total n pasos para completar merge).
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio del vector.
 * @param m Int index del punto medio del vector.
 * @param r Int index del final de un vector.
 */
void merge(vector<string>& V, int l, int m, int r){
    vector<string> L, R; // Subarreglos temporales
    int n1 = m-l+1, n2 = r-m, i = 0, j = 0, k = l;
    for (int i=0; i<n1; i++){
        L.push_back(V[l+i]);
    }
    for (int j=0; j<n2; j++){
        R.push_back(V[m+j+1]);
    }
    i = j = 0;
    while (i < n1 && j < n2){
        if (tiempoDecimal(L[i]) <= tiempoDecimal(R[j])){
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
 * Función que compara elementos de un vector y los ordena (parte del función Merge Sort).
 * Complejidad computacional: O(n).
 * Aunque tenga varios for loops y whiles, ninguno está anidado (en total n pasos para completar merge).
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio del vector.
 * @param m Int index del punto medio del vector.
 * @param r Int index del final de un vector.
 */
 
void mergeIp(vector<vector<string>>& V, int l, int m, int r){
    vector<string> temp1, temp2; // Subarreglos temporales de los IPs
    vector<vector<string>> L, R; // Vectores que contienen tanto la línea de bitacora como sus ocurrencias en IP.
    int n1 = m-l+1, n2 = r-m, i = 0, j = 0, k = l;
    for (int i=0; i<n1; i++){
        L.push_back(V[l+i]);
    }
    for (int j=0; j<n2; j++){
        R.push_back(V[m+j+1]);
    }
    i = j = 0;
    temp1 = L[i]; // Información de una línea de bitacora.
    temp2 = R[j]; // Información de una línea de bitacora.
    while (i < n1 && j < n2){
        temp1 = L[i];
        temp2 = R[j];
        if (stoi(temp1[1]) >= stoi(temp2[1])){ // Comparamos por cantidad de ocurrencia.
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
 * Complejidad computacional (promedio): O(nLog n).
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio de un vector.
 * @param r Int index del final de un vector (size - 1).
 */
void ordenaMerge(vector<string>& V, int l, int r){
    int m = 0;
    if (l<r){
      m = floor(((l+r)/2));
      ordenaMerge(V, l, m);
      ordenaMerge(V, m+1, r);
      merge(V, l, m, r);
    }
    
}

/**
 * Ordena un vector de vectores string con el algoritmo MergeSort.
 * Complejidad computacional (promedio): O(nLog n).
 * Log n se obtiene por la sumatoria de las particiones de los sub-arreglos. Esto multiplicado por n de la parte merge.
 * 
 * @param V Vector tipo int que se desea ordenar.
 * @param l Int index del inicio de un vector.
 * @param r Int index del final de un vector (size - 1).
 */
void ordenaMergeIp(vector<vector<string>>& V, int l, int r){
    int m = 0;
    if (l<r){
      m = floor(((l+r)/2));
      ordenaMergeIp(V, l, m);
      ordenaMergeIp(V, m+1, r);
      mergeIp(V, l, m, r);
    }
    
}

/**
 * Lee un archivo, y cada línea de texto lo guarda dentro de un vector.
 * Complejidad computacional: O(n).
 * Tiene que leer cada línea que viene dentro del archivo.
 * 
 * @param nombreArchivo El nombre del archivo en string.
 * @return Un vector que contiene las líneas del archivo.
 * 
 */
vector<string> leerVectorizarArchivo(string nombreArchivo) {
    vector<string> bitacora;
    ifstream archivo(nombreArchivo.c_str()); // Abrir archivo.
    string linea;
    
    // Obtener línea de archivo, y almacenar contenido en "linea".
    while (getline(archivo, linea)) {
       bitacora.push_back(linea);
    }
    archivo.close();
    return bitacora;
}

/**
 * Imprime por línea un archivo.
 * Complijidad computacinoal: O(n).
 * Esto es debido a que tenemos un ciclo iterativo while, que lee cada línea del archivo.
 * 
 * @param nombreArchivo Archivo que imprimimos en consola.
 */
void ImprimeArchivo(string nombreArchivo){
  ifstream archivo(nombreArchivo); //Abrimos archivo.
  string linea;
  //Leemos el archivo
  while (getline(archivo, linea)){
    cout << linea << endl; // Imprimos la línea.
  }
  archivo.close(); // Cerramos archivo.
}


/**
 * Función que pide el rango de fechas a consultar.
 * Complejidad computacional: O(n).
 * Depende de lo que ingrese el usuario.
 * 
 * @param indiceConsulta Número de consulta.
 * @return Un vector string con las fechas de rango.
 */
vector<string> consulta(int indiceConsulta){
  int mesIni = 0, diaIni = 0, mesFin = 0, diaFin = 0;
  string fechaIni = "", fechaFin = "";
  vector<string> fechasBusqueda;
  
  cout << endl << "-=-= Consulta " << indiceConsulta << " -=-=-=-=" << endl;
  cout << "Por favor ingrese el rango de meses que quiera consultar: " << endl;
  cout << "Meses: [1=Ene, 2=Feb, 3=Mar, 4=Abr, 5=May, 6=Jun, 7=Jul, 8=Aug, 9=Sep, 10=Oct, 11=Nov, 12=Dic]" << endl;
  cout << "Dias: [Del 1 al 31]" << endl;

  // Verificamos que ingrese un mes correcto.
  while(mesIni <= 0 || mesIni > 11){ 
    cout << "Mes de inicio: [Ingrese el numero de mes de inicio (1-11)] " << endl << "-> ";
    cin >> mesIni;
    if(mesIni <= 0 || mesIni > 11){
      cout << "Por favor, el mes de inicio debe ser mayor a 0 y menor que 11 :)" << endl;
    } else {
      fechaIni += to_string(mesIni); // Guardamos el valor del mes.
    }
  }

  //Verificamos que ingrese un dia correcto
  while(diaIni <= 0 || diaIni > 31){
    cout << "Dia del mes de inicio: [Ingrese el numero del dia del mes de inicio]" << endl << "-> "; 
    cin >> diaIni;
    if(diaIni <= 0 || diaIni > 31){
      cout << "El dia debe ser entre un numero del 1 al 31 :)" << endl;
    } else if (diaIni < 10) { // Guardamos el valor del día.
      fechaIni += "0" + to_string(diaIni); // Agregamos un cero para mantener formato.
    } else {
      fechaIni += to_string(diaIni); // Guardamos el valor del día.
    }
  }

  // Verificamos que ingrese un mes correcto. Cuidando que no ingrese un mes menor al del mes inicial.
  while(mesFin <= 0 || mesFin > 12 || mesFin < mesIni){
    cout << "Mes final: [Ingrese el numero de mes final]" << endl << "-> ";
    cin >> mesFin;
    if(mesFin <= 0 || mesFin > 12 || mesFin < mesIni){
      cout << "El mes final debe de estar entre el mes " << mesIni << " y el mes 12 :)" << endl;
    } else {
      fechaFin += to_string(mesFin); // Guardamos el valor del mes.
    }
  }

  //Verificamos que ingrese un dia correcto. Cuidando que si es el mismo mes no sea un día menor.
  while(diaFin <= 0 || diaFin > 31 || diaFin < diaIni && mesFin == mesIni){
    cout << "Dia del mes final: [Ingrese el numero del dia del mes final]" << endl << "-> ";
    cin >> diaFin;
    if(diaFin <= 0 || diaFin > 31){
      cout << "Recuerda que el dia es numero entre el 1 y el 31 :)";
    } else if (diaFin < diaIni && mesFin == mesIni){
      cout << "El dia final no puede ser menor al dia de inicio en el mismo mes :)" << endl; 
    } else if (diaFin < 10) {
      fechaFin += "0" + to_string(diaFin); // Agregamos 0 para mantener formato.
    } else {
      fechaFin += to_string(diaFin);
    } 
  }
  // Terminamos de completar nuestras fechas de busqueda.
  fechaIni += "000000"; // Inicio del día.
  fechaFin += "235959"; // Final del día. 

  fechasBusqueda.push_back(fechaIni);
  fechasBusqueda.push_back(fechaFin);
  
  return fechasBusqueda;
}

/**
 * Función que regresa el index de un elemento dentro de un vector, o regresa el índice mas cercano al key,
 * con el algoritmo Binary Search.
 * Complejidad computacional: O(Logn)
 * Dividimos al arreglo de tamaño n en dos hasta llegar a un tamaño 1 (o un lugar en donde se encuentra el elemento).
 * 
 * @param V vector tipo int em donde se busca el elemento.
 * @param key elemento que se desea encontrar su index dentro del vector (si existe).
 * @return El índice en donde se encuentra el elemento o el índice más cercano.
 */
int busqBinaria(vector<string> V, int key){
    int l = 0, r = V.size()-1, index = 0, temp;
    while (r >= l){
        index = floor((l+r)/2);
        temp = tiempoDecimal(V[index]);
        if (temp == key){
            return index;
        } else if (temp > key){
            r = index - 1;
        } else {
            l = index + 1 ;
        }
    }
    return index; // Retorna el índice más cercano al key. 
}

/**
 * Funcion que tiene un vector de IPs y cuenta cuantas veces se repite cada uno, a continuación 
 * manda llamar la función ordenaMergeIP para un ordenamiento en descenso.
 * Complejidad computacional: O(n).
 * 
 * @param V Vector de IPs.
 */

void ordenaPorIP(vector<vector<string>>& V){
  vector<string> IpUnicos, temp;
  unordered_map<string, int> IPS;
  int oc;
  // Encontrar y definir las veces que se encuentra un IP en el vector.
  for(int i=0; i < V.size(); i++){
    temp = V[i];
    if(IPS.count(ipFromLine(temp[0]))){
      IPS[ipFromLine(temp[0])] += 1;
    } else {
      IPS[ipFromLine(temp[0])] = 1;
    }
  }
  // Actualizar los valores por cada línea.
  for(int i=0; i < V.size(); i++){
    temp = V[i];
    if(IPS.count(ipFromLine(temp[0]))){
      temp[1] = to_string(IPS[ipFromLine(temp[0])]);
      V[i] = temp;
    }
  }
  // Ordenar el vector.
  ordenaMergeIp(V, 0, V.size()-1);
}

/**
 * Función que despliega los registros en el rango de fechas, y los guarda en un archivo.
 * Complejidad computacional: O(n).
 * Dependiendo del rango de las fechas, será la cantidad de regsitros.
 
 * @param fechas El rango de fechas de consulta.
 * @param bitacora Todas las lineas de la bitacora.
 * @param numConsulta Números de consulta que se realizarán.
 */
void guardaArchivo(vector<string> fechas, vector<string> bitacora, int numConsulta){
  int inicio=0, fin=0, key = 0, temp = 0;
  string consulta = "Consulta" + to_string(numConsulta+1) + ".txt", lineaIP;
  vector<string> registros, IpDia;
  vector<vector<string>> IpsPorDia;
  
  // Consultar las fechas. Ver de donde empieza y donde termina para guardar estos registros en un vector.
  // Buscamos el índice "start" (fecha de inicio) más cercano en bitacora.
  key = stoi(fechas[0]); // ID de la fecha inicio.
  inicio = busqBinaria(bitacora, key); // Indice más cercano a la fecha inico.
  key = stoi(fechas[1]); // ID de la fecha fin.
  fin = busqBinaria(bitacora, key); //Indice más cercano a la fecha fin.
  
  // Verificar que los índices no sean los mismos.
  if(inicio-fin==0){
    cout << endl << "-=-= Consulta " << numConsulta + 1 << " -=-=-=-=" << endl;
    cout << "No se encontro ningun registro en el intervalo de fecha solicitado." << endl;
  }else{
    // Recorrer bitacora por estos indices, para guardar los registros en un vector.
    // Guardamos la primera línea de la bitacora en inicio, para poder usar los valores de tiempo e IP, y así gurdarñp em registros.
    temp = tiempoDecimal(bitacora[inicio]);
    IpDia.push_back(bitacora[inicio]); // Guardamos línea entera de bitacora en inicio.
    IpDia.push_back("1"); // Guardamos que tiene una ocurrencia.
    IpsPorDia.push_back(IpDia); // Esta información de línea y ocurrencia se guardan juntos dentro de otro vector.
    registros.push_back(tiempoString(bitacora[inicio])); // Agregamos el primer día en el registro.
    IpDia.clear();
    for(int i = inicio+1; i < fin+1; i++){
      // Recorrer por días dentro de la bitacora.
      temp -= tiempoDecimal(bitacora[i]);
      if(temp < -235959){ // Detecta que cambió de día.
        if( IpsPorDia.size() < 2){ // Si solamente tiene un IP el día, se guardan directo en los registros.
          IpDia = IpsPorDia[0];
          lineaIP = ipFromLine(IpDia[0], 1) + " -> " + IpDia[1]; // Creamos nuestro string para guardar en registros.
          // Asegurar que no se repita el IP en el registro.
          if( find(registros.begin(), registros.end(), lineaIP) != registros.end()){
            ; // No hacer nada si ya se encuentra el IP dentro de registros, para no repetir.
          } else {
            registros.push_back(lineaIP);
          }
          // Borrar los datos para poder guardar los IPs del siguiente día.
          IpDia.clear();
          IpsPorDia.clear();
        }else{
          // Ordenamos por IP y luego por fecha a los registros en un día.
          ordenaPorIP(IpsPorDia);
          // Guardamos en registros las líneas de texto (consultas).
          for(int e=0; e < IpsPorDia.size(); e++){
            IpDia = IpsPorDia[e];
            lineaIP = ipFromLine(IpDia[0], 1) + " -> " + IpDia[1]; // Creamos nuestro string para guardar en registros.
            // Asegurar que no se repita el IP en el registro.
            if( find(registros.begin(), registros.end(), lineaIP) != registros.end()){
              ; // No hacer nada si ya se encuentra el IP dentro de registros, para no repetir.
            } else {
              registros.push_back(lineaIP);
            }
            IpDia.clear();
            temp = 0; // Reiniciamos temp para poder comparar y detectar un cambio de día, de acuerdo a los días que vengan en la bitacora.
          }
          IpsPorDia.clear();
        }
        registros.push_back(tiempoString(bitacora[i])); // Ingresamos el nuevo día al registro.
      }
      temp = tiempoDecimal(bitacora[i]);
      IpDia.push_back(bitacora[i]);
      IpDia.push_back("1");
      IpsPorDia.push_back(IpDia);
      IpDia.clear();      
    }
    // Revisar si tiene datos IpsPorDia. Si tiene repetir los mismos pasos anteriores para guardarlos en registro.
    if(IpsPorDia.size() > 0){
      if( IpsPorDia.size() < 2){
          IpDia = IpsPorDia[0];
          lineaIP = ipFromLine(IpDia[0], 1) + " -> " + IpDia[1];
          if( find(registros.begin(), registros.end(), lineaIP) != registros.end()){
            ;
          } else {
            registros.push_back(lineaIP);
          }
          IpDia.clear();
        }else{
          // Ordenamos por IP y luego por fecha a los registros en un día.
          ordenaPorIP(IpsPorDia);
          // Guardamos en registros las líneas de texto (consultas).
          for(int e= 0; e < IpsPorDia.size(); e++){
            IpDia = IpsPorDia[e];
            lineaIP = ipFromLine(IpDia[0], 1) + " -> " + IpDia[1];
            if( find(registros.begin(), registros.end(), lineaIP) != registros.end()){
              ;
            } else {
              registros.push_back(lineaIP);
            }
            IpDia.clear();
          }
          IpsPorDia.clear(); // Borrar los IP del día, para empezar con los nuevos.
      }
    }
    cout << endl << "-=-= Consulta " << numConsulta + 1 << " -=-=-=-=" << endl;
    cout<<"El vector tiene "<< registros.size() <<" registros"<<endl;
    if(registros.size()>10){
      int op=0;
      cout<<"1 - Imprimir todo"<<endl;
      cout<<"2 - Imprimir los primeros 10"<<endl;
      cout<<"3 - Imprimir los ultimos 10"<<endl;
      cin >> op;
      if(op == 1){
        for(int i=0; i < registros.size(); i++){ // Despliega a pantalla todos los datos que se encuentran dentro del rango asignado. 
          cout << i + 1 << " - " << registros[i] << endl;
        }
      }else if(op == 2){
        for(int i=0; i < 10; i++){ // Despliega a pantalla solo los primeros diez datos que se encuentran dentro del rango asignado.
          cout << i + 1 << " - " << registros[i] << endl;
        }      
      }else if(op == 3){ // Despliega a pantalla solo los ultimos diez datos que se encuentran dentro del rango asignado.
        for (int i = (registros.size()-10); i < registros.size(); i++){
          cout << i + 1 << " - " << registros[i] << endl;
        }
      }
    }else{
      for(int i=0; i < registros.size(); i++){ // En caso de ser menor a diez datos dentro del rango, los imprime todos.
        cout << i + 1 << " - " << registros[i] << endl;
      }
    }
    // Guarda un archivo .txt con los registros.
    cout << "Ya guarde los registros en el archivo " << consulta << endl; 
    ofstream archivoTxt(consulta);
    for(int i=0; i < registros.size(); i++){
      archivoTxt << registros[i] + "\n";
    }
    archivoTxt.close();
  }
}

int main(){
  int numConsultas = 0, opc=1;
  cout << "Leyendo archivo de registros, cargando..." << endl;
  vector<string> bitacora, temp;
  vector<vector<string>> fechasConsultas;

  // Leer archivo bitacora.txt y ordenarlo en un vector.
  bitacora = leerVectorizarArchivo("bitacora.txt");
  ordenaMerge(bitacora, 0, bitacora.size()-1);

  // La verdad no creo que vamos a ocupar el while, amenos que implementos un menú o algo.
  ImprimeArchivo("portada.txt");
  cout << endl << "Bienvenido a los registros de ingreso de Data TC :)" << endl;
  while(numConsultas == 0 || numConsultas > 10){ // Revisar que el usuario ingrese un número válido.
    cout << "Cuantas consultas va a realizar? [Ingrese un numero entero]" << endl << "-> ";
    cin >> numConsultas;
    if (numConsultas <= 0){
      cout << endl << "Por favor, un numero mayor que cero :)" << endl;
    } else if (numConsultas > 10){
      cout << endl << "Nada mas es permitido hacer hasta 9 consultas, gracias por su comprension :)" << endl;
    }
  }

  //Ciclo for para solicitar las fechas de la cantidad del numero de consultas   
  for(int i=1; i<numConsultas+1; i++){
    temp = consulta(i); // Guarda el rango de fechas.
    fechasConsultas.push_back(temp);
  }

  //Ciclo for para guardar e imprimir los datos (la cantidad del numero de consultas)
  for(int i=0; i<fechasConsultas.size(); i++){
    temp = fechasConsultas[i]; // temp = rango que consultar.
    guardaArchivo(temp, bitacora, i);
  }

  cout << endl << "Gracias por usar el programa, si quiere hacer otra consulta, reinicie el programa :)." << endl;
  return 0;
}