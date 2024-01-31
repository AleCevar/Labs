#include <iostream>
using namespace std;

//Problema 34: Alphabet Kattis (Aceptado)
//https://open.kattis.com/submissions/12538641
//https://open.kattis.com/problems/alphabet
//Complejidad: O($ n \times 26$) n= tamaño del string, 26=cardinalidad del alfabeto

int memo[51][27];
string s;

int solve(int pos, int l){
    if(l > 25) return  0;
    if(s.size() == pos){ return 26-l;}
    if(memo[pos][l]!=-1) return memo[pos][l];
    if(s[pos] == (char)'a'+l) return memo[pos][l] = min(solve(pos+1, l+1), solve(pos+1,l));
    if(s[pos]-'a' < l) return memo[pos][l] = solve(pos+1,l);   
    return memo[pos][l] = min(solve(pos+1,s[pos]-'a'+1) + (int)(s[pos]-'a'-l), solve(pos+1,l));
}

int main(){
    cin >> s;
    for(int i=0; i<s.size(); i++)
        for(int j=0; j<27; j++) memo[i][j]=-1;    
    cout << solve(0, 0) << '\n';
}
