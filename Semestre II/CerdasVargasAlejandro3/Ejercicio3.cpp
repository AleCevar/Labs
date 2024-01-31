/*
Se desea imprimir una serie de strings en una imprenta móvil en la menor cantidad de pasos posible. 
En la imprenta se puede quitar una letra, agregar una letra e imprimir. 
*/

#include <bits/stdc++.h>
#include "Ejercicio3.h"
using namespace std;

int Trie :: insert(string word, int flag) {                     // insert a word into trie
    vertex* cur = root;
    int cuenta = 0;
    for (int i = 0; i < (int)word.size(); ++i) { // O(n)
        int alphaNum = word[i]-'a';
        if (cur->child[alphaNum] == NULL){          // add new branch if NULL
            cur->child[alphaNum] = new vertex(word[i]);
            cuenta++;}
        if(flag == 1 && cur->alphabet != '!'){cur->p_mayor = true;}
        cur = cur->child[alphaNum];
    }    
    cur->exist = true;
    if(flag == 1){cur->p_mayor = true;}
    return (2 * cuenta) + 1;
  }

void Trie :: imprenta(vertex* T){
        if(T->alphabet != '!'){cout << T->alphabet << endl;}
        int mayor = -1;
        for(int i = 0; i < 26; i++){
          if(T->child[i] != NULL){
            if(!T->child[i]->p_mayor){imprenta(T->child[i]);}
            else{mayor = i;} 
          }
        }
        if(T->exist){cout << 'P' << endl;}
        if(!T->p_mayor && T->alphabet != '!'){cout << '-' << endl;}
        if(mayor > -1){imprenta(T->child[mayor]);
        }
}

int main() {
  Trie T;
  int cantidad;
  int inst = 0;
  string s;
  string mayor = "";
  cin >> cantidad;
  for(int i = 0; i < cantidad; i++){
    cin >> s;
    if(mayor == ""){mayor = s;}
    else if(mayor.size() > s.size()){inst += T.insert(s,0);}
        else{
            inst += T.insert(mayor,0);
            mayor = s;}
  }
  inst += T.insert(mayor,1);
  inst -= mayor.size();
  cout << inst << endl;
  T.imprenta(T.getRoot());
  return 0;
}
