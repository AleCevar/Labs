#include <iostream>
#include "SET.h"
#include <cmath>
using namespace std;

int SET :: estaVacio(){
    //Retorna un valor booleano dependiendo si la lista esta vacia o no
    if(arbol->size == 0){return 1;}
    return 0;
}
int SET :: cardinalidad(){
    // Retorna la cardinalidad del conjunto
    return arbol->size;
}
int SET :: cardinalidadMax(){
    // Retorna la capacidad maxima del conjunto
    return arbol->capacidad;
}
bool SET :: insertar(string s){
    //inserta un string y retorna un booleano
    return arbol->insert(s);
}
bool SET :: eliminar(string s){
    // Elimina un string
    return arbol->remove(s);
}
bool SET :: contiene(string s){
    //Verifica si un string esta en el conjunto
    return arbol->contiene(s);
}
SET SET :: intersect(SET conj){
    //Devuelve un conjunto con la interseccion
    SET conjuntoR = SET();
    if(conj.cardinalidad() > this->cardinalidad()) {conjuntoR.intersect_aux(conj.arbol,this->arbol->getRoot());}
    else{conjuntoR.intersect_aux(arbol, conj.arbol->getRoot());}
    return conjuntoR;
}
void SET :: intersect_aux(AVL* arbolA, BSTVertex * T){
    // Verifica si un elemnto esta en ambos y lo inserta
    if(T == NULL) {return;}
    if(arbolA->contiene(T->key)) {insertar(T->key);}   
    intersect_aux(arbolA,T->left);
    intersect_aux(arbolA,T->right);
}
SET SET :: unionSET(SET conj){
    // Devuelve un conjunto con la union 
    SET conjuntoR = SET();
    if(conj.cardinalidad() > cardinalidad()) {
        conjuntoR.union_aux(conj.arbol->getRoot());
        conjuntoR.union_aux(arbol->getRoot());}
    else{
        conjuntoR.union_aux(arbol->getRoot());
        conjuntoR.union_aux(conj.arbol->getRoot());}
    return conjuntoR;
}
void SET :: union_aux(BSTVertex * T){
    // Inserta los elementos de un conjunto en otro
    if(T == NULL){return;}
    insertar(T->key);
    union_aux(T->left);
    union_aux(T->right);
}
lista* SET :: elementos(){
    // Devuelve una lista con el preorden
    lista* SLL = new lista();
    elementos_aux(arbol->getRoot(), SLL);
    return SLL;
}
void SET :: elementos_aux(BSTVertex* T, lista* SLL){
    // Inserta el preorden en una lista
    if(T == NULL){return;}
    SLL->append(T->key);
    elementos_aux(T->left,SLL);
    elementos_aux(T->right,SLL);
}

string pasar(string s){
    // Elimina los dos primero campos de un string
    string g;
    for(int i = 2; s[i] != 0; i++){g.push_back(s[i]);}
    return g;
}

int convertir(string s){
    //Pasa el string a int
    string g = pasar(s);
    if(g.length() == 0){return -1;}
    int res = 0;
    for(int i = (g.length() - 1), j = 0; i >= 0; i--, j++){ 
        res += (g[j] - '0') * pow(10,i);
    }
    return res;
}
int main(){
    long long int num = 0;
    string inst;
    SET conjunto;
    cin >> num;
    cin.ignore();
    for(int i = 0; i < num; i++){
        getline(cin,inst);
        int cant = 0;
        string s;
        if(inst[0] == 'E'){
            cant = convertir(inst);
            if(cant < 0){conjunto = SET();}
            else{conjunto = SET(cant);} 
            continue;}
        if(inst[0] == 'i'){
            s = pasar(inst);
            if(conjunto.insertar(s) == true) {cout << "SI insertado" << endl;}
            else{cout << "NO insertado" << endl;}continue;}
        if(inst[0] == 'r'){
            s = pasar(inst);
            if(conjunto.eliminar(s) == true) {cout << "SI removido" << endl;}
            else{cout << "NO removido" << endl;}continue;}
        if(inst[0] == 'c'){
            cout << conjunto.cardinalidad() << endl;continue;}
        if(inst[0] == 'v'){
            if(conjunto.estaVacio() == true) {cout << "VACIO" << endl;}
            else{cout << "NO VACIO" << endl;}continue;}
        else{
            s = pasar(inst);
            if(conjunto.contiene(s) == true){cout << "SI ESTA" << endl;} 
            else{cout << "NO ESTA" << endl;}continue;}
    }    
}