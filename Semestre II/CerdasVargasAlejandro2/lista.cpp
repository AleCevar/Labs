#include <iostream>
#include "lista.h"
using namespace std;

void lista :: append(string s){
    nodo_sll * nuevo = new nodo_sll(s);
    if(head == NULL){head = nuevo; return;}
    nodo_sll * actual = head;
    while(actual->sig != NULL){
        actual = actual -> sig;
    }
    actual->sig = nuevo;
    return;
}
void lista :: mostrar(){
    if(head == NULL){return;}
    nodo_sll * actual = head;
    while(actual != NULL){
        cout << actual->dato << ' ';
        actual = actual->sig;
    }
    cout << endl;
}
nodo_sll* lista :: ultimo(){
    if(head == NULL){return head;}
    nodo_sll* actual = head;
    while(actual->sig != NULL){actual = actual->sig;}
    return actual;
}