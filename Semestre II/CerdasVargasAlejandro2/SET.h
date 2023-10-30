#include <iostream>
#include "AVL.cpp"
using namespace std;

class SET{
    public:
        int capacidad;
        AVL * arbol;
        SET(){
            capacidad = 2147483647;
            arbol = new AVL(2147483647);
        }
        SET(int cap){
            capacidad = cap;
            arbol = new AVL(cap);
        }
        int estaVacio();
        int cardinalidad();
        int cardinalidadMax();
        bool insertar(string s);
        bool eliminar(string s);
        bool contiene(string s);
        SET intersect(SET conj);
        void intersect_aux(AVL* arbolA, BSTVertex * T);
        SET unionSET(SET conj);
        void union_aux(BSTVertex * A);
        lista* elementos();
        void elementos_aux(BSTVertex * T, lista* SLL);
};
