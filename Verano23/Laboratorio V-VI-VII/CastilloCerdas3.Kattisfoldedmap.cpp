// Problema 5 kattis Folded Map (ACEPTADO)
// https://open.kattis.com/problems/foldedmap
// https://open.kattis.com/submissions/12554099
// Complejidad: $O(R \times C)$

#include <iostream>
using namespace std;

int R,C,L,A,iF = -1,jF = -1;
char mapa[1002][1002];
int acomu[1002][1002];

int cantLeft(int x, int y){
    int i= (x-L<=0)? 0: x-L;
    int j=(y-A<=0)? 0: y-A;
    if(y>C) y=C;
    if(x>R) x=R;
    return acomu[x][y]-acomu[i][y]-acomu[x][j]+acomu[i][j];
}


int contar(int x, int y){
    int contCuadrados=0;
    int i, j;
    for(i=x; i<R; i+=L){
        for(j=y; j<C; j+=A){
            if(cantLeft(i, j)!=0) contCuadrados++;
        }
        if(cantLeft(i, j)!=0) contCuadrados++;
    }
    for(j=y; j<C; j+=A){
        if(cantLeft(i, j)!=0) contCuadrados++;
    }
    if(cantLeft(i, j)!=0) contCuadrados++;
    return contCuadrados;
}

int solve(){
    int minC = 10000000,j,i;
    for(j=1; j <= L; j++){
        for(i=1; i <= A; i++){
            minC = min(minC,contar(j, i));
        }
    }
    return minC;
}


int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(cin >> R >> C >> L >> A){
        for(int i = 1; i <=R; i++){
            for(int j = 1; j <= C; j++){
                cin >> mapa[i][j];
                if(mapa[i][j] == 'X'){
                    if(iF == -1) iF = i, jF = j;
                    acomu[i][j] = acomu[i][j-1] + acomu[i-1][j] - acomu[i-1][j-1] + 1;
                }
                else acomu[i][j] = acomu[i][j-1] + acomu[i-1][j] - acomu[i-1][j-1];
            }
        }
        cout << solve() << '\n';
    }
    return 0;
}
