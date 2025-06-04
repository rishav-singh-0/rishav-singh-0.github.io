#include <stdio.h>
#include <pthread.h>

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
    pthread_join(thread[0], (void*)&ret_value);
    pthread_join(thread[1], (void*)&ret_value);

    printf("Return value: %d\n", *ret_value);
    
    return 0;
}