#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

pthread_mutex_t * bridge;
int bridgeSize = 5;
int izqOE = 1e5;
int derOE = 6e5;
int izqEO = 1e5;
int derEO = 6e5;
int ambulanceProbOE = 20;
int ambulanceProbEO = 20;
int mediaEO = 0;
int mediaOE = 0;
int timeSleepSemaphoreOE = 5e6;
int timeSleepSemaphoreEO = 5e6;
int kOE = 10;
int kEO = 10;

double timeSleepGeneratorsOE;
double timeSleepGeneratorsEO;
unsigned short ids[10000];
int inBridge = 0;
int carrosOE = 0;
int carrosEO = 0;
pthread_cond_t condSemaphore = PTHREAD_COND_INITIALIZER;
pthread_mutex_t entryDirectionController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semaphoreController = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condEntradaOE = PTHREAD_COND_INITIALIZER;
pthread_cond_t condEntradaEO = PTHREAD_COND_INITIALIZER;
pthread_mutex_t entradaEOController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t entradaOEController = PTHREAD_MUTEX_INITIALIZER;
int entradaEO = 0;
int entradaOE = 0;
pthread_cond_t condEsperaOE = PTHREAD_COND_INITIALIZER;
pthread_cond_t condEsperaEO = PTHREAD_COND_INITIALIZER;
int ambulanceOE = 0;
int ambulanceEO = 0;
int entryDirection = 2;

// ----------------------------------- variables

int rando(int min, int max){return (int) (min + rand() % (max-min+1));}

double exponencialDistribution(double media){
    double r = (double) drand48();
    return -1 * media * log(1.0 - 0.99);
}

void cambiarDireccion(int n){
    pthread_mutex_lock(&entryDirectionController);
    if(entryDirection == 2) entryDirection = n;
    pthread_mutex_unlock(&entryDirectionController);
}

void driveToOE(unsigned short id){
    int vel = rando(izqOE, derOE);
    pthread_mutex_lock(&bridge[0]);
    printf("El carro %hu entra a la casilla %d hacia el Este \n", id, 0);
    inBridge++;
    carrosOE++;
    entradaOE--;
    usleep(vel);
    pthread_cond_signal(&condEntradaOE);
    int pos = 1;
    for(; pos < bridgeSize;  pos++){
        pthread_mutex_lock(&bridge[pos]);
        printf("El carro %hu entra a la casilla %d hacia el Este \n", id, pos);
        pthread_mutex_unlock(&bridge[pos - 1]);
        usleep(vel);
    }
    pthread_mutex_unlock(&bridge[pos - 1]);
}

void driveToEO(unsigned short id){
    int vel = rando(izqEO, derEO);
    pthread_mutex_lock(&bridge[bridgeSize-1]);
    printf("El carro %hu entra a la casilla %d hacia el Oeste\n", id, bridgeSize-1);
    inBridge++;
    carrosEO++;
    entradaEO--;
    usleep(vel);
    pthread_cond_signal(&condEntradaEO);
    int pos = bridgeSize-2;
    for(; pos >= 0;  pos--){
        pthread_mutex_lock(&bridge[pos]);
        printf("El carro %hu entra a la casilla %d hacia el Oeste\n", id, pos);
        pthread_mutex_unlock(&bridge[pos + 1]);
        usleep(vel);
    }
    pthread_mutex_unlock(&bridge[pos + 1]);
}

// ---------------------------------- funciones

void leaveBridgeCarnage(int n){
    inBridge--;
    (!n)? carrosOE-- : carrosEO--;
    if(!inBridge){
        pthread_mutex_lock(&entryDirectionController);
        if(n){
            entryDirection = 0;
            pthread_cond_signal(&condEsperaOE);
        }
        else {
            entryDirection = 1;    
            pthread_cond_signal(&condEsperaEO);
        }
        pthread_mutex_unlock(&entryDirectionController);
    }
}

void leaveBridgeSemaphore(int n){
    inBridge--;
    (!n)? carrosOE-- : carrosEO--;
    if(!inBridge) {
        if(!n && (ambulanceEO || entryDirection)) pthread_cond_signal(&condEsperaEO);
        if(n && (ambulanceOE || !entryDirection)) pthread_cond_signal(&condEsperaOE);
    }
}

// ----------------------------------- funciones especiales

void * passOECarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(0);

    pthread_mutex_lock(&entradaOEController);
    while(entradaOE) pthread_cond_wait(&condEntradaOE,&entradaOEController);
    entradaOE++;
    ambulanceOE = 0;
    printf("Soy un carro %hu chu chu hacia el ESTE\n",id);
    while(entryDirection == 1 || carrosEO || ambulanceEO) pthread_cond_wait(&condEsperaOE,&entradaOEController);
    pthread_mutex_unlock(&entradaOEController);

    driveToOE(id);
    leaveBridgeCarnage(0); 
    printf("El carro %hu salio del puente hacia el Este\n", id);
}

void * passAmbulanceOECarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(0);

    pthread_mutex_lock(&entradaOEController);
    while(entradaOE) pthread_cond_wait(&condEntradaOE,&entradaOEController);
    entradaOE++;
    ambulanceOE = 1;
    printf("Soy una ambulancia %hu chu chu hacia el ESTE\n",id);
    while((entryDirection == 1 && ambulanceEO) || carrosEO) pthread_cond_wait(&condEsperaOE,&entradaOEController);
    pthread_mutex_unlock(&entradaOEController);

    driveToOE(id);
    leaveBridgeCarnage(0);
    printf("La ambulancia %hu salio del puente hacia el Este\n", id);
}

void * passEOCarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(1);

    pthread_mutex_lock(&entradaEOController);
    while(entradaEO) pthread_cond_wait(&condEntradaEO,&entradaEOController);
    entradaEO++;
    ambulanceEO = 0;
    printf("Soy un carro %hu chu chu hacia el OESTE\n",id);
    while(entryDirection == 0 || carrosOE || ambulanceOE) pthread_cond_wait(&condEsperaEO,&entradaEOController);
    pthread_mutex_unlock(&entradaEOController);

    driveToEO(id);
    leaveBridgeCarnage(1);
    printf("El carro %hu salio del puente hacia el Oeste\n", id);
}

void * passAmbulanceEOCarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(1);

    pthread_mutex_lock(&entradaEOController);
    while(entradaEO) pthread_cond_wait(&condEntradaEO,&entradaEOController);
    entradaEO++;
    ambulanceEO = 1;
    printf("Soy una ambulancia %d chu chu hacia el OESTE\n",id);
    while((entryDirection == 0 && ambulanceOE) || carrosOE) pthread_cond_wait(&condEsperaEO,&entradaEOController);
    pthread_mutex_unlock(&entradaEOController);

    driveToEO(id);
    leaveBridgeCarnage(1);
    printf("La ambulancia %hu salio del puente hacia el Oeste\n", id);
}

void * passOESemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaOEController);
    while(entradaOE) pthread_cond_wait(&condEntradaOE,&entradaOEController);
    entradaOE++;
    ambulanceOE = 0;
    printf("Soy un carro %hu chu chu hacia el ESTE\n",id);
    while(ambulanceEO || carrosEO || entryDirection != 0) pthread_cond_wait(&condEsperaOE,&entradaOEController);
    pthread_mutex_unlock(&entradaOEController);

    driveToOE(id);
    leaveBridgeSemaphore(0); 
    printf("El carro %hu salio del puente hacia el Este\n", id);
}

void * passEOSemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    
    pthread_mutex_lock(&entradaEOController);
    while(entradaEO) pthread_cond_wait(&condEntradaEO,&entradaEOController);
    entradaEO++;
    ambulanceEO = 0;
    printf("Soy un carro %hu chu chu hacia el OESTE\n",id);
    while(ambulanceOE || entryDirection != 1 || carrosOE) pthread_cond_wait(&condEsperaEO,&entradaEOController);
    pthread_mutex_unlock(&entradaEOController);

    driveToEO(id);
    leaveBridgeSemaphore(1);
    printf("El carro %hu salio del puente hacia el Oeste\n", id);
}

void * passAmbulanceOESemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    
    pthread_mutex_lock(&entradaOEController);
    while(entradaOE) pthread_cond_wait(&condEntradaOE,&entradaOEController);
    entradaOE++;
    ambulanceOE = 1;
    printf("Soy una ambulancia %hu chu chu hacia el ESTE\n",id);
    while(carrosEO) pthread_cond_wait(&condEsperaOE,&entradaOEController);
    pthread_mutex_unlock(&entradaOEController);

    driveToOE(id);
    leaveBridgeSemaphore(0);
    printf("La ambulancia %hu salio del puente hacia el Este\n", id);
}

void * passAmbulanceEOSemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;

    pthread_mutex_lock(&entradaEOController);
    while(entradaEO) pthread_cond_wait(&condEntradaEO,&entradaEOController);
    entradaEO++;
    ambulanceEO = 1;
    printf("Soy una ambulancia %d chu chu hacia el OESTE\n",id);
    while(carrosOE) pthread_cond_wait(&condEsperaEO,&entradaEOController);
    pthread_mutex_unlock(&entradaEOController);

    driveToEO(id);
    leaveBridgeSemaphore(1);
    printf("La ambulancia %hu salio del puente hacia el Oeste\n", id);
}

