#include <iostream>
using namespace std;

int fibonacci(int x){
    if (x <= 1){
        return 1;
    } else {
        return fibonacci(x - 1) + fibonacci(x - 2);
    }
}

int factorial(int x){
    if (x == 0){
        return 1;
    } else {
        return factorial(x-1) * x;
    }
}

int main(){
    cout << "Fibonacci of 5: " << fibonacci(5) << "\n";
    cout << "Factorial of 5: " << factorial(5);

    return 0;
}