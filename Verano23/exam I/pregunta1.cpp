#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

bool solve(vi ar, int n){
    vi aco(ar.size()+1);
    aco[0] = 0; aco[1] = ar[0];
    for(int i = 1; i < ar.size(); i++)
        aco[i+1] = aco[i] + ar[i];
    int j = 0,i = 1;
    while(j < i && i < aco.size()){
        if(aco[i]-aco[j] == n) return true;
        if(aco[i]-aco[j] < n) i++;
        if(aco[i]-aco[j] > n) j++;
    }
    return false;
}
