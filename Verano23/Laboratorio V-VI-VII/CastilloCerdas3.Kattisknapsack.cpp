#include <iostream>
using namespace std;

#define oo -20000

// Knapsack Kattis (Aceptado)
// https://open.kattis.com/problems/knapsack
// https://open.kattis.com/submissions/12543033
// Complejidad: $ O(n \times C)$

int C,n;
int valor[2005];
int peso[2005];
int memo[2005][2005];

int solve(int pos, int cap){
    if(cap < 0) return oo;
    if(!cap || pos==n) return memo[pos][cap]=0;
    if(memo[pos][cap]!=-1) return memo[pos][cap];
    return memo[pos][cap] = max(valor[pos] + solve(pos+1,cap-peso[pos]),
        solve(pos+1,cap));
}

void imprimir(){
    int j = C, cont=0;
    int i;
    string s = "";
    for(i = 0; i < n-1; i++){
        if(j<=0) break;
        if(memo[i][j] != memo[i+1][j]){ 
            j -= peso[i]; cont++;
            s+= " "+ to_string(i);
        }
    }
    if(j>=0 && peso[i]<=j) s+=" "+to_string(i), cont++;
    cout << cont<<'\n';
    if(!cont) return;
    for(i = 1; s[i]; i++){
        cout << s[i];
    }
    cout << '\n';
}

int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(cin >> C >> n){
        for(int i = 0; i < n; i++){
            cin >> valor[i] >> peso[i];
        }
        for(int i=0; i<n; i++) for(int j=0; j<=C; j++) memo[i][j]=-1;
        solve(0,C); 
        imprimir();
    }
    return 0;
}
