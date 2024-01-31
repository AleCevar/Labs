#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

//Prom 1.7 Room Painting Kattis
// https://open.kattis.com/submissions/12527949
// $O(m \times log(n))$
// https://open.kattis.com/submissions/12527949

int busq(int num, int n, vi &array){
    int inf=0, sup=n;
    int m=(inf+sup)/2;
    while(inf+1<sup){
        if(array[m]==num) return array[m];
        if(array[m]>num) sup=m;
        else inf=m;
        m=(inf+sup)/2;
    }
    return array[sup];
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, num;
    cin>>n>>m;
    vi tienda(n);
    long long total=0, necesario=0;
    for (int i = 0; i <n; i++)
    {
        cin>>tienda[i];
    }
    sort(tienda.begin(), tienda.end());
    for (int i = 0; i <m; i++)
    {
        cin>>num;
        total+=busq(num, n, tienda);
        necesario+=num;
    }
    cout<<total-necesario<<'\n';
    return 0;
}
