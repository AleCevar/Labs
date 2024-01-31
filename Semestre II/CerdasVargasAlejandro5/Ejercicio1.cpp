/*
Dada una serie de personas que pertenecen o no a fraternidades, se debe indicar cuantas fraternidades hay y cuantas personas están solas.
Algunas personas ofrecen información de algunos de sus compañeros.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
  int numIndividuales;
public:
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = 0;                                 // optional feature
    numIndividuales = N;
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];
    if(setSize[x] == 1) numIndividuales--;
    if(setSize[y] == 1) numIndividuales--;                                               // optional speedup
    if(setSize[x] == 1 && setSize[y] == 1){numSets++;}
    if(setSize[x] > 1 && setSize[y] > 1){numSets--;}
    setSize[y] += setSize[x];                        // combine set sizes at y
  }

  int numNoSets(){
    return numIndividuales;
  }
};

int main() {
  ios_base :: sync_with_stdio(false); cin.tie(0);
  int personas,conocidos,x,y;
  cin >> personas >> conocidos;
  UnionFind uf(personas);
  for(int i = 0; i < conocidos; i++){
      cin >> x >> y;
      x--;y--;
      uf.unionSet(x,y);
  }
  cout << uf.numDisjointSets() << ' ' << uf.numNoSets() << "\n";
  return 0;
}
