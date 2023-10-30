#include <iostream>
using namespace std;

long long int pentagonal[816496];
long long int repes;
long long int entrada;

long long int penta( long long int num){
    // Calcula los números pentagonales.
    return (num * (3 * num - 1)) / 2;
}

void generar_lista(){
    // Genera una lista que contiene números pentagonales.
    for(int i = 1; i <= 816496; i++){
        pentagonal[i-1] = penta(i);
    }
}

long long int buscar(){
    // Busca los dos números pentagonales más cerca de la entrada, y se queda con el que tiene menor distancia.
    long long int mayor = 816495;// número que da aproximadamente 10 elevado a la 12 con la fórmula pentagonal.
    long long int menor = 0;
    long long int medio = (mayor + menor) / 2;

    while(menor + 1 < mayor){
        if(pentagonal[medio] > entrada){
            mayor = medio;
        }
        else{
            menor = medio;
        }
        medio = (mayor + menor) / 2;
    }
    if (entrada - pentagonal[medio] <= pentagonal[medio+1] - entrada){
        return pentagonal[medio];
    }
    return pentagonal[medio+1];
}

int main(){
    generar_lista();
    cin >> repes;
    for(int i = 0; i < repes; i++){
        cin >> entrada;
        cout << buscar() << endl;

    }
    return 0;
}