//Saber si un número es primo.
#include <iostream>
using namespace std;

typedef unsigned long long int ll;
const ll ten14 = 100000000000000;

ll mulmod (ll a, ll b, ll c) { //Una multiplicacion logaritmica con modulo, muy interesante
	ll x = 0, y = a%c;
	while (b > 0){
		if (b % 2 == 1) x = (x+y) % c;
		y = (y*2) % c;
		b /= 2;
	}
	return x % c;
}

ll expLog (ll a, ll exp, ll mod){
	if(!exp) return 1;
	ll res= expLog(a,exp/2,mod); 
    res = mulmod(res,res,mod);
	if(exp%2) res = mulmod(a,res,mod);
    return res;
}

bool esPrimoProbabilistico (ll n, int a){
	if (n == a) return true;
	ll exp = n-1;
    while(!(exp&1)){
        ll c = expLog(a,exp,n);
        if(!((c+1)%n)) return true;
        exp /= 2;
    }
    ll c = expLog(a,exp,n);
    if(!((c+1)%n)) return true;
    if(!((c-1)%n)) return true;
    return false;
}

bool esPrimo (ll n){ 
	const int ar[] = {2,3,5,7,11,13,17,19,23};
	for(int j = 0; j < 9; j++)
		if (!esPrimoProbabilistico(n,ar[j]))
			return false;
	return true;
}

int isPrime(ll n){
    if(n == 2) return 1;
    if(!(n%2)) return 0;
    ll i = 3;
    while(i*i <= n){
        if(!(n%i)) return 0;
        i++; i++;
    }
    return 1;
}

bool determinar(ll n){
    if(!n || n == 1) return false;
    return (n > ten14) ? esPrimo(n) : isPrime(n);
}

int main(){
    ios_base :: sync_with_stdio(false);cin.tie(0);
    ll T,n; cin >> T;
    for(int i = 0; i < T; i++){
        cin >> n;
        if(determinar(n)) cout << "Si" << "\n";
        else cout << "No" << "\n";
    }       
}
