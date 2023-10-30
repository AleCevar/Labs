#include <iostream>
#include "CDLL.h"
using namespace std;

int CDLL :: longitud(){
    // Calcula la longitud de la lista
    if(head == NULL) return 0;
    nodo_cdll * actual = head -> sig;
    int cuenta = 1;
    while(actual != head){
        actual = actual -> sig;
        cuenta ++;
    }
    return cuenta;
}
void CDLL :: insertarPosicion(int pos, int val){
    //Inserta un valor en una posicion solicitada
    nodo_cdll * nuevo = new nodo_cdll(val);
    if(head == NULL) {head = nuevo; head -> sig = head -> ant = head; return;}
    nodo_cdll * actual = head;
    nodo_cdll * ult = actual -> ant;
    if(pos == 0){
        nuevo -> sig = head;
        nuevo -> ant = ult;
        head -> ant = ult -> sig = nuevo;
        head = nuevo; return;}
    actual = actual -> sig;
    int ind = 1;
    while(actual != head){
        if(pos == ind){
            nodo_cdll * previo = actual -> ant;
            previo -> sig = actual -> ant = nuevo;
            nuevo -> sig = actual;
            nuevo -> ant = previo; return;}
        actual = actual -> sig;
        ind ++;}
    ult -> sig = head -> ant = nuevo;
    nuevo -> sig = head;
    nuevo -> ant = ult; return;
}
void CDLL :: push(int val){
    // Inserta el valor al inicio
    insertarPosicion(0,val);
}
void CDLL :: append(int val){
    // Inserta un elemento al final
    insertarPosicion(longitud(),val);
}
int CDLL :: remove(int pos){
    // Remueve un valor de la lista
    nodo_cdll * actual = head;
    int res;
    if (pos == 0){
        nodo_cdll * ult = head -> ant;
        res = head -> dato;
        head = head -> sig;
        head -> ant = ult;
        ult -> sig = head;
        delete(actual);
        return res;}
    int ind = 1;
    actual = actual -> sig;
    while(ind <= longitud()){
        if(ind == pos){
            nodo_cdll * anterior = actual -> ant;
            nodo_cdll * siguiente = anterior -> sig = actual -> sig;
            siguiente -> ant = anterior;
            res = actual -> dato;
            delete(actual);
            return res;}
        actual = actual -> sig; ind ++;}
    cout << "No existe la posicion solicitada" << endl;
    return -1;
}
void CDLL :: mostrar(){
    // Funcion que muestra el contenido de la listas
    if(head == NULL){
        cout << endl;
        return;}
    cout << head -> dato << ' ';
    nodo_cdll * actual = head -> sig;
    while(actual != head){
        cout << actual -> dato << ' ';
        actual = actual -> sig; 
    }
    cout << endl; 
}
CDLL * CDLL :: permutar(){
    // Devuelve un arreglo con todas las permutaciones de la lista
    CDLL * array = new CDLL[factorial(longitud())];
    CDLL * pun = array;
    nodo_cdll * punteros[longitud()];
    int i = 0;
    nodo_cdll * actual = head;
    do{ punteros[i] = actual;
        actual = actual -> sig;
        i++;}while(actual != head);
    solucion(pun,longitud(),0,punteros);
    //for(int i = 0; i < factorial(longitud()); i++){pun[i].mostrar();}
    return pun;
}
void CDLL :: solucion(CDLL * pun, int size, int count, nodo_cdll * punteros[]){ 
    // Busca las permutaciones de la lista
    if(size == 1){
        colocar(pun,count);return;}
    for(int i = 0; i < size; i++){
        solucion(pun,size-1,count,punteros);
        if(size % 2 == 1){swap(punteros[0] -> dato, punteros[size-1] -> dato);}
        else{swap(punteros[i] -> dato,punteros[size-1] -> dato);}
    }
}
void CDLL :: colocar(CDLL * pun, int count){
    // Coloca la permutacion en el arreglo
    CDLL res;
    nodo_cdll * actual = head;
    do{ res.append(actual -> dato);
        actual = actual -> sig;
    }while(actual != head);
    for(int i = 0; pun[count].head != NULL; count++);
    pun[count] = res;
    res.head = NULL;
    return;
}
int CDLL :: factorial(int num){
    // Calcula la factorial de un numero
    if(num == 1){return 1;}
    return num * factorial(num-1);
}
int main(){
    CDLL lista;
    lista.insertarPosicion(0,2);
    lista.insertarPosicion(2,3);
    lista.append(6);
    lista.push(7);
    lista.insertarPosicion(1,4);
    lista.mostrar();
    lista.remove(1);
    lista.mostrar();
    cout << lista.longitud() << endl;
    CDLL * pun = lista.permutar();
    for(int i = 0; i < lista.factorial(lista.longitud()); i++) {pun[i].mostrar();}
    return 0;
}