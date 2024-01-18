#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
#define clear(a,b) (a&~(1<<b))
#define test(a,b) (a&(1<<b))

int c,e,r,b,corre = 0;
vi cantC,solu,posi;

void imprimir(){
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
void validar(){
    if(r == corre) for(int i = 0; i < solu.size();i++) posi[solu[i]]= clear(posi[solu[i]],i);
    for(int i = 0; i < posi.size(); i++)
        if(cantC[posi[i]] && cantBits(posi[i]) == cantC[posi[i]]) corre+=cantC[i],posi[i]=0;
}
void permutar(){
    vi pas(e,-1);
    for(int i = 0;i < solu.size();i++){
        if(!posi[solu[i]]) continue;
        for(int j = 0; j < solu.size(); j++){
            if(test(posi[solu[i]],j) && test(posi[solu[j]],i )  && solu[i] != solu[j] && pas[j] != solu[i]){ 
                swap(solu[i],solu[j]);
                pas[i] = solu[j];
                pas[j] = solu[i];
                break;
            }
        }
    }
}
void descarte(){for(int i = 0; i < solu.size(); i++) cantC[solu[i]] = 0;}
int rando(int mod, int a){return rand()%mod+a;}

int buscarC(){ 
    solu.assign(0,0);
    for(int i = 1; i <= c;i++){
        if(cantC[i] != 0){
            for(int j = 0; j < e; j++)cout << i << ' ';
            cout << '\n';
            cin >> r >> b;
            if(r==e) return 1;
            cantC[i]+=r;
            while(r--) solu.push_back(i);
            if(solu.size() == e) break;
        }
    }
    imprimir();
    validar();
    return 0;
}

int iniciar(){
    int d = 3;
    while(d--){
        for(int i = 0; i < solu.size();i++){
            while(true){
                int a = rando(c,1);
                if(cantC[a] != 0 && test(posi[a],i)){
                    solu[i] = a;break;
                }
            }
        }
        imprimir();
        if(b+r == 0) descarte();
        if(r==0) for(int i = 0; i < solu.size();i++) posi[solu[i]]= clear(posi[solu[i]],i);
        if(r+b == e){
            if(r==e) return 1;
            if(b==e) descarte();
            for(int i = 0; i < solu.size(); i++) cantC[solu[i]];
            d = 8;
            break;
        }   
    }
    if(d == 8) return 0;
    return buscarC();
}

void solve(){
    int corre = 0;
    solu.assign(e,0);
    cantC.assign(c+1,-1);
    posi.assign(c+1,(1<<e)-1);
    if(iniciar())return;
    while(r!=e){
        permutar();
        imprimir();
        validar();
    }
}

int main(){
    cin >> c >> e;
    srand(static_cast<unsigned int>(time(nullptr)));
    solve();
    return 0;
}