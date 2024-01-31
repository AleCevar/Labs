#include <bits/stdc++.h>
using namespace std;

// Problema 38 Increaing subsequence Kattis (Aceptado)
// https://open.kattis.com/problems/increasingsubsequence
// https://open.kattis.com/submissions/12539746
// Complejidad: O($n^2$)


int valores[205];
int n;

void solve(){
    int len[n];
    int before[n];
    for(int i=0; i<n; i++) len[i]=1, before[i]=i;
    int sub = 0;
    for(int i =1; i<n; i++){
        for(int j=0; j<i; j++){
            if(valores[i] > valores[j]){
                if(len[i]<=len[j]) before[i] = j, len[i]=len[j]+1;
                else if(len[i]==len[j]+1 && valores[j]<valores[before[i]]) before[i]=j;
            }
        }
        if(len[sub] < len[i]) sub = i;
        if(len[sub] == len[i] && valores[sub] > valores[i]) sub = i;
    }
    cout << len[sub];
    stack<int> pila;
    int i = sub;
    while(i != before[i]){
        pila.push(valores[i]);
        i = before[i];
    }
    pila.push(valores[i]);
    while(!pila.empty()){
        int a = pila.top();pila.pop();
        cout<< ' ' << a; 
    }
    cout << '\n';
}
        
int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(cin>>n && n){
        for (int i = 0; i <n; i++) cin >> valores[i];   
        solve();
    }
    return 0;
}
