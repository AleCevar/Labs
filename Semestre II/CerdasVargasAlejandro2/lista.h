#include <iostream>
using namespace std;

class nodo_sll{
    public:
        nodo_sll * sig;
        string dato;
        nodo_sll(string s){
            dato = s;
            sig = nullptr;
        }
        ~nodo_sll() = default;
};

class lista{
    public:
        nodo_sll * head;
        lista(){head = nullptr;}
        void append(string s);
        nodo_sll* ultimo();
        void mostrar();
        /*
        ~lista(){
            if(head == nullptr) {return;}
            nodo_sll * borrar;
            for(borrar = head; head != nullptr ; borrar = head){
                head = head -> sig;
                delete(borrar);
            }
        }*/
};