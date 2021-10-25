/*
Actividad 3.3 - Árbol AVL (originalmente Árbol Desplegado: Implementando un Splay Tree).
- Implementar un Árbol AVL en C++. 
Autor:
- Jeshua Nava Avila | A01639282
Fecha de creación y última modificación:
- 20/10/2021
- 25/10/2021 
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
        int sizeTree;
        // Constructor y destructor.
        TreeAVL(){
            root = NULL;
            sizeTree = 0;
        }
        ~TreeAVL(){}

        // Métodos de inserción.
        Node<T>* insert(Node<T>* currentNode, Node<T>* insertNode);
        void insert(T data, int key); // Ocupa dos entradas, uno para el data y el otro para el key.
        // Deletion
        Node<T>* del(int key, Node<T>* currentNode);
        void del(int key);
        // Métodos de rotación.
        Node<T>* rotaR(Node<T>* currentNode);
        Node<T>* rotaL(Node<T>* currentNode);
        // Métodos de impresión.
        void pre_order(Node<T>* currentNode);
        void pre_order();
        void in_order(Node<T>* currentNode);
        void print();
        void post_order(Node<T>* currentNode);
        void post_order();
        void levelByLevel();
        // Otros métodos
        int size(){return sizeTree;} // Retorna la cantidad de elementos en el árbol.
        bool find(Node<T>* currentNode, int searchkey); // Buscar un elemento dentro del árbol.
        bool find(int searchKey);
        int heightNode(Node<T>* currentNode); // Encontrar la altura de un nodo.
        int balanceFact(Node<T>* currentNode); // Obtener el balance factor de un nodo.
        Node<T>* minValueNode(Node<T>* currentNode); // Regresar el nodo con key mínomo dentro de un subárbol.
};

/** Inserta un nodo al árbol AVL.
 * Complejidad Computacional: O(log n).
 * Ya que tenemos que buscar una posición para insertar el nodo, y esta busqueda se basa en el binary search.
 * @param currentNode El nodo en que nos encontramos en el árbol
 * @param insertNode Nodo a insertar.
 * @return Un nodo del árbol.
 */
template<class T>
Node<T>* TreeAVL<T>::insert(Node<T>* currentNode, Node<T>* insertNode){
    int bFactor = 0;
    if(currentNode == NULL){
        sizeTree++;
        return insertNode; // Insertamos un nodo en un lugar NULL
    }
    if(insertNode -> key < currentNode -> key){
        currentNode -> left = insert(currentNode -> left, insertNode); // Avanzamos al hijo izquierdo.
    } else if (insertNode -> key > currentNode -> key){
        currentNode -> right = insert(currentNode -> right, insertNode); // Avanzamos al hijo derecho (si es mayor o igual).
    } else {
        return currentNode;
    }
    bFactor = balanceFact(currentNode); // Obtenemos el bFactor del nodo en que nos encontremos.
    if (bFactor > 1 && balanceFact(currentNode -> left) == 1){ // Rotación LL.
        return rotaR(currentNode);
    }
    if (bFactor < -1 && balanceFact(currentNode -> right) == -1){ // Rotación RR.
        return rotaL(currentNode);
    }
    if (bFactor > 1 && balanceFact(currentNode -> left) == -1){ // Rotación lR.
        currentNode -> left = rotaL(currentNode -> left);
        return rotaR(currentNode);
    }
    if (bFactor < -1 && balanceFact(currentNode -> right) == 1){ // Rotación RL.
        currentNode -> right = rotaR(currentNode -> right);
        return rotaL(currentNode);
    }
    return currentNode;
}

// Iniciador de insert. Complejidad: O(1)
template<class T>
void TreeAVL<T>::insert(T data, int key){
    Node<T> *InsertNode = new Node<T>(data, key);
    if(root != NULL){ // Si root es diferente a NULL, insertamos recursivamente.
        this -> root = insert(root, InsertNode);
    } else { // Insertamos nuevo nodo en root.
        this -> root = InsertNode;
        sizeTree++;
    }
}

