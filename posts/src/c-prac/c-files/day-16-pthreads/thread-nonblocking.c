#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

# define NUM 5

pthread_t thread[NUM];
// pthread_mutex_t

void * fun(void *num){
    int var = 100;
    printf("Address of var: %p\n", &var);
    for(int i=0; i<3; i++){
        printf("Number is: %d, thread_id: %lu\n", *(int *)num, pthread_self());
        sleep(1);
    }
    return num;
}

int main() {
    
    int num = 10;
    int *ret_value;
    pthread_create(&thread[0], NULL, &fun, &num);
    pthread_create(&thread[1], NULL, &fun, &num);
    // pthread_detach(thread[1]);
    printf("thread_id: %lu\n", pthread_self());
    printf("Return value: %d\n", pthread_tryjoin_np(thread[0], (void*)&ret_value));
    printf("Errno: %d\n", errno);
    pthread_tryjoin_np(thread[1], (void*)&ret_value);
    printf("Errno: %d\n", errno);

    // printf("Return value of thread: %d\n", *ret_value);
    
    return 0;
}