#include <iostream>
using namespace std;

// Prom 1.11 The Stern Brocot Number System Vjudge
// https://vjudge.net/problem/UVA-10077
// Complejidad: $O(log(a \times b))$
// https://vjudge.net/solution/47712531

void solve(long n, long d){
    long left[]={0, 1};
    long right[]={1, 0};
    long m[]={1, 1};
    while(true){
        if(m[0]==n && m[1]==d) return;
        if((n*m[1])<(d*m[0])){
            cout<<'L';
            right[0]=m[0], right[1]=m[1];
        }
        else{
            cout<<'R';
            left[0]=m[0], left[1]=m[1];
        }
        m[0]=left[0]+right[0];
        m[1]=left[1]+right[1];
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    long num, den;
    while(true){
        cin>>num>>den;
        if(num==1 && den==1) return 0;
        solve(num, den);
        cout<<'\n';
    }
    return 0;
}
