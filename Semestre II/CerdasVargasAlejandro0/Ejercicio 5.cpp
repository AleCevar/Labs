#include <iostream>
#include <math.h>
using namespace std;

long long int pruebas;
long long int cuenta;
long long int mod = 1000000007;
long long int array[2001];
long long int pri;
long long int seg;
long long int memo[2001][2001];

bool esprimo(int num){
    // Verifica si el n�mero es primo.
    if(num < 0) return false;
    if(num == 1 || num == 4 || num == 0) return false;
    if(num == 2 || num == 3) return true;
    int div = 2;
    while(div * div <= num){
        if (num % div == 0) return false;
        div ++;
    }
    return true;
}

long long int inverso(int a, int exp, int mod){
    // Funci�n que calcula el inverso de un n�mero.
    if (!exp) return 1L;
    long long r = inverso(a, exp/2, mod);
    r *= r;
    r %= mod; 
    if (exp & 1) r *= a;
    return r % mod;
}

long long int combinacion(long long int n, long long int k){
    //Calcula las combinaciones posibles.
    if(n == k || !k) return 1;
    if(memo[n][k]) return memo[n][k];
    return memo[n][k] = combinacion(n-1,k-1) + combinacion(n-1,k);
}

void posibilidades(int x){
    //Verifica las posibilidades de que los n�meros sean primos.
    if(x & 1){
       if (esprimo(x-2)){
            if (2 == x-2) cuenta += combinacion(x,2);
            else cuenta += 2 * combinacion(x,2); 
       }
    }
    else{
        for(int i = 2; i <= x/2; i++){
            if(esprimo(i) && esprimo(x-i)){
                if (i == x-i) cuenta += combinacion(x,i);
                else cuenta += 2 * combinacion(x,i);
            }
        }
    }
}
void generar_array(){
    // Genera el arreglo con las suma de las combinaciones. posibles 
    posibilidades(0);
    array[0] = cuenta;
    for(int i = 1; i < 2001; i++){
        posibilidades(i);
        array[i] += cuenta + array[i-1];
        cuenta = 0;
    }
}

void respuesta(long long int pri, long long int seg){
    // Resta la posici�n del arreglo segun el intervalo solicitado.
    long long int res = array[seg] - array[pri-1];
    cout << res << endl;   
}

int main(){
    cin >> pruebas;
    cout << esprimo(pruebas) << endl;
    return 0;
}
