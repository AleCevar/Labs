#include <bits/stdc++.h>
using namespace std;

struct vertex {
  char alphabet;
  int exist;
  vector<vertex*> child;
  vertex(char a): alphabet(a), exist(0) { child.assign(26, NULL); }
};

class Trie {                                     // this is TRIE
private:                                         // NOT Suffix Trie
  vertex* root;
public:
  Trie() { root = new vertex('!'); }

  void insert(string word, int n);
  int search(string word);
  int contarBits(int n);
};