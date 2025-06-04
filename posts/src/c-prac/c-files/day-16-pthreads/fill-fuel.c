#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define TH_NUM 5

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel = 0;

void* fuel_filling(void* arg){
    for(int i=0; i<5; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel += 55;
        printf("[%lu]: Filled fuel... %d\n", pthread_self(), fuel);        
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
        pthread_cond_broadcast(&condFuel);
    }
}

void* car(void* arg){
    pthread_mutex_lock(&mutexFuel);
    
    while(fuel<40){
        printf("[%lu]: No Fuel. Waiting...\n", pthread_self());
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("[%lu]: Got Fuel. Now left: %d\n", pthread_self(), fuel);        
    sleep(1);
    pthread_mutex_unlock(&mutexFuel);
}

int main() {

    pthread_t thread[TH_NUM];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    
    for(int i=0; i<TH_NUM; i++){
        if(i==2){
            pthread_create(&thread[i], NULL, fuel_filling, NULL);
        }
        else{
            pthread_create(&thread[i], NULL, car, NULL);
        }
    }
    for(int i=0; i<TH_NUM; i++){
        pthread_join(thread[i], NULL);
    }
    
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}