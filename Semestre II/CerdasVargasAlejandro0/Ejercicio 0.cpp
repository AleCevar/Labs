/*
En una matriz A de tamaño n × m se colocan números naturales de forma que a_ij es el j−esimo múltiplo de i
Dos estudiantes universitarios de la carrera de ingeniería compiten para poder indicar cuál es la suma de todos los números de la matriz
*/
#include <iostream>
using namespace std;

long long int casos;
long long int fila;
long long int columna;
long long int modulo = 1000000007;

long long int pot(int a, int exp, int mod){
    // Funcion que calcula el inverso de un nomero.
    if (!exp) return 1L;
    long long r = pot(a, exp/2, mod);
    r *= r;
    r %= mod; 
    if (exp & 1) r *= a;
    return r % mod;
}

void gauss(long long int fila, long long int columna, long long inverso){
    // Funcion que calcula la multiplicacion de la matriz, usando Gauss.
    fila = (fila * (fila+1)) % modulo ;
    columna = (columna * (columna+1)) % modulo ;
    long long int res =((fila * columna) % modulo) * inverso;
    res %= modulo;
    cout << res << endl;
}

int main ( ){
    long long int inverso = pot(4,modulo-2, modulo);
    cin >> casos;
    for (long long int i = 0; i < casos; i++){
        cin >> fila >> columna;
        gauss(fila,columna,inverso);
    }
    return 0;
}
