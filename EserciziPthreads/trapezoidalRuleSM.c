//? Modify the mutex version of the trapezoidal program so that it uses a semaphore instead of a mutex.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define num_threads 4
#define a 0.0
#define  b 10.0
#define n 40.0

double total_sum = 0.0;
sem_t semaphores[num_threads];


float my_func(double x) {
    return (-x * (x - b)) / n;
}
void* Thread_sum(void* arg){
    int t_ID = * (int *) arg;
    double my_sum = 0.0;
    double my_width = (b - a) / n;
    int local_traps = n / num_threads;
    double start = a + t_ID * local_traps * my_width;
    //printf("intervals : %f \n", my_width);
    int i;
    for( i = 0; i < local_traps; i++){
        double x = start + i * my_width;
        my_sum += (my_func(x) + my_func(x + my_width)) * my_width / 2.0;
    }

    sem_wait(&semaphores[t_ID]);
        total_sum += my_sum;
    sem_post(&semaphores[(t_ID + 1) % num_threads]);
   //printf("thread %d , sum : %f\n",t_ID, my_sum);

    return NULL;
}

int main(){
    pthread_t threads[num_threads];
    int threadsIDs[num_threads];

    for(int i = 0; i < num_threads; i++){
        sem_init(&semaphores[i], 0, 1 );
    }
    for(int i = 0; i < num_threads; i++){
        threadsIDs[i] = i;
        pthread_create(&threads[i], NULL, Thread_sum, &threadsIDs[i]);
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        sem_destroy(&semaphores[i]);
    }

    printf("The estimated integral is %f \n:", total_sum);
    //free(threads);
    return 0;
}
