#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

int bridgeSize;
int izqOE;
int derOE;
int izqEO;
int derEO;
int ambulanceProbOE;
int ambulanceProbEO;
int mediaEO;
int mediaOE;
int timeSleepSemaphoreOE;
int timeSleepSemaphoreEO;
int kOE;
int kEO;

int * bridgeState;
pthread_mutex_t * bridge;
int timeSleepGeneratorsOE;
int timeSleepGeneratorsEO;
unsigned short ids[10000];
int inBridge = 0;
int carrosOE = 0;
int carrosEO = 0;
pthread_cond_t condSemaphore = PTHREAD_COND_INITIALIZER;
pthread_mutex_t entryDirectionController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semaphoreOfficerController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t entradaEOController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t entradaOEController = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condEsperaOE = PTHREAD_COND_INITIALIZER;
pthread_cond_t condEsperaEO = PTHREAD_COND_INITIALIZER;
int ambulanceOE = 0;
int ambulanceEO = 0;
int entryDirection = 2;
int officerFlag;
pthread_cond_t condOfficerEO = PTHREAD_COND_INITIALIZER;
pthread_cond_t condOfficerOE = PTHREAD_COND_INITIALIZER;
int nEO;
int nOE;
int modo;
pthread_mutex_t esperaEOController = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t esperaOEController = PTHREAD_MUTEX_INITIALIZER;

// ----------------------------------- variables

int rando(int min, int max){return (int) (min + rand() % (max-min+1));}

double exponencialDistribution(double media){
    double r = (double) drand48();
    return -1 * media * log(1.0 - r);
}

void cambiarDireccion(int n){
    pthread_mutex_lock(&entryDirectionController);
    if(entryDirection == 2) entryDirection = n;
    pthread_mutex_unlock(&entryDirectionController);
}

void driveToOE(unsigned short id, int a){
    int vel = rando(izqOE, derOE);
    pthread_mutex_lock(&bridge[0]);
    printf("El carro %hu entra a la casilla %d hacia el Este \n", id, 0);
    pthread_mutex_unlock(&entradaOEController);
    bridgeState[0] = a;
    usleep(vel);
    int pos = 1;
    for(; pos < bridgeSize;  pos++){
        pthread_mutex_lock(&bridge[pos]);
        bridgeState[pos] = a;
        printf("El carro %hu entra a la casilla %d hacia el Este \n", id, pos);
        pthread_mutex_unlock(&bridge[pos - 1]);
        bridgeState[pos - 1] = 0;
        usleep(vel);
    }
    pthread_mutex_unlock(&bridge[pos - 1]);
    bridgeState[pos - 1] = 0;
}

void driveToEO(unsigned short id, int a){
    int vel = rando(izqEO, derEO);
    pthread_mutex_lock(&bridge[bridgeSize-1]);
    printf("El carro %hu entra a la casilla %d hacia el Oeste\n", id, bridgeSize-1);
    pthread_mutex_unlock(&entradaEOController);
    bridgeState[bridgeSize-1] = a;
    usleep(vel);
    int pos = bridgeSize-2;
    for(; pos >= 0;  pos--){
        pthread_mutex_lock(&bridge[pos]);
        bridgeState[pos] = a; 
        printf("El carro %hu entra a la casilla %d hacia el Oeste\n", id, pos);
        pthread_mutex_unlock(&bridge[pos + 1]);
        bridgeState[pos + 1] = 0;
        usleep(vel);
    }
    pthread_mutex_unlock(&bridge[pos + 1]);
    bridgeState[pos + 1] = 0;        
}

int parsear(char * a){
    if(a[0] == '\n')return 0;
    int i, res = 0;
    for(i = 0; a[i] != ':'; i++);
    i++;
    for(;a[i] != '\n';i++){
        res = res * 10 + (a[i] - '0');
    }  
    return res;
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

void leaveBridgeTraffic(int n){
    inBridge--;
    (!n)? carrosOE-- : carrosEO--;
    if(!inBridge) {
        if(!n && (ambulanceEO || entryDirection)) {pthread_cond_signal(&condEsperaEO);return;}
        if(n && (ambulanceOE || !entryDirection)) {pthread_cond_signal(&condEsperaOE);return;}
        if(!n && !entryDirection) {pthread_cond_signal(&condOfficerOE);}
        if(n && entryDirection) {pthread_cond_signal(&condOfficerEO);}
    }
}

// ----------------------------------- funciones especiales

void * passOECarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(0);
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 0;
    printf("Soy un carro %hu chu chu hacia el ESTE\n",id);
    while(entryDirection == 1 || carrosEO || ambulanceEO) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,1);
    leaveBridgeCarnage(0); 
    printf("El carro %hu salio del puente hacia el Este\n", id);
}

void * passAmbulanceOECarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(0);
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 1;
    printf("Soy una ambulancia %hu chu chu hacia el ESTE\n",id);
    while((entryDirection == 1 && ambulanceEO) || carrosEO) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,2);
    leaveBridgeCarnage(0);
    printf("La ambulancia %hu salio del puente hacia el Este\n", id);
}

void * passEOCarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(1);
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 0;
    printf("Soy un carro %hu chu chu hacia el OESTE\n",id);
    while(entryDirection == 0 || carrosOE || ambulanceOE) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-1);
    leaveBridgeCarnage(1);
    printf("El carro %hu salio del puente hacia el Oeste\n", id);
}

void * passAmbulanceEOCarnage(void * arg){
    unsigned short id = *(unsigned short*) arg;
    if(entryDirection == 2) cambiarDireccion(1);
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 1;
    printf("Soy una ambulancia %d chu chu hacia el OESTE\n",id);
    while((entryDirection == 0 && ambulanceOE) || carrosOE) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-2);
    leaveBridgeCarnage(1);
    printf("La ambulancia %hu salio del puente hacia el Oeste\n", id);
}

void * passOESemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 0;
    printf("Soy un carro %hu chu chu hacia el ESTE\n",id);
    while(ambulanceEO || carrosEO || entryDirection != 0) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,1);
    leaveBridgeSemaphore(0); 
    printf("El carro %hu salio del puente hacia el Este\n", id);
}

void * passEOSemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 0;
    printf("Soy un carro %hu chu chu hacia el OESTE\n",id);
    while(ambulanceOE || entryDirection != 1 || carrosOE) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-1);
    leaveBridgeSemaphore(1);
    printf("El carro %hu salio del puente hacia el Oeste\n", id);
}

void * passAmbulanceOESemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 1;
    printf("Soy una ambulancia %hu chu chu hacia el ESTE\n",id);
    while((entryDirection == 1 && ambulanceEO) || carrosEO) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,2);
    leaveBridgeSemaphore(0);
    printf("La ambulancia %hu salio del puente hacia el Este\n", id);
}

void * passAmbulanceEOSemaphore(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 1;
    printf("Soy una ambulancia %d chu chu hacia el OESTE\n",id);
    while((entryDirection == 0 && ambulanceOE) || carrosOE) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-2);
    leaveBridgeSemaphore(1);
    printf("La ambulancia %hu salio del puente hacia el Oeste\n", id);
}

void * semaphoreOE(){
    while(1){
        pthread_mutex_lock(&semaphoreOfficerController);
        while(entryDirection) pthread_cond_wait(&condSemaphore,&semaphoreOfficerController);
        printf("Turno hacia el ESTE\n");
        pthread_mutex_unlock(&semaphoreOfficerController);
        pthread_cond_signal(&condEsperaOE);
        usleep(timeSleepSemaphoreOE);
        entryDirection = 1;
        printf("AQUI NO PASA NADIE\n");
        pthread_cond_signal(&condSemaphore);
    }
}

void * semaphoreEO(){
    while(1){
        pthread_mutex_lock(&semaphoreOfficerController);
        while(!entryDirection) pthread_cond_wait(&condSemaphore,&semaphoreOfficerController);
        printf("Turno hacia el OESTE\n");
        pthread_mutex_unlock(&semaphoreOfficerController);
        pthread_cond_signal(&condEsperaEO);
        usleep(timeSleepSemaphoreEO);
        entryDirection = 0;
        printf("AQUI NO PASA NADIE\n");
        pthread_cond_signal(&condSemaphore);
    }
}

void * passOETraffic(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 0;
    printf("Soy un carro %hu chu chu hacia el ESTE\n",id);
    while(entryDirection == 1 || carrosEO || ambulanceEO || nOE < 1) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    nOE--;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,1);
    leaveBridgeTraffic(0); 
    printf("El carro %hu salio del puente hacia el Este\n", id);
}

void * passEOTraffic(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 0;
    printf("Soy un carro %hu chu chu hacia el OESTE\n",id);
    while(entryDirection == 0 || carrosOE || ambulanceOE || nEO < 1) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    nEO--;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-1);
    leaveBridgeTraffic(1);
    printf("El carro %hu salio del puente hacia el Oeste\n", id);
}

void * passAmbulanceOETraffic(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaOEController);
    pthread_mutex_lock(&esperaOEController);
    ambulanceOE = 1;
    printf("Soy una ambulancia %hu chu chu hacia el ESTE\n",id);
    while((entryDirection == 1 && ambulanceEO) || carrosEO) pthread_cond_wait(&condEsperaOE,&esperaOEController);
    inBridge++;
    carrosOE++;
    nOE--;
    pthread_mutex_unlock(&esperaOEController);
    driveToOE(id,2);
    leaveBridgeTraffic(0);
    printf("La ambulancia %hu salio del puente hacia el Este\n", id);
}

