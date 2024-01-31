#include <iostream>
using namespace std;

typedef unsigned long long int ull;

// Prom 2.4 Count it Online Judge
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=861&page=show_problem&problem=4758
// Complejidad: $O(log(n))$ por cada caso 

int calcular(ull n){
    if(!n) return 0;
    if(n == 1) return 1;
    return (n%2) ? calcular(n/2) + 1 : calcular(n/2);
}

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--){
        ull n; cin >> n;
        cout << calcular(n) << "\n";
    }
    return 0;
}
