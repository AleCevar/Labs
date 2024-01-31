/*
Tomas desea ganar un concurso de perros que arrean ovejas. El objetivo es entregar a Tomas, los 3 nombres de los perros(en orden
alfabético) que más arrean ovejas y el total de ovejas que pueden arrear.
*/

#include <iostream>
#include <stdio.h>
using namespace std;

long long int cantidad;
char perro[21];
long long int ovejas;
long long int m_oveja[6];
char m_nombre[1000][21];


void llenar_mat(){
    // se toma las entradas y las introduce en las variables.
    cin >> cantidad;
    for (int i = 0; i < cantidad; i++){
        cin >> perro >> ovejas;
        swap(m_nombre[i],perro);
        m_oveja[i] = ovejas;
        
    }
}

void generar_actual(int i){
    // genera el actual nombre para ordenarlo a partir de las ovejas.
    for(int j = 0; j < 21; j++)
        if(m_nombre[i][j] == 0){
            perro[j] = 0;
        }
        else{
            perro[j] = m_nombre[i][j];
        }
    }

void mover_nombre(int original, int remplazo){
    // mueve un nombre un espacio a la derecha.
    for (int j = 0; j < 21; j++){
        if (m_nombre[remplazo][j] == 0){
            m_nombre[original][j] = 0;
        }
        else{
            m_nombre[original][j] = m_nombre[remplazo][j];
        }
    }
}

void colocar_nombre(int i){
    // finalmente coloca el nombre actual en donde debe.
    for(int j = 0; j < 21; j++){
        if(perro[j] == 0){
            m_nombre[i][j] = 0;
        }
        else{
            m_nombre[i][j] = perro[j];
        }
    }
}

void insertionsort(int size){
    // ordena por número de ovejas que arrea.
    for (int i = 0; i < size; i++){
        int actual = m_oveja[i];
        generar_actual(i);
        int j = i-1;
        while(j >=0 && actual > m_oveja[j]){
            m_oveja[j + 1] = m_oveja[j];
            mover_nombre(j+1,j);
            j--; 
        }
        m_oveja[j+1] = actual;
        colocar_nombre(j+1);    
    }
}

void calcular_total(){
    // calcula el total de ovejas que arrea entre los tres mejores.
    ovejas = 1;
    for(int i = 0; i < 3; i++){
        if (m_oveja[i] != 0){
            ovejas *= m_oveja[i];
        }
    }
}

int ordenar(int i, int j, int size){
    // ordena alfabéticamente los nombres.
    if(i+1 >= size){
        return 1;
    }
    if(m_nombre[i][j] > m_nombre[i+1][j]){
        swap(m_nombre[i],m_nombre[i+1]);
        return ordenar(i+1,0,size);
    }
    if(m_nombre[i][j] == m_nombre[i+1][j]){
        return ordenar(i,j+1,size);
    }
    else{
        return ordenar(i+1,0,size);
    }
}

int main(){
    llenar_mat();
    int size = sizeof(m_oveja)/sizeof(m_oveja[0]);
    insertionsort(size);
    calcular_total();
    
    // se ajusta el size para quedarse con los 3 mejores
    size = 3;
    for( int i = 0; i < 3; i++){
        if(m_oveja[i] == 0){
            size --;
        }
    }
    // se ordena alfabéticamente.
    int stop = 0;
    while(stop < 2){
        stop += ordenar(0,0,size);    
    }
    // se imprime el resultado.
    for(int i = 0; i < 3; i++){
        cout << m_nombre[i] << ' ';
    }
    cout << ovejas << endl;
    return 0;
}
