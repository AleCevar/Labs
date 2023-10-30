#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class Grafo{
    public:
        int n;
        vi visitados, necesitados;
        vector<vi> adyancencia;
        vector<vi> res;

        Grafo(int num){
            n = num;
            visitados.assign(n,0);
            necesitados.assign(n,0);
            adyancencia.assign(n,vector<int>(0));
            res.assign(n,vector<int>(0));
        }

        void unir(int n1, int n2){
            adyancencia[n1].push_back(n2);
            adyancencia[n2].push_back(n1);
        }

        void calcularIntermedios(int n){
            queue<int> cola;
            cola.push(n);
            visitados[n]++;
            while(!cola.empty()){
                int actual = cola.front();
                cola.pop();
                for(int i = 0; i < adyancencia[actual].size(); i++){
                    int adya = adyancencia[actual][i];
                    if(!visitados[adya]){
                        necesitados[adya] = necesitados[actual] + 1;
                        visitados[adya]++;
                        cola.push(adya);
                        }
                }
                
            }
        }

        void resultado(int n){
            for(int i = 0; i < necesitados.size(); i++){
                if(i != n){
                    res[necesitados[i]].push_back(i);
                }
            }
            darResultado();
        }

        void darResultado(){
            if(res[0].size() > 0){
                cout << "0:";
                for(int i = 0; i < res[0].size(); i++){
                    cout << ' ' << res[0][i];
                }
                cout << endl;
            }
            for(int i = 1; res[i].size() > 0; i++){
                cout << i << ":";
                for(int j = 0; j < res[i].size(); j++){
                    cout << ' ' << res[i][j];
                }
                cout << endl;
            }
        }
};

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    int nodos, adyacentes, inicial, x, y;
    cin >> nodos >> adyacentes >> inicial;
    Grafo * g = new Grafo(nodos);
    for(int i = 0; i < adyacentes; i++){
        cin >> x >> y;
        g->unir(x,y);
    }
    g->calcularIntermedios(inicial);
    g->resultado(inicial);
    return 0;
}