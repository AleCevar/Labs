//Kener Castillo y Alejandro Cerdas
//Solución al clásico problema de TSP, mediante dinámica, genética y backtracking. Todos corriendo de forma paralela.

#include <bits/stdc++.h>
#include "castillocerdasvargasBT.cpp"
#include "castillocerdasvargasDP.cpp"
#include "castillocerdasvargasGN.cpp"

using namespace std;

typedef vector<int> vi;

mutex terminal;

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    int V,E;
    cin >> V >> E;    
    vector<vi> mat(V,vi(V,-1));
    for(int i = 0; i < E;i++){
        int u,v,w; cin >> u >> v >> w;
        mat[max(u,v)][min(u,v)] = w;
    }
    TSP solve(V,E,mat);
    thread hilo1(backTrack,V,E,ref(mat));
    thread hilo2(crear,V,E,ref(mat));
    thread hilo3(tspDynamic,V,E,ref(mat));
    hilo1.join();
    hilo2.join();
    hilo3.join();
    return 0;
}
