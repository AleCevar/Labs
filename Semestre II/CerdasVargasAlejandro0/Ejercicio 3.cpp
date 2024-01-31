/*
Un guía quiere saber cuantas aves diferentes puede observar dada una matriz de 1 y 0; y una serie de puntos desde donde buscara aves.
*/
#include <iostream>
using namespace std;

    long long int filas;
    long long int columnas;
    long long int vista;
    long long int x;
    long long int y;
    int * p_mat;
    long long int cuenta;

void revisar(int i, int j){
    /* Función que verifica si los valores son posibles dentro de la matriz y de serlo, verifica si en la posición hay un uno. En este caso lo cuentan
    y lo eliminan.
    */
    if (i >= 0 && i < filas){
        if (j >= 0 && j < columnas){
            long long int des = (i * columnas) + j;
            if(*(p_mat + des) == 1){
                *(p_mat + des) = 0;
                cuenta ++;
            }
        }
    }
}

void generar_coord(){ 
    // Función que verfica todas las posibilidades de las coordenadas entrantes.
    for (int i = 0; i < vista; i++){
        cin >> x >> y;
        x --; y--;
        revisar(x-1,y-1);
        revisar(x-1,y);
        revisar(x-1,y+1);
        revisar(x,y-1);
        revisar(x,y);
        revisar(x,y+1);
        revisar(x+1,y-1);
        revisar(x+1,y);
        revisar(x+1,y+1);
    }
}

int main(){
    // Función principal.
    cin >> filas >> columnas >> vista;
    int matriz[filas][columnas];
    for (int i=0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            cin >> matriz[i][j];
        }
    }
    p_mat = &matriz[0][0];
    generar_coord();
    cout << cuenta << endl;
    return 0;
}
