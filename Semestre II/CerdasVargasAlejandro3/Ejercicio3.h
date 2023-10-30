#include <bits/stdc++.h>
using namespace std;

struct vertex {
  char alphabet;
  bool exist;
  bool p_mayor;
  vector<vertex*> child;
  vertex(char a): alphabet(a), exist(false), p_mayor(false) { child.assign(26, NULL); }
};

class Trie {                                     // this is TRIE
private:                                         // NOT Suffix Trie
  vertex* root;
public:
  Trie() { root = new vertex('!'); }

  vertex* getRoot(){return root;}

  int insert(string word, int flag);
  void imprenta(vertex* T);
};
