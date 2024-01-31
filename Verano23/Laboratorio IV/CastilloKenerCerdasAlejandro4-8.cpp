#include <iostream>
using namespace std;

// Prom 1.5 Firefly Kattis
// https://open.kattis.com/problems/firefly
// Complejidad: O(h)
// https://open.kattis.com/submissions/12527368

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, h, num;
    cin>>n>>h;
    int abajo[h+1];
    int arriba[h+1];
    for (int i = 0; i <=h; i++)
    {
        abajo[i]=arriba[i]=0;
    }
    for (int i = 1; i <=n; i++)
    {
        cin>>num;
        if(i%2) abajo[num]++;
        else arriba[h-num]++;
    }
    for (int i = 1; i <=h; i++)
    {
        abajo[i]+=abajo[i-1];
        arriba[i]+=arriba[i-1];
    }
    int res=100000000, cont=1, cant;
    for (int i = 1; i <=h; i++)
    {
        cant=n/2-abajo[i-1] + arriba[i-1];
        if(cant==res) cont++;
        else if(cant<res) res=cant, cont=1;
    }
    cout<<res<<' '<<cont<<'\n';
    return 0;
}
