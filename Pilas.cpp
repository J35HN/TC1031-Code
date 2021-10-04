#include <iostream>

using namespace std;

template <class T> class Stack {
    private:
        T data; // The object information
        Stack* next; // Pointer to the next node element

    public:
        Stack(T new_data, Stack* next_node){
            this->data = new_data;
            this->next = next_node;
        }

        Stack(T new_data){
            this->data = new_data;
            this->next = NULL;
        }

        void set_data(T new_data){
            this->data = new_data;
        }

        T get_data(){
            return this->data;
        }

        void set_next(Stack *next_node){
            this->next = next_node;
        }

        Stack* get_next(){
            return this->next;
        }
};


template <class T> class CustomStack{
    Stack<T> *top;

    public:
        CustomStack(){
            top = NULL;
        }

        ~CustomStack(){

        }

        void push(T data){
            if(top == NULL){
                top = new Stack<T>(data);
            }
            else{
                Stack<T>* temp = new Stack<T> (data);
                temp -> set_prev(top); 
                this -> top = temp;
            }
        }
        void pop(){
            if(top == NULL){
                return;
            }else{
                Stack<T>* temp = top -> get_prev();
                top = temp;
            }
        }
};



int main(){
    CustomStack<int> firstList;
}