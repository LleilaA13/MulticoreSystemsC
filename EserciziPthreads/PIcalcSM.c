//? Modify the mutex version of the pi calculation program so that it uses a semaphore instead of a mutex.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define num_terms 100000
#define num_threads 4

sem_t semaphore;
double sum = 0.0;

void* calc_partial_sums(void* arg){
    int t_ID = * (int*)arg;
    double factor;
    long my_terms = num_terms / num_threads;
    long my_start = my_terms * t_ID;
    long my_end = my_start + my_terms;
    double my_sum = 0.0;

    if (my_start % 2 == 0){
        factor = 1.0;
    }
    else{
        factor = -1.0;
    }

    for(int i = my_start ; i < my_end; i++, factor = - factor){
        my_sum += factor / (double) ( 2 * i + 1);
    }

    sem_wait(&semaphore);
        sum += my_sum;
    sem_post(&semaphore);

    return NULL;
}

int main(){
    pthread_t thread_handles[num_threads];
    int threadIDs[num_threads];
    
    sem_init(&semaphore, 0, 1);

    for(int i = 0; i < num_threads; i++){
        threadIDs[i] = i;
        pthread_create(&thread_handles[i], NULL, calc_partial_sums, &threadIDs[i]);
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(thread_handles[i], NULL);
    }

    sem_destroy(&semaphore);
    printf("Pi calculated is: %f \n", 4.0 * sum);
    //free(thread_handles);
    return 0;
}



