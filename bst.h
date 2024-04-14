#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

template <class T>
class BST {
private:
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: 

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:
    void removeAllNodes(TreeNode* &r){ 
        if(r){
            removeAllNodes(r->left);
            removeAllNodes(r->right);
            delete r;
        }
    }
    
    void insert(TreeNode* &r, const std::string key, const T& value){  
        if(r==NULL){
            r=new TreeNode(key, value);
        }
        else if(key < r->key){
            insert(r->left, key, value);
        }
        else if(r->key < key){
            insert(r->right, key, value);
        }
    }
    
    bool search(TreeNode* r, std::string value) const {  
        if(r==NULL){ 
            return false;
        }else if(value == r->key){
            return true;
        }else if(value < r->key){
            return search(r->left, value);
        }else if(r->key < value){
            return search(r->right, value);
        }
        
    }
    
    TreeNode* getMin(TreeNode* r) const {
        while(r->left) r=r->left;
        return r;
    }
    
    void remove(TreeNode*& r, std::string key){  
        if(r==NULL){
            return;
        }else if(key < r->key){
            remove(r->left, key);
        }else if(r->key < key){
            remove(r->right, key);
        }else if(key == r->key){
            if(r->left != NULL && r->right != NULL){
                TreeNode* t=getMin(r->right);
                r->key=t->key;
                r->data=t->data;
                remove(r->right, r->key);
            }
            else{
                TreeNode* oldNode=r;
                r = (r->left != NULL) ? r->left : r->right;
                delete oldNode;
            }
        }
    }
    
    void inorderPushing(TreeNode* r, vector<TreeNode>& result){
        if(r){
            inorderPushing(r->left, result);
            result.push_back(*r);
            inorderPushing(r->right, result);
        }
    }
    
    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); 
    
};

// Constructor
template <class T>
BST<T>::BST() : root(NULL) {}

// Destructor
template <class T>
BST<T>::~BST() {
    /* IMPLEMENT THIS */

    removeAllNodes(root);

}

// Insert function for BST.    
template <class T>
BST<T>& BST<T>::insert(const string key, const T& value) {
    /* IMPLEMENT THIS */
         
    insert(root, key, value);
    return *this;

}

// Search function for BST.
template <class T>
bool BST<T>::search(std::string value) const {
    /* IMPLEMENT THIS */
    
    return search(root, value);
    
}

// Remove a node from BST for given key. If key not found, do not change anything.
template <class T>
void BST<T>::remove(std::string key) {
    /* IMPLEMENT THIS */
    
    remove(root, key);
    
}

// A helper function for converting a BST into vector.
template <class T>
vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
    vector<TreeNode> result;
    inorderPushing(root, result);
    return result;
}

// Merge two BST's and return merged BST.
template <class T>
BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> vector1, vector2, vector3;
    int size1, size2, i=0, j=0;
    vector1=tree2vector(root);
    vector2=tree2vector(bst->root);
    size1=vector1.size();
    size2=vector2.size();
    
    while(i<size1 && j<size2){
        if(vector1[i].key < vector2[j].key){
            vector3.push_back(vector1[i]);
            i++;
        }
        else if(vector1[i].key > vector2[j].key){
            vector3.push_back(vector2[j]);
            j++;
        }
        else if(vector1[i].key == vector2[j].key){
            vector3.push_back(vector1[i]);
            i++;
            j++;
        }
    }
    
    while(i<size1){
        vector3.push_back(vector1[i]);
        i++;
    }
    
    while(j<size2){
        vector3.push_back(vector2[j]);
        j++;
    }
    
    BST<T>* X=new BST<T>();
    for(i=0;i<vector3.size();i++) X->insert(vector3[i].key, vector3[i].data);
    return X;
}
    
// Intersect two BST's and return new BST.
template <class T>
BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> vector1, vector2, vector3;
    int size1,size2,i,j;
    vector1=tree2vector(root);
    vector2=tree2vector(bst->root);
    size1=vector1.size();
    size2=vector2.size();
    
    for(j=0;j<size2;j++){
        for(i=0;i<size1;i++){
            if(vector1[i].key != vector2[j].key) continue;
            else{
                vector3.push_back(vector2[j]);
                break;
            }
        }
    }
    
    BST<T>* X=new BST<T>();
    for(i=0;i<vector3.size();i++) X->insert(vector3[i].key, vector3[i].data);
    return X;
}

template <class T>
void BST<T>::print() {
    print(root, "", true, false);

}

template <class T>
void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
    if (node != NULL) {
        cout << node->key << endl;
        print(node->left, indent, false, true);
        print(node->right, indent, true, false);
    }

}


