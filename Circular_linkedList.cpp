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
    Node<T> *tail;

    public:
        CustomLinkedList(){
            head = NULL;
            tail = NULL;
        }

        ~CustomLinkedList(){

        }

        // Method adds info to the end of the list
        void add_end(T info){
            if(head == NULL){ //if our list is currently empty
                Node<T>* node = new Node<T>; //Create new node of type T
                node -> set_data(info);
                node -> set_next(node);
                node -> set_previous(node);
                head = node;
                tail = node;
            }
            else{ //if not empty add to the end and move the tail
                Node<T>* temp = new Node<T>;
                temp -> set_data(info);
                temp -> set_next(head);
                temp -> set_previous(tail);
                tail -> set_next(temp);
                tail = temp; 
                head -> set_previous(tail);

                /* Ya no se necesita buscar
                Node<T>* current_node = this->head;
                while (current_node->next != NULL){
                    current_node = current_node->next;
                }
                temp->set_previous(current_node);
                current_node->next = temp;
                */
            }
        }

        // Method adds info to the begining of the list
        void add_begin(T info){
            Node<T>* temp = new Node<T>;
            temp->set_data(info);
            temp->set_next(head);
            temp->set_previous(tail);
            tail -> set_next(temp);
            this->head = temp;
        }

        // Method adds info to the begining of the list
        void add_after_node(T value_insert, T value_after){
            Node<T>* temp = head;
            while (temp->data != value_after){
                temp = temp->next;
            }
            if (!temp) {
                return;
            }
            Node <T>* nodito= new Node<T>;
            nodito -> set_data(value_insert);
            nodito -> set_previous(temp);

            //Buscar que next se debe est.
            if (temp->next != head) {
              nodito -> set_next(temp->next);
              nodito -> next -> set_previous(nodito);
              temp -> set_next(nodito);
            }
            else {
                /*
              nodito -> set_next(head);
              nodito -> set_previous(tail);
              nodito = tail;
              head -> set_next(nodito);*/
             add_end(value_insert);
            }
            
        }


        void delete_node(T value){
            if(!this->head){
                // Empty linked list, no values to delete
                return;
            }

            // Check if the node to delete is the head
            if(this->head->data == value){
                this->head = this->head->next;
                head->set_previous(tail);
                tail -> set_next(head);
                return;
            }

            Node<T>* current_node = this->head;
            // Search for the node to delete
            while ( current_node && current_node->next->data != value){
                current_node = current_node->next;
            }

            // Check if the node to delete is the tail
            if(this->tail->data == value){
                this->tail = this->tail->previous;
                tail -> set_next(head); 
                head -> set_previous(tail);
                return;
            }

            // current node is empty the node wasn't found
            if(!current_node){
                return;
            }

            Node<T>* node_to_delete = current_node->next;

            current_node->next = node_to_delete->next;
            /*
            if (node_to_delete->next != NULL) {
              
            }
            */
           current_node->next->set_previous(current_node);
            delete node_to_delete;
        }

        void print_list(){
            Node<T>* current_node = this->head;
            while (current_node != tail){
                cout << current_node ->data << " -> ";
                current_node = current_node->next;
            }
            cout << current_node ->data << " -> ";
            cout << endl;
        }


};



int main(){
    CustomLinkedList<int> firstList;

    firstList.add_end(33);
    firstList.add_end(34);
    firstList.add_end(35);
    firstList.add_begin(32);
    firstList.add_begin(31);
    firstList.add_end(100);
    firstList.print_list();
    firstList.delete_node(100);
    firstList.print_list();

    // firstList.delete_node(34);
    // firstList.print_list();


    return 0;
}
