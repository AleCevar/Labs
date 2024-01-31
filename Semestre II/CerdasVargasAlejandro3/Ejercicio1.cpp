/*
Dada una serie de strings con que representan abreviaciones de algunas profesiones, se debe determinar cuantas profesiones 
diferentes hay en una  entrada.
*/

#include <bits/stdc++.h>
#include "Ejercicio1.h"
using namespace std;

void Trie :: insert(string word, int n) {                     // insert a word into trie
    vertex* cur = root;
    for (int i = 0; i < (int)word.size(); ++i) { // O(n)
      int alphaNum = word[i]-'A';
      if(cur->exist != n){cur->exist = 0;}
      if (cur->child[alphaNum] == NULL){         // add new branch if NULL
        cur->child[alphaNum] = new vertex(word[i]);
        cur->child[alphaNum]->exist = n;
      }
      cur = cur->child[alphaNum];
    }
  }

int Trie :: search(string word) {                     // true if word in trie
    vertex* cur = root;
    for (int i = 0; i < (int)word.size(); ++i) { // O(m)
      int alphaNum = word[i]-'A';
      if (cur->child[alphaNum] == NULL)          // not found
        return 0;
      cur = cur->child[alphaNum];
    }
    return cur->exist;                         // check exist flag
  }

int Trie :: contarBits(int n){
    int cuenta = 0;
    while(n){
      n &= (n-1);
      cuenta ++;
    }
    return cuenta;
}


int main() {
  int casos;
  int profesiones;
  int resume;
  int n;
  string s;
  cin >> casos;
  for(int z = 0; z < casos; z++){
    Trie T;
    cin >> profesiones >> resume;
    for(int i = 0; i < profesiones; i++){
      cin >> n;
      for(int j = 0; j < n; j++){
        cin >> s;
        T.insert(s,pow(2,i));
      }
    }
    for(int i = 0; i < resume; i++){
      cin >> n;
      int cuenta = 0;
      for(int j = 0; j < n; j++){
        cin >> s;
        cuenta |= T.search(s);
      }
      cout << T.contarBits(cuenta) << endl;
    }
  }
  return 0;
}
