/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
void merge(vector<int>& V, int l, int m, int r){
    vector<int> L, R; // Subarreglos temporales
    int n1 = m-l+1, n2 = r-m, i = 0, j = 0, k = l;
    for (int i=0; i<n1; i++){
        L.push_back(V[l+i]);
    }
    for (int j=0; j<n2; j++){
        R.push_back(V[m+j+1]);
    }
    i = j = 0;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        V[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        V[k] = R[j];
        j++;
        k++;
    }
}

void ordenaMerge(vector<int>& V, int l, int r){
    int m = 0;
    if (l<r){
        m = floor(((l+r)/2));
        ordenaMerge(V, l, m);
        ordenaMerge(V, m+1, r);
        merge(V, l, m, r);
    }
}
    
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* output = NULL;
        vector<int> data;
        // Pasamos los valores de los linked list en un vector
        while(l1 != NULL){
            data.push_back(l1 -> val);
            l1 = l1 -> next;
        }
        while(l2 != NULL){
            data.push_back(l2 -> val);
            l2 = l2 -> next;
        }
        
        // Ordenamos el vector
        ordenaMerge(data, 0, data.size()-1);
        
        // Guardamos los valores en nuestro linked list
        for(int i = 0; i < data.size(); i++){
            ListNode* temp = new ListNode(data[i]); // Creamos un nodo con el valor corresponidiente del vector.
            
            if(output == NULL){
                output = temp;
            } else{
                ListNode* aux = output;
                while(aux -> next != NULL){
                    aux = aux -> next;
                }
                aux -> next = temp;
            }
        }
        return output;
    }
};