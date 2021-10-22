#include <iostream>

using namespace std;

template <class T> class Node {
    public:
        T data; // The object information
        int key; // key of the value
        int height;
        Node<T>* left; // Pointer to the left node element
        Node<T>* right; // Pointer to the right node element
        
        Node(T new_data, int key, Node<T>* left, Node<T>* right){
            this->data = new_data;
            this->key = key;
            this->left = left;
            this->right = right;
            this->height = 1;
        }

        Node(){
            this->key = key;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }

        Node(T new_data, int key){
            this->data = new_data;
            this->key = key;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }
        
};
template <class T>
int getHeight(Node<T>* N){
    if(N){
        return N->height;
    }
    else{
        return 0;
    }
}

int max(int data1, int data2){
    if(data1 > data2){
        return data1;
    }
    else{
        return data2;
    }
}



template <class T> class AVL{
    public:
        Node<T> *root;
        
        AVL(){
            this->root = NULL;
        }

        ~AVL(){

        }
        // Función que despliega el arbol en forma ascendente con complejidad O(log(n))
        void print(Node<T>* current_node){
            if(current_node) {
                print(current_node->left);
                cout << current_node->key << " ";
                print(current_node->right);
            }

            if(this->root == current_node){
                cout << endl;
            }
        }
        // Función que realiza la right rotation Complejidad O(log(n))
        Node<T> *rightRotate(Node<T> *node){
            Node<T> *lnode = node->left;
            Node<T> *lrnode = lnode->right;
        
            lnode->right = node;
            node->left = lrnode;
            if(node == this->root){
                this->root = lnode;
            }

            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            lnode->height = max(getHeight(lnode->left), getHeight(lnode->right)) + 1;
        

            return lnode;
        }
        // Función que realiza la left rotation O(log(n))
        Node<T> *leftRotate(Node<T> *node){

            Node<T> *rnode = node->right;
            Node<T> *rlnode = rnode->left;
        

            rnode->left = node;
            node->right = rlnode;
            if(node == this->root){
                this->root = rnode;
            }
        

            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            rnode->height = max(getHeight(rnode->left), getHeight(rnode->right)) + 1;
        

            return rnode;
        }
        //Función para insertar un nuevo dato en el arbol con complejidad O(log(n))
        Node<T>* insert(Node<T> *node, int key, T data){
            // inserción tipica de un BST
            if (root == NULL){
                Node<T>* temp = new Node<T>;
                temp->key = key;
                temp->data = data;
                this->root = temp;
                return(temp);
            }
            if (node == NULL){
                Node<T>* temp = new Node<T>;
                temp->key = key;
                temp->data = data;
                return(temp);
            }
            if (key < node->key){
                node->left = insert(node->left, key, data);
            }
            else if (key > node->key){
                node->right = insert(node->right, key, data);
            }
            else{ // Niega la inserción si la llave es repetida
                return node;
            }
        
            // Cambiar la altura de los nodos anteriores
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
            // verificar balance despues de la inserción
            int balance = getBal(node);
        
            // Casos de desbalance:
        
            // LL rotartion
            if (balance > 1 && key < node->left->key){
                return rightRotate(node);
            }
        
            // RR rotation
            if ((balance < -1) && (key > node->right->key)){
                return leftRotate(node);
            }

            // LR rotation
            if ((balance > 1) && (key > node->left->key)){

                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // RL rotation
            if (balance < -1 && key < node->right->key)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        
            // Regresa el apuntador normal si este no requiere de balanceo
            return node;
        }

        // Función auxiliar para insertar con parametros distintos a los originales
        void insert(T data, int key){
            insert(this->root, key, data);
        }


        // Función para obtener el balance de un nodo dado que recurre a O(log(n))
        int getBal(Node<T> *node){

            if (node == NULL)
                return 0;
            return getHeight(node->left) - getHeight(node->right);
        }
        // Función para obtener el tamaño del árbol mediante recursividad O(log(n))
        int size(Node<T> *node){
            if (node == NULL){
                return 0;
            }else{
                return 1 + size(node->left) + size(node->right);
            }
        }

        //Función auxiliar para obtener el tamaño del árbol sin parámetros O(log(n))
        int size(){
            return this->size(this->root);
        }

        //Función auxiliar para conocer si una llave es existente dentro del arbol O(log(n))
        bool find(int key, Node<T> *node){
            if(node != NULL){
                if(node->key==key){
                    return 1;
                }else{
                    return find(key, node->left) || find(key, node->right);
                }
            }
            else{
                return 0;
            }
        }


        //Función para eliminar elementos del arreglo bastante similar a la inserción Complejidad O(log(n))
        Node<T>* del(Node<T>* node, int key){
     
            if (node == NULL)
                return node;
        
            if ( key < node->key ){
                node->left = del(node->left, key);
            }else if( key > node->key ){
                node->right = del(node->right, key);
            }else{

                if( (node->left == NULL) || (node->right == NULL) ){
                    Node<T>* temp = new Node<T>;
                    if(node->left){
                        temp = node->left;
                    }else{
                        temp = node->right;
                    }
        
                    if (temp == NULL){
                        temp = node;
                        node = NULL;
                    }
                    else{
                        *node = *temp;
                    }

                    free(temp);
                }
                else{
                    Node<T>* temp = node->right;
                    while(temp->left){
                        temp = temp->left;
                    }

                    node->key = temp->key;
        
                    node->right = del(node->right, temp->key);
                }
            }
        
            if (node == NULL){
                return node;
            }
        

            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
            int bal = this->getBal(node);
        
        
            // LL
            if (bal > 1 && getBal(node->left) >= 0){
                return rightRotate(node);
            }
        
            // LR
            if (bal > 1 && getBal(node->left) < 0){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        
            // RR
            if (bal < -1 && getBal(node->right) <= 0){
                return leftRotate(node);
            }
        
            // RL
            if (bal < -1 && getBal(node->right) > 0){
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        
            return node;
        }

};


int main(){
    AVL<char> myAvl;
    myAvl.insert('h', 10);
    myAvl.insert('g', 40);
    myAvl.insert('d', 50);
    myAvl.insert('t', 70);
    myAvl.insert('a', 60);
    myAvl.insert('b', 20);
    cout << "Contenido del arbol" << endl;
    myAvl.print(myAvl.root);
    cout << "Tamano del arbol: " << endl;
    cout << myAvl.size() << endl;
    cout << "Booleano de existencia de 50 en el arbol: " << myAvl.find(50, myAvl.root) << endl;
    myAvl.del(myAvl.root, 40);
    cout << "Eliminacion del dato 40 en el arbol" << endl;
    myAvl.print(myAvl.root);
    myAvl.del(myAvl.root, 50);
    cout << "Eliminacion del dato 50 en el arbol" << endl;
    myAvl.del(myAvl.root, 60);
    cout << "Eliminacion del dato 60 en el arbol" << endl;
    myAvl.print(myAvl.root);
    cout << "Booleano de existencia de 60 en el arbol: " << myAvl.find(60, myAvl.root) << endl;
    cout << "Booleano de existencia de 70 en el arbol: " << myAvl.find(70, myAvl.root) << endl;
    cout << "Insercion de 30 en el arbol" << endl;
    myAvl.insert('d', 30);
    cout << "Booleano de existencia de 30 en el arbol: " << myAvl.find(30, myAvl.root) << endl;
    cout << "Tamano del arbol: " << endl;
    cout << myAvl.size() << endl;
    myAvl.print(myAvl.root);


    return 0;
}