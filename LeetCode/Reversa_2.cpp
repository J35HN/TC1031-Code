#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;


class Solution {
public:
    int reverse(int x) {
        int num=2;
        if(x>=(pow(num,31)-1) || x<=pow(-num,31)){ //x no se tiene que pasar de esos rangos
            cout<<"Numero invalido"<<endl;
            return 0;
        }
        else{
            string xs = to_string(x); //Convierte a string el valor de x
            if(x>=0){ //si el valor de x es mayor o igual a 0...en caso de ser un número positivo
                cout<<"Valor positivo: "<<x<<endl;
                string xs_reversed(xs.rbegin(), xs.rend()); // se invierte el string x
                string xsnew = xs_reversed; // se crea una nueva variable con el string invertido 
                stringstream geek(xsnew); //Se convierte de string a int
                int xi = 0;
                geek >> xi;
                if(xi>=(pow(num,31)-1) || xi<=pow(-num,31)){ //xi no se tiene que pasar de esos rangos
                    cout<<"Resultado invalido"<<endl;
                    return 0;
                }
                else{
                    cout<<"Resultado: ";
                    return xi; //regresa el valor invertido
                }
            }
            else{//si el valor de x es menor a 0...en caso de ser número negativo
                cout<<"Valor negativo: "<<x<<endl;
                //int s=xs.at(0);//Guarda el signo "-"
                //int xs.at(0);//Guardar el primer número (absoluto) en una variable
                string xs_reversed(xs.rbegin(), xs.rend()); // se invierte el string 
                string xsnew = xs_reversed; // se crea una nueva variable con el string invertido 
                stringstream geek(xsnew); //Se convierte de string a int
                int xi = 0;
                geek >> xi;
                if(xi>=(pow(num,31)-1) || xi<=pow(-num,31)){ //xi no se tiene que pasar de esos rangos
                    cout<<"Resultado invalido"<<endl;
                    return 0;
                }
                else{
                    cout<<"Resultado: ";
                    return -xi; //se regresa el valor en negativo
                }
            }
        }
    }
};