#include <iostream>

using namespace std;

template <class T> class Node {
    public:
        T data; // The object information
        Node* next; // Pointer to the next node element
        Node* Front; // Pointer to the front of queue
        Node* Rear; // Pointer to the end of queue

        void set_data(T new_data){
            this->data = new_data;
        }

        void set_next(Node *next_node){
            this->next = next_node;
        }

        void set_Front(Node *front_node){
            this -> Front = front_node;
        }

        void set_Rear(Node *rear_node){
            this -> Rear = rear_node;
        }
};


template <class T> class Queue{
    Node<T> *Front;
    Node<T> *Rear;
    int Size;

    public:
        Queue(){
            Front = NULL;
            Rear = NULL;
            Size = 0;
        }

        ~Queue(){
        }

        // Method adds info to the end of the list
        void push(T info){
            if(Rear == NULL){ //if our queue is currently empty
                Front = new Node<T>;
                Front -> set_data(info);
                Rear = Front;
                Rear -> set_next(NULL);
                Front -> set_next(NULL);
                Size = 1;
            }
            else{ //if not empty add to the end and move the 
                Node<T>* temp = new Node<T>;
                temp->set_data(info);
                temp->set_next(NULL);

                Node<T>* current_node = this -> Front;
                while (current_node->next != NULL){
                    current_node = current_node->next; 
                }
                
                current_node->next = temp; // Rear va ser temp.
                
                Rear = temp; // temp lo establecemos como Rear.
                //Rear -> set_data(temp -> data); // Por si acaso, Rear tenga el valor de temp.
                
                Size++; // Incrementar el valor de size.
            }
        }

        // Sacar o devolver el primer elemento.
        void pop(){
            if(!this->Rear){
                // Empty queue, no values to delete
                return;
            }
            Node<T>* current_node = this->Front;
            current_node = current_node -> next;
            delete Front;
            Front = current_node;
            Front -> set_data(current_node -> data);
            Size--; // Restar Size menos 1.
        }

        // empty
        bool empty(){
            if(Size > 0){
                return false;
            } else {
                return true;
            }
        }

        // size
        int size(){
            return Size;
        }

        int front(){
            return Front -> data;
        }

        int back(){
            return Rear -> data;
        }

        void print_list(){
            cout << "funciona print" << endl;
            Node<T>* current_node = this->Front;
            while (current_node != NULL){
                cout << current_node ->data << " -> ";
                current_node = current_node->next;
            }
            cout << endl;
        }

        
};



int main(){
    Queue<int> rabo;
    int x, y;
    cout << "cac"; 
    rabo.push(1);
    rabo.push(2);
    rabo.push(3);
    cout << "Tamanio de rabo: " << rabo.size() << endl;
    cout << rabo.empty() << endl;
    rabo.print_list();
    rabo.pop();
    rabo.print_list();
    rabo.pop();
    x = rabo.front();
    y = rabo.back();
    cout << x << " " << y << endl;

    
    // firstList.delete_node(34);
    // firstList.print_list();
    return 0;
}