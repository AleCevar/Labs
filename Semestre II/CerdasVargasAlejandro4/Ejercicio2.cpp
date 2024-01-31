/*
Dada una serie de personas y un número de prioridad, se desea vacunar a los de mayor prioridad en un centro de médico.
*/

#include <bits/stdc++.h>
#include <functional>
using namespace std;

typedef pair<int,string> is;

struct ParOrden {
    is par;
    long long int orden;

    ParOrden(const is p, long long int o) : par(p), orden(o){}

    bool operator <(const ParOrden p) const {
        if(par.first == p.par.first) return orden > p.orden;
        return par.first < p.par.first;
    }
};

int main(){
    priority_queue <ParOrden> pq;
    long long int cuenta = 0;
    string s;
    int prioridad;

    while(cin >> s){
        if(s.compare("V")){
            cin >> prioridad;
            pq.push(ParOrden({prioridad,s},cuenta++));
        }
        else{
            if(pq.empty()){
                cout << endl;
            }
            else{
                ParOrden top = pq.top();
                pq.pop();
                cout << top.par.second << endl;
            }
        }
    }    
    return 0;
}
