/*
    Write a Pthreads program that implements the trapezoidal rule. Use a shared variable
for the sum of all the threads’ computations. Use busy-waiting and mutexes to enforce
mutual exclusion in the critical section. What advantages and disadvantages do you see
with each approach?
*/
//Busy-waiting approach: while loop ...
//? we identify 2 main things to do:
    //* 1- Computation of the areas of individual trapezoids.
    //* 2- Adding the areas of trapezoids.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define num_threads 4
#define a 0.0
#define  b 10.0
#define n 40.0

double total_sum = 0.0;

pthread_mutex_t mutex;

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
    pthread_mutex_lock(&mutex);
        total_sum += my_sum;
    pthread_mutex_unlock(&mutex);
   //printf("thread %d , sum : %f\n",t_ID, my_sum);

    return NULL;
}

int main(){
    pthread_t threads[num_threads];
    int threadsIDs[num_threads];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < num_threads; i++){
        threadsIDs[i] = i;
        pthread_create(&threads[i], NULL, Thread_sum, &threadsIDs[i]);
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("The estimated integral is %f \n:", total_sum);
    //free(threads);
    return 0;
}
