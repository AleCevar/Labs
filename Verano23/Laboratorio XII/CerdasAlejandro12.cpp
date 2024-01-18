//Complejidad: $O(colores \times espacios)$

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define clear(a,b) (a&~(1<<b))
#define test(a,b) (a&(1<<b))

int c,e,r,b,menor = 1;
vi cantC;

void imprimir(vi solu){
    for(int i = 0; i < solu.size();i++) cout << solu[i] << ' ';
    cout << '\n';
    cin >> r >> b;
}

int iniciar(){
    int cue = 0;
    cantC.assign(c+1,0);
    for(int i = 1; i <= c; i++){
        for(int j = 0; j < e; j++) cout << i << ' ';
        cout << '\n';
        cin >> r >> b;
        if(r == e) return 1;
        cantC[i] += r;
        cue += r;
        menor = (cantC[menor] < cantC[i] && cantC[i])? i : menor;
        if(cue == e) return 0; 
    }
    return 0;
}

void solve(){
    vi solu(e,menor);
    int cue = cantC[menor], msk = (1 << e)-1;
    for(int i = 1; i <= c; i++){
        if(i == menor) continue;
        for(int j = 0, n = cantC[i]; j < e && n; j++){
            if(n == e-j){
                for(int k = j; k < e; k++){
                    msk = clear(msk,j);
                    solu[k] = i;
                    cue++;
                }
                break;
            } 
            if(test(msk,j)){
                solu[j] = i;
                imprimir(solu);
                if(r == e) return;
                if(r == cue){
                    solu[j] = menor;
                }
                if(r < cue){
                    solu[j] = menor;
                    msk = clear(msk,j);
                }
                if(r > cue){
                    msk = clear(msk,j);
                    n--;
                    cue++;
                }
            }   
        }
    }
    if(r!=e) imprimir(solu);
}

int main(){
    cin >> c >> e;
    if(!iniciar())solve();
    return 0;
}