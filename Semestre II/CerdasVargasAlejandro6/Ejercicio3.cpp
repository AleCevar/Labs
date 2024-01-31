// En el metro de Nueva York existen varias paradas ubicadas en distintos puntos,
//se desea conocer el mínimo tiempo para llegar de una parada-i a una parada-j.

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow
const int MAX_V = 450; // if |V| > 450, you cannot use Floyd Washall's
int V;
int AM[MAX_V][MAX_V]; // it is better to store a big array in the heap

void floydWharsall(){
    for (int k = 1; k <= V; ++k)                    // loop order is k->u->v
        for (int u = 1; u <= V; ++u)
            for (int v = 1; v <= V; ++v)
                AM[u][v] = min(AM[u][v], AM[u][k]+AM[k][v]);
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int E,C,x,y; cin >> V >> E >> C;
    for (int u = 0; u <= V; ++u) {
        for (int v = 0; v <= V; ++v)
        AM[u][v] = INF;
        AM[u][u] = 0;
    }
    for (int i = 0; i < E; ++i) {
        int u, v, w; cin >> u >> v >> w;
        AM[u][v] = w;                                
        AM[v][u] = w;
    }
    floydWharsall();
    for(int i = 0; i < C; i++){
        cin >> x >> y;
        cout << AM[x][y] << "\n";
    }
    return 0;
}
