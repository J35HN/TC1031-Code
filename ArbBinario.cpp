#include <iostream>

using namespace std;

template <class T> class Node {
    public:
        T data; // Information stored by data.
        Node* left; // Pointer to the left son (node).
        Node* right; // Pointer to the right son (node).
        Node* father; // Pointer to father (node).

        void set_data(T new_data){
            this -> data = new_data;
        }

        void set_left(Node *next_left){
            this -> left = next_left;
        }

        void set_right(Node *next_right){
            this -> right = next_right;
        }

        void set_father(Node *next_father){
            this -> father = next_father;
        }
};

template <class T> class BinaryTree{
    Node<T> *current; // Node so we can traverse the tree.

    public:
        BinaryTree(){
            current = NULL;
        }
        ~BinaryTree(){}
    void add_node(T info){
        if(current == NULL){
            current = new Node<T>;
            current -> set_data(info);
            current -> set_father(NULL);
            current -> set_left(NULL);
            current -> set_right(NULL);
        } else {
            if(current -> left == NULL){ // If our current left son is without info.
                Node<T>* temp = new Node<T>;
                // First create new left node.
                temp -> set_data(info);
                temp -> set_father(current);
                temp -> set_left(NULL);
                temp -> set_right(NULL);
                // Then set left son to current temp.
                current -> set_left(temp);
            } else if(current -> right == NULL){
                Node<T>* temp = new Node<T>;
                // First create new right node.
                temp -> set_data(info);
                temp -> set_father(current);
                temp -> set_left(NULL);
                temp -> set_right(NULL);
                // Then set right son to current temp.
                current -> set_right(temp);
            } else {
                // If right or left are occupied, we don't add node.
                cout << "Not possible to add a son to this node, left or right already have information." << endl;
            }
        }
    }

    void go_left(){
        // Set current to left, unless it's null.
        if(current -> left != NULL){
            current = current -> left;
        }
    }

    void go_right(){
        // Set current to right, unless it's null.
        if(current -> right != NULL){
            current = current -> right;
        }
    }

    void go_father(){
        // Set current to father, unless it's root.
        if(current -> father != NULL){
            current = current -> father;
        }
    }

    void print_node(){
        // Prints current node with its info.
        Node<T>* temp = new Node<T>;
        cout << "Node's info: " << current -> data << endl;
        temp = current -> left;
        if(temp == NULL){
            cout << "Node's left: NULL" << endl;
        } else {
            cout << "Node's left: " << temp -> data << endl;
        }
        temp = current -> right;
        if(temp == NULL){
            cout << "Node's right: NULL" << endl;
        } else {
            cout << "Node's right: " << temp -> data << endl;
        }
        temp = current -> father;
        if(temp == NULL){
            cout << "Node's father: NULL. Because I Am gROOT :)" << endl;
        } else {
            cout << "Node's father: " << temp -> data << endl;
        }
    }

};

int main(){
    BinaryTree<int> Arbol;
    int men = 0;
    // Menu
    
    return 0;
}