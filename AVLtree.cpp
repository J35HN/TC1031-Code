/*
Actividad 3.3 - Árbol AVL (originalmente Árbol Desplegado: Implementando un Splay Tree).
- Implementar un Árbol AVL en C++. 
Autor:
- Jeshua Nava Avila | A01639282
Fecha de creación y última modificación:
- 20/10/2021
- XX/10/2021 
*/

// Librerías
#include <iostream>
#include <queue>

using namespace std;

template <class T> class Node{
    public:
        T data;
        int key;
        Node<T>* left;
        Node<T>* right;

        // Constructor.
        Node(T n_data, int n_key = 0, Node<T>* n_left = NULL, Node<T>* n_right = NULL){
            data = n_data;
            key = n_key;
            left = n_left;
            right = n_right;
        }
};

template <class T> class TreeAVL{
    public:
        Node<T>* root;
        // Constructor y destructor.
        TreeAVL(){root = NULL;}
        ~TreeAVL(){}

        void insert(Node<T>* current, Node<T>* insert);
        void insert(T data, int key);

        // Métodos de impresión.
        void pre_order(Node<T>* current);
        void pre_order();
        void in_order(Node<T>* current);
        void in_order();
        void post_order(Node<T>* current);
        void post_order();
        void levelByLevel();

        int heightNode(Node<T>* current); // Encontrar la altura de un nodo.


};

/** Imprime al árbol de manera Preorder.
 * Complejidad Computacional: O(n).
 */
template<class T>
void TreeAVL<T>::pre_order(Node<T>* current){
    cout << current -> key << " ";
    if(current -> left != NULL){
        pre_order(current -> left);
    }
    if(current -> right != NULL){
        pre_order(current -> right);
    }
}

// Iniciador del pre_order. Complejidad: O(1).
template<class T>
void TreeAVL<T>::pre_order(){
    pre_order(root);
}

/** Imprime al árbol de manera Inorder.
 * Complejidad Computacional: O(n).
 */
template<class T>
void TreeAVL<T>::in_order(Node<T>* current){
    if(current -> left != NULL){
        in_order(current -> left);
    }
    cout << current -> key << " ";
    if(current -> right != NULL){
        in_order(current -> right);
    }
}

// Iniciador del in_order. Complejidad: O(1).
template<class T>
void TreeAVL<T>::in_order(){
    in_order(root);
}

/** Imprime al árbol de manera Postorder.
 * Complejidad Computacional: O(n).
 */
template<class T>
void TreeAVL<T>::post_order(Node<T>* current){
    if(current -> left != NULL){
        post_order(current -> left);
    }
    if(current -> right != NULL){
        post_order(current -> right);
    }
    cout << current -> key << " ";
}

// Iniciador del post_order. Complejidad: O(1).
template<class T>
void TreeAVL<T>::post_order(){
    post_order(root);
}

/** Imprime el árbol de manera Level by level o Lever Order Traversal.
 * Complejidad Computacional: O(n).
 */
template<class T>
void TreeAVL<T>::levelByLevel(){
    Node<T>* temp;
    queue<Node<T>*> Q;
    Q.push(root);
    while(Q.size() > 0){
        temp = Q.front();
        cout << temp -> key << " ";
        Q.pop();
        if(temp -> left != NULL){
            Q.push(temp -> left);
        }
        if(temp -> right != NULL){
            Q.push(temp -> right);
        }
    }
}

/** Regresa la altura de un nodo.
 * Complejidad Computacional: O(n).
 * Aunque sea recursivo, un subárbol siempre tendrá n elementos.
 * @return Entero que indica la altura del nodo.
 */
template<class T>
int TreeAVL<T>::heightNode(Node<T>* currentNode){
    int height = 0;
    height = max(heightNode(currentNode -> left), heightNode(currentNode -> right));
    return 1 + height;
}

/**
 * 
 */
template<class T>
void TreeAVL<T>::insert(Node<T>* currentNode, Node<T>* insertNode){
    Node<T> * nextNode = currentNode -> left;
    bool toLeft = true;
    if(insertNode -> key > currentNode -> key){
        nextNode = currentNode -> right;
        toLeft = false;
    }
    if(nextNode != NULL){
        insert(nextNode, insertNode);
    } else if (toLeft == true){
        currentNode -> left = insertNode;
    } else {
        currentNode -> right = insertNode;
    }
}

/**
 * 
 */
template<class T>
void TreeAVL<T>::insert(T data, int key){
    Node<T> *InsertNode = new Node<T>(data, key);
    if(root == NULL){
        root = InsertNode;
    } else {
        insert(root, InsertNode);
    }
}

int main(){
    TreeAVL<int> h;
    h.insert(1, 100);
    h.insert(2, 50);
    h.insert(3, 150);
    h.insert(4, 25);
    h.insert(4, 125);
    h.pre_order();
    cout << endl;
    h.in_order();
    cout << endl;
    h.post_order();
    cout << endl;
    h.levelByLevel();
    cout << endl;
    return 0;
}