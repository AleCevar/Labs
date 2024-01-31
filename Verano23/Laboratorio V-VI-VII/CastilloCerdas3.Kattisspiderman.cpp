#include <iostream>
using namespace std;
#define Inf 10000


// Problema 67: Spiderman Kattis (Aceptado)
// https://open.kattis.com/problems/spiderman
// https://open.kattis.com/submissions/12529140
// Complejidad: O(n*suma( alts))


int alturas[40];
int memo[40][1001];
int m;

int solve(int pos, int alt){
    if(alt<0) return Inf;
    if(pos==m) return (alt==0)? 0:Inf;
    if(memo[pos][alt]!=-1) return memo[pos][alt];
    int menor=min(solve(pos+1, alt+alturas[pos]), solve(pos+1, alt-alturas[pos]));
    return memo[pos][alt]=max(menor, alt);
}   

int down(int i, int alt){
    if(alt-alturas[i]<0) return Inf;
    return (memo[i+1][alt-alturas[i]]<0)? Inf: memo[i+1][alt-alturas[i]];
}

int up(int i, int alt){
    return (memo[i+1][alt+alturas[i]]<0)? Inf: memo[i+1][alt+alturas[i]];
}

void imprimir(){
    int alt=alturas[0], i=1, minimo;
    cout<<'U';
    while(i<m-1){
        if(up(i, alt)<down(i, alt)) cout<<'U', alt+=alturas[i];
        else cout<<'D', alt-=alturas[i];
        i++;
    }
    cout<<"D\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, mayor, res;
    cin>>n;
    while(n--){
        cin>>m;
        mayor=0;
        for (int i = 0; i <m; i++)
        {
            cin>>alturas[i];
            mayor+=alturas[i];
        }
        for(int i=0; i<m; i++){
            for(int j=0; j<=mayor; j++) memo[i][j]=-1;
        }
        res = solve(1, alturas[0]);
        if(res==Inf) cout<<"IMPOSSIBLE\n";
        else{
            imprimir();
        }
    }
    return 0;
}
