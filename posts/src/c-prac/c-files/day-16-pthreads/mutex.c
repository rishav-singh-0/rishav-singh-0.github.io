#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define NUM 5

pthread_mutex_t mutex;

void * fun(void *num){
    int var = 100;
    pthread_mutex_lock(&mutex);
    for(int i=0; i<3; i++){
        printf("Number is: %d, thread_id: %lu\n", *(int *)num, pthread_self());
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
    return num;
}

int main() {

    pthread_t thread[NUM];
    
    int num = 10;
    int *ret_value;
    int index;
    
    pthread_mutex_init(&mutex, NULL);

    for(index=0; index< NUM; index++){
        if(pthread_create(&thread[index], NULL, &fun, &num) != 0){
            perror("Error at creating thread");
        }
    }
    for(index=0; index< NUM; index++){
        if(pthread_join(thread[index], (void*)&ret_value) != 0){
            perror("Error at joining thread");
        }
    }

    printf("Return value: %d\n", *ret_value);
    
    return 0;
}