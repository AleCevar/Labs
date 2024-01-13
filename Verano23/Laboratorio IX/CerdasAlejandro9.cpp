//Complejidad: $O(n^2 \times generacion)$

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class nreinas{
    public:
        vi * poblacion;
        int n;
        int elite;
        int solu;
        int * fit;
        bool cambio;
        int cont;
        int m;
        int tam;
        vi * neva;
        int sum;
        int * acomu;

        nreinas(int num,int M){
            n = num;
            tam = 5*n;
            if(n > 31) tam*=2;
            if(tam%2 == 0) tam--;
            poblacion = new vi[tam];
            fit = new int[tam];
            solu = -1;
            elite = 0;
            m = M;
            neva = new vi[tam];
            sum = 0;
            acomu = new int[tam];
            evolucion();
        }   

        int colisiones(vi indi){
            int cont = 0;
            vi di(n*2), da(n*2), ho(n);
            for(int i = 0; i < 2*n; i++){
                di[i] = da[i] = 0;
                if(i < n) ho[i] = 0;
            }       
            for(int i = 0; i < n; i++){
                int res = i-indi[i];
                if(res < 0) res *= -1;
                else res+=n; 
                di[res]++;
                da[i+indi[i]]++;
                ho[indi[i]]++; 
            }
            for(int i = 0 ; i < n*2; i++){
                if(i < n && ho[i] > 1) cont+=ho[i]-1;
                if(di[i] > 1) cont+=di[i]-1;
                if(da[i] > 1) cont+=da[i]-1;
            }
            return cont;
        }

        int rando(int mod, int min){
            return (rand()%mod)+min;
        }

        void generarPobla(){
            for(int i = 0; i < tam; i++){
                poblacion[i] = vi(n);
                neva[i] = vi(n);
                for(int j = 0; j < n; j++){
                    poblacion[i][j] = rando(n,0);
                }
            }
            fit[0] = INT32_MAX;
            fitness();
        }

        void fitness(){
            sum = 0;
            for(int i = 0; i < tam; i++){
                fit[i] = colisiones(poblacion[i]);
                sum += fit[i]*fit[i];
                if(fit[i] == 0) {
                    solu = i;
                    fit[i] = 1;
                }    
                if(fit[elite] > fit[i]){
                    cambio = true;
                    elite = i;
                }
            }
            acomu[0] = sum / (fit[0] * fit[0]);
            int i;
            for(i = 1; i < tam; i++)
                acomu[i] = acomu[i-1] + (sum/(fit[i]*fit[i]));
            sum = acomu[i-1];
        }

        void newGen(){
            neva[0] = poblacion[elite];        
            elite = 0;
            for(int i = 1; i < tam; i+=2){
                int gm = elegir(rando(sum,0)),gf = elegir(rando(sum,0));
                crossover(gm,gf,i);
            }
            swap(neva,poblacion);
            fitness();
        }

        int elegir(int r){
            int ma = tam, me, mi = 0;
            while(mi+1 < ma){
                me = (mi+ma)/2;
                if(acomu[me] == r) return me;
                if(acomu[me] < r) mi = me;
                else ma = me;
            }
            return (r <= acomu[0]) ? 0 : mi+1;
        }

        void crossover(int m, int f, int i){
            int c = rando(n/3,1), j = 0;
            for(;j < c; j++){
                neva[i][j] = poblacion[m][j];
                neva[i+1][j] = poblacion[f][j];
            }
            for(;j < n; j++){
                neva[i][j] = poblacion[f][j];
                neva[i+1][j] = poblacion[m][j];
            }
            if(rando(100,0) < 5){
                int pos = rando(n,0);
                neva[i][pos] = rando(n,0);  
            }
        }

        void evolucion(){
            generarPobla();
            int flag = 1, gen = 0;
            cambio = false;
            while(flag){
                if(solu != -1){
                    imprimir(gen);
                    break;
                }
                if(cont >= n*n){
                    imprimirEli(gen);
                    break;
                }
                if(m) imprimirEli(gen);
                newGen();
                if(!cambio) cont++;    
                else {
                    cont = 0;
                    cambio = false;
                }
                gen++;
            }
        }

        void imprimir(int gen){
            cout << "Generacion: " << gen << '\n';   
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(poblacion[solu][j] == i) cout << 'Q' << ' ';
                    else cout << '#' << ' ';
                }
                cout << '\n';
            }
        }

        void imprimirEli(int gen){
            cout << "Generacion: " << gen << '\n';
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(poblacion[elite][j] == i) cout << 'Q' << ' ';
                    else cout << '#' << ' ';
                }
                cout << '\n';
            }
            cout << "Colisiones: " << fit[elite] << '\n';
        }
};

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    int n,m; cin >> n >> m;
    nreinas s(n,m);
    return 0;
}
