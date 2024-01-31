#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Prom 1.9 Popes VJudge
// https://vjudge.net/problem/UVA-957
// Complejidad: $O(n \times log(n))$ por cada caso
// https://vjudge.net/solution/47751113

int buscar(int x, vi &nums){
    int inf=0, sup=nums.size();
    int m;
    while(inf+1<sup){
        m=(inf+sup)/2;
        if(nums[m]>x) sup=m;
        else inf=m;
    }
    return inf;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int y, p, tam;
    while(cin>>y>>p){
        vi num(p);
        int a, b, ind;
        tam=0;
        for (int i = 0; i<p; i++)
        {
            cin>>num[i];
        }
        for (int i = 0; i<p; i++)
        {
            ind=buscar(num[i]+y-1, num);
            if(tam<ind-i+1) tam=ind-i+1, a=i, b=ind;
        }
        cout<<tam<<' '<<num[a]<<' '<<num[b]<<'\n';
    }
    return 0;
}
