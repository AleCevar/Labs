#include <iostream>
#include "AVL.h"
using namespace std;

long long int BSTVertex :: hash(string s, int p, int q){
    // Calcula el hash aparatir de dos primos y un string
    unsigned long long int res = 0;
    for(int i = 0; s[i] ; i++, res %= p){
      res += expt(q,s[i],p);
    }
    return res % p;
}
long long int BSTVertex :: expt(int a, int exp, int mod){
    // Funci�n que calcula el inverso de un n�mero.
    if (!exp) return 1L;
    unsigned long long int r = expt(a, exp/2, mod);
    r *= r;
    r %= mod; 
    if (exp & 1) r *= a;
    return r % mod;
}


  string AVL :: findMin(BSTVertex* T) {
         if (T == NULL)       return "-1";         // BST is empty, no minimum
    else if (T->left == NULL) return T->key;     // this is the min
    else                      return findMin(T->left); // go to the left
  }

  string AVL :: findMax(BSTVertex* T) {
         if (T == NULL)        return "-1";        // BST is empty, no maximum
    else if (T->right == NULL) return T->key;    // this is the max
    else                       return findMax(T->right); // go to the right
  }
  int AVL :: veri_palabra(string a, string b){
    //Verifica si las palabras son iguales o no
    for(int i = 0; i < a.size() && i < b.size(); i++){
      if(a[i] != b[i]){return 0;}
    }
    return 2;
  }

  int AVL :: verificacion(BSTVertex * T, BSTVertex * N, unsigned long long int h1, unsigned long long int h2, int flag){
    //Verifica si los hash de dos nodos son iguales
    if(h1 == h2 && flag == 1) return veri_palabra(T->key,N->key);
    else{
      if(h1 == h2) return verificacion(T,N,T->h2,N->h2,1);
      return h1 > h2;
    }
  }
  BSTVertex* AVL :: search(BSTVertex* T, string s){
    BSTVertex* N = new BSTVertex(s);
         if (T == NULL)   return T;              // not found
    else if (veri_palabra(T->key,s) == 2) return T;              // found
    else if (verificacion(T,N,T->h1,N->h1,0) == 1)  return search(T->right, s); // search to the right
    else                  return search(T->left, s); // search to the left
  }
  
  string AVL ::successor(BSTVertex* T) {
    if (T->right != NULL)                        // we have right subtree
      return findMin(T->right);                  // this is the successor
    else {
      BSTVertex* par = T->parent;
      BSTVertex* cur = T;
      // if par(ent) is not root and cur(rent) is its right children
      while ((par != NULL) && (cur == par->right)) {
        cur = par;                               // continue moving up
        par = cur->parent;
      }
      return par == NULL ? "-1" : par->key;        // this is the successor of T
    }
  }

  BSTVertex* AVL :: rotateLeft(BSTVertex* T) {
    // T must have a right child
    BSTVertex* w = T->right;
    w->parent = T->parent;
    T->parent = w;
    T->right = w->left;
    if (w->left != NULL) w->left->parent = T;
    w->left = T;

    T->height = max(h(T->left), h(T->right)) + 1;
    w->height = max(h(w->left), h(w->right)) + 1;

    return w;
  }

  BSTVertex* AVL :: rotateRight(BSTVertex* T) {
    // T must have a left child

    BSTVertex* w = T->left;
    w->parent = T->parent;
    T->parent = w;
    T->left = w->right;
    if (w->right != NULL) w->right->parent = T;
    w->right = T;

    T->height = max(h(T->left), h(T->right)) + 1;
    w->height = max(h(w->left), h(w->right)) + 1;

    return w;
  }

  BSTVertex* AVL :: insert(BSTVertex* T, BSTVertex* N) {       // override insert in BST class
    if (T == NULL) {                             // insertion point is found
      T = N;
      T->parent = T->left = T->right = NULL;
      T->height = 0;
      size++;}                             // used in AVL lecture
    else{
      int veri = verificacion(T,N,T->h1,N->h1,0);
      if(veri == 1){                       // search to the right
          T->right = insert(T->right, N);
          T->right->parent = T;}  
      else if(veri == 0){                                         // search to the left
            T->left = insert(T->left, N);
            T->left->parent = T;}}
      balancear(T);
      return T;}                                    // return the updated AVL
  
  BSTVertex* AVL :: remove(BSTVertex* T, BSTVertex* N) {
    int veri = verificacion(T,N,T->h1,N->h1,0);
    if (T == NULL)  return T;                    // cannot find the item
    if (veri == 2) {                           // the node to be deleted
      if (T->left == NULL && T->right == NULL){   // this is a leaf
        T = NULL;
        size--;}                                // simply erase this node
      else if (T->left == NULL && T->right != NULL) { // only one child at right
        T->right->parent = T->parent;
        T = T->right; size--;                            // bypass T
      }
      else if (T->left != NULL && T->right == NULL) { // only one child at left
        T->left->parent = T->parent;
        T = T->left; size--;}                             // bypass T
      else {                                     // find successor
        string successorS = successor(N->key);
        T->key = successorS;
        BSTVertex* S = new BSTVertex(successorS);                     // replace with successorV
        T->right = remove(T->right, S);} // delete the old successorV  
    }
    else if (veri == 1 && T->right != NULL)                         // search to the right
      T->right = remove(T->right, N);
    else if(T->left != NULL)                                        // search to the left
      T->left = remove(T->left, N);
    if (T != NULL) { balancear(T);}              // similar as insertion code except this line
    return T;}                                       // return the updated BST

  void AVL :: balancear(BSTVertex* T){
    //Verifica si el arbol esta balanceado si no lo balancea
    int balance = h(T->left) - h(T->right);
      if (balance == 2) { // left heavy
        int balance2 = h(T->left->left) - h(T->left->right);
        if (balance2 == 1) {
          T = rotateRight(T);
        }
        else { // -1
          T->left = rotateLeft(T->left);
          T = rotateRight(T);
        }
      }
      else if (balance == -2) { // right heavy
        int balance2 = h(T->right->left) - h(T->right->right);
        if (balance2 == -1)
          T = rotateLeft(T);
        else { // 1
          T->right = rotateRight(T->right);
          T = rotateLeft(T);
        }
      }
      T->height = max(h(T->left), h(T->right)) + 1;
  }                                    // return the updated BST


  bool AVL :: insert(string s) {
    if(capacidad == size){return false;}
    BSTVertex * N = new BSTVertex(s); 
    int ant = size;
    root = insert(root, N);
    if(ant != size)return true;
    return false;}

  bool AVL :: remove(string s) {
    int ant = size;
    BSTVertex* N = new BSTVertex(s);
    root = remove(root, N);
    if(ant != size) return true;
    return false;}

  bool AVL :: contiene(string s){
    string res = search(s);
    if(res == "-1"){return false;}
    return true; 
  }
  string AVL :: search(string s) {
    BSTVertex* res = search(root, s);
    return res == NULL ? "-1" : res->key;
  }

  string AVL :: successor(string s) { 
    BSTVertex* vPos = search(root, s);
    return vPos == NULL ? "-1" : successor(vPos);
  }
  BSTVertex* AVL :: getRoot(){
    return root;
  }
  void AVL :: destructor(BSTVertex* T){
    if(T == NULL){return;}
    destructor(T->left);
    destructor(T->right);
    delete(T);
    T = NULL;
  }
