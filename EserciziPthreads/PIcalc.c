//!with mutexes:

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define num_terms 100000
#define num_threads 4

pthread_mutex_t mutex;
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

    pthread_mutex_lock(&mutex);
        sum += my_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(){
    pthread_t thread_handles[num_threads];
    int* ids = (int*) malloc(sizeof(int)*num_threads);
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < num_threads; i++){
        ids[i] = i;
        pthread_create(&thread_handles[i], NULL, calc_partial_sums, &(ids[i]));
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(thread_handles[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Pi calculated is: %f \n", 4.0 * sum);
    free(ids);
    return 0;
}
