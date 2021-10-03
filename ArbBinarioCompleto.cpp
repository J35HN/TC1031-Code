#include <iostream>
#include <queue>

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
    int heightTree; // Height of the tree.

    public:
        BinaryTree(){
            current = NULL;
            root = NULL;
            heightTree = 0;
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
            int exit = 0, step = 0;
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
                        step++;
                    } else {
                        current = current -> right;
                        step++;
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
                        step++;
                    } else {
                        current = current -> left;
                        step++;
                    }
                }
            }
            current = root; // Current ends back at root.
            // Update height of tree.
            if(step > heightTree){
                heightTree = step;
            }
        }
    }

    // Visit
    void visit(int opc){
        current = root;
        if(opc == 1){
            this -> pre_order();
            cout << endl;
        } else if(opc == 2){
            this -> in_order();
            cout << endl;
        } else if(opc == 3){
            this -> post_order();
            cout << endl;
        } else if(opc == 4){
            this -> levelBLevel();
            cout << endl;
        }
        cout << endl;
    }

    void pre_order(){
        cout << current -> data << " ";
        if(current -> left != NULL){
            current = current -> left;
            this -> pre_order();
            current = current -> father;
        }
        if(current -> right != NULL){
            current = current -> right;
            this -> pre_order();
            current = current -> father;
        }
    }

    void in_order(){
        if(current -> left != NULL){
            current = current -> left;
            this -> in_order();
            current = current -> father;
        }
        cout << current -> data << " ";
        if(current -> right != NULL){
            current = current -> right;
            this -> in_order();
            current = current -> father;
        }
    }

    void post_order(){
        if(current -> left != NULL){
            current = current -> left;
            this -> post_order();
            current = current -> father;
        }
        if(current -> right != NULL){
            current = current -> right();
            this -> post_order();
            current = current -> father();
        }
        cout << current -> data << " ";
    }

    void levelBLevel(){
        Node<T>* temp = new Node<T>;
        queue<Node> q;
        q.push(current);
        while(!q.empty()){
            temp = q.front();
            q.pop();
            cout << temp -> data << " ";
            if(temp -> left != NULL){
                q.push(temp->left);
            }
            if(temp -> right != NULL){
                q.push(temp -> right);
            }
        }
    }

    // Height
    int height(){
        return heightTree;
    }

    // Ancestors
    void ancestors(int dat){
        this -> search_node(dat);
        while(current -> father != NULL){
            cout << current -> data << " -> ";
            current = current -> father;
            if(current -> father == NULL){
                cout << current -> data << endl;
            }
        }
    }

    // WhatlevelamI
    int whatlevelamI(int dato){
        int level = -1;
        this -> search_node(dato); // Set current to node that has dat.
        while(current -> father != NULL){
            level += 1;
            current = current -> father;
        }
        if(level == -1){
            return level;
        } else {
            return level+1;
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

    void search_node(T info){
        current = root; // Current start at root.
        while(current -> data != info){
            // In case there is no node.
            if(current -> left == NULL && current -> right == NULL){
                current = root; // Reset to root.
                break;
            }
            if(info < current -> data){
                current = current -> left;
            } else {
                current = current -> right;
            }
        }
        // Current will be set at the searched node.
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
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        cout << "1. Agregar un valor.\n2. Go father.\n3. Go left.\n4. Go right.\n5. Ancestor.\n6. What Level.\n7. Height.\n8. Visit.\n0. Salir.\nOpcion: ";
        cin >> menu;
        cout << endl;
        switch (menu){
            case 0:
                break;
            case 1:
                cout << "Ingrese un valor: ";
                cin >> temp;
                cout << endl;
                Arbol.add_node(temp);
                break;
            case 2:
                Arbol.go_father();
                break;
            case 3:
                Arbol.go_left();
                break;
            case 4:
                Arbol.go_right();
                break;
            case 5:
                cout << "Ingrese el valor de un nodo para imprimir sus ancestros: ";
                cin >> temp;
                cout << endl;
                Arbol.ancestors(temp);
                break;
            case 6:
                cout << "Ingrese el valor de un nodo para imprimir su nivel en el arbol: ";
                cin >> temp;
                temp = Arbol.whatlevelamI(temp);
                cout << "Estoy en el nivel: " << temp << endl << endl;
                break;
            case 7:
                temp = Arbol.height();
                cout << "La altura del arbol es: " << temp << "." << endl << endl;
                break;
            case 8:
                cout << "[1] -> Pre-order. [2] -> In-order. [3] -> Postorder. [4] -> level by level." << endl;
                cin >> temp;
                Arbol.visit(temp);
                break;
            default:
                cout << "Ingrese un numero valido" << endl << endl;
                break;
        }
    }
    return 0;
}