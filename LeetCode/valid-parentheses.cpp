#include <string>
#include <iostream>

template <class T> class Node {
    private:
        T data; //Information of this node
        Node* next; //Reference to next node in list
    
    public:
        //Constructor
        Node(T new_data, Node *next_node){
            this->data = new_data;
            this->next = next_node;
        }

        //Default constructor
        Node(T new_data){
            this->data = new_data;
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

        void set_next(Node *next_node){
            this->next = next_node;
        }

        Node* get_next(){
            return this->next;
        }
};

template <class T> class CustomStack{
    private:
        Node<T> *head;

    public:
        CustomStack(){
            this->head = NULL;
        }

        ~CustomStack(){}

        //Method to add a new node to the stack
        void push(T data){
            Node<T> *node = new Node<T>(data); //Create the new node
            node->set_next(this->head); //This new node, reference to the "old head"
            this->head = node; //Update the head to new node created
        }

        //Mehod to get the data of head and delete the actual head
        T pop(){
            if(this->head){
                T data; //Create a "T" varaible because we dont know what kind of data we going to work
                Node<T> *node = this->head; //We create a node with the actual head
                data = node->get_data(); //Get the data of the actual head (or node)
                this->head = this->head->get_next(); //Update the head with the reference of the "old head"
                delete node; 
                return data;
            }

            return -1;
        }

        //Method to know if stack is empty
        bool isEmpty(){
            if(!this->head){
                return true;
            }else{
                return false;
            }
        }
};

class Solution {
    public:
        bool isValid(std::string s) {
            CustomStack<char> stack; //Declarate a stack structure

            for(int i=0; i < s.length(); i++){
                //Keep the actual character of the string in a char variable
                char actual_bracket = s[i]; 

                //Check if the actual character is a left bracket
                if(actual_bracket == '(' 
                || actual_bracket == '[' 
                || actual_bracket == '{'){
                    stack.push(actual_bracket); //Push in the stack
                }

                //Check if the actual character is a right bracket
                if(actual_bracket == ')' || actual_bracket == ']' || actual_bracket == '}'){
                    char last_bracket = stack.pop(); //Get the last bracket saved in the stack

                    //Verify that the "last_barcket" and "actual_brack" are the complement of the other
                    if(!(((last_bracket=='(') && (actual_bracket==')'))
                    || ((last_bracket=='[') && (actual_bracket==']'))
                    || ((last_bracket=='{') && (actual_bracket=='}')))){
                        return false; //That means, The string has an error
                    }
                }
            }

            //If stack is empty means that all is ok, but if not, means that the string has an error
            return stack.isEmpty();
        }
};

int main(){
    std::string chain;
    std::cin>>chain;

    Solution solution;

    bool ans = solution.isValid(chain);
    std::cout << ans << std::endl;
}