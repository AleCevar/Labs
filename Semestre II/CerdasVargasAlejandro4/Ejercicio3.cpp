#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquerMin(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  int conquerMax(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return max(a, b);                            // RMQ
  }

  void buildMin(int p, int L, int R) {              // O(n)
    if (L == R)
      stMin[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      buildMin(l(p), L  , m);
      buildMin(r(p), m+1, R);
      stMin[p] = conquerMin(stMin[l(p)], stMin[r(p)]);
    }
  }

  void buildMax(int p, int L, int R) {              // O(n)
    if (L == R)
      stMax[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      buildMax(l(p), L  , m);
      buildMax(r(p), m+1, R);
      stMax[p] = conquerMax(stMax[l(p)], stMax[r(p)]);
    }
  }

  void propagateMin(int p, int L, int R) {
    if (lazyMin[p] != -1) {                         // has a lazy flag
      stMin[p] = lazyMin[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazyMin[l(p)] = lazyMin[r(p)] = lazyMin[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazyMin[p];                          // time to update this
      lazyMin[p] = -1;                              // erase lazy flag
    }
  }

  void propagateMax(int p, int L, int R) {
    if (lazyMax[p] != -1) {                         // has a lazy flag
      stMax[p] = lazyMax[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazyMax[l(p)] = lazyMax[r(p)] = lazyMax[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazyMax[p];                          // time to update this
      lazyMax[p] = -1;                              // erase lazy flag
    }
  }

  int minRMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagateMin(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return stMin[p];      // found the segment
    int m = (L+R)/2;
    return conquerMin(minRMQ(l(p), L  , m, i , min(m, j)), minRMQ(r(p), m+1, R, max(i, m+1), j ));
  }
  
  int maxRMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagateMax(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return stMax[p];      // found the segment
    int m = (L+R)/2;
    return conquerMax(maxRMQ(l(p), L  , m, i , min(m, j)), maxRMQ(r(p), m+1, R, max(i, m+1), j ));
  }

  void updateMin(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagateMin(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazyMin[p] = val;                             // update this
      propagateMin(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      updateMin(l(p), L  , m, i, min(m, j), val);
      updateMin(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazyMin[l(p)] != -1) ? lazyMin[l(p)] : stMin[l(p)];
      int rsubtree = (lazyMin[r(p)] != -1) ? lazyMin[r(p)] : stMin[r(p)];
      stMin[p] = (lsubtree <= rsubtree) ? stMin[l(p)] : stMin[r(p)];
    }
  }

  void updateMax(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagateMax(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazyMax[p] = val;                             // update this
      propagateMax(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      updateMax(l(p), L  , m, i, min(m, j), val);
      updateMax(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazyMax[l(p)] != -1) ? lazyMax[l(p)] : stMax[l(p)];
      int rsubtree = (lazyMax[r(p)] != -1) ? lazyMax[r(p)] : stMax[r(p)];
      stMax[p] = (lsubtree >= rsubtree) ? stMax[l(p)] : stMax[r(p)];
    }
  }


public:
  vi A, stMin, lazyMin;                                // the arrays
  vi stMax, lazyMax;

  SegmentTree(int sz) : n(sz), stMin(4*n), lazyMin(4*n, -1), stMax(4*n), lazyMax(4*n,-1) {}
  
  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    buildMin(1, 0, n-1);
    buildMax(1,0,n-1);
  }

  void update(int i, int j, int val) { 
    updateMin(1, 0, n-1, i, j, val); 
    updateMax(1, 0, n-1, i, j, val);}

  int RMQMIN(int i, int j) { return minRMQ(1, 0, n-1, i, j); }
  int RMQMAX(int i, int j) {return maxRMQ(1,0,n-1,i,j);}
};

int main(){
  vi array;
  int estrellas;
  int consultas;
  string s;
  int x;
  int y;

  cin >> estrellas >> consultas;
  for(int i = 0; i < estrellas; i++){
    cin >> x;
    array.push_back(x);
  }
  SegmentTree * ST = new SegmentTree(array);
  
  for(int  i = 0; i < consultas; i++){
    cin >> s >> x >> y;
    if(s.compare("MAX") == 0){
      cout << ST->RMQMAX(x-1,y-1) << endl;
    }
    else if (s.compare("MIN") == 0) {
      cout << ST->RMQMIN(x-1,y-1) << endl;
    }
    else{
      ST->update(x-1,x-1,y);  
    }
  }
  return 0;
}