/*
Link debe perseguir a Bolokin por el reino de Hyrule, pero bolokin solo se mueve a cuidades con un centaleón.
Determine la cantidad de centaleones que debe derrotar Link hasta llegar a Bolokin.
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int,int,int> ti;

class Grafo{
    public:
        int mayor;
        int n;
        int visitados;
        vector<vi> adyancencia, excentricidad;

        Grafo(int num){
            n = num;
            visitados = 0;
            adyancencia.assign(n+1,vector<int>(0));
            excentricidad.assign(n+1,vector<int>(n+1,1));
            mayor = 0;
        }

        void unir(int n1, int n2){
            adyancencia[n1].push_back(n2);
            adyancencia[n2].push_back(n1);
        }

        void eccentricity(int n1){
            int n2,exce;
            queue<ti> cola;
            visitados |= 1 << n1;
            cola.push({n1,visitados,1});
            while(!cola.empty()){
                ti trio = cola.front();
                n2 = get<0>(trio);
                visitados = get<1>(trio);
                exce = get<2>(trio);
                cola.pop();
                for(int i = 0; i < adyancencia[n2].size(); i++){
                    int adya = adyancencia[n2][i];
                    if(!((visitados >> adya) & 1)){
                        cola.push({adya,visitados | (1 << adya), exce+1});
                    }
                }
            }
            if(exce > mayor) mayor = exce; 
        }

        void calcularExcentricidades(){
            for(int i = 1; i < n+1; i++){
                eccentricity(i);
                if(mayor == n) return;
                visitados = 0;
            }
        }
};

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int nodos,uniones,x,y;
    cin >> nodos >> uniones;
    Grafo * g = new Grafo(nodos);
    for(int i = 0; i < uniones; i++){
        cin >> x >> y;
        g->unir(x,y);
    }
    g->calcularExcentricidades();
    cout << g->mayor << endl;
    return 0;
}
