//Complejidad: $O(n)$

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int n,k;

int solve(vi ar){
    vi aco(ar.size()+1); aco[0] = 0;
    int i = 0,j = k, cont = 0;
    for(int m = 1; m <= k; m++) aco[m] = aco[m-1] + ar[m];
    while(j < ar.size()){
        if(aco[j]-aco[i] == k){
            aco[j]--;
            cont++;
        }
        j++;i++;
        aco[j] = aco[j-1] + ar[j]; 
    }
    return cont;
}

int main(){
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n >> k;
        vi ar(n+1); ar[0] = 0;
        for(int j = 1; j <= n; j++)cin >> ar[j];
        cout << solve(ar) << '\n';
    }
    return 0;
}