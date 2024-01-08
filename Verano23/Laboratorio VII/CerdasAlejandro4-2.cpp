//$O(\frac{n!}{(n-p)!})$ donde n = 26-alfa.size() y p = cantidad de letras diferentes a cambiar

#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vc;
typedef tuple<vc,int,int> vcii;

string alfa, ora = "", s1;

void imprimir(vc ar){
    for(int i = 0; i < ar.size(); i++){
        cout << ar[i] << ' ';
    }
    cout << '\n';
}

int convertirMinus(int n){return n += (1 << 5);}
int convertirMayus(int n){return n -= (1 << 5);}
int validar(int n,vc ar){return (ar[n] != '.') && (ar[n] != '+') && (ar[n] != '-');}

vc formar(){
    vc ar(26,'+');
    for(int i = 0; i < ora.size(); i++){
        if(ora[i] >= 97 && ora[i] <= 122) ar[ora[i]-'a'] = '-';
        if(ora[i] >= 65 && ora[i] <= 90) ar[convertirMinus(ora[i])-'a'] = '-';
    }    
    for(int i = 0; i < alfa.size(); i+=2) ar[alfa[i]-'a'] = '.';
    return ar;
}

void print(vc ar){
    for(int i = 0; i < ora.size(); i++){
        if((ora[i] >= 97 && ora[i] <= 122) && validar(ora[i]-'a',ar)){
            cout << ar[ora[i]-'a'];
        } 
        else{ 
            if((ora[i]>= 65 && ora[i] <= 90) && validar(convertirMinus(ora[i])-'a',ar)){
                cout << (char)convertirMayus(ar[convertirMinus(ora[i])-'a']);
            }
            else cout << ora[i];
        }  
    }
}

void solve(){
    stack<vcii> pila;
    pila.push({formar(),0,0});
    while(!pila.empty()){
        vcii p = pila.top(); pila.pop();
        vc ar = get<0>(p); int pos = get<2>(p), msk = get<1>(p); 
        if(pos >= 26){
            print(ar);   
            continue; 
        }
        if(ar[pos] == '.' || ar[pos] == '+'){
            pila.push({ar,msk,pos+1});
            continue;
        }
        for(int i = 0; i < 26; i++){
            if(ar[i] != '.' && !(msk&(1<<i))){
                vc co = ar;
                co[pos] = i+'a';
                pila.push({co,msk+(1<<i),pos+1});
            }   
        }
    }
}

int main(){
    getline(cin,alfa);
    while(getline(cin,s1)){
        ora+=s1+'\n';
    }
    solve();
    return 0;
}