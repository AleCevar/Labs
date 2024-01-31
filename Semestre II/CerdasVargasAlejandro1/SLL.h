/*
Clase de lista enlazada simple
*/

#include<iostream>
using namespace std;

class nodo_sll{
    public:
        int dato;
        string word;
        nodo_sll * sig;
        nodo_sll(int entrada){
            dato = entrada;
            sig = nullptr;
        }
        nodo_sll(string s){
            word = s;
            sig = nullptr;
        }
        ~nodo_sll() = default;
};

class SLL{
    public:
        nodo_sll * head;
        SLL(){head = nullptr;}
        int longitud();
        void insertarPosicion(int pos, int val);
        void push(int val);
        void append(int val);
        int remove(int pos);
        void mostrar();
        void barajar();
        void ordenarRapido(int asc);
        bool relacion(int a, int b, int asc);
        void ordenarRadio(int asc);
        void appendString(string s);
        ~SLL(){
            if(head == nullptr) {return;}
            nodo_sll * borrar;
            for(borrar = head; head != nullptr ; borrar = head){
                head = head -> sig;
                delete(borrar);
            }
        }
};
