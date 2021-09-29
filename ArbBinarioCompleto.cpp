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
    Node<T> *root; // Node that is the root of the tree.

    public:
        BinaryTree(){
            current = NULL;
            root = NULL;
        }
        ~BinaryTree(){}

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
    
    void add_node(T info){
        if(root == NULL){ // If our binary tree is empty.
            root = new Node<T>;
            root -> set_data(info);
            root -> set_father(NULL);
            root -> set_left(NULL);
            root -> set_right(NULL);
            current = root;
        } else {
            int exit = 0;
            current = root; // Start at root
            while(exit == 0){
                if(info > current -> data){ // Traverse right if info is bigger than the current node.
                    if(current -> right == NULL){ // Check in case we need to save info in right.
                        Node<T>* temp = new Node<T>;
                        temp -> set_data(info);
                        temp -> set_left(NULL);
                        temp -> set_right(NULL);
                        temp -> set_father(current);
                        current -> set_right(temp);
                        exit++;
                    } else {
                        current = current -> right;
                    }
                } else { // Traverse left.
                    if(current -> left == NULL){
                        Node<T>* temp = new Node<T>;
                        temp -> set_data(info);
                        temp -> set_left(NULL);
                        temp -> set_right(NULL);
                        temp -> set_father(current);
                        current -> set_left(temp);
                        exit++;
                    } else {
                        current = current -> left;
                    }
                }
                //cout << "Ya no soy null" << endl;
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

};

int main(){
    BinaryTree<int> Arbol;
    int menu = 1, temp = 0;
    cout << "Ingrese un valor para el root del arbol.\nValor: ";
    cin >> temp;
    Arbol.add_node(temp);
    cout << endl;
    // Menu 
    while(menu != 0){
        Arbol.print_node();
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        cout << "1. Agregar un valor.\n0. Salir.\nOpcion: ";
        cin >> menu;
        cout << endl;
        if(menu == 1){
            cout << "Ingrese un valor: ";
            cin >> temp;
            cout << endl;
            Arbol.add_node(temp);
        }
    }
    return 0;
}