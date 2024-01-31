// Problema 3 Kattis Short Sell (Aceptado)
// https://open.kattis.com/problems/shortsell
// https://open.kattis.com/submissions/12543574
// Complejidad: O(N)

#include <iostream>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, K;
    cin >> N >> K;
    int dias[N];
    for(int i = 0; i < N; i++){
        cin >> dias[i];
    }
    int memo[2][2];
    memo[N&1][0]=0;
    memo[N&1][1]=1000000000;
    for(int i=N-1; i>=0; i--){
        memo[i&1][1]=min(K+100*dias[i], memo[(i+1)&1][1]+K);
        memo[i&1][0]=max(100*dias[i]-memo[(i+1)&1][1]-K, memo[(i+1)&1][0]);
    }
    cout<<memo[0][0]<<'\n';
}
