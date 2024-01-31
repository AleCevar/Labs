// Problema 4 kattis Purplerain (Aceptado)
// https://open.kattis.com/problems/purplerain
// https://open.kattis.com/submissions/12546935
// Complejidad: O(n)

#include <iostream>
using namespace std;

string s;
int n;
int memo[100005][3];

int solveConB(int pos, int cont){
	if(pos==n) return 0;
    if(memo[pos][1]) return memo[pos][1];
	if(s[pos]=='B'){
		memo[pos][1]=max(1, 1+solveConB(pos+1, 0));
        return memo[pos][1]+cont;
	}
	else{
		memo[pos][1]=solveConB(pos+1, cont-1);
	}
	return memo[pos][1];
}

int solveConR(int pos, int cont){
	if(pos==n) return 0;
    if(memo[pos][0]) return memo[pos][0];
	if(s[pos]=='R'){
		memo[pos][0]=max(1, 1+solveConR(pos+1, 0));
        return memo[pos][0]+cont;
	}
	else{
		memo[pos][0]=solveConR(pos+1, cont-1);
	}
	return memo[pos][0];
}

void buscar(){
    int mayorR=0, posR=0;
    int mayorB=0, posB=0;
    for (int i = 0; i <n; i++)
    {
        if(memo[i][0]>mayorR) mayorR=memo[i][0], posR=i;
        if(memo[i][1]>mayorB) mayorB=memo[i][1], posB=i;
    }
    char let='B';
    int i=posB, j;
    if(mayorR>mayorB) let='R', i=posR;
    if(mayorB==mayorR && posR < posB) let = 'R', i = posR;
	int cont=max(mayorB, mayorR);
    j=i;
	while(cont){
        (s[j]==let)? cont--:cont++;
        j++;
    }
    cout<<i+1<<" "<<j<<'\n';
}

int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin>>s;
    n=s.size();
    solveConB(0, 0);
    solveConR(0, 0);
    buscar();
    return 0;
}

