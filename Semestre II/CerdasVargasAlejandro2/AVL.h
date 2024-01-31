/*
AVL modificado para funcionar como un conjunto de strings, usa hash
*/

#include <bits/stdc++.h>
#include "lista.cpp"
using namespace std;

// Every vertex in this BST is a C Struct (to expose all its members publicly)
struct BSTVertex {
  // all these attributes remain public to slightly simplify the code although this may not be the best practice
  int primo1 = 613;
  int primo2 = 1048627;
  int primo3 = 709;
  int primo4 = 1100039;
  unsigned long long int h1;
  unsigned long long int h2;
  BSTVertex* parent;
  BSTVertex* left;
  BSTVertex* right;
  string key;
  int height; // will be used in AVL lecture
  BSTVertex(string s){
    h1 = hash(s, primo2, primo1);
    h2 = hash(s, primo4, primo3);
    key = s;
  }
  long long int hash(string s, int p, int q);
  long long int expt(int a, int exp, int mod);
  //~BSTVertex() = default;
};
class AVL{
private:
  BSTVertex *root;
  int h(BSTVertex* T) { return T == NULL ? -1 : T->height; }
  void preorder(BSTVertex* T);
  string findMin(BSTVertex* T);
  string findMax(BSTVertex* T);
  int veri_palabra(string a, string b);
  int verificacion(BSTVertex * T, BSTVertex * N, unsigned long long int h1, unsigned long long int h2, int flag);
  BSTVertex* search(BSTVertex* T, string s);
  string successor(BSTVertex* T);
  BSTVertex* rotateLeft(BSTVertex* T);
  BSTVertex* rotateRight(BSTVertex* T);
  BSTVertex* insert(BSTVertex* T, BSTVertex* N);
  BSTVertex* remove(BSTVertex* T, BSTVertex* N); 
  void balancear(BSTVertex* T);

public:
  int size;
  int capacidad;
  AVL(int capa){
    capacidad = capa; 
    root = NULL; 
    size = 0;
    root = NULL;}

  bool insert(string s);
  bool remove(string s);
  bool contiene(string s);
  string search(string s);
  string successor(string s);
  BSTVertex * getRoot();
  void destructor(BSTVertex * T);
  ~AVL(){
    destructor(getRoot());
  }
};
