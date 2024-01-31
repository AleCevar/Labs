//Alejandro Cerdas y Kener Castillo
//BackTracking

#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef list<int> li;

int VBT,EBT;
vector<vi> matBT;
extern mutex terminal;

int accederBT(int a, int b){return matBT[max(a,b)][min(a,b)];}


class tsp{
public:
    ll msk;
    li camino;
    ll costo;
    int nodo;

    tsp(int n){
        msk=costo=0;
        nodo=n;
    }
};

void imprimir(li cam, ll cost){
    lock_guard<mutex> lock(terminal);
    cout << "Backtracking: " << cam.front();
    li::iterator it=cam.begin();
    it++;
    for(; it!=cam.end(); it++) cout<<','<<*it;
    cout<<" Costo: " << cost << '\n';
}

void backTrack(int v, int e, vector<vi> &m){
    VBT = v;
    EBT = e;
    matBT = m; 
    stack<tsp> pila;
    ll menor=INT32_MAX;
    li answer;
    tsp start(0);
    start.camino.push_back(0);
    start.msk = 1;
    pila.push(start);
    while(!pila.empty()){
        tsp node=pila.top(); pila.pop();
        if(node.camino.size()==VBT && accederBT(node.nodo,node.camino.front())!=-1){
            if(node.costo + accederBT(node.nodo,node.camino.front())<menor){
                menor=node.costo+ accederBT(node.nodo,node.camino.front());
                answer=node.camino;
                answer.push_back(node.camino.front());
            }
            continue;
        }
        for(int i=0; i<VBT; i++){
            if(accederBT(node.nodo, i)!=-1 && !(node.msk&(1<<i))){
                tsp hijo(i);
                hijo.camino=node.camino;
                hijo.camino.push_back(i);
                hijo.costo = node.costo + accederBT(node.nodo,i);
                hijo.msk=node.msk|(1<<i);
                hijo.nodo=i;
                pila.push(hijo);
            }
        }
    }
    imprimir(answer, menor);    
}



