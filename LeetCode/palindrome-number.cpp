#include <string>
#include <iostream>

//Class to create a node with refernce to next node and previous node
template <class T> class Node{
private:
    T data;     //Information of this node
    Node *previous; //Reference to previus node in list
    Node *next; //Reference to next node in list

public:
    //Constructor
    Node(T new_data, Node *previous_node, Node *next_node){
        this->data = new_data;
        this->previous = previous_node;
        this->next = next_node;
    }

    //Default constructor
    Node(T new_data){
        this->data = new_data;
        this->previous = NULL;
        this->next = NULL;
    }

    void set_data(T new_data){
        this->data = new_data;
    }

    T get_data(){
        return this->data;
    }

    T get_afterNode_data(){
        return this->next->get_data();
    }

    void set_previous(Node *previous_node){
        this->previous = previous_node;
    }

    Node *get_previous(){
        return this->previous;
    }

    void set_next(Node *next_node){
        this->next = next_node;
    }

    Node *get_next(){
        return this->next;
    }
};

//Double linked list
template <class T> class CustomDoubleLinkedList{
    Node<T> *head, *tail;

public:
    CustomDoubleLinkedList(){
        head = NULL;
        tail = NULL;
    }

    //Method adds data to the end of the list
    void add_end(T data){
        if (this->head == NULL){ //If our list is currently empty, simply add the node
            this->head = new Node<T>(data);
            this->tail = this->head;
        }else{ //If not empty add to end and move the tail
            Node<T> *temp = new Node<T>(data);

            //Remember tail is the reference to the last node
            this->tail->set_next(temp);
            temp->set_previous(this->tail);

            this->tail = temp;
        }
    }

    //Method to know if is palindrome number
    bool verifyPalindrome(){
        //Declarate two variables, one begin in the head and the other in the tail
        Node<T> *asc_node = this->head; 
        Node<T> *desc_node = this->tail;

        /*
        Basically the "asc_node" scrolls through the list in ascending order 
        and "desc_node" do the same but in descendent order 
        */
        while (asc_node != NULL){
            //If we find a number that not is the same , then, the number is not palindrome
            if(asc_node->get_data() != desc_node->get_data())
                return false;

            //We go through list (in ascedent and descendent form)
            asc_node = asc_node->get_next();
            desc_node = desc_node->get_previous();
        }

        return true; //That means that the number is palindrome number
    }
};

class Solution {
public:
    bool isPalindrome(int x) {
        std::string chain = std::to_string(x);
        char verifyNegative = chain[0];

        //If the first character is "-" (it's a negative number), not is palindrome  
        if(verifyNegative=='-')
            return false;
        
        CustomDoubleLinkedList<char> doubleLinkedList;
        
        //Save each character of the number in the double linked list
        for (int i = 0; i < chain.length(); i++){
            doubleLinkedList.add_end(chain[i]);
        }

        //Make a proof if is palindrome number (more details inside of the function) 
        return doubleLinkedList.verifyPalindrome();
    }
};

int main(){
    int number;
    std::cin >> number;

    
    Solution solution;

    bool ans = solution.isPalindrome(number);
    std::cout << ans << std::endl;
}