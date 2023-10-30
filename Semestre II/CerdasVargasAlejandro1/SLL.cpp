#include <iostream>
#include <cstdlib> //Biblioteca de random
#include "SLL.h"
using namespace std;

int SLL :: longitud(){
    //Determina la longitud de la lista
    if(head == NULL) return 0;
    nodo_sll * actual = head;
    int r = 1;
    while(actual -> sig != NULL){
        r ++;
        actual = actual -> sig;
    }
    return r;
}
void SLL :: insertarPosicion(int pos, int val){
    // Inserta un valor en una posicion determinada
    nodo_sll * nuevo = new nodo_sll(val);
    if(head == NULL){
        head = nuevo; return;}
    nodo_sll * actual = head;
    if(pos == 0){
        head = nuevo;
        head -> sig = actual;return;}
    int ind = 1;
    while(actual -> sig != NULL){
        if(ind == pos){ 
            nodo_sll * temp = actual -> sig;
            actual -> sig = nuevo;
            actual -> sig -> sig = temp;
            return;
        }
        actual = actual -> sig;
        ind++;}
    actual -> sig = nuevo;
}
void SLL :: push(int val){
    // Inserta un valor al inicio
    insertarPosicion(0,val);
}
void SLL :: append(int val){
    // Inserta un valor al final
    int len = longitud();
    insertarPosicion(len,val);
}
int SLL :: remove(int pos){
    //Remueve el valor de una posicion determinada
    nodo_sll * actual = head;
    int res;
    if(pos == 0){
        res = head -> dato;
        head = head -> sig;
        delete(actual);
        return res;}
    int ind = 1;
    while(actual -> sig != NULL){
        if(ind == pos){
            nodo_sll * temp = actual -> sig;
            res = temp -> dato;
            actual -> sig = temp -> sig;
            delete(temp);
            return res;}
        ind++;
        actual = actual -> sig;}
    cout << "La posicion deseada no existe dentro de la lista" << endl;
    return -1;
}
void SLL :: mostrar(){
    // Demuestra en consola la lista
    nodo_sll * actual = head;
    while(actual != NULL){
        cout << actual -> word << ' ';
        actual = actual -> sig;
    }
    cout << endl;
}
void SLL :: barajar(){
    // Cambia al azar la poscion de los nodos
    nodo_sll * actual = head;
    int cuenta1 = 0;
    int size = longitud();
    srand((unsigned) time(0));
    while(cuenta1 < size){
	    int num = rand() % size;
        nodo_sll * temp = head;
        if(num == 0){
            swap(head ->dato,actual -> dato);}
        else{
            int cuenta2 = 0;
            while(cuenta2 < num){
                temp = temp -> sig;
                cuenta2++;}
            swap(temp -> dato,actual -> dato);}
        actual = actual -> sig; 
        cuenta1++;}
}
void SLL :: ordenarRapido(int asc){
    //Aplica quicksort a la lista
    if(longitud() < 2){return;}
    SLL menores; SLL mayores;
    nodo_sll * pivote = head;
    nodo_sll * actual = head -> sig; 
    while (actual != NULL){
        if(relacion(pivote -> dato, actual -> dato, asc)) {menores.append(actual -> dato);}
        else{mayores.append(actual -> dato);}
        actual = actual -> sig;}
    menores.ordenarRapido(asc);
    mayores.ordenarRapido(asc);
    if(menores.longitud() > 0){ 
        actual = head = menores.head;
        while(actual -> sig != NULL) {actual = actual -> sig;}
        actual -> sig = pivote;
        pivote -> sig = NULL;}
    if(mayores.longitud() > 0) {pivote -> sig = mayores.head;}
    menores.head = NULL;
    mayores.head = NULL;
}
bool SLL :: relacion(int a, int b, int asc){
    // Determina el si es verdadera la relacion propuesta
    if(!asc) return a > b;
    else; return a < b;
}
void SLL :: ordenarRadio(int asc){
    // Aplica radix sort
    nodo_sll * actual;
    for( int i = 0; i < 31 ; i++){
        actual = head;
        SLL uno; 
        SLL cero;
        while(actual != NULL){
            if(asc == 0){
                if((actual -> dato & (1 << i)) == 0){cero.append(actual -> dato);}
                else{uno.append(actual -> dato);}}
            else{
                if((actual -> dato & (1 << i)) == 0){uno.append(actual -> dato);}
                else{cero.append(actual -> dato);}
            }
            actual = actual -> sig;}
        if(cero.longitud() == 0){head = uno.head; continue;}
        actual = head = cero.head;
        if(uno.longitud() > 0){
            while(actual -> sig != NULL){actual = actual -> sig;}
            actual -> sig = uno.head;}
        if(i == 29) {asc = (asc == 0);}
        uno.head = NULL;
        cero.head = NULL;
    }
}       
void SLL :: appendString(string s){
    //cout << s << endl;
    nodo_sll * nuevo = new nodo_sll(s);
    if(head == NULL){head = nuevo; return;}
    nodo_sll * actual = head;
    while(actual->sig != NULL){
        actual = actual -> sig;
    }
    actual->sig = nuevo;
    return;
}
