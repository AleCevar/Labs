#include <bits/stdc++.h>
using namespace std;

struct vertex {
  int paso;
  char alphabet;
  bool exist;
  vector<vertex*> child;
  vertex(char a): alphabet(a), paso(0) ,exist(false) { child.assign(10, NULL); }
};

class Trie {                                     // this is TRIE
private:                                         // NOT Suffix Trie
  vertex* root;
public:
  Trie() { root = new vertex('!'); }

  void insert(string word);
};