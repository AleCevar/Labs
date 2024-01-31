//Dada una figura se debe indicar cuantos lados tiene.

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;

int fila,columna;
int matriz[200][200];
int visited[200][200];
int af[] = {-1,0,1,0};
int ac[] = {0,-1,0,1};
int lados = 0;

bool verificar(int a, int b){
    return a >= 0 && a < fila && b < columna && b >=0;
}

void calcularMsk(int a, int b){
    if(matriz[a][b] != 32) return;
    matriz[a][b] = 0;
    for(int i = 0; i < 4; i++){
        if(!verificar(a+af[i],b+ac[i])){
            matriz[a][b] |= (1 << i);
        } else if(matriz[a+af[i]][b+ac[i]] == -1){
            matriz[a][b] |= (1 << i);
        }
    }
}

int bits(int num){
    int cuenta = 0;
    while(num){
        if(num & 1) cuenta++; num>>=1;
    }
    return cuenta;
}

void calcularLados(pi tata){
    stack<pi> pila;
    pila.push(tata);
    while(!pila.empty()){
        pi p = pila.top();pila.pop();
        if(!visited[p.first][p.second]){ 
            visited[p.first][p.second]++;
            calcularMsk(p.first,p.second);
            lados += bits(matriz[p.first][p.second]);
            for(int i = 0; i < 4; i++){
                int a = p.first + af[i], b = p.second + ac[i];
                if(verificar(a,b) && matriz[a][b] != -1){
                    if(visited[a][b]){
                        int msk = matriz[p.first][p.second] & matriz[a][b];
                        lados -= bits(msk);
                    }else{pila.push({a,b});}
                }
            }
        }    
    }
}


int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int x,y;
    char e;
    cin >> fila >> columna;
    for(int i = 0; i<fila; i++){
        for(int j = 0; j < columna; j++){
            cin >> e;
            if(e == '#'){
                x = i; y = j;
                matriz[i][j] = 32;
            }else{
                matriz[i][j] = -1;
            }
            visited[i][j] = 0;
        }
    }
    pi p = {x,y};
    calcularLados(p);
    cout << lados << "\n";    
    return 0;
}
