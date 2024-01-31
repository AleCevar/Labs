//Un número hermoso es un número con 2N dígitos,
//y cuyos primeros N dígitos suman lo mismo que sus dígitos faltantes. Imprima la cantidad de números hermosos en un intervalo.
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll t,x,y;
int memo[11][99];

ll expoLog(int a, int exp){
    if(!exp) return 1;
    if(exp == 1) return a;
    ll res = expoLog(a,exp/2);
    res*=res;
    if(exp%2) res*=a;
    return res; 
}

int contDigi(ll n){
    int res = 0;
    while(n){
        res++;
        n/=10;
    }
    return res;
}

int calcular(int n, int c){
    if(!c) return (!n) ? 1 : 0; 
    if(c == 1) return (n > 9) ? 0 : 1;
    if(memo[c][n]) return memo[c][n]; 
    memo[c][n] = 0;
    for(int i = 0; i <= min(9,n); i++){
        memo[c][n]+=calcular(n-i,c-1);
    }
    return memo[c][n]; 
}

ll solve(ll x, ll y){
    ll fin, di = contDigi(x);
    ll res = 0;
    di = (di%2) ? di : di/2;
    fin = 9 * di; 
    while(expoLog(10,di*2) <= y){
        for(int i = 1; i <= fin; i++){
            int temW = 0, tem = calcular(i,di);
            for(int j = 1; j <= min(9,i); j++) 
                temW += calcular(i-j,di-1);
            res += (tem * temW);
        }
        di++;
        fin = 9*di;    
    }
    return res;
}

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> x >> y;
        cout << solve(x,y) << '\n';
    }
    return 0;
}
