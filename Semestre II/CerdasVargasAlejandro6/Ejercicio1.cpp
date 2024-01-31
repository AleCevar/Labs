//En un parqueo en Japón, se tiene 7 vehículos, con cierto peso, 
//y se desea ordenar estos vehículos de una forma conveniente, pero se desea minimizar el costo de realizar estos movimientos.
#include <bits/stdc++.h>
using namespace std;

int fa[4] = {0,0,1,-1};
int ca[4] = {1,-1,0,0};
const int INF = 1000000000;
map<string,int> mapa;

class Grafo{
    public:
        int Mat[3][3];
        
        void leer(){
            Mat[0][0] = Mat[2][2] = -1;
            int i = 0, j = 1, n, a = 3;
            while(i < 3){
                while(j < a){
                    cin >> n;
                    Mat[i][j] = n;
                    j++;
                }
                j = 0;
                if(i) a = 2;
                i++;
            }
        }

        string crearString(){
            string s = "";    
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(i%2 || i != j)
                    s.append(to_string(Mat[i][j]));
                }
            }
            return s;
        }

        Grafo copiar(){
            Grafo n;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    n.Mat[i][j] = Mat[i][j];    
                }
            }
            return n;
        }

        bool comparar(Grafo C){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(Mat[i][j] != C.Mat[i][j]) return false; 
                }
            }
            return true;
        }

        int verificar(string key){
            if(mapa.find(key) == mapa.end()) return INF;
            return mapa[key];
        }

        void cambiar(int i, int j, int x, int y){
            int n = Mat[i][j];
            Mat[i][j] = Mat[x][y];
            Mat[x][y] = n;
        }
};

bool validar(int a, int b){
    return a >= 0 && a < 3 && b >= 0 && b < 3;
}

typedef pair<int, Grafo> ig;
bool operator <(const ig p, const ig a){
    return p.first > a.first;
}

void dijkstra(Grafo G, Grafo R){
    priority_queue<ig> pq;
    mapa[G.crearString()] = 0;
    pq.push({0,G});
    while(!pq.empty()){
        ig p = pq.top(); pq.pop();
        if(p.first > mapa[p.second.crearString()]) continue;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(i%2 || i != j){
                    for(int k = 0; k < 4; k++){
                        int x = i + fa[k], y = j + ca[k];
                        if(validar(x,y) && p.second.Mat[x][y] != -1){
                            Grafo C = p.second.copiar();
                            int peso = mapa[p.second.crearString()] + C.Mat[i][j] + C.Mat[x][y];
                            C.cambiar(i,j,x,y);
                            if(C.verificar(C.crearString()) > peso){    
                                mapa[C.crearString()] = peso;
                                pq.push({peso,C});
                            }
                        }
                    }
                }
    }
}


int main() {
    Grafo G ;
    Grafo R ;
    G.leer();
    R.leer();
    dijkstra(G,R);
    cout << mapa[R.crearString()] << "\n";
}
