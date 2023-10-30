#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pi;

class Grafo{
    public:        
        int n;
        vector<vi> adyancencia, excentricidad;
        priority_queue<pi> colaP;
        int mayor;

        Grafo(int num){
            n = num;
            adyancencia.assign(n,vector<int>(0));
            excentricidad.assign(n,vector<int>(n,0));
            mayor = 0;
        }

        void unir(int n1, int n2){
            adyancencia[n1].push_back(n2);
            adyancencia[n2].push_back(n1);
        }

        void diametro(int n1){
            vi visitados;
            visitados.assign(n,0);
            int n2;
            queue<int> cola;
            cola.push(n1);
            visitados[n1]++;
            while(!cola.empty()){
                n2 = cola.front();
                cola.pop();
                for(int i = 0; i < adyancencia[n2].size(); i++){
                    int adya = adyancencia[n2][i];
                    if(!visitados[adya]){
                        cola.push(adya);
                        excentricidad[n1][adya] = excentricidad[n1][n2] + 1;
                        visitados[adya]++;
                    }
                }
            }
            if(excentricidad[n1][n2] > mayor) mayor = excentricidad[n1][n2]; 
        }

        void calcularDiametro(){
            nodoAlejado(0);
            pi p = colaP.top();
            colaP.pop();
            int n = p.first;
            while(!colaP.empty() && p.first == n){ 
                n = p.first;
                diametro(p.second);
                p = colaP.top();
                colaP.pop();
            }
        }

        void nodoAlejado(int n1){
            vi visitados;
            visitados.assign(n,0);
            int n2;
            queue<int> cola;
            cola.push(n1);
            visitados[n1]++;
            while(!cola.empty()){
                n2 = cola.front();
                cola.pop();
                pi p = {excentricidad[n1][n2],n2};
                colaP.push(p);
                for(int i = 0; i < adyancencia[n2].size(); i++){
                    int adya = adyancencia[n2][i];
                    if(!visitados[adya]){
                        excentricidad[n1][adya] = excentricidad[n1][n2] + 1;
                        cola.push(adya);
                        visitados[adya]++;
                    }
                }
            }
        }

        int getMayor(){
            return mayor;
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
    g->calcularDiametro();
    cout << g->getMayor() << "\n";
    return 0;
}