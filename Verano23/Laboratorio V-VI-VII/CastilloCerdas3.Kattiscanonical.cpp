//Problema 71 Canonical Kattis (Aceptado)
// https://open.kattis.com/problems/canonical
// https://open.kattis.com/submissions/12539027
// Complejidad: O($mayor \times num \times n$) aproximadamente por la memoizacion

#include <iostream>
using namespace std;

int coins[101];
int n;
int memo[2000005];
int const oo = 100000000;


int dinamica(int num){
    if(!num) return 0;
    if(memo[num]>0) return memo[num];
    int minimo=oo;
    for(int i=0; i<n; i++){
        if(coins[i]>num) break;
        minimo= min(minimo, dinamica(num-coins[i])+1);
    }
    return memo[num]=minimo;
}

int buscar(int num){
    int inf=0, sup=n;
    int m;
    while(inf+1<sup){
        m=(inf+sup)/2;
        if(coins[m]>num) sup=m;
        else inf=m;
    }
    return coins[inf];
}

int voraz(int num){
    int cont=0;
    int moneda=oo;
    while(num){
        if(moneda<=num) cont+=num/moneda, num-=(num/moneda)*moneda;
        else moneda=buscar(num);
    }
    return cont;
}

int probar(int mayor){
    for(int i = mayor; i > 0; i--) 
        if(voraz(i) != dinamica(i)) return 0;   
    return 1;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> coins[i];
    int mayor = coins[n-1] + coins[n-2]; 
    if(probar(mayor-1)) cout<<"canonical\n";
    else cout <<"non-canonical\n";
}