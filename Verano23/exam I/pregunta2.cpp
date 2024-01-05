#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<vi> memo;
vi packsG;
vi preciosG;
int obje;
const int oo = 100000000;

int solve(int pos, int res){
    if(res >= obje) return 0;
    if(pos == packsG.size()) return oo;   
    if(memo[pos][res]) return memo[pos][res];
    return memo[pos][res] = min(solve(pos+1,res),solve(pos,res+packsG[pos]) + preciosG[pos]);
}

int minCosto(int n,vi packs, vi precios){
    memo.assign(packs.size(),vi(n));
    obje = n;
    packsG = packs;
    preciosG = precios;
    return solve(0,0);
}