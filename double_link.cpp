#include <iostream>

using namespace std;

template <class T> class Node {
    public:
        T data; // The object information
        Node* next; // Pointer to the next node element
        Node* previous;

        void set_data(T new_data){
            this->data = new_data;
        }

        void set_next(Node *next_node){
            this->next = next_node;
        }

        void set_previous(Node *previous_node){
            this->previous = previous_node;
        }
};


template <class T> class CustomLinkedList{
    Node<T> *head;

    public:
        CustomLinkedList(){
            head = NULL;
        }

        ~CustomLinkedList(){

        }

        // Method adds info to the end of the list
        void add_end(T info){
            if(head == NULL){ //if our list is currently empty
                head = new Node<T>; //Create new node of type T
                head->set_data(info);
            }
            else{ //if not empty add to the end and move the tail
                Node<T>* temp = new Node<T>;
                temp->set_data(info);
                temp->set_next(NULL);

                Node<T>* current_node = this->head;
                while (current_node->next != NULL){
                    current_node = current_node->next;
                }
                temp->set_previous(current_node);
                current_node->next = temp;
            }
        }

        // Method adds info to the begining of the list
        void add_begin(T info){
            Node<T>* temp = new Node<T>;
            temp->set_data(info);
            temp->set_next(head);
            temp->set_previous(NULL);
            this->head = temp;
        }

        // Method adds info to the begining of the list
        void add_after_node(T value_insert, T value_after){
            Node<T>* temp = head;
            while (temp != NULL && temp->data != value_after){
                temp = temp->next;
            }
            if (!temp) {
                return;
            }
            Node <T>* nodito= new Node<T>;
            nodito -> set_data(value_insert);
            nodito -> set_previous(temp);

            if (temp->next != NULL) {
              nodito -> set_next(temp->next);
              nodito -> next -> set_previous(nodito);
            }
            else {
              nodito -> set_next(NULL);
            }
            temp -> set_next(nodito);
        }


        void delete_node(T value){
            if(!this->head){
                // Empty linked list, no values to delete
                return;
            }

            // Check if the node to delete is the head
            if(this->head->data == value){
                this->head = this->head->next;
                head->set_previous(NULL);
                return;
            }

            Node<T>* current_node = this->head;
            // Search for the node to delete
            while ( current_node && current_node->next->data != value){
                current_node = current_node->next;
            }

            // current node is empty the node wasn't found
            if(!current_node){
                return;
            }

            Node<T>* node_to_delete = current_node->next;

            current_node->next = node_to_delete->next;

            if (node_to_delete->next != NULL) {
              current_node->next->set_previous(current_node);
            }
            delete node_to_delete;
        }

        void print_list(){
            Node<T>* current_node = this->head;
            while (current_node != NULL){
                cout << current_node ->data << " -> ";

                current_node = current_node->next;
            }
            cout << endl;
        }


};



int main(){
    CustomLinkedList<int> firstList;

    firstList.add_begin(32);
    firstList.print_list();
    //Pause the program until input is received

    firstList.add_end(33);
    firstList.print_list();
    firstList.add_end(34);
    firstList.print_list();
    firstList.add_end(35);
    firstList.print_list();
    firstList.add_after_node(1, 35);
    firstList.print_list();
    firstList.delete_node(1);
    firstList.print_list();

    // firstList.delete_node(34);
    // firstList.print_list();


    return 0;
}
