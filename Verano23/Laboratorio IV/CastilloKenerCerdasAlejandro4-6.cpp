#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Prom 1.20 The Monkey and the Oiled Bamboo VJudge
// https://vjudge.net/problem/UVA-12032
// Complejidad: O(n) por cada paso donde n es la cantidad de elementos
// https://vjudge.net/solution/47749947

bool probar(int k, int mayor, vi &nums){
    if(k<mayor) return false;
    int i=0;
    while(i<nums.size()){
        if(k<nums[i]) return false;
        if(k==nums[i]) k--;
        i++;
    }    
    return true;
}

int solve(int n){
    int inf=0, sup=0;
    int m, mayor=0;
    vi num(n);
    for (int i = 0; i <n; i++)
    {
        cin>>m;
        num[i]=m-inf;
        mayor=max(mayor, num[i]);
        inf=m;
    }
    if(probar(mayor, mayor, num)) return mayor;
    return mayor+1;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t, n, cont=1;
    cin>>t;
    while(t--){
        cin>>n;
        cout<<"Case "<<cont<<": ";
        cout<<solve(n)<<'\n';
        cont++;
    }
    return 0;
}
