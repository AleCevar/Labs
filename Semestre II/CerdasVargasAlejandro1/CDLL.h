/*
Clase de circular doubly link list
*/

class nodo_cdll{
    public:
        int dato;
        nodo_cdll * sig;
        nodo_cdll * ant;
        nodo_cdll(int x){
            dato = x;
            sig = nullptr;
            ant = nullptr;
        }
        ~nodo_cdll() = default;
};
class CDLL{
    public:
        nodo_cdll * head;
        CDLL(){head = nullptr;}
        int longitud();
        void insertarPosicion(int pos, int val);
        void push(int val);
        void append(int val);
        int remove(int pos);
        void mostrar();
        CDLL * permutar();
        int factorial(int val);
        void solucion(CDLL * pun, int size, int count, nodo_cdll * punteros[]);
        void colocar(CDLL * pun,int count);
        ~CDLL(){
            if(head == nullptr){return;}
            nodo_cdll * actual = head;
            do{ nodo_cdll * borrar = actual;
                actual = actual -> sig;
                delete(borrar);
            }while(actual != head);
        }
};