/** Borra un nodo dentro del árbol.
 * Complejidad Computacional: O(log n).
 * Primero se basa en una busqueda binaria para encontrar un elemento, para luego borrarlo.
 * Lo pasos para acomodar el árbol es O(n).
 * @param key La llave de un nodo que se quiere borrar.
 * @param currentNode El nodo en el cual nos encontramos en el árbol.
 * @return Un nodo del árbol, para hacer la función recursiva.
 */
template<class T>
Node<T>* TreeAVL<T>::del(int key, Node<T>* currentNode){
    // Encontrar el elemento.
    if(currentNode == NULL){ // Si encuentra null, significa que no existe.
        return currentNode;
    }
    // Recorremos el árbol de manera binaria hasta encontrar el nodo a borrar.
    if(key < currentNode -> key){
        currentNode -> left = del(key, currentNode -> left);
    } else if(key > currentNode -> key){
        currentNode -> right = del(key, currentNode -> right);
    } else { // Si se encuentra el nodo, entramos al else.
        if((currentNode -> left == NULL) || (currentNode -> right == NULL)){ // En caso de que el nodo tenga un hijo o no.
            Node<T>* temp = currentNode;
            if(currentNode -> left){
                temp = currentNode -> left;
            } else {
                temp = currentNode -> right;
            }
            if(temp == NULL){
                temp = currentNode;
                currentNode = NULL;
            } else {
                *currentNode = *temp;
            }
            free(temp);
            sizeTree--;
        } else {
            Node<T>* temp = currentNode -> left;
            while(temp -> left){
                temp = temp -> left;
            }
            currentNode -> key = temp -> key;
            currentNode -> right = del(temp -> key, currentNode -> right);
        }
    }
    if(currentNode == NULL){
        return currentNode;
    }
    // Reacomodamos el árbol.
    int bFactor = balanceFact(currentNode);
    if(bFactor > 1 && balanceFact(currentNode -> left) >= 0){ // Rotación LL.
        return rotaR(currentNode);
    }
    if(bFactor > 1 && balanceFact(currentNode -> left) < 0){ // Rotación LR.
        currentNode -> left = rotaL(currentNode -> left);
        return rotaR(currentNode);
    }
    if(bFactor < -1 && balanceFact(currentNode -> right) <= 0){ // Rotación RR.
        return rotaL(currentNode);
    }
    if(bFactor < -1 && balanceFact(currentNode -> right) > 0){ // Rotación RL.
        currentNode -> right = rotaR(currentNode -> right);
        return rotaL(currentNode);
    }
    return currentNode;
}

// Iniciador de del. Complejidad O(1).
template<class T> 
void TreeAVL<T>::del(int key){
    root = del(key, root);
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
    if(currentNode == NULL){
        return 0;
    } else {
        return max(heightNode(currentNode -> left), heightNode(currentNode -> right)) + 1;
    }
}

/** Regresa el balance factor de un nodo dado.
 * Complejidad Computacional: O(1) + Complejidad de heightNode.
 * @param currentNode Nodo al cual se le quiere conocer su balance factor.
 * @return Entero que indica su balance factor.
 */
template<class T>
int TreeAVL<T>::balanceFact(Node<T>* currentNode){
    int HL = heightNode(currentNode -> left); // Left height. 
    int HR = heightNode(currentNode -> right); // Left height.
    return HL - HR;
}

/** Función para realizar la rotación RR.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el RR.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
Node<T>* TreeAVL<T>::rotaR(Node<T>* currentNode){
    Node<T> *nodeHI = currentNode -> left; // Nodo hijo izquierdo de current.
    Node<T> *nodeHID = nodeHI -> right; // El subárbol derecho del nodo hijo izquierdo.
    nodeHI -> right = currentNode;
    currentNode -> left = nodeHID;
    return nodeHI;
}

/** Función para realizar la rotación LL.
 * Complejidad Computacional: O(1).
 * Nada más realizar una serie de pasos, no importa el tamaño del árbol.
 * @param currentNode Nodo (o padre) al cual se le hara el LL.
 * @return El Nodo con los sub-árboles acomodados.
 */