void * passAmbulanceEOTraffic(void * arg){
    unsigned short id = *(unsigned short*) arg;
    pthread_mutex_lock(&entradaEOController);
    pthread_mutex_lock(&esperaEOController);
    ambulanceEO = 1;
    printf("Soy una ambulancia %d chu chu hacia el OESTE\n",id);
    while((entryDirection == 0 && ambulanceOE) || carrosOE) pthread_cond_wait(&condEsperaEO,&esperaEOController);
    inBridge++;
    carrosEO++;
    nEO--;
    pthread_mutex_unlock(&esperaEOController);
    driveToEO(id,-2);
    leaveBridgeTraffic(1);
    printf("La ambulancia %hu salio del puente hacia el Oeste\n", id);
}

void * trafficOfficerOE(){
    while(1){
        pthread_mutex_lock(&semaphoreOfficerController);
        while(officerFlag) pthread_cond_wait(&condOfficerOE,&semaphoreOfficerController);
        nOE = kOE;
        entryDirection = 0;
        printf("Van %d a al ESTE\n", kOE);
        pthread_cond_signal(&condEsperaOE);
        pthread_cond_wait(&condOfficerOE,&semaphoreOfficerController);
        officerFlag++;
        pthread_mutex_unlock(&semaphoreOfficerController);
        pthread_cond_signal(&condOfficerEO);
    }
}

void * trafficOfficerEO(){
    while(1){
        pthread_mutex_lock(&semaphoreOfficerController);
        while(!officerFlag) pthread_cond_wait(&condOfficerEO,&semaphoreOfficerController);
        entryDirection = 1;
        printf("Van %d a al OESTE\n", kEO);
        nEO = kEO;
        pthread_cond_signal(&condEsperaEO);
        pthread_cond_wait(&condOfficerEO,&semaphoreOfficerController);
        officerFlag--;
        pthread_mutex_unlock(&semaphoreOfficerController);
        pthread_cond_signal(&condOfficerOE);
    }
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

void initializeTraffic(){
    officerFlag = rando(0,1);
    pthread_t threadTrafficOfficerOE;
    pthread_t threadTrafficOfficerEO;
    pthread_create(&threadTrafficOfficerOE, NULL, &trafficOfficerOE, NULL);
    pthread_detach(threadTrafficOfficerOE);
    pthread_create(&threadTrafficOfficerEO, NULL, &trafficOfficerEO, NULL);
    pthread_detach(threadTrafficOfficerEO);
}

int initializeVariables(){
    FILE * file;
    char buffer[100];
    int numeros[14];
    int i = 0;
    file = fopen("Entrada.txt","r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        numeros[i] = parsear(buffer);
        i++;
    }
    int bridgeSize = numeros[0];
    int izqOE = numeros[1];
    int derOE = numeros[2];
    int izqEO = numeros[3];
    int derEO = numeros[4];
    int ambulanceProbOE = numeros[5];
    int ambulanceProbEO = numeros[6];
    int mediaEO = numeros[7];
    int mediaOE = numeros[8];
    int timeSleepSemaphoreOE = numeros[9];
    int timeSleepSemaphoreEO = numeros[10];
    int kOE = numeros[11];
    int kEO = numeros[12];
    fclose(file);

}

// ------------------------------------inicializadores
int main(){
    srand(time(NULL));
    srand48(time(NULL));
    initializeVariables();
    bridge = (pthread_mutex_t*) malloc (bridgeSize * sizeof(pthread_mutex_t));
    bridgeState = (int*) malloc (bridgeSize * sizeof(int));
    for(int i = 0; i < bridgeSize; i++) pthread_mutex_init(&bridge[i],NULL);
    timeSleepGeneratorsOE = (int) exponencialDistribution(mediaOE);
    timeSleepGeneratorsEO = (int) exponencialDistribution(mediaEO);
    for(short i = 0; i < 10000; i++) ids[i] = i+1;

    printf("Favor seleccione un modo:\n 1.Carnage\n 2.Semáforos\n 3.Oficial de transito\n> ");
    scanf("%d",&modo);
    
    // if(modo == 2) initializeSemaphore();
    // if(modo == 3) initializeTraffic();
    // pthread_t threadGeneratorOE;
    // pthread_t threadGeneratorEO;
    // pthread_create(&threadGeneratorOE, NULL, &generadorOE, &modo);
    // pthread_detach(threadGeneratorOE);
    // pthread_create(&threadGeneratorEO, NULL, &generadorEO, &modo);
    // pthread_detach(threadGeneratorEO);
    // while(1){
    //     usleep(150000);
    //     system("clear");
    //     if(!entryDirection) printf("🟢                                        🔴\n");
    //     else printf("🔴                                        🟢\n");
    //     if(ambulanceOE) printf("🚑 ➡️ ||");
    //     else printf("🚘 ➡️ ||");
    //     for(int i = 0; i < bridgeSize; i++)
    // }
    return 0;
}
