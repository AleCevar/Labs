//Alejandro Cerdas y Kener Castillo
//Algoritmo Genetico
#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

extern mutex terminal;

class Individuo{
public:
    vi camino;
    int fit;
    
};

class TSP{
public:
    vector<vi> matGN;
    int cantGen;
    int probMut;
    int cantPob;
    int VGN;
    int EGN;
    Individuo * poblacion;
    Individuo * nextG;
    int elite;
    int mantener;

    TSP(int v, int e, vector<vi> &m){
        VGN = v;
        EGN = e;
        matGN = m;
        cantGen=VGN*VGN;
        probMut=15;
        cantPob=VGN*VGN;
        (cantPob&1)? cantPob: cantPob--;
        poblacion = new Individuo[cantPob];
        nextG = new Individuo[cantPob];
        mantener = VGN/2;    
    }   
    
    int accederGN(int a, int b){return matGN[max(a,b)][min(a,b)];}

    int randon(int sta, int end){
        return rand()%end + sta;     
    }    
    
    void generarPobla(){
        elite = 0;
        int perm[VGN];
        for(int i=0; i<VGN; i++) perm[i]=i;
        for(int i = 0; i < cantPob; i++){
            poblacion[i].camino.reserve(VGN+1);
            nextG[i].camino.reserve(VGN+1);
            poblacion[i].camino[0]=poblacion[i].camino[VGN]=0;
            for(int j = 1; j < VGN; j++){
                swap(perm[j], perm[randon(j, VGN-j)]);
                poblacion[i].camino[j]=perm[j];
            }
            fitness(poblacion[i]);
            if(poblacion[elite].fit > poblacion[i].fit) elite = i;
        }
            
    }
    
    void fitness(Individuo &ind){
        int res=0;    
        int error = 0;
        for(int i = 1; i <= VGN; i++){
            if(accederGN(ind.camino[i],ind.camino[i-1]) == -1) error++;
            else res += accederGN(ind.camino[i],ind.camino[i-1]);
        }
        ind.fit = res + (10000*error);
    }

    void cruce(int i){
        int padre1=elegir(randon(0, cantPob),randon(0, cantPob)), 
            padre2 = elegir(randon(0,cantPob),randon(0,cantPob));
        int mant = randon(1,VGN-1);
        int ar[VGN]={};
        for(int p=0; p<mant; p++){
            nextG[i].camino[p]=poblacion[padre1].camino[p];
            ar[nextG[i].camino[p]] = 1;
        }
        ar[0]=0;
        int p = 1;
        for(int j = mant; j <= VGN; j++){
            for(; p <=VGN; p++){
                if(ar[poblacion[padre2].camino[p]] != 1){
                    nextG[i].camino[j]=poblacion[padre2].camino[p];
                    p++;
                    break;
                }
            }
        }
        if(randon(0,100) < probMut){
            int pos1 = randon(1,VGN-1), pos2 = randon(1,VGN-1);
            swap(nextG[i].camino[pos1],nextG[i].camino[pos2]);
        }
    }


    int elegir(int a, int b){
        return (poblacion[a].fit > poblacion[b].fit) ? b : a;
    }

    void siguienteGen(){
        nextG[0].fit=poblacion[elite].fit;
        for(int i=0; i<=VGN; i++) nextG[0].camino[i]=poblacion[elite].camino[i];
        elite=0;
        for(int i = 1; i < cantPob; i++){
            cruce(i);
            fitness(nextG[i]);
            if(nextG[elite].fit > nextG[i].fit) elite = i;
        }
    }

    void start(){
        generarPobla();
        int cont=0;
        while(cont<cantGen){
            siguienteGen();
            swap(poblacion, nextG);
            cont++;
        }
        imprimir();
    }

    void imprimir(){
        lock_guard<mutex> lock(terminal);
        cout<<"Genetico: 0";
        for(int i = 1 ; i <= VGN; i++){
            cout << ',' << poblacion[elite].camino[i];    
        }
        cout<<" Costo " << poblacion[elite].fit << '\n';
    }
};

void crear(int v, int e, vector<vi> &m){
    TSP solve(v,e,m);
    solve.start();
}