// Problema 7 kattis Selling Spatulas
// (No lo acepta y no sabemos por qué)
// https://open.kattis.com/problems/sellingspatulas
// https://open.kattis.com/submissions/12554185
// Complejidad: O(n)

#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld costo=0.08;
const ld oo = -10000000;
int n;
ld minutes[1005];
ld profit[1005];
ld memo[1005][3];

void solve(){
    memo[n][0]= 0, memo[n][1] = oo; 
    for(int i = n-1; i>=0; i--){
        memo[i][0]= max(max(memo[i+1][0], profit[i]-costo),
            memo[i+1][1]+profit[i]- (costo*(minutes[i+1]- minutes[i])));
        memo[i][1]= max(profit[i]-costo,memo[i+1][1]+profit[i]- ((costo*(minutes[i+1]-minutes[i]))+0.0));
    }    
}

void imprimir(){
    if(memo[0][0]==0){
        printf("%s\n","no profit"); return;
    }
    printf("%.2Lf ",memo[0][0]);
    int i, j=-1;
    int start=0, end=minutes[n-1];
    for(i = 0; i < n; i++){
        if(memo[i][0] == memo[i][1] && j == -1) j=minutes[i];
        if(memo[i][1] == profit[i]-costo && j > -1) {
            end=minutes[i];
            break;
        }
    }
    start=j;
    printf("%d %d\n", (int) start, (int) end);
}

int main(int argc, char const *argv[]){
    cin.tie(0);
    while(cin >> n && n){
        int i;
        for (i = 0; i <n; i++){
            cin >> minutes[i]>>profit[i];
        }
        minutes[i] = minutes[i-1];
        solve();
        imprimir(); 
    }
}

/*
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

// Kattis Selling Spatulas (Aceptado)
// Otra solución que sí la acepta, pero con diferente enfoque
// https://open.kattis.com/problems/sellingspatulas
// https://open.kattis.com/submissions/12552982
// Complejidad: O(n) por cada caso

ld costo=0.08;
int n;
ld minutes[1500];

int main(int argc, char const *argv[]){
    int num;
    ld profit;
    while(cin >> n && n){
        int i;
        for(int i = 0; i < 1500;i++) minutes[i] = -costo;
        for (i = 0; i <n; i++){
            cin >> num>>profit;
            minutes[num]+=profit;
        }  
        int start=0, end=1, actual=0;
        ld mayor=0.0, rango=0.0;
        for(int i=0; i<=num; i++){
            rango+=minutes[i];
            //if(rango==mayor && (i-actual)<(end-start)) end=i, start=actual; 
            if(rango>mayor) mayor=rango, end=i, start=actual;
            if(rango<0) rango=0, actual=i+1;
        }
        if(mayor==0) printf("no profit\n");
        else printf("%.2Lf %d %d\n", mayor, start, end);
    }
}

*/
