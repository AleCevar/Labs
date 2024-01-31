/*
Cierto vendedor de productos navideños, que los vende en combos quiere determinar cuánto dinero obtendría si se vendiera cada producto,
en diferentes cantidades, según los combos. El vendedor tiene una cantidad de productos por combo preparado, sólo los vende en esos
combos específicos. Luego, se desea sumar todas las combinaciones cuyo valor supera cierto umbral G. Dicho de otra manera, el vendedor 
quiere que se sumen las ganancias que resultan de multiplicar el precio de cada producto por
cada combo vendido según sus especificaciones, pero sólo para los resultados que sean mayores o iguales a un valor G determinado.
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi p,c;
int g;

int bb(int i){
    int ma = c.size(),me,mi= 0;
    while(mi < ma){
        me = (ma+mi)/2;
        if(p[i]*c[me] == g) return me;
        if(p[i]*c[me] > g) ma = me-1;
        else mi = me+1;
    }
    return mi;
}

int solve(int tamP, vi precios, int tamC, vi combos, int n){
    p = precios; c = combos; g = n;
    vi aco(tamC); aco[tamC-1] = combos[tamC-1];
    for(int i = tamC-2; i >= 0; i--) aco[i] = aco[i+1] + combos[i];
    int res = 0;
    for(int i = 0; i < tamP; i++){
        int j = bb(i);
        res += aco[j]*p[i];
    }
    return res;
}
