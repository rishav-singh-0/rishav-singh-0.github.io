#include <stdio.h>
#include <pthread.h>

#define NUM_TH 50

int mail = 0;

void *routine(){
    for (int i=0; i<100000; i++){
        mail++;
    }
}

int main() {
    pthread_t th[NUM_TH];
    
    int i = 0;
    for(i=0; i<NUM_TH; i++){
        if(pthread_create(th + i, NULL, routine, NULL)){
            return 1;
        };
    }
    for(i=0; i<NUM_TH; i++){
        if(pthread_join(th[i], NULL)){
            return 2;
        };
    }
    
    printf("Mails: %d\n", mail);

    return 0;
}