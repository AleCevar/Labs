// Problema 6 Kattis Alice in the Digital World (ACEPTADO)
// https://open.kattis.com/problems/alicedigital
// https://open.kattis.com/submissions/12551006
// Complejidad: O(n);

#include <iostream>
using namespace std;

int array[100005];
int acomu[100005];
int acomuI[100005];

int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t, n, m, j; 
    int mayor, left;
    cin>>t;
    while(t--){        
        cin>>n>>m;
        acomu[0]=0;
        acomuI[n+1]=0;
        for (int i = 1; i <=n; i++){
            cin>>array[i];
            if(array[i] <= m) acomu[i] = 0;
            else acomu[i] = array[i] + acomu[i-1];
        }
        for(int i = n; i>=1; i--){
            if(array[i] <= m) acomuI[i] = 0;
            else acomuI[i] = array[i] + acomuI[i+1];
        }
        mayor=m;
        for(int i = 1; i <=n; i++){
            if(array[i]==m){
                mayor=max(mayor, acomu[i-1]+m+acomuI[i+1]);
            }
        }
        cout << mayor << '\n';
    }
    return 0;
}