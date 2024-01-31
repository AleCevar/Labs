/*
Para una carrera atlética se necesitan n medallas, pero el fabricante sólo vende paquetes de {a1, a2, a3 . . . ak} medallas.
Cada paquete con un costo {p1, p2, p3 . . . pk}, siendo A el conjunto de los paquetes de medallas y siendo P el conjunto de 
los precios (ordenados respectivamente), ¿Cuál sería el mínimo precio que se puede pagar por conjuntos 
de medallas que sean mayores o iguales que n?
*/
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
