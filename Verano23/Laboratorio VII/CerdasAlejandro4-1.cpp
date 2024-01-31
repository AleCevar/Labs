//Dado tres string : s1,s2,s3, se debe cumplir que s1+s2=s3. Se debe buscar los valores que cumplan con esto.
//$O(\frac{10!}{(10-n)!})$ siendo n la cantidad de letras diferentes

#include <bits/stdc++.h>
using namespace std;

#define test(a,b) (a&(1<<b))
typedef vector<int> vi;
typedef tuple<vi,int,int> viii;

string s1,s2,s3,i1,i2;

void print(vi a){
    for(int i = 0; i < 26; i++){
        cout << a[i];
    }
    cout << '\n';
}

void probar(vi ar){
    int carry = 0, n = s3.size()-1,i,j;
    if(s1.size() > s2.size()){
        i = s1.size()-1; j = s2.size()-1;
        i1 = s1; i2 = s2;
    }
    else{
        i = s2.size()-1; j = s1.size()-1;
        i1 = s2; i2 = s1;
    }
    while(i>=0||j>=0){
        int a = (i < 0) ? 0 : ar[i1[i]-'A'];
        int b = (j < 0) ? 0 : ar[i2[j]-'A'];
        int res = a + b + carry;
        carry = 0;
        if(res > 9) carry = 1 , res %= 10;
        if(n<0 || res != ar[s3[n]-'A']) return;
        i--;j--;n--;
    }
    if(carry && ar[s3[n]-'A'] != 1) return;
    if(max(s1.size(),s2.size())+carry < s3.size()) return;
    for(int i = 0; i < s1.size(); i++) cout << ar[s1[i]-'A'];
    cout << '\n';
    for(int i = 0; i < s2.size(); i++) cout << ar[s2[i]-'A'];
    cout << '\n';
    for(int i = 0; i < s3.size(); i++) cout << ar[s3[i]-'A'];
    cout << "\n\n";
}

vi formar(){
    vi ar(26,-2);
    for(int i = 0 ;i < s1.size(); i++) ar[s1[i]-'A'] = -1;
    for(int i = 0 ;i < s2.size(); i++) ar[s2[i]-'A'] = -1;
    for(int i = 0 ;i < s3.size(); i++) ar[s3[i]-'A'] = -1;
    return ar;
}

void solve(){
    stack<viii> pila;
    pila.push({formar(),0,0});
    while(!pila.empty()){
        viii t = pila.top(); pila.pop();
        if(get<2>(t) >= 26){
            probar(get<0>(t));
            continue;
        } 
        vi ar = get<0>(t);
        if(ar[get<2>(t)] == -2) pila.push({ar,get<1>(t),get<2>(t)+1}); 
        else {
            vi ar = get<0>(t); int msk = get<1>(t), pos = get<2>(t),j = 0;
            if(pos+'A' == s1[0] || pos+'A' == s2[0]) j = 1;
            for(int i = 9;j<=i;i--){
                if(!test(msk,i)){
                    vi ve = ar;
                    ve[pos] = i;
                    pila.push({ve,msk+ (1<<i),pos+1});
                }
            }
        }
    }
}

int main(){
    cin >> s1 >> s2 >> s3;
    solve();
    return 0;
}
