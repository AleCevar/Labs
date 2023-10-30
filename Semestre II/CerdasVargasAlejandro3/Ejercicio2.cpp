#include <bits/stdc++.h>
#include "Ejercicio2.h"
using namespace std;

int cuenta = 0;

void Trie :: insert(string word) {                     // insert a word into trie
    vertex* cur = root;
    for (int i = 0; i < (int)word.size(); ++i) { // O(n)
        int alphaNum = word[i]-'0';
        if (cur->child[alphaNum] == NULL){          // add new branch if NULL
            cur->child[alphaNum] = new vertex(word[i]);}
        if(cur->child[alphaNum]->exist){cuenta++;}
        else if(i+1 < (int)word.size()){cur->child[alphaNum]->paso++;}
        cur = cur->child[alphaNum];
    }
    cur->exist = true;
    cuenta += cur->paso;
}

int main() {
    Trie T;
    int cantidad;
    string s;
    cin >> cantidad;
    for(int i = 0; i < cantidad; i++){
        cin >> s;
        T.insert(s);
    }
    cout << cuenta << endl;
    return 0;
}
