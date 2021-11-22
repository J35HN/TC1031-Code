#ifndef THASH_H
#define THASH_H
#include <vector> 
#include <string>
#include <cmath>
#include <iostream>
class TablaHash{
    public:
        TablaHash();
        TablaHash(int, int);
        int convertToASCII(std::string);
        int hashFunction(std::string);
        void insertar(std::string);
        void exist(std::string);

        private:
            int sizeT;
            int typeT;
            std::vector< std::vector< std::string> > hashtableCHAIN;
            std::vector<std::string> hashtableQUAD;
            
};
/**
 * Constructor default.
 * Complejidad Computacional: O(1).
 */
TablaHash::TablaHash(){
    sizeT = 1000;
    typeT = 1;
    hashtableCHAIN.resize(sizeT);
    hashtableQUAD.resize(sizeT);
}

/**
 * Constructor por parámetros.
 * Complejidad Computacional: O(1).
 * 
 * @param type Tipo de hash table.
 * @param size Tamaño del hash table.
 */
TablaHash::TablaHash(int type = 1, int size = 1000){
    sizeT = size;
    typeT = type;
    if(typeT == 1){
        hashtableCHAIN.resize(sizeT); // Type 1
    } else {
        hashtableQUAD.resize(sizeT); // Type 2 or other number
    }
}

/**
 * Convierte un char de un string en su valor numérico ASCII.
 * Complejidad Computacional: O(1).
 * 
 * @param letter String al cual el primer caracter se convertirá a valor ASCII.
 * @return int, valor numérico del char.
 */
int TablaHash::convertToASCII(std::string letter){
    for(int i = 0; i < letter.length(); i++){
        char x = letter.at(i);
        return int(x);
    }
    return 127;
}

/**
 * Función Hash de nuestra Tabla Hash.
 * Es la suma de los valores numéricos ASCII de los primeros tres char y el último.
 * Complejidad Computacional: O(1).
 * Debería ser O(n), porque indexamos al último elemento de un string. Pero como el nombre o string normalmente 
 * son cortos, este se comporta como O(1).
 * 
 * @param nombre String al cual se obtiene su index por la función.
 * @return int Index.
 */
int TablaHash::hashFunction(std::string nombre){
    int indice = 0;
    std::string a = "", b = "", c = "", d = "";
    a = nombre[0];
    b = nombre[1];
    c = nombre[2];
    d = nombre[nombre.length()-1];
    indice += convertToASCII(a) + convertToASCII(b) + convertToASCII(c) + convertToASCII(d);
    return indice;
}

/**
 * Insertar un elemento string a la Tabla Hash.
 * Complejidad Computacional: O(1).
 * 
 * @param palabra String que inserta a la Tabla Hash.
 */
void TablaHash::insertar(std::string palabra){
    int indice = hashFunction(palabra), collision = 1, hx = indice, it = 1, temp = 0;
    if(typeT == 1){
        hashtableCHAIN[indice].push_back(palabra);
    } else {
        while(collision == 1){
            if(hashtableQUAD[indice] == ""){
                collision = 0;
                hashtableQUAD[indice] = palabra;
            } else {
                temp = hx + std::pow(it, 2);
                indice = temp % sizeT;
                it++;
            }
        }
    }
    
}

/**
 * Encuentra (imprime) los índice(s) de un elemento en la Tabla Hash.
 * Complejidad Computacional: O(n).
 * Hacemos un recorrido por toda la Tabla Hash para encontrar los índices de un elemento.
 * 
 * @param palabra String, a encontrar su índices en la Tabla Hash.
 */
void TablaHash::exist(std::string palabra){
    int indice = hashFunction(palabra);
    std::vector<int> index;
    if(typeT == 1){
        for(int i = 0; i < hashtableCHAIN[indice].size(); i++){
            if(palabra == hashtableCHAIN[indice][i]){
                index.push_back(i);
            }
            if(i == hashtableCHAIN[indice].size()-1){
                std::cout << "Indice(s): " << std::endl << "[" << indice << "]-> ";
            }
        }
        for(int e = 0; e < index.size(); e++){
            if(e == index.size()-1){
                std::cout << index[e] << "." << std::endl;
            } else {
                std::cout << index[e] << ", ";
            }
        }
    } else {
        for(int i = 0; i < hashtableQUAD.size(); i++){
            if(hashtableQUAD[i] == palabra){
                index.push_back(i);
            }
        }
        std::cout << palabra << " existe en los indices: ";
        for(int e = 0; e < index.size(); e++){
            if(e == index.size()-1){
                std::cout << index[e] << "." << std::endl;
            } else {
                std::cout << index[e] << ", ";
            }
        }
    }
    
}

#endif //THASH_H