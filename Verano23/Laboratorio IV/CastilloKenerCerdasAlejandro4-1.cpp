#include <stdio.h>
using namespace std;
typedef long double ld;

// Prom 2.11 Jewerly Box VJudge
// https://vjudge.net/problem/Kattis-jewelrybox
// Complejidad: $O(log(min(x,y)))$
// https://vjudge.net/solution/47772091

ld min(ld x, ld y){
    return (x<y)? x:y;
}

ld buscar(ld x, ld y){
    ld error=0.0000001;
    ld m1;
    ld m2;
    ld l=0, r=min(x, y)/2;
    while(l+error<r){
        m1=l+(r-l)/3, m2=r-(r-l)/3;
        ((x-2*m1)*(y-2*m1)*m1 < (x-2*m2)*(y-2*m2)*m2)? l=m1:r=m2;
    }
    return (x-2*l)*(y-2*l)*l;
}

int main(int argc, char const *argv[])
{
    int t;
    ld x, y;
    scanf("%d\n", &t);
    while(t--){
        scanf("%Lf %Lf\n", &x, &y);
        printf("%Lf\n", buscar(x, y));
    }
    return 0;
}
