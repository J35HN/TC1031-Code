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

        // Métodos de inserción. [TERMINAR INSERCIÓN COMPLETA]
        void insert(Node<T>* currentNode, Node<T>* insertNode);
        void insert(T data, int key);
        void balanceTree(Node<T>* currentNode);
        int heightNode(Node<T>* currentNode); // Encontrar la altura de un nodo.
        int balanceFact(Node<T>* currentNode); // Obtener el balance factor de un nodo.
        // Métodos de rotación.
        void rotaRR(Node<T>* currentNode);
        void rotaLL(Node<T>* currentNode);
        void rotaRL(Node<T>* currentNode);
        void rotaLR(Node<T>* currentNode);

        // Deletion

    // Métodos de impresión.
        void pre_order(Node<T>* currentNode);
        void pre_order();
        void in_order(Node<T>* currentNode);
        void in_order();
        void post_order(Node<T>* currentNode);
        void post_order();
        void levelByLevel();
};

/**
 * 
 */
template<class T>
void TreeAVL<T>::insert(Node<T>* currentNode, Node<T>* insertNode){
    Node<T> *nextNode = currentNode -> left;
    Node<T> *temp;
    bool toLeft = true;
    if(insertNode -> key > currentNode -> key){
        nextNode = currentNode -> right;
        toLeft = false;
    }
    cout << "Current key:: " << currentNode -> key << endl;
    if(nextNode){
        insert(nextNode, insertNode);
        cout << "A balancear. Mi ultimo key: " << insertNode -> key << " Ultimo current: " << currentNode -> key << endl;
        balanceTree(currentNode);
    } else if (toLeft == true){
        cout << "Inserte LEFT: " << insertNode -> key << endl;
        currentNode -> left = insertNode;
    } else {
        cout << "Inserte RIGTH: " << insertNode -> key << endl;
        currentNode -> right = insertNode;
    }
}

/**
 * 
 */
template<class T>
void TreeAVL<T>::insert(T data, int key){
    Node<T> *InsertNode = new Node<T>(data, key);
    if(root){
        insert(root, InsertNode);
    } else {
        root = InsertNode;
    }
}

/**
 * 
 */
template<class T>
void TreeAVL<T>::balanceTree(Node<T>* currentNode){
    int bFactor = 0;
    bFactor = balanceFact(currentNode);
    if(bFactor > 1){
        if (balanceFact(currentNode -> left) > 0){
            rotaLL(currentNode);
        } else {
            rotaLR(currentNode);
        }
    } else if (bFactor < -1){
        if (balanceFact(currentNode -> right) > 0){
            rotaRL(currentNode);
        } else {
            rotaRR(currentNode);
        }
    }
}

/** Regresa la altura de un nodo.
 * Complejidad Computacional: O(n).
 * Aunque sea recursivo, un subárbol siempre tendrá n elementos.
 * @param currentNode Nodo al cual se le va obtener su altura dentro del árbol.
 * @return Entero que indica la altura del nodo.
 */
template<class T>
int TreeAVL<T>::heightNode(Node<T>* currentNode){
    int height = 0;
    if(currentNode != NULL){
        height = max(heightNode(currentNode -> left), heightNode(currentNode -> right));
    }
    return 1 + height;
}

/** Regresa el balance factor de un nodo dado.
 * Complejidad Computacional: O(1).
 * @param currentNode Nodo al cual se le quiere conocer su balance factor.
 * @return Entero que indica su balance factor.
 */
template<class T>
int TreeAVL<T>::balanceFact(Node<T>* currentNode){
    int HL = heightNode(currentNode -> left);
    int HR = heightNode(currentNode -> right);
    return HL - HR;
}

/** Función para realizar la rotación RR.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el RR.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
void TreeAVL<T>::rotaRR(Node<T>* currentNode){
    Node<T> *temp;
    temp = currentNode -> right;
    currentNode -> right = temp -> left;
    temp -> left = currentNode;
    cout << "RR al key: " << currentNode -> key << endl;
    /*
    if(currentNode == root){
        root = temp;
    }*/
}

/** Función para realizar la rotación LL.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el LL.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
void TreeAVL<T>::rotaLL(Node<T>* currentNode){
    Node<T> *x = currentNode -> left;
    Node<T> *rightX = x -> right;
    x -> right = currentNode;
    currentNode -> left = rightX;    
    cout << "LL al key: " << currentNode -> key << endl;
    /*
    if(currentNode == root){
        root = temp;
    }*/
}

/** Función para realizar la rotación RL.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el RL.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
void TreeAVL<T>::rotaRL(Node<T>* currentNode){
    currentNode -> right = currentNode -> right -> left -> left;
    currentNode -> right -> left -> left = currentNode;
    currentNode -> right -> left = currentNode -> right -> left -> right;
}

/** Función para realizar la rotación LR.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el LR.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
void TreeAVL<T>::rotaLR(Node<T>* currentNode){
    currentNode -> left = currentNode -> left -> right -> right;
    currentNode -> left -> right -> right = currentNode;
    currentNode -> left -> right = currentNode -> left -> right -> left;
}

/** Imprime al árbol de manera Preorder.
 * Complejidad Computacional: O(n).
 * @param currentNode Nodo en el que se encuentra travesando por el momento, y al cual se 
 * va imprimir su valor.
 */
template<class T>
void TreeAVL<T>::pre_order(Node<T>* currentNode){
    cout << currentNode -> key << " ";
    if(currentNode -> left != NULL){
        pre_order(currentNode -> left);
    }
    if(currentNode -> right != NULL){
        pre_order(currentNode -> right);
    }
}

// Iniciador del pre_order. Complejidad: O(1).
template<class T>
void TreeAVL<T>::pre_order(){
    pre_order(root);
}

/** Imprime al árbol de manera Inorder.
 * Complejidad Computacional: O(n).
 * @param currentNode Nodo en el que se encuentra travesando por el momento, y al cual se 
 * va imprimir su valor.
 */
template<class T>
void TreeAVL<T>::in_order(Node<T>* currentNode){
    if(currentNode -> left != NULL){
        in_order(currentNode -> left);
    }
    cout << currentNode -> key << " ";
    if(currentNode -> right != NULL){
        in_order(currentNode -> right);
    }
}

// Iniciador del in_order. Complejidad: O(1).
template<class T>
void TreeAVL<T>::in_order(){
    in_order(root);
}

/** Imprime al árbol de manera Postorder.
 * Complejidad Computacional: O(n).
 * @param currentNode Nodo en el que se encuentra travesando por el momento, y al cual se 
 * va imprimir su valor.
 */
template<class T>
void TreeAVL<T>::post_order(Node<T>* currentNode){
    if(currentNode -> left != NULL){
        post_order(currentNode -> left);
    }
    if(currentNode -> right != NULL){
        post_order(currentNode -> right);
    }
    cout << currentNode -> key << " ";
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


int main(){
    TreeAVL<int> h;
    h.insert(1, 100);
    h.insert(1, 200);
    h.insert(1, 50);
    h.insert(1, 25);
    cout << "---INSERTANDO 12---" << endl;
    h.insert(1, 12);
    h.levelByLevel();
    cout << endl;
    return 0;
}