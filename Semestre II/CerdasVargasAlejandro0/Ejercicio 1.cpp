#include <iostream>
using namespace std;

long long int profesores;
long long int estudiantes;
char nota;
int array[6]={0,0,0,0,0,0};
int total[6]={0,0,0,0,0,0};

void identificar(char nota){
    // Incrementa la posición del array donde es la nota, se resta entre 'A' debido a que en ASCII da el número de la posición.
    array[nota-'A']++;
}

void sumar_total(){
    // Imprime el la suma de las revisiones del profesor y suma las notas a una lista total.
    cout << "A:" << array[0] << " B:" << array[1] << " C:" << array[2] << " D:" << array[3] << " E:" << array[4] << " F:" << array[5] << endl;
    for(int i =0; i < 6; i++){
        total[i] += array[i];
        array[i] = 0;
    }
}

int main () {
    cin >> profesores;
    
    for (int i=0; i < profesores; i++){
        cin >> estudiantes;
        for (int j=0; j < estudiantes; j++){
            cin  >> nota;
            identificar(nota);
        }
        sumar_total();
    }
    cout << "TOTAL: A:" << total[0] << " B:" << total[1] << " C:" << total[2] << " D:" << total[3] << " E:" << total[4] << " F:" << total[5]<< endl;
    return 0;
}