template<class T>
Node<T>* TreeAVL<T>::rotaL(Node<T>* currentNode){
    Node<T> *nodeHD = currentNode -> right; // Nodo hijo derecho de current.
    Node<T> *nodeHDI = nodeHD -> left; // El subárbol izquierdo del nodo hijo derecho.
    nodeHD -> left = currentNode;
    currentNode -> right = nodeHDI;
    return nodeHD;
}

/** Busca un elemento dentro del árbol.
 * Complejidad Computacional: O(log n).
 * Nos basamos en el algoritmo de busqueda binary search.
 * @param currentNode El nodo en que nos encontramos en el árbol.
 * @param searchKey La llave de un nodo a buscar.
 * @return Bool (true o false) en caso de encontrar o no el key de un nodo.
 */
template<class T>
bool TreeAVL<T>::find(Node<T>* currentNode, int searchkey){
    if(currentNode == NULL){ // Regresar false si el nodo es NULL, significa que no encontro el key.
        return false;
    } else if (currentNode -> key == searchkey){ // Si encuentra el key en el nodo, regresa true.
        return true;
    } else {
        // Buscar en el siguiente hijo ya sea si el key es mayor o menor al current node.
        if( searchkey > currentNode -> key){
            return find(currentNode -> right, searchkey);
        } else {
            return find(currentNode -> left, searchkey);
        }
    }
}

// Iniciador de search. Complejidad: O(1).
template<class T>
bool TreeAVL<T>::find(int searchKey){
    return find(root, searchKey);
}

/** Obtener el key mínimo de un subárbol. 
 * Complejidad Computacional: O(n).
 * Un subárbol tiene n elementos a la izquierda, se necesita recorrer todos.
 * @param currentNode Nodo en el cual nos encontramos en el árbol.
 * @return Nodo con el key más mínimo en el subárbol.
 */
template<class T>
Node<T>* TreeAVL<T>::minValueNode(Node<T>* currentNode){
    Node<T> *temp = currentNode; // Utilizamos otra variable para no cambiar currentNode.
    // Recorrer al elemento mínimo (izquierda) del subárbol.
    while(temp -> left != NULL){
        temp = temp -> left;
    }
    return temp;
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
void TreeAVL<T>::print(){
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
    TreeAVL<string> AVL;
    cout << "Insertando al arbol los elementos (en el mismo orden): 100, 50." << endl;
    AVL.insert("01", 100);
    AVL.insert("02", 50);
    cout << "Contenido del arbol: " << endl;
    AVL.print();
    cout << endl;
    cout << "Size of tree: " << AVL.size() << endl;
    cout << "Esta el 101? [0] = No, [1] = Si: " << AVL.find(101) << endl;
    cout << "Insertando al arbol: 25." << endl;
    AVL.insert("03", 25);
    cout << "Contenido del arbol: " << endl;
    AVL.print();
    cout << endl;
    cout << "Esta el 25? [0] = No, [1] = Si: " << AVL.find(25) << endl;
    cout << "Size of tree: " << AVL.size() << endl;
    cout << "Borramos: 100." << endl;
    AVL.del(100);
    cout << "Contenido del arbol: " << endl;
    AVL.print();
    cout << endl;
    cout << "Size of tree: " << AVL.size() << endl;    
    cout << "Esta el 100? [0] = No, [1] = Si: " << AVL.find(100) << endl;
    cout << "Insertando al arbol los elementos (en el mismo orden): 200, 75." << endl;
    AVL.insert("04", 200);
    AVL.insert("05", 75);
    cout << "Contenido del arbol: " << endl;
    AVL.print();
    cout << endl;
    cout << "Size of tree: " << AVL.size() << endl;
    cout << "Esta el 50? [0] = No, [1] = Si: " << AVL.find(50) << endl;
    cout << "Borramos del arbol los elementos (en el mismo orden): 25, 50, 75." << endl;
    AVL.del(25);
    AVL.del(50);
    AVL.del(75);
    cout << "Contenido del arbol: " << endl;
    AVL.print();
    return 0;
}