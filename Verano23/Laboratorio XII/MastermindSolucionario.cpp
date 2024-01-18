#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,r=0,b=0,n = 6, c=8;
    vector<int> ar,res = {4,4,2,1,4,7},b1(c+1,0),b2(c+1,0);
    for(int i = 0; i < n; i++){
        cin >> a;
        ar.push_back(a);
        b1[res[i]]++;
        b2[ar[i]]++;
    }
    for(int i = 1; i < c; i++) 
        if(b1[i]>b2[i]) b+=b2[i];
        else b+=b1[i];
    for(int i = 0; i < n; i++) 
        if(res[i] == ar[i]){ 
            r++;
            b--;
    }
    cout << r << ' ' << b << '\n';
    return 0;
}

/*
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
*/