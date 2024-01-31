#include <iostream>
using namespace std;

// Prom 1.3 Grapevine VJudge
// https://vjudge.net/problem/UVA-12192
// Complejidad: O(N \times M + N \times log(M))$ Al ser una matriz lo expresamos así
// https://vjudge.net/solution/47749935


int N, M, o, x, y;
int array [500][500];

bool esValidoC(int a){return a >= 0 && a < M;}
bool esValidoF(int a){return a >= 0 && a < N;}

int rangoInf(int a, int j){
    int ma = M, me, mi = 0;
    while(mi <= ma){
        me = (ma+mi)/2;
        if(array[j][me] == a){
            if(!esValidoC(me-1)) return me;
            if(array[j][me-1] != a) return me;
            ma = me - 1;
        }
        if(array[j][me] > a) ma = me - 1;
        if(array[j][me] < a) mi = me + 1;
    }
    return mi;
}

void calcularCuad(){
    int tam = 0;
    for(int i = 0; i < N; i++){
        int lo = rangoInf(x,i);
        for(int j = 0; j < M; j++){
            if(!esValidoF(i+j) || !esValidoC(lo+j)) break;
            if(array[i+j][lo+j] > y) break;
            tam = max(tam,j+1);
        }
    }
    cout << tam << "\n";
}

int main(){
    ios_base :: sync_with_stdio(false); cin.tie(0);
    while(cin >> N >> M ){
        if(!N && !N) break;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++){
                cin >> array[i][j];
            }
        cin >> o;
        while(o){
            cin >> x >> y;
            calcularCuad();
            o--;
        }
        cout << '-' << "\n";
    }
    return 0;
}