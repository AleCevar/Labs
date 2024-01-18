#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define clear(a,b) (a&~(1<<b))
#define test(a,b) (a&(1<<b))
#define ult (ar.size()-1)

int c,e,r,b,god=0;
vi posi,cantC,solu;

void imprimir(vi solu){
    for(int i = 0; i < solu.size();i++) cout << solu[i] << ' ';
    cout << '\n';
    cin >> r >> b;
}

int cantBits(int n){
    int res = 0;
    while(n){
        res += (n&1);
        n/=2;
    }
    return res;
}

void cambios(vi ar){
    if(r <= god) 
        for(int j = 0; j < ar.size(); j++) 
            if(ar[j] != solu[j]) posi[ar[j]] = clear(posi[ar[j]],j);
    for(int i = 1; i < posi.size(); i++) 
        if(cantBits(posi[i]) == cantC[i]){
            for(int j = 0; j < e; j++) if(test(posi[i],j)) solu[j] = i,god+=cantC[i];
    }
    for(int i = 1; posi[i]; i++) cout << posi[i] << ' ';
    cout << '\n';
}


int verificar(vi ar){
    if(!test(posi[ar[ult]],ult)) return 0;
    int cue = 0;
    for(int i = 0; i < ar.size(); i++)
        if(ar[i] == ar[ult]) cue++;
    //cout << cantC[ar[ult]] << '\n';
    if(cue > cantC[ar[ult]]) return 0;
    return 1;
}

int buscar(){
    int cue = 0;
    int i;
    for(i = 1; i <= c;i++){
        if(cantC[i] > -1){
            for(int j = 0; j < e; j++)cout << i << ' ';
            cout << '\n';
            cin >> r >> b;
            if(r==e) return 1;
            cantC[i]+=r;
            cue +=r;
            if(r == 0) cantC[i] = -1;
            if(cue == e) break;
        }
    }
    for(i++;i <= c; i++) cantC[i] = -1;
    return 0;
}

int iniciar(){
    posi.assign(c+1,(1<<e)-1);
    cantC.assign(c+1,0);
    solu.assign(e,0);
    vi ar(e);
    for(int i = 0; i < 2; i++){    
        for(int j = 0; j < ar.size(); j++){
            while(true){
                int a = (rand()%c)+1;
                if(test(posi[a],i)){
                    ar[j] = a;
                    break;
                }
            }
        }    
        imprimir(ar);
        if(r==e) return 1;
        cambios(ar);
        if(!b && !r) for(int j = 0; j < ar.size(); j++) cantC[ar[j]] = -1;
        if(r+b == e){
            for(int j = 0;j < ar.size(); j++) cantC[ar[j]]++;
            return 0;
        }
    }
    return buscar();
}

void solve(){
    stack<vi> pila;
    for(int i = 1; i <= c; i++) pila.push({i});
    while(!pila.empty()){
        vi ar = pila.top();pila.pop();
        if(!verificar(ar)) continue;
        if(ar.size() == e) {
            imprimir(ar);
            if(r == e) return;
            cambios(ar);
        }
        else{
            for(int i = 1; i <= c; i++){
                vi er = ar;
                er.push_back(i);
                pila.push(er);
            }
        }
    }
}

int main(){
    cin >> c >> e;
    srand(static_cast<unsigned int>(time(nullptr)));
    int res = iniciar();
    if(!res) solve();
    return 0;
}