#include <iostream>
using namespace std;

// Prom 1.6 Out of sorts Kattis
// https://open.kattis.com/problems/outofsorts
// $O(n \times log(n))$
// https://open.kattis.com/submissions/12527790

int busq(long num, int n, long array[]){
    int inf=1, sup=n;
    int m=(inf+sup)/2;
    while(inf<sup){
        if(array[m]==num) return m;
        if(array[m]>num) sup=m-1;
        else inf=m+1;
        m=(inf+sup)/2;
    }
    return inf;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    long n;
    long m, a, c, x0;
    cin>>n>>m>>a>>c>>x0;
    long sec[n+1];
    sec[0]=x0;
    for (int i = 1; i <=n; i++)
    {
        sec[i]=(a*sec[i-1]+c)%m;
    }
    int cont=0;
    for (int i = 1; i <=n; i++)
    {
        m=busq(sec[i], n, sec);
        if(i==m) cont++;
    }
    cout<<cont<<'\n';
    return 0;
}
