//Kener Castillo y Alejandro Cerdas
//Programacion Dinamica

#pragma once

#include <bits/stdc++.h>
using namespace std;
 
typedef list<int> li;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;

extern mutex terminal;
int VDP,EDP; 
vector<vi> matDP;

int accederDP(int a, int b){return matDP[max(a,b)][min(a,b)];}

vector<vll> memo;

ll dp(int nodo, ll msk){
    if(msk==(1<<VDP)-1) return memo[nodo][msk] = (accederDP(nodo,0) != -1)? accederDP(0,nodo):INT32_MAX;
    if(memo[nodo][msk] != -1) return memo[nodo][msk];
    ll menor=INT32_MAX;
    for(int i = 0; i < VDP; i++)
        if(accederDP(i,nodo) != -1 && !(msk&(1<<i)))
            menor = min(menor,dp(i, msk|(1<<i))+accederDP(i,nodo));
    return memo[nodo][msk]=menor;
}

void tspDynamic(int v, int e, vector<vi> &m){
    VDP=v, EDP=e;
    matDP=m;
    memo.assign(VDP,vll(1<<VDP,-1));
    ll costo = dp(0,1), msk=1;
    int nodo=0;  
    li cam;
    cam.push_back(0);
    for(int n=1; n<VDP; n++){
        for(int i=0; i<VDP; i++){
            if(!(msk&(1<<i)) && memo[i][msk|(1<<i)]+accederDP(nodo, i)==costo){
                costo-=accederDP(nodo, i);
                msk|=(1<<i); nodo=i;
                cam.push_back(i);
                break;
            } 
        }
    } cam.push_back(0);
    lock_guard<mutex> lock(terminal);
    cout << "DP: " << cam.front();
    li::iterator it=cam.begin();
    it++;
    for(; it!=cam.end(); it++) cout<<','<<*it;
    cout<<" Costo: " << memo[0][1] << '\n';
}