void * semaphoreOE(){
    while(1){
        pthread_mutex_lock(&semaphoreController);
        while(entryDirection) pthread_cond_wait(&condSemaphore,&semaphoreController);
        printf("Turno hacia el ESTE\n");
        pthread_mutex_unlock(&semaphoreController);
        pthread_cond_signal(&condEsperaOE);
        usleep(timeSleepSemaphoreOE);
        entryDirection = 1;
        printf("AQUI NO PASA NADIE\n");
        pthread_cond_signal(&condSemaphore);
    }
}

void * semaphoreEO(){
    while(1){
        pthread_mutex_lock(&semaphoreController);
        while(!entryDirection) pthread_cond_wait(&condSemaphore,&semaphoreController);
        printf("Turno hacia el OESTE\n");
        pthread_mutex_unlock(&semaphoreController);
        pthread_cond_signal(&condEsperaEO);
        usleep(timeSleepSemaphoreEO);
        entryDirection = 0;
        printf("AQUI NO PASA NADIE\n");
        pthread_cond_signal(&condSemaphore);
    }
}

void * passOETraffic(){

}

void * passEOTraffic(){

}

void * passAmbulanceOETraffic(){

}

void * passAmbulanceEOTraffic(){

}

void * generadorOE(void * arg){
    int m = * (int *) arg;
    int seq = 0;
    void * carro = (m == 1)? &passOECarnage : (m == 2)? &passOESemaphore : &passOETraffic;
    void * ambulancia = (m == 1)? &passAmbulanceOECarnage : (m == 2)? &passAmbulanceOESemaphore : &passAmbulanceOETraffic;
    while(1){
        usleep(timeSleepGeneratorsOE);        
        pthread_t h;
        int r = rando(0,99);
        if(r < ambulanceProbOE) pthread_create(&h, NULL, ambulancia, &ids[seq]);
        else pthread_create(&h, NULL, carro, &ids[seq]);
        pthread_detach(h);
        seq++;
    }
}

void * generadorEO(void * arg){
    int m = *(int*) arg;
    int seq = 0;
    void * carro = (m == 1)? &passEOCarnage : (m == 2)? &passEOSemaphore : &passEOTraffic;
    void * ambulancia = (m == 1)? &passAmbulanceEOCarnage : (m == 2)? &passAmbulanceEOSemaphore : &passAmbulanceEOTraffic;
    while(1){
        usleep(timeSleepGeneratorsEO);
        pthread_t h;
        int r = rando(0,99);
        if(r < ambulanceProbEO) pthread_create(&h,NULL,ambulancia,&ids[seq]);
        else pthread_create(&h,NULL,carro,&ids[seq]);
        pthread_detach(h);
        seq++;
    }
}

// ------------------------------------metodos hilos

void initializeSemaphore(){
    entryDirection = rando(0,1);
    pthread_t threadSemaphoreOE;
    pthread_t threadSemaphoreEO;
    pthread_create(&threadSemaphoreOE,NULL,&semaphoreOE,NULL);
    pthread_detach(threadSemaphoreOE);
    pthread_create(&threadSemaphoreEO,NULL,&semaphoreEO,NULL);
    pthread_detach(threadSemaphoreEO);
}

// ------------------------------------inicializadores
int main(){
    srand(time(NULL));
    srand48(time(NULL));
    bridge = (pthread_mutex_t*) malloc (bridgeSize * sizeof(pthread_mutex_t));
    for(int i = 0; i < bridgeSize; i++) pthread_mutex_init(&bridge[i],NULL);
    timeSleepGeneratorsOE = 1e5 * rando(5,15);  //exponencialDistribution(5.0);
    timeSleepGeneratorsEO = 1e5 * rando(5,15); //exponencialDistribution(3.0);
    for(short i = 0; i < 10000; i++) ids[i] = i+1;
    int m;
    scanf("%d",&m);
    if(m == 2) initializeSemaphore();
    if(m == 3);
    
    pthread_t threadGeneratorOE;
    pthread_t threadGeneratorEO;
    pthread_create(&threadGeneratorOE, NULL, &generadorOE, &m);
    pthread_detach(threadGeneratorOE);
    pthread_create(&threadGeneratorEO, NULL, &generadorEO, &m);
    pthread_detach(threadGeneratorEO);
    
    while(1);
    return 0;
}
