#include <iostream>
using namespace std;

//Problema 43 Presidential Elections Kattis
// https://open.kattis.com/problems/presidentialelections?tab=submissions
// https://open.kattis.com/submissions/12533313
// Complejidad :O(S \times S)

int const inf = 1000000001;
int S,cantTotal=0, cantDel=0;
int info[2016][4];
int faltantes;
int memo[2016][2016];

int solve(int estado, int delegados){
    if(faltantes < delegados) return 0;
    if(estado == S) return inf;
    if(memo[estado][delegados] > 0) return memo[estado][delegados];
    int costo = 0;
    if(info[estado][1] > info[estado][2] + info[estado][3]) return memo[estado][delegados] = solve(estado+1,delegados+info[estado][0]);
    if(info[estado][2] - info[estado][1] >= info[estado][3]) return memo[estado][delegados]= solve(estado+1,delegados);
    costo = (info[estado][2] - info[estado][1] + info[estado][3])/2+1;
    return memo[estado][delegados] = min(solve(estado+1,delegados+info[estado][0]) + costo,solve(estado+1,delegados));
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> S;
    for (int i = 0; i<S; i++)
    {
        cin >> info[i][0] >> info[i][1] >> info [i][2] >> info[i][3];
        cantTotal +=  info[i][0];
        if(info[i][1]>info[i][2]+info[i][3]) cantDel+=info[i][0];
    }
    if(cantDel>(cantTotal-cantDel)) cout<<"0\n";
    else{
        for(int i = 0; i < S; i++)
            for(int j = 0; j < 2016; j++)
                memo[i][j] = -1;
        faltantes = cantTotal/2;
        int res = solve(0,0);
        (res==inf)? cout<<"impossible\n": cout<<res<<'\n';
    }
    return 0;
}