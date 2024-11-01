#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_TERMS 100000000 // Total number of terms in the series
#define NUM_THREADS 4       // Number of threads

//Estimating π using pthreads, sommation
void *Thread_sum(void *rank) {
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = NUM_TERMS / NUM_THREADS;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0) {
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    double my_sum = 0.0;
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        my_sum += factor / (2 * i + 1);
    }

    return NULL;
}



