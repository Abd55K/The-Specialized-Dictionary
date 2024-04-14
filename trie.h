#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.

    void removeAllNodes(TrieNode* &r){  // My function
        if(r){
            delete r->data;
            for(int i=0;i<r->ALPHABET_SIZE;i++){
                if(r->children[i]) removeAllNodes(r->children[i]);
            }
            delete r;
        }
    }
    
    void wildcardSearch(TrieNode* r, int i , const std::string &wildcardKey, std::vector<T*> &results){ // My function
        
        if(i==wildcardKey.size()) return;
        
        bool flag;
        
        // The end of the string, time for pushing
        if(i==wildcardKey.size()-1){
            if(wildcardKey[i] != '*' && wildcardKey[i] != '?' && r->children[wildcardKey[i]]){
                r=r->children[wildcardKey[i]];
                if(r->isEndOfKey){
                    flag=true;
                    for(int k=0; k<results.size(); k++){
                        if(r->data == results[k]){
                            flag=false;
                        }
                    }
                    
                    if(flag) {
                        results.push_back(r->data);
                    }
                }
                return;
            }
            else if(wildcardKey[i] == '?'){
                for (int j = 0; j< r->ALPHABET_SIZE; j++){
                    if(r->children[j]){
                        if(r->children[j]->isEndOfKey){
                            flag=true;
                            for(int k=0; k<results.size(); k++){
                                if(r->children[j]->data == results[k]){
                                    flag=false;
                                }
                            }
                            
                            if(flag){
                                results.push_back(r->children[j]->data);
                            }
                        }
                    }
                }
                return;
            }
            else if(wildcardKey[i] == '*'){
                starcase(r, results);
                return;
            }
        }
        
        
        
        // The middle of the string
        if(wildcardKey[i] != '*' && wildcardKey[i] != '?' && r->children[wildcardKey[i]]){
            wildcardSearch(r->children[wildcardKey[i]], i+1, wildcardKey, results);
        }
        else if(wildcardKey[i] == '?'){
            for (int j = 0; j< r->ALPHABET_SIZE; j++){
                if(r->children[j]){
                    wildcardSearch(r->children[j], i+1, wildcardKey, results);
                }
            }
        }
        else if(wildcardKey[i] == '*'){
            
            wildcardSearch(r, i+1, wildcardKey, results);
            
            for(int j = 0; j< r->ALPHABET_SIZE; j++){
                if(r->children[j]){
                    wildcardSearch(r->children[j], i, wildcardKey, results);
                }
            }
        }
    }
    
    void starcase(TrieNode* r, std::vector<T*> &results){
        if(r==NULL) return;
        
        bool flag;
        
        if(r->isEndOfKey){
            flag=true;
            for(int k=0; k<results.size(); k++){
                if(r->data == results[k]){
                    flag=false;
                }
            }
            
            if(flag){
                results.push_back(r->data);
            }
        }
        
        for (int j = 0; j< r->ALPHABET_SIZE; j++){
            starcase(r->children[j], results);
        }
    }
    
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    
    removeAllNodes(root);
    
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    int size=key.size();
    if(size==0) return *this;
    TrieNode* r=root;
    for(int i=0;i<size;i++){
        if(r->children[key[i]] == NULL){
            r->children[key[i]]=new TrieNode(key[i]);
        }
        r=r->children[key[i]];
    }
    
    r->isEndOfKey=true;
    r->data=new T(key);
    
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    int size=username.size();
    TrieNode* r=root;
    bool B=false;
    for(int i=0;i<size;i++){
        if(r->children[username[i]]){
            r=r->children[username[i]];
        }
        else{
            return NULL;
        }
    }
    B=r->isEndOfKey;
    
    if(B){
        return r->data;
    }
    else return NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    /* IMPLEMENT THIS */
    int size=username.size();
    TrieNode* r=root;
    for(int i=0;i<size;i++){
        if(r->children[username[i]]){
            r=r->children[username[i]];
        }
        else{
            return;
        }
    }
    r->isEndOfKey=false;
    delete r->data;
    r->data=NULL;
}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
    /* IMPLEMENT THIS */
    
    wildcardSearch(prefix+"*", results);
    
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    /* IMPLEMENT THIS */
    
    wildcardSearch(root, 0, wildcardKey, results);
    
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}

