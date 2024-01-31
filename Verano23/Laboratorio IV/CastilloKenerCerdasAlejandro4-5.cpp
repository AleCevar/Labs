#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Prom 1.12 Where is the marbel? Vjudge
// https://vjudge.net/problem/UVA-10474
// Complejidad: $O(n \times log(n))$ por cada caso 
// https://vjudge.net/solution/47748715

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q, m, ind;
    int cont=1;
    while(true){
        cin>>n>>q;
        if(!n && !q) return 0;
        vi num(n);
        for (int i = 0; i <n; i++)
        {
            cin>>num[i];
        }
        sort(num.begin(), num.end());
        map<int, int> mapa;
        for (int i = 0; i <n; i++)
        {
            if(mapa.find(num[i])==mapa.end()) mapa[num[i]]=i+1;
        }
        cout<<"CASE# "<<cont<<":\n";
        while(q--){
            cin>>m;
            if(mapa.find(m)==mapa.end()) cout<<m<<" not found\n";
            else cout<<m<<" found at "<<mapa[m]<<'\n';
        }
        cont++;
    }
    return 0;
}